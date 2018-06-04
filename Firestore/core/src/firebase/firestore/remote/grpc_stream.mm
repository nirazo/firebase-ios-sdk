/*
 * Copyright 2018 Google
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "Firestore/core/src/firebase/firestore/remote/grpc_stream.h"

#include <grpcpp/create_channel.h>
#include <utility>

#include "Firestore/core/src/firebase/firestore/util/executor_libdispatch.h"
#include "Firestore/Source/Remote/FSTDatastore.h"
#include "Firestore/Source/Remote/FSTStream.h"
#include "absl/memory/memory.h"

#include <fstream>
#include <sstream>

namespace firebase {
namespace firestore {
namespace remote {

using firebase::firestore::model::SnapshotVersion;

namespace internal {

std::unique_ptr<grpc::ClientContext> ObjcBridge::CreateContext(
    const model::DatabaseId& database_id, const absl::string_view token) const {
  return [FSTDatastore createGrpcClientContextWithDatabaseID:&database_id
                                                       token:token];
}

grpc::ByteBuffer ObjcBridge::ToByteBuffer(FSTQueryData* query) const {
  GCFSListenRequest* request = [GCFSListenRequest message];
  request.database = [serializer_ encodedDatabaseID];
  request.addTarget = [serializer_ encodedTarget:query];
  request.labels = [serializer_ encodedListenRequestLabelsForQueryData:query];

  return ToByteBuffer([request data]);
}

grpc::ByteBuffer ObjcBridge::ToByteBuffer(FSTTargetID target_id) const {
  GCFSListenRequest* request = [GCFSListenRequest message];
  request.database = [serializer_ encodedDatabaseID];
  request.removeTarget = target_id;

  return ToByteBuffer([request data]);
}

grpc::ByteBuffer ObjcBridge::ToByteBuffer(NSData* data) const {
  const grpc::Slice slice{[data bytes], [data length]};
  return grpc::ByteBuffer{&slice, 1};
}

FSTWatchChange* ObjcBridge::GetWatchChange(GCFSListenResponse* proto) {
  return [serializer_ decodedWatchChange:proto];
}

SnapshotVersion ObjcBridge::GetSnapshotVersion(GCFSListenResponse* proto) {
  return [serializer_ versionFromListenResponse:proto];
}

NSData* ObjcBridge::ToNsData(const grpc::ByteBuffer& buffer) const {
  std::vector<grpc::Slice> slices;
  buffer.Dump(&slices);  // TODO: check return value
  if (slices.size() == 1) {
    return [NSData dataWithBytes:slices.front().begin()
                          length:slices.front().size()];
  } else {
    // FIXME
    return [NSData dataWithBytes:slices.front().begin()
                          length:slices.front().size()];
  }
}

void BufferedWriter::Enqueue(grpc::ByteBuffer&& bytes) {
  buffer_.push_back(std::move(bytes));
  TryWrite();
}

void BufferedWriter::TryWrite() {
  if (!is_started_) {
    return;
  }
  if (buffer_.empty()) {
    return;
  }
  // From the docs:
  // Only one write may be outstanding at any given time. This means that
  /// after calling Write, one must wait to receive \a tag from the completion
  /// queue BEFORE calling Write again.
  if (has_pending_write_) {
    return;
  }

  has_pending_write_ = true;
  call_->Write(buffer_.back(), CreateContinuation());
  buffer_.pop_back();
}

BufferedWriter::FuncT* BufferedWriter::CreateContinuation() {
  return new FuncT{[this] (const bool ok) {
    has_pending_write_ = false;
    if (ok) {
      TryWrite();
    }
  }};
}

GrpcQueue::GrpcQueue(grpc::CompletionQueue* grpc_queue,
                     std::unique_ptr<util::internal::Executor> own_executor,
                    // util::AsyncQueue* callback_executor)
                    FSTDispatchQueue* callback_executor)
    : grpc_queue_{grpc_queue},
      own_executor_{std::move(own_executor)},
      callback_executor_{callback_executor} {
  own_executor_->Execute([this] {
    void* tag = nullptr;
    bool ok = false;
    while (grpc_queue_->Next(&tag, &ok)) {
      const auto operation = [tag, ok] {
        auto func = static_cast<std::function<void(bool)>*>(tag);
        (*func)(ok);
        delete func;
      };
      [callback_executor_ dispatchAsync:^() { operation(); }];
    }
  });
}

GrpcQueue::~GrpcQueue() {
  grpc_queue_->Shutdown();
  own_executor_->ExecuteBlocking([]{});
}

}  // namespace internal

using firebase::firestore::auth::CredentialsProvider;
using firebase::firestore::auth::Token;
using firebase::firestore::core::DatabaseInfo;
using firebase::firestore::model::DatabaseId;
// using firebase::firestore::model::SnapshotVersion;

WatchStream::WatchStream(/*util::AsyncQueue* async_queue,*/
    FSTDispatchQueue* async_queue,
                         const DatabaseInfo& database_info,
                         CredentialsProvider* const credentials_provider,
                         FSTSerializerBeta* serializer)
    // : executor_{std::move(executor)},
       :
      database_info_{&database_info},
      credentials_provider_{credentials_provider},
      stub_{CreateStub()},
      objc_bridge_{serializer},
      polling_queue_{&queue_, CreateExecutor(), async_queue} {
}

