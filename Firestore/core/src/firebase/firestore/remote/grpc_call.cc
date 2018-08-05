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

#include "Firestore/core/src/firebase/firestore/remote/grpc_call.h"

namespace firebase {
namespace firestore {
namespace remote {

void GrpcCall::Start(StreamOperation* const operation) {
  call_->StartCall(operation);
}

void GrpcCall::Read(grpc::ByteBuffer* const buffer,
                    StreamOperation* const operation) {
  call_->Read(buffer, operation);
}

void GrpcCall::Write(const grpc::ByteBuffer& buffer,
                     StreamOperation* const operation) {
  call_->Write(buffer, operation);
}

void GrpcCall::Finish(grpc::Status* const status,
                      StreamOperation* const operation) {
  call_->Finish(status, operation);
}

void GrpcCall::TryCancel() {
  context_->TryCancel();
}

}  // namespace remote
}  // namespace firestore
}  // namespace firebase