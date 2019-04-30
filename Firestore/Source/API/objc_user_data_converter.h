/*
 * Copyright 2019 Google
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

#ifndef FIRESTORE_SOURCE_API_OBJC_USER_DATA_CONVERTER_H_
#define FIRESTORE_SOURCE_API_OBJC_USER_DATA_CONVERTER_H_

#if !defined(__OBJC__)
#error "This header only supports Objective-C++"
#endif  // !defined(__OBJC__)

#import <Foundation/Foundation.h>

#include <set>
#include <vector>

#include "Firestore/core/src/firebase/firestore/api/user_data_converter.h"

NS_ASSUME_NONNULL_BEGIN

@class FIRDocumentReference;
@class FIRFieldValue;
@class FIRTimestamp;
@class FSTDocumentKeyReference;

namespace firebase {
namespace firestore {
namespace core {
class ParseAccumulator;
class ParseContext;
}

namespace model {
class FieldPath;
}

namespace api {

/**
 * A UserData implementation that carries a value of type `id`. This almost
 * always points to a user-supplied NSDictionary<NSString *, id> but not always.
 */
class ObjcUserData : public UserData {
 public:
  explicit ObjcUserData(id _Nullable input) : input_(input) {
  }

  /**
   * Validates that input is of type NSDictionary.
   *
   * The public API is typed as NSDictionary but we type 'input' as 'id'
   * since we can't trust Objective-C to verify the type for us.
   */
  NSDictionary<id, id>* RequireDictionary() const;

  template <typename T>
  T Cast() const {
    return static_cast<T>(input_);
  }

  bool has_value() const override {
    return static_cast<bool>(input_);
  }

  id value() const {
    return input_;
  }

 private:
  id _Nullable input_;
};

/**
 * An implementation of UserDataConverter that converts from Objective-C types
 * to C++ core values.
 */
class ObjcUserDataConverter : public UserDataConverter {
 public:
  using UserDataConverter::UserDataConverter;

  SetOptions ParseSetOptions(bool merge, const UserData& fields) const override;

  core::ParsedSetData ParseSetData(const UserData& api_input,
                                   const SetOptions& options) const override;

  core::ParsedUpdateData ParseUpdateData(const UserData& api_input) const override;

  FSTFieldValue* ParseQueryValue(const UserData& api_input) const override;

 private:
  std::set<model::FieldPath> ParseFieldMask(NSArray<id>* field_mask,
                                            const core::ParseAccumulator& accumulator) const;

  model::FieldPath ParseFieldPath(id field_path) const;

  /**
   * Internal helper for parsing user data.
   *
   * @param input Data to be parsed.
   * @param context A context object representing the current path being parsed, the source of the
   *   data being parsed, etc.
   *
   * @return The parsed value, or nil if the value was a FieldValue sentinel that should not be
   *   included in the resulting parsed data.
   */
  FSTFieldValue* _Nullable ParseData(id input, core::ParseContext&& context) const;

  FSTFieldValue* ParseDictionary(NSDictionary<NSString*, id>* dict,
                                 core::ParseContext&& context) const;

  FSTFieldValue* ParseArray(NSArray<id>* array, core::ParseContext&& context) const;

  /**
   * "Parses" the provided FIRFieldValue, adding any necessary transforms to
   * context.fieldTransforms.
   */
  void ParseSentinelFieldValue(FIRFieldValue* fieldValue, core::ParseContext&& context) const;

  /**
   * Helper to parse a scalar value (i.e. not an NSDictionary, NSArray, or FIRFieldValue).
   *
   * Note that it handles all NSNumber values that are encodable as int64_t or doubles
   * (depending on the underlying type of the NSNumber). Unsigned integer values are handled though
   * any value outside what is representable by int64_t (a signed 64-bit value) will throw an
   * exception.
   *
   * @return The parsed value.
   */
  FSTFieldValue* _Nullable ParseScalarValue(id _Nullable input, core::ParseContext&& context) const;

  FSTFieldValue* ParseTimestamp(FIRTimestamp* originalTimestamp) const;

  FSTFieldValue* ParseDocumentReference(FIRDocumentReference* ref,
                                        core::ParseContext&& context) const;

  FSTFieldValue* ParseDocumentKeyReference(FSTDocumentKeyReference* ref,
                                           core::ParseContext&& context) const;

  std::vector<FSTFieldValue*> ParseArrayTransformElements(NSArray<id>* elements) const;
};

}  // namespace api
}  // namespace firestore
}  // namespace firebase

NS_ASSUME_NONNULL_END

#endif  // FIRESTORE_SOURCE_API_OBJC_USER_DATA_CONVERTER_H_
