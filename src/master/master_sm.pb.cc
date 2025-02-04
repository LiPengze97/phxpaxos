// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: master_sm.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "master_sm.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/port.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace phxpaxos {

namespace {

const ::google::protobuf::Descriptor* MasterOperator_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  MasterOperator_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_master_5fsm_2eproto() GOOGLE_ATTRIBUTE_COLD;
void protobuf_AssignDesc_master_5fsm_2eproto() {
  protobuf_AddDesc_master_5fsm_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "master_sm.proto");
  GOOGLE_CHECK(file != NULL);
  MasterOperator_descriptor_ = file->message_type(0);
  static const int MasterOperator_offsets_[6] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MasterOperator, nodeid_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MasterOperator, version_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MasterOperator, timeout_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MasterOperator, operator__),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MasterOperator, sid_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MasterOperator, lastversion_),
  };
  MasterOperator_reflection_ =
    ::google::protobuf::internal::GeneratedMessageReflection::NewGeneratedMessageReflection(
      MasterOperator_descriptor_,
      MasterOperator::default_instance_,
      MasterOperator_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MasterOperator, _has_bits_[0]),
      -1,
      -1,
      sizeof(MasterOperator),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MasterOperator, _internal_metadata_),
      -1);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_master_5fsm_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) GOOGLE_ATTRIBUTE_COLD;
void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
      MasterOperator_descriptor_, &MasterOperator::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_master_5fsm_2eproto() {
  delete MasterOperator::default_instance_;
  delete MasterOperator_reflection_;
}

void protobuf_AddDesc_master_5fsm_2eproto() GOOGLE_ATTRIBUTE_COLD;
void protobuf_AddDesc_master_5fsm_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\017master_sm.proto\022\010phxpaxos\"v\n\016MasterOpe"
    "rator\022\016\n\006nodeid\030\001 \002(\004\022\017\n\007version\030\002 \002(\004\022\017"
    "\n\007timeout\030\003 \002(\005\022\020\n\010operator\030\004 \002(\r\022\013\n\003sid"
    "\030\005 \002(\r\022\023\n\013lastversion\030\006 \001(\004", 147);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "master_sm.proto", &protobuf_RegisterTypes);
  MasterOperator::default_instance_ = new MasterOperator();
  MasterOperator::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_master_5fsm_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_master_5fsm_2eproto {
  StaticDescriptorInitializer_master_5fsm_2eproto() {
    protobuf_AddDesc_master_5fsm_2eproto();
  }
} static_descriptor_initializer_master_5fsm_2eproto_;

// ===================================================================

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int MasterOperator::kNodeidFieldNumber;
const int MasterOperator::kVersionFieldNumber;
const int MasterOperator::kTimeoutFieldNumber;
const int MasterOperator::kOperatorFieldNumber;
const int MasterOperator::kSidFieldNumber;
const int MasterOperator::kLastversionFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

MasterOperator::MasterOperator()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:phxpaxos.MasterOperator)
}

void MasterOperator::InitAsDefaultInstance() {
}

MasterOperator::MasterOperator(const MasterOperator& from)
  : ::google::protobuf::Message(),
    _internal_metadata_(NULL) {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:phxpaxos.MasterOperator)
}

void MasterOperator::SharedCtor() {
  _cached_size_ = 0;
  nodeid_ = GOOGLE_ULONGLONG(0);
  version_ = GOOGLE_ULONGLONG(0);
  timeout_ = 0;
  operator__ = 0u;
  sid_ = 0u;
  lastversion_ = GOOGLE_ULONGLONG(0);
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

MasterOperator::~MasterOperator() {
  // @@protoc_insertion_point(destructor:phxpaxos.MasterOperator)
  SharedDtor();
}

void MasterOperator::SharedDtor() {
  if (this != default_instance_) {
  }
}

void MasterOperator::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* MasterOperator::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return MasterOperator_descriptor_;
}

const MasterOperator& MasterOperator::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_master_5fsm_2eproto();
  return *default_instance_;
}

MasterOperator* MasterOperator::default_instance_ = NULL;

MasterOperator* MasterOperator::New(::google::protobuf::Arena* arena) const {
  MasterOperator* n = new MasterOperator;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void MasterOperator::Clear() {
// @@protoc_insertion_point(message_clear_start:phxpaxos.MasterOperator)
#if defined(__clang__)
#define ZR_HELPER_(f) \
  _Pragma("clang diagnostic push") \
  _Pragma("clang diagnostic ignored \"-Winvalid-offsetof\"") \
  __builtin_offsetof(MasterOperator, f) \
  _Pragma("clang diagnostic pop")
#else
#define ZR_HELPER_(f) reinterpret_cast<char*>(\
  &reinterpret_cast<MasterOperator*>(16)->f)
#endif

#define ZR_(first, last) do {\
  ::memset(&first, 0,\
           ZR_HELPER_(last) - ZR_HELPER_(first) + sizeof(last));\
} while (0)

  if (_has_bits_[0 / 32] & 63u) {
    ZR_(nodeid_, sid_);
  }

#undef ZR_HELPER_
#undef ZR_

  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  if (_internal_metadata_.have_unknown_fields()) {
    mutable_unknown_fields()->Clear();
  }
}

bool MasterOperator::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:phxpaxos.MasterOperator)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required uint64 nodeid = 1;
      case 1: {
        if (tag == 8) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint64, ::google::protobuf::internal::WireFormatLite::TYPE_UINT64>(
                 input, &nodeid_)));
          set_has_nodeid();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(16)) goto parse_version;
        break;
      }

      // required uint64 version = 2;
      case 2: {
        if (tag == 16) {
         parse_version:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint64, ::google::protobuf::internal::WireFormatLite::TYPE_UINT64>(
                 input, &version_)));
          set_has_version();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(24)) goto parse_timeout;
        break;
      }

      // required int32 timeout = 3;
      case 3: {
        if (tag == 24) {
         parse_timeout:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &timeout_)));
          set_has_timeout();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(32)) goto parse_operator;
        break;
      }

      // required uint32 operator = 4;
      case 4: {
        if (tag == 32) {
         parse_operator:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &operator__)));
          set_has_operator_();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(40)) goto parse_sid;
        break;
      }

      // required uint32 sid = 5;
      case 5: {
        if (tag == 40) {
         parse_sid:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &sid_)));
          set_has_sid();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(48)) goto parse_lastversion;
        break;
      }

      // optional uint64 lastversion = 6;
      case 6: {
        if (tag == 48) {
         parse_lastversion:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint64, ::google::protobuf::internal::WireFormatLite::TYPE_UINT64>(
                 input, &lastversion_)));
          set_has_lastversion();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectAtEnd()) goto success;
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:phxpaxos.MasterOperator)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:phxpaxos.MasterOperator)
  return false;
#undef DO_
}

void MasterOperator::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:phxpaxos.MasterOperator)
  // required uint64 nodeid = 1;
  if (has_nodeid()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt64(1, this->nodeid(), output);
  }

  // required uint64 version = 2;
  if (has_version()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt64(2, this->version(), output);
  }

  // required int32 timeout = 3;
  if (has_timeout()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(3, this->timeout(), output);
  }

  // required uint32 operator = 4;
  if (has_operator_()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(4, this->operator_(), output);
  }

  // required uint32 sid = 5;
  if (has_sid()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(5, this->sid(), output);
  }

  // optional uint64 lastversion = 6;
  if (has_lastversion()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt64(6, this->lastversion(), output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:phxpaxos.MasterOperator)
}

::google::protobuf::uint8* MasterOperator::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:phxpaxos.MasterOperator)
  // required uint64 nodeid = 1;
  if (has_nodeid()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt64ToArray(1, this->nodeid(), target);
  }

  // required uint64 version = 2;
  if (has_version()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt64ToArray(2, this->version(), target);
  }

  // required int32 timeout = 3;
  if (has_timeout()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(3, this->timeout(), target);
  }

  // required uint32 operator = 4;
  if (has_operator_()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(4, this->operator_(), target);
  }

  // required uint32 sid = 5;
  if (has_sid()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(5, this->sid(), target);
  }

  // optional uint64 lastversion = 6;
  if (has_lastversion()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt64ToArray(6, this->lastversion(), target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:phxpaxos.MasterOperator)
  return target;
}

int MasterOperator::RequiredFieldsByteSizeFallback() const {
// @@protoc_insertion_point(required_fields_byte_size_fallback_start:phxpaxos.MasterOperator)
  int total_size = 0;

  if (has_nodeid()) {
    // required uint64 nodeid = 1;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::UInt64Size(
        this->nodeid());
  }

  if (has_version()) {
    // required uint64 version = 2;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::UInt64Size(
        this->version());
  }

  if (has_timeout()) {
    // required int32 timeout = 3;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->timeout());
  }

  if (has_operator_()) {
    // required uint32 operator = 4;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::UInt32Size(
        this->operator_());
  }

  if (has_sid()) {
    // required uint32 sid = 5;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::UInt32Size(
        this->sid());
  }

  return total_size;
}
int MasterOperator::ByteSize() const {
// @@protoc_insertion_point(message_byte_size_start:phxpaxos.MasterOperator)
  int total_size = 0;

  if (((_has_bits_[0] & 0x0000001f) ^ 0x0000001f) == 0) {  // All required fields are present.
    // required uint64 nodeid = 1;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::UInt64Size(
        this->nodeid());

    // required uint64 version = 2;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::UInt64Size(
        this->version());

    // required int32 timeout = 3;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->timeout());

    // required uint32 operator = 4;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::UInt32Size(
        this->operator_());

    // required uint32 sid = 5;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::UInt32Size(
        this->sid());

  } else {
    total_size += RequiredFieldsByteSizeFallback();
  }
  // optional uint64 lastversion = 6;
  if (has_lastversion()) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::UInt64Size(
        this->lastversion());
  }

  if (_internal_metadata_.have_unknown_fields()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void MasterOperator::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:phxpaxos.MasterOperator)
  if (GOOGLE_PREDICT_FALSE(&from == this)) {
    ::google::protobuf::internal::MergeFromFail(__FILE__, __LINE__);
  }
  const MasterOperator* source = 
      ::google::protobuf::internal::DynamicCastToGenerated<const MasterOperator>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:phxpaxos.MasterOperator)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:phxpaxos.MasterOperator)
    MergeFrom(*source);
  }
}

void MasterOperator::MergeFrom(const MasterOperator& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:phxpaxos.MasterOperator)
  if (GOOGLE_PREDICT_FALSE(&from == this)) {
    ::google::protobuf::internal::MergeFromFail(__FILE__, __LINE__);
  }
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_nodeid()) {
      set_nodeid(from.nodeid());
    }
    if (from.has_version()) {
      set_version(from.version());
    }
    if (from.has_timeout()) {
      set_timeout(from.timeout());
    }
    if (from.has_operator_()) {
      set_operator_(from.operator_());
    }
    if (from.has_sid()) {
      set_sid(from.sid());
    }
    if (from.has_lastversion()) {
      set_lastversion(from.lastversion());
    }
  }
  if (from._internal_metadata_.have_unknown_fields()) {
    mutable_unknown_fields()->MergeFrom(from.unknown_fields());
  }
}

void MasterOperator::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:phxpaxos.MasterOperator)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void MasterOperator::CopyFrom(const MasterOperator& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:phxpaxos.MasterOperator)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool MasterOperator::IsInitialized() const {
  if ((_has_bits_[0] & 0x0000001f) != 0x0000001f) return false;

  return true;
}

void MasterOperator::Swap(MasterOperator* other) {
  if (other == this) return;
  InternalSwap(other);
}
void MasterOperator::InternalSwap(MasterOperator* other) {
  std::swap(nodeid_, other->nodeid_);
  std::swap(version_, other->version_);
  std::swap(timeout_, other->timeout_);
  std::swap(operator__, other->operator__);
  std::swap(sid_, other->sid_);
  std::swap(lastversion_, other->lastversion_);
  std::swap(_has_bits_[0], other->_has_bits_[0]);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  std::swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata MasterOperator::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = MasterOperator_descriptor_;
  metadata.reflection = MasterOperator_reflection_;
  return metadata;
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// MasterOperator

// required uint64 nodeid = 1;
bool MasterOperator::has_nodeid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
void MasterOperator::set_has_nodeid() {
  _has_bits_[0] |= 0x00000001u;
}
void MasterOperator::clear_has_nodeid() {
  _has_bits_[0] &= ~0x00000001u;
}
void MasterOperator::clear_nodeid() {
  nodeid_ = GOOGLE_ULONGLONG(0);
  clear_has_nodeid();
}
 ::google::protobuf::uint64 MasterOperator::nodeid() const {
  // @@protoc_insertion_point(field_get:phxpaxos.MasterOperator.nodeid)
  return nodeid_;
}
 void MasterOperator::set_nodeid(::google::protobuf::uint64 value) {
  set_has_nodeid();
  nodeid_ = value;
  // @@protoc_insertion_point(field_set:phxpaxos.MasterOperator.nodeid)
}

// required uint64 version = 2;
bool MasterOperator::has_version() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
void MasterOperator::set_has_version() {
  _has_bits_[0] |= 0x00000002u;
}
void MasterOperator::clear_has_version() {
  _has_bits_[0] &= ~0x00000002u;
}
void MasterOperator::clear_version() {
  version_ = GOOGLE_ULONGLONG(0);
  clear_has_version();
}
 ::google::protobuf::uint64 MasterOperator::version() const {
  // @@protoc_insertion_point(field_get:phxpaxos.MasterOperator.version)
  return version_;
}
 void MasterOperator::set_version(::google::protobuf::uint64 value) {
  set_has_version();
  version_ = value;
  // @@protoc_insertion_point(field_set:phxpaxos.MasterOperator.version)
}

// required int32 timeout = 3;
bool MasterOperator::has_timeout() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
void MasterOperator::set_has_timeout() {
  _has_bits_[0] |= 0x00000004u;
}
void MasterOperator::clear_has_timeout() {
  _has_bits_[0] &= ~0x00000004u;
}
void MasterOperator::clear_timeout() {
  timeout_ = 0;
  clear_has_timeout();
}
 ::google::protobuf::int32 MasterOperator::timeout() const {
  // @@protoc_insertion_point(field_get:phxpaxos.MasterOperator.timeout)
  return timeout_;
}
 void MasterOperator::set_timeout(::google::protobuf::int32 value) {
  set_has_timeout();
  timeout_ = value;
  // @@protoc_insertion_point(field_set:phxpaxos.MasterOperator.timeout)
}

// required uint32 operator = 4;
bool MasterOperator::has_operator_() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
void MasterOperator::set_has_operator_() {
  _has_bits_[0] |= 0x00000008u;
}
void MasterOperator::clear_has_operator_() {
  _has_bits_[0] &= ~0x00000008u;
}
void MasterOperator::clear_operator_() {
  operator__ = 0u;
  clear_has_operator_();
}
 ::google::protobuf::uint32 MasterOperator::operator_() const {
  // @@protoc_insertion_point(field_get:phxpaxos.MasterOperator.operator)
  return operator__;
}
 void MasterOperator::set_operator_(::google::protobuf::uint32 value) {
  set_has_operator_();
  operator__ = value;
  // @@protoc_insertion_point(field_set:phxpaxos.MasterOperator.operator)
}

// required uint32 sid = 5;
bool MasterOperator::has_sid() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
void MasterOperator::set_has_sid() {
  _has_bits_[0] |= 0x00000010u;
}
void MasterOperator::clear_has_sid() {
  _has_bits_[0] &= ~0x00000010u;
}
void MasterOperator::clear_sid() {
  sid_ = 0u;
  clear_has_sid();
}
 ::google::protobuf::uint32 MasterOperator::sid() const {
  // @@protoc_insertion_point(field_get:phxpaxos.MasterOperator.sid)
  return sid_;
}
 void MasterOperator::set_sid(::google::protobuf::uint32 value) {
  set_has_sid();
  sid_ = value;
  // @@protoc_insertion_point(field_set:phxpaxos.MasterOperator.sid)
}

// optional uint64 lastversion = 6;
bool MasterOperator::has_lastversion() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
void MasterOperator::set_has_lastversion() {
  _has_bits_[0] |= 0x00000020u;
}
void MasterOperator::clear_has_lastversion() {
  _has_bits_[0] &= ~0x00000020u;
}
void MasterOperator::clear_lastversion() {
  lastversion_ = GOOGLE_ULONGLONG(0);
  clear_has_lastversion();
}
 ::google::protobuf::uint64 MasterOperator::lastversion() const {
  // @@protoc_insertion_point(field_get:phxpaxos.MasterOperator.lastversion)
  return lastversion_;
}
 void MasterOperator::set_lastversion(::google::protobuf::uint64 value) {
  set_has_lastversion();
  lastversion_ = value;
  // @@protoc_insertion_point(field_set:phxpaxos.MasterOperator.lastversion)
}

#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

}  // namespace phxpaxos

// @@protoc_insertion_point(global_scope)