std::unique_ptr<util::internal::Executor> WatchStream::CreateExecutor() const {
  const auto queue = dispatch_queue_create(
      "com.google.firebase.firestore.watchstream", DISPATCH_QUEUE_SERIAL);
  return absl::make_unique<util::internal::ExecutorLibdispatch>(queue);
}

void WatchStream::Start(id delegate) {
  delegate_ = delegate;
  // TODO: on error state
  // TODO: state transition details

  state_ = State::Auth;
  // TODO: delegate?

  const bool do_force_refresh = false;
  credentials_provider_->GetToken(
      do_force_refresh,
      [this](util::StatusOr<Token> maybe_token) { Authenticate(maybe_token); });
}

// Call may be closed due to:
// - error;
// - idleness;
// - network disable/reenable
void WatchStream::Authenticate(const util::StatusOr<Token>& maybe_token) {
  if (state_ == State::Stopped) {
    // Streams can be stopped while waiting for authorization.
    return;
  }
  // TODO: state transition details
  if (!maybe_token.ok()) {
    // TODO: error handling
    return;
  }

  const absl::string_view token = [&] {
    const auto token = maybe_token.ValueOrDie();
    return token.user().is_authenticated() ? token.token()
                                           : absl::string_view{};
  }();
  context_ = objc_bridge_.CreateContext(database_info_->database_id(), token);
  call_ = stub_.PrepareCall(
      context_.get(), "/google.firestore.v1beta1.Firestore/Listen", &queue_);
  buffered_writer_.SetCall(call_.get());
  call_->StartCall(new std::function<void(bool)>{[this] (const bool ok) {
      if (!ok) {
        state_ = State::Stopped;
        buffered_writer_.Stop();

        call_->Finish(&status_, new std::function<void(bool)>{[this] (const bool ok) {
            const auto status = status_;
            int i = 0;
            ++i;
        }});

//        return;
      }

      state_ = State::Open;
      buffered_writer_.Start();
      call_->Read(&last_read_message_, OnRead()); // ?

      id<FSTWatchStreamDelegate> delegate = delegate_;
      [delegate watchStreamDidOpen];
  }});
  // TODO: if !call_
  // callback filter

  // notifystreamopen
}

std::function<void(bool)>* WatchStream::OnRead() {
  return new std::function<void(bool)>{[this] (const bool ok) {
    if (!ok) {
      Stop();
      return;
    }
    auto* proto = objc_bridge_.ToProto<GCFSListenResponse>(last_read_message_);
    id<FSTWatchStreamDelegate> delegate = delegate_;
    [delegate watchStreamDidChange:objc_bridge_.GetWatchChange(proto) snapshotVersion:objc_bridge_.GetSnapshotVersion(proto)];

    call_->Read(&last_read_message_, OnRead());
  }};
}

void WatchStream::WatchQuery(FSTQueryData* query) {
  // [self cancelIdleCheck];
  buffered_writer_.Enqueue(objc_bridge_.ToByteBuffer(query));
}

void WatchStream::UnwatchTargetId(FSTTargetID target_id) {
  // [self cancelIdleCheck];
  buffered_writer_.Enqueue(objc_bridge_.ToByteBuffer(target_id));
}

void WatchStream::Stop() {
  if (!IsOpen()) {
    return;
  }
  state_ = State::Stopped;
  buffered_writer_.Stop();

  call_->Finish(&status_, new std::function<void(bool)>{[] (const bool ok) {
      int i = 0;
      ++i;
  }});
}

bool WatchStream::IsOpen() const {
  return state_ == State::Open;
}

bool WatchStream::IsStarted() const {
  // return state_ == State::Auth || state_ == State::Open;
  return state_ == State::Initial || state_ == State::Auth || state_ == State::Open;
}

// void WatchStream::Close() {
// }

// Private


const char* WatchStream::pemRootCertsPath = nullptr;

grpc::GenericStub WatchStream::CreateStub() const {
  if (pemRootCertsPath) {
    grpc::SslCredentialsOptions options;
    std::fstream file{pemRootCertsPath};
    std::stringstream buffer;
    buffer << file.rdbuf();
    const std::string cert = buffer.str();
    options.pem_root_certs = cert;

    grpc::ChannelArguments args;
     args.SetSslTargetNameOverride("test_cert_2");
    //args.SetSslTargetNameOverride("test_cert_4");
    return grpc::GenericStub{
        grpc::CreateCustomChannel(database_info_->host(), grpc::SslCredentials(options), args)};
  }
  return grpc::GenericStub{
      grpc::CreateChannel(database_info_->host(),
                          grpc::SslCredentials(grpc::SslCredentialsOptions()))};
}

}  // namespace remote
}  // namespace firestore
}  // namespace firebase