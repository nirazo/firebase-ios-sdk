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

// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: firestore/local/mutation.proto

#include "firestore/local/mutation.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

extern PROTOBUF_INTERNAL_EXPORT_google_2ffirestore_2fv1_2fwrite_2eproto ::google::protobuf::internal::SCCInfo<4> scc_info_Write_google_2ffirestore_2fv1_2fwrite_2eproto;
extern PROTOBUF_INTERNAL_EXPORT_google_2fprotobuf_2ftimestamp_2eproto ::google::protobuf::internal::SCCInfo<0> scc_info_Timestamp_google_2fprotobuf_2ftimestamp_2eproto;
namespace firestore {
namespace client {
class MutationQueueDefaultTypeInternal {
 public:
  ::google::protobuf::internal::ExplicitlyConstructed<MutationQueue> _instance;
} _MutationQueue_default_instance_;
class WriteBatchDefaultTypeInternal {
 public:
  ::google::protobuf::internal::ExplicitlyConstructed<WriteBatch> _instance;
} _WriteBatch_default_instance_;
}  // namespace client
}  // namespace firestore
static void InitDefaultsMutationQueue_firestore_2flocal_2fmutation_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::firestore::client::_MutationQueue_default_instance_;
    new (ptr) ::firestore::client::MutationQueue();
    ::google::protobuf::internal::OnShutdownDestroyMessage(ptr);
  }
  ::firestore::client::MutationQueue::InitAsDefaultInstance();
}

::google::protobuf::internal::SCCInfo<0> scc_info_MutationQueue_firestore_2flocal_2fmutation_2eproto =
    {{ATOMIC_VAR_INIT(::google::protobuf::internal::SCCInfoBase::kUninitialized), 0, InitDefaultsMutationQueue_firestore_2flocal_2fmutation_2eproto}, {}};

static void InitDefaultsWriteBatch_firestore_2flocal_2fmutation_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::firestore::client::_WriteBatch_default_instance_;
    new (ptr) ::firestore::client::WriteBatch();
    ::google::protobuf::internal::OnShutdownDestroyMessage(ptr);
  }
  ::firestore::client::WriteBatch::InitAsDefaultInstance();
}

::google::protobuf::internal::SCCInfo<2> scc_info_WriteBatch_firestore_2flocal_2fmutation_2eproto =
    {{ATOMIC_VAR_INIT(::google::protobuf::internal::SCCInfoBase::kUninitialized), 2, InitDefaultsWriteBatch_firestore_2flocal_2fmutation_2eproto}, {
      &scc_info_Write_google_2ffirestore_2fv1_2fwrite_2eproto.base,
      &scc_info_Timestamp_google_2fprotobuf_2ftimestamp_2eproto.base,}};

void InitDefaults_firestore_2flocal_2fmutation_2eproto() {
  ::google::protobuf::internal::InitSCC(&scc_info_MutationQueue_firestore_2flocal_2fmutation_2eproto.base);
  ::google::protobuf::internal::InitSCC(&scc_info_WriteBatch_firestore_2flocal_2fmutation_2eproto.base);
}

::google::protobuf::Metadata file_level_metadata_firestore_2flocal_2fmutation_2eproto[2];
constexpr ::google::protobuf::EnumDescriptor const** file_level_enum_descriptors_firestore_2flocal_2fmutation_2eproto = nullptr;
constexpr ::google::protobuf::ServiceDescriptor const** file_level_service_descriptors_firestore_2flocal_2fmutation_2eproto = nullptr;

const ::google::protobuf::uint32 TableStruct_firestore_2flocal_2fmutation_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::firestore::client::MutationQueue, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::firestore::client::MutationQueue, last_acknowledged_batch_id_),
  PROTOBUF_FIELD_OFFSET(::firestore::client::MutationQueue, last_stream_token_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::firestore::client::WriteBatch, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::firestore::client::WriteBatch, batch_id_),
  PROTOBUF_FIELD_OFFSET(::firestore::client::WriteBatch, writes_),
  PROTOBUF_FIELD_OFFSET(::firestore::client::WriteBatch, local_write_time_),
  PROTOBUF_FIELD_OFFSET(::firestore::client::WriteBatch, base_writes_),
};
static const ::google::protobuf::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(::firestore::client::MutationQueue)},
  { 7, -1, sizeof(::firestore::client::WriteBatch)},
};

static ::google::protobuf::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::google::protobuf::Message*>(&::firestore::client::_MutationQueue_default_instance_),
  reinterpret_cast<const ::google::protobuf::Message*>(&::firestore::client::_WriteBatch_default_instance_),
};

::google::protobuf::internal::AssignDescriptorsTable assign_descriptors_table_firestore_2flocal_2fmutation_2eproto = {
  {}, AddDescriptors_firestore_2flocal_2fmutation_2eproto, "firestore/local/mutation.proto", schemas,
  file_default_instances, TableStruct_firestore_2flocal_2fmutation_2eproto::offsets,
  file_level_metadata_firestore_2flocal_2fmutation_2eproto, 2, file_level_enum_descriptors_firestore_2flocal_2fmutation_2eproto, file_level_service_descriptors_firestore_2flocal_2fmutation_2eproto,
};

const char descriptor_table_protodef_firestore_2flocal_2fmutation_2eproto[] =
  "\n\036firestore/local/mutation.proto\022\020firest"
  "ore.client\032\037google/firestore/v1/write.pr"
  "oto\032\037google/protobuf/timestamp.proto\"N\n\r"
  "MutationQueue\022\"\n\032last_acknowledged_batch"
  "_id\030\001 \001(\005\022\031\n\021last_stream_token\030\002 \001(\014\"\261\001\n"
  "\nWriteBatch\022\020\n\010batch_id\030\001 \001(\005\022*\n\006writes\030"
  "\002 \003(\0132\032.google.firestore.v1.Write\0224\n\020loc"
  "al_write_time\030\003 \001(\0132\032.google.protobuf.Ti"
  "mestamp\022/\n\013base_writes\030\004 \003(\0132\032.google.fi"
  "restore.v1.WriteB/\n#com.google.firebase."
  "firestore.protoP\001\242\002\005FSTPBb\006proto3"
  ;
::google::protobuf::internal::DescriptorTable descriptor_table_firestore_2flocal_2fmutation_2eproto = {
  false, InitDefaults_firestore_2flocal_2fmutation_2eproto, 
  descriptor_table_protodef_firestore_2flocal_2fmutation_2eproto,
  "firestore/local/mutation.proto", &assign_descriptors_table_firestore_2flocal_2fmutation_2eproto, 433,
};

void AddDescriptors_firestore_2flocal_2fmutation_2eproto() {
  static constexpr ::google::protobuf::internal::InitFunc deps[2] =
  {
    ::AddDescriptors_google_2ffirestore_2fv1_2fwrite_2eproto,
    ::AddDescriptors_google_2fprotobuf_2ftimestamp_2eproto,
  };
 ::google::protobuf::internal::AddDescriptors(&descriptor_table_firestore_2flocal_2fmutation_2eproto, deps, 2);
}

// Force running AddDescriptors() at dynamic initialization time.
static bool dynamic_init_dummy_firestore_2flocal_2fmutation_2eproto = []() { AddDescriptors_firestore_2flocal_2fmutation_2eproto(); return true; }();
namespace firestore {
namespace client {

// ===================================================================

void MutationQueue::InitAsDefaultInstance() {
}
class MutationQueue::HasBitSetters {
 public:
};

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int MutationQueue::kLastAcknowledgedBatchIdFieldNumber;
const int MutationQueue::kLastStreamTokenFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

MutationQueue::MutationQueue()
  : ::google::protobuf::Message(), _internal_metadata_(nullptr) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:firestore.client.MutationQueue)
}
MutationQueue::MutationQueue(const MutationQueue& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(nullptr) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  last_stream_token_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (from.last_stream_token().size() > 0) {
    last_stream_token_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.last_stream_token_);
  }
  last_acknowledged_batch_id_ = from.last_acknowledged_batch_id_;
  // @@protoc_insertion_point(copy_constructor:firestore.client.MutationQueue)
}

void MutationQueue::SharedCtor() {
  ::google::protobuf::internal::InitSCC(
      &scc_info_MutationQueue_firestore_2flocal_2fmutation_2eproto.base);
  last_stream_token_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  last_acknowledged_batch_id_ = 0;
}

MutationQueue::~MutationQueue() {
  // @@protoc_insertion_point(destructor:firestore.client.MutationQueue)
  SharedDtor();
}

void MutationQueue::SharedDtor() {
  last_stream_token_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}

void MutationQueue::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const MutationQueue& MutationQueue::default_instance() {
  ::google::protobuf::internal::InitSCC(&::scc_info_MutationQueue_firestore_2flocal_2fmutation_2eproto.base);
  return *internal_default_instance();
}


void MutationQueue::Clear() {
// @@protoc_insertion_point(message_clear_start:firestore.client.MutationQueue)
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  last_stream_token_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  last_acknowledged_batch_id_ = 0;
  _internal_metadata_.Clear();
}

#if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
const char* MutationQueue::_InternalParse(const char* begin, const char* end, void* object,
                  ::google::protobuf::internal::ParseContext* ctx) {
  auto msg = static_cast<MutationQueue*>(object);
  ::google::protobuf::int32 size; (void)size;
  int depth; (void)depth;
  ::google::protobuf::uint32 tag;
  ::google::protobuf::internal::ParseFunc parser_till_end; (void)parser_till_end;
  auto ptr = begin;
  while (ptr < end) {
    ptr = ::google::protobuf::io::Parse32(ptr, &tag);
    GOOGLE_PROTOBUF_PARSER_ASSERT(ptr);
    switch (tag >> 3) {
      // int32 last_acknowledged_batch_id = 1;
      case 1: {
        if (static_cast<::google::protobuf::uint8>(tag) != 8) goto handle_unusual;
        msg->set_last_acknowledged_batch_id(::google::protobuf::internal::ReadVarint(&ptr));
        GOOGLE_PROTOBUF_PARSER_ASSERT(ptr);
        break;
      }
      // bytes last_stream_token = 2;
      case 2: {
        if (static_cast<::google::protobuf::uint8>(tag) != 18) goto handle_unusual;
        ptr = ::google::protobuf::io::ReadSize(ptr, &size);
        GOOGLE_PROTOBUF_PARSER_ASSERT(ptr);
        object = msg->mutable_last_stream_token();
        if (size > end - ptr + ::google::protobuf::internal::ParseContext::kSlopBytes) {
          parser_till_end = ::google::protobuf::internal::GreedyStringParser;
          goto string_till_end;
        }
        GOOGLE_PROTOBUF_PARSER_ASSERT(::google::protobuf::internal::StringCheck(ptr, size, ctx));
        ::google::protobuf::internal::InlineGreedyStringParser(object, ptr, size, ctx);
        ptr += size;
        break;
      }
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->EndGroup(tag);
          return ptr;
        }
        auto res = UnknownFieldParse(tag, {_InternalParse, msg},
          ptr, end, msg->_internal_metadata_.mutable_unknown_fields(), ctx);
        ptr = res.first;
        GOOGLE_PROTOBUF_PARSER_ASSERT(ptr != nullptr);
        if (res.second) return ptr;
      }
    }  // switch
  }  // while
  return ptr;
string_till_end:
  static_cast<::std::string*>(object)->clear();
  static_cast<::std::string*>(object)->reserve(size);
  goto len_delim_till_end;
len_delim_till_end:
  return ctx->StoreAndTailCall(ptr, end, {_InternalParse, msg},
                               {parser_till_end, object}, size);
}
#else  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
bool MutationQueue::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!PROTOBUF_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:firestore.client.MutationQueue)
  for (;;) {
    ::std::pair<::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // int32 last_acknowledged_batch_id = 1;
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) == (8 & 0xFF)) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &last_acknowledged_batch_id_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // bytes last_stream_token = 2;
      case 2: {
        if (static_cast< ::google::protobuf::uint8>(tag) == (18 & 0xFF)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadBytes(
                input, this->mutable_last_stream_token()));
        } else {
          goto handle_unusual;
        }
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, _internal_metadata_.mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:firestore.client.MutationQueue)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:firestore.client.MutationQueue)
  return false;
#undef DO_
}
#endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER

void MutationQueue::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:firestore.client.MutationQueue)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // int32 last_acknowledged_batch_id = 1;
  if (this->last_acknowledged_batch_id() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->last_acknowledged_batch_id(), output);
  }

  // bytes last_stream_token = 2;
  if (this->last_stream_token().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::WriteBytesMaybeAliased(
      2, this->last_stream_token(), output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        _internal_metadata_.unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:firestore.client.MutationQueue)
}

::google::protobuf::uint8* MutationQueue::InternalSerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:firestore.client.MutationQueue)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // int32 last_acknowledged_batch_id = 1;
  if (this->last_acknowledged_batch_id() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, this->last_acknowledged_batch_id(), target);
  }

  // bytes last_stream_token = 2;
  if (this->last_stream_token().size() > 0) {
    target =
      ::google::protobuf::internal::WireFormatLite::WriteBytesToArray(
        2, this->last_stream_token(), target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:firestore.client.MutationQueue)
  return target;
}

size_t MutationQueue::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:firestore.client.MutationQueue)
  size_t total_size = 0;

  if (_internal_metadata_.have_unknown_fields()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        _internal_metadata_.unknown_fields());
  }
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // bytes last_stream_token = 2;
  if (this->last_stream_token().size() > 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::BytesSize(
        this->last_stream_token());
  }

  // int32 last_acknowledged_batch_id = 1;
  if (this->last_acknowledged_batch_id() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->last_acknowledged_batch_id());
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void MutationQueue::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:firestore.client.MutationQueue)
  GOOGLE_DCHECK_NE(&from, this);
  const MutationQueue* source =
      ::google::protobuf::DynamicCastToGenerated<MutationQueue>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:firestore.client.MutationQueue)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:firestore.client.MutationQueue)
    MergeFrom(*source);
  }
}

void MutationQueue::MergeFrom(const MutationQueue& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:firestore.client.MutationQueue)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.last_stream_token().size() > 0) {

    last_stream_token_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.last_stream_token_);
  }
  if (from.last_acknowledged_batch_id() != 0) {
    set_last_acknowledged_batch_id(from.last_acknowledged_batch_id());
  }
}

void MutationQueue::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:firestore.client.MutationQueue)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void MutationQueue::CopyFrom(const MutationQueue& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:firestore.client.MutationQueue)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool MutationQueue::IsInitialized() const {
  return true;
}

void MutationQueue::Swap(MutationQueue* other) {
  if (other == this) return;
  InternalSwap(other);
}
void MutationQueue::InternalSwap(MutationQueue* other) {
  using std::swap;
  _internal_metadata_.Swap(&other->_internal_metadata_);
  last_stream_token_.Swap(&other->last_stream_token_, &::google::protobuf::internal::GetEmptyStringAlreadyInited(),
    GetArenaNoVirtual());
  swap(last_acknowledged_batch_id_, other->last_acknowledged_batch_id_);
}

::google::protobuf::Metadata MutationQueue::GetMetadata() const {
  ::google::protobuf::internal::AssignDescriptors(&::assign_descriptors_table_firestore_2flocal_2fmutation_2eproto);
  return ::file_level_metadata_firestore_2flocal_2fmutation_2eproto[kIndexInFileMessages];
}


// ===================================================================

void WriteBatch::InitAsDefaultInstance() {
  ::firestore::client::_WriteBatch_default_instance_._instance.get_mutable()->local_write_time_ = const_cast< ::google::protobuf::Timestamp*>(
      ::google::protobuf::Timestamp::internal_default_instance());
}
class WriteBatch::HasBitSetters {
 public:
  static const ::google::protobuf::Timestamp& local_write_time(const WriteBatch* msg);
};

const ::google::protobuf::Timestamp&
WriteBatch::HasBitSetters::local_write_time(const WriteBatch* msg) {
  return *msg->local_write_time_;
}
void WriteBatch::clear_writes() {
  writes_.Clear();
}
void WriteBatch::clear_local_write_time() {
  if (GetArenaNoVirtual() == nullptr && local_write_time_ != nullptr) {
    delete local_write_time_;
  }
  local_write_time_ = nullptr;
}
void WriteBatch::clear_base_writes() {
  base_writes_.Clear();
}
#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int WriteBatch::kBatchIdFieldNumber;
const int WriteBatch::kWritesFieldNumber;
const int WriteBatch::kLocalWriteTimeFieldNumber;
const int WriteBatch::kBaseWritesFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

WriteBatch::WriteBatch()
  : ::google::protobuf::Message(), _internal_metadata_(nullptr) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:firestore.client.WriteBatch)
}
WriteBatch::WriteBatch(const WriteBatch& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(nullptr),
      writes_(from.writes_),
      base_writes_(from.base_writes_) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  if (from.has_local_write_time()) {
    local_write_time_ = new ::google::protobuf::Timestamp(*from.local_write_time_);
  } else {
    local_write_time_ = nullptr;
  }
  batch_id_ = from.batch_id_;
  // @@protoc_insertion_point(copy_constructor:firestore.client.WriteBatch)
}

void WriteBatch::SharedCtor() {
  ::google::protobuf::internal::InitSCC(
      &scc_info_WriteBatch_firestore_2flocal_2fmutation_2eproto.base);
  ::memset(&local_write_time_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&batch_id_) -
      reinterpret_cast<char*>(&local_write_time_)) + sizeof(batch_id_));
}

WriteBatch::~WriteBatch() {
  // @@protoc_insertion_point(destructor:firestore.client.WriteBatch)
  SharedDtor();
}

void WriteBatch::SharedDtor() {
  if (this != internal_default_instance()) delete local_write_time_;
}

void WriteBatch::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const WriteBatch& WriteBatch::default_instance() {
  ::google::protobuf::internal::InitSCC(&::scc_info_WriteBatch_firestore_2flocal_2fmutation_2eproto.base);
  return *internal_default_instance();
}


void WriteBatch::Clear() {
// @@protoc_insertion_point(message_clear_start:firestore.client.WriteBatch)
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  writes_.Clear();
  base_writes_.Clear();
  if (GetArenaNoVirtual() == nullptr && local_write_time_ != nullptr) {
    delete local_write_time_;
  }
  local_write_time_ = nullptr;
  batch_id_ = 0;
  _internal_metadata_.Clear();
}

#if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
const char* WriteBatch::_InternalParse(const char* begin, const char* end, void* object,
                  ::google::protobuf::internal::ParseContext* ctx) {
  auto msg = static_cast<WriteBatch*>(object);
  ::google::protobuf::int32 size; (void)size;
  int depth; (void)depth;
  ::google::protobuf::uint32 tag;
  ::google::protobuf::internal::ParseFunc parser_till_end; (void)parser_till_end;
  auto ptr = begin;
  while (ptr < end) {
    ptr = ::google::protobuf::io::Parse32(ptr, &tag);
    GOOGLE_PROTOBUF_PARSER_ASSERT(ptr);
    switch (tag >> 3) {
      // int32 batch_id = 1;
      case 1: {
        if (static_cast<::google::protobuf::uint8>(tag) != 8) goto handle_unusual;
        msg->set_batch_id(::google::protobuf::internal::ReadVarint(&ptr));
        GOOGLE_PROTOBUF_PARSER_ASSERT(ptr);
        break;
      }
      // repeated .google.firestore.v1.Write writes = 2;
      case 2: {
        if (static_cast<::google::protobuf::uint8>(tag) != 18) goto handle_unusual;
        do {
          ptr = ::google::protobuf::io::ReadSize(ptr, &size);
          GOOGLE_PROTOBUF_PARSER_ASSERT(ptr);
          parser_till_end = ::google::firestore::v1::Write::_InternalParse;
          object = msg->add_writes();
          if (size > end - ptr) goto len_delim_till_end;
          ptr += size;
          GOOGLE_PROTOBUF_PARSER_ASSERT(ctx->ParseExactRange(
              {parser_till_end, object}, ptr - size, ptr));
          if (ptr >= end) break;
        } while ((::google::protobuf::io::UnalignedLoad<::google::protobuf::uint64>(ptr) & 255) == 18 && (ptr += 1));
        break;
      }
      // .google.protobuf.Timestamp local_write_time = 3;
      case 3: {
        if (static_cast<::google::protobuf::uint8>(tag) != 26) goto handle_unusual;
        ptr = ::google::protobuf::io::ReadSize(ptr, &size);
        GOOGLE_PROTOBUF_PARSER_ASSERT(ptr);
        parser_till_end = ::google::protobuf::Timestamp::_InternalParse;
        object = msg->mutable_local_write_time();
        if (size > end - ptr) goto len_delim_till_end;
        ptr += size;
        GOOGLE_PROTOBUF_PARSER_ASSERT(ctx->ParseExactRange(
            {parser_till_end, object}, ptr - size, ptr));
        break;
      }
      // repeated .google.firestore.v1.Write base_writes = 4;
      case 4: {
        if (static_cast<::google::protobuf::uint8>(tag) != 34) goto handle_unusual;
        do {
          ptr = ::google::protobuf::io::ReadSize(ptr, &size);
          GOOGLE_PROTOBUF_PARSER_ASSERT(ptr);
          parser_till_end = ::google::firestore::v1::Write::_InternalParse;
          object = msg->add_base_writes();
          if (size > end - ptr) goto len_delim_till_end;
          ptr += size;
          GOOGLE_PROTOBUF_PARSER_ASSERT(ctx->ParseExactRange(
              {parser_till_end, object}, ptr - size, ptr));
          if (ptr >= end) break;
        } while ((::google::protobuf::io::UnalignedLoad<::google::protobuf::uint64>(ptr) & 255) == 34 && (ptr += 1));
        break;
      }
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->EndGroup(tag);
          return ptr;
        }
        auto res = UnknownFieldParse(tag, {_InternalParse, msg},
          ptr, end, msg->_internal_metadata_.mutable_unknown_fields(), ctx);
        ptr = res.first;
        GOOGLE_PROTOBUF_PARSER_ASSERT(ptr != nullptr);
        if (res.second) return ptr;
      }
    }  // switch
  }  // while
  return ptr;
len_delim_till_end:
  return ctx->StoreAndTailCall(ptr, end, {_InternalParse, msg},
                               {parser_till_end, object}, size);
}
#else  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
bool WriteBatch::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!PROTOBUF_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:firestore.client.WriteBatch)
  for (;;) {
    ::std::pair<::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // int32 batch_id = 1;
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) == (8 & 0xFF)) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &batch_id_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // repeated .google.firestore.v1.Write writes = 2;
      case 2: {
        if (static_cast< ::google::protobuf::uint8>(tag) == (18 & 0xFF)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessage(
                input, add_writes()));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // .google.protobuf.Timestamp local_write_time = 3;
      case 3: {
        if (static_cast< ::google::protobuf::uint8>(tag) == (26 & 0xFF)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessage(
               input, mutable_local_write_time()));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // repeated .google.firestore.v1.Write base_writes = 4;
      case 4: {
        if (static_cast< ::google::protobuf::uint8>(tag) == (34 & 0xFF)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessage(
                input, add_base_writes()));
        } else {
          goto handle_unusual;
        }
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, _internal_metadata_.mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:firestore.client.WriteBatch)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:firestore.client.WriteBatch)
  return false;
#undef DO_
}
#endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER

void WriteBatch::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:firestore.client.WriteBatch)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // int32 batch_id = 1;
  if (this->batch_id() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->batch_id(), output);
  }

  // repeated .google.firestore.v1.Write writes = 2;
  for (unsigned int i = 0,
      n = static_cast<unsigned int>(this->writes_size()); i < n; i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      2,
      this->writes(static_cast<int>(i)),
      output);
  }

  // .google.protobuf.Timestamp local_write_time = 3;
  if (this->has_local_write_time()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      3, HasBitSetters::local_write_time(this), output);
  }

  // repeated .google.firestore.v1.Write base_writes = 4;
  for (unsigned int i = 0,
      n = static_cast<unsigned int>(this->base_writes_size()); i < n; i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      4,
      this->base_writes(static_cast<int>(i)),
      output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        _internal_metadata_.unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:firestore.client.WriteBatch)
}

::google::protobuf::uint8* WriteBatch::InternalSerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:firestore.client.WriteBatch)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // int32 batch_id = 1;
  if (this->batch_id() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, this->batch_id(), target);
  }

  // repeated .google.firestore.v1.Write writes = 2;
  for (unsigned int i = 0,
      n = static_cast<unsigned int>(this->writes_size()); i < n; i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      InternalWriteMessageToArray(
        2, this->writes(static_cast<int>(i)), target);
  }

  // .google.protobuf.Timestamp local_write_time = 3;
  if (this->has_local_write_time()) {
    target = ::google::protobuf::internal::WireFormatLite::
      InternalWriteMessageToArray(
        3, HasBitSetters::local_write_time(this), target);
  }

  // repeated .google.firestore.v1.Write base_writes = 4;
  for (unsigned int i = 0,
      n = static_cast<unsigned int>(this->base_writes_size()); i < n; i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      InternalWriteMessageToArray(
        4, this->base_writes(static_cast<int>(i)), target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:firestore.client.WriteBatch)
  return target;
}

size_t WriteBatch::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:firestore.client.WriteBatch)
  size_t total_size = 0;

  if (_internal_metadata_.have_unknown_fields()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        _internal_metadata_.unknown_fields());
  }
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // repeated .google.firestore.v1.Write writes = 2;
  {
    unsigned int count = static_cast<unsigned int>(this->writes_size());
    total_size += 1UL * count;
    for (unsigned int i = 0; i < count; i++) {
      total_size +=
        ::google::protobuf::internal::WireFormatLite::MessageSize(
          this->writes(static_cast<int>(i)));
    }
  }

  // repeated .google.firestore.v1.Write base_writes = 4;
  {
    unsigned int count = static_cast<unsigned int>(this->base_writes_size());
    total_size += 1UL * count;
    for (unsigned int i = 0; i < count; i++) {
      total_size +=
        ::google::protobuf::internal::WireFormatLite::MessageSize(
          this->base_writes(static_cast<int>(i)));
    }
  }

  // .google.protobuf.Timestamp local_write_time = 3;
  if (this->has_local_write_time()) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::MessageSize(
        *local_write_time_);
  }

  // int32 batch_id = 1;
  if (this->batch_id() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->batch_id());
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void WriteBatch::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:firestore.client.WriteBatch)
  GOOGLE_DCHECK_NE(&from, this);
  const WriteBatch* source =
      ::google::protobuf::DynamicCastToGenerated<WriteBatch>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:firestore.client.WriteBatch)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:firestore.client.WriteBatch)
    MergeFrom(*source);
  }
}

void WriteBatch::MergeFrom(const WriteBatch& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:firestore.client.WriteBatch)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  writes_.MergeFrom(from.writes_);
  base_writes_.MergeFrom(from.base_writes_);
  if (from.has_local_write_time()) {
    mutable_local_write_time()->::google::protobuf::Timestamp::MergeFrom(from.local_write_time());
  }
  if (from.batch_id() != 0) {
    set_batch_id(from.batch_id());
  }
}

void WriteBatch::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:firestore.client.WriteBatch)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void WriteBatch::CopyFrom(const WriteBatch& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:firestore.client.WriteBatch)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool WriteBatch::IsInitialized() const {
  return true;
}

void WriteBatch::Swap(WriteBatch* other) {
  if (other == this) return;
  InternalSwap(other);
}
void WriteBatch::InternalSwap(WriteBatch* other) {
  using std::swap;
  _internal_metadata_.Swap(&other->_internal_metadata_);
  CastToBase(&writes_)->InternalSwap(CastToBase(&other->writes_));
  CastToBase(&base_writes_)->InternalSwap(CastToBase(&other->base_writes_));
  swap(local_write_time_, other->local_write_time_);
  swap(batch_id_, other->batch_id_);
}

::google::protobuf::Metadata WriteBatch::GetMetadata() const {
  ::google::protobuf::internal::AssignDescriptors(&::assign_descriptors_table_firestore_2flocal_2fmutation_2eproto);
  return ::file_level_metadata_firestore_2flocal_2fmutation_2eproto[kIndexInFileMessages];
}


// @@protoc_insertion_point(namespace_scope)
}  // namespace client
}  // namespace firestore
namespace google {
namespace protobuf {
template<> PROTOBUF_NOINLINE ::firestore::client::MutationQueue* Arena::CreateMaybeMessage< ::firestore::client::MutationQueue >(Arena* arena) {
  return Arena::CreateInternal< ::firestore::client::MutationQueue >(arena);
}
template<> PROTOBUF_NOINLINE ::firestore::client::WriteBatch* Arena::CreateMaybeMessage< ::firestore::client::WriteBatch >(Arena* arena) {
  return Arena::CreateInternal< ::firestore::client::WriteBatch >(arena);
}
}  // namespace protobuf
}  // namespace google

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
