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

#ifndef FIRESTORE_CORE_SRC_FIREBASE_FIRESTORE_API_USER_DATA_CONVERTER_H_
#define FIRESTORE_CORE_SRC_FIREBASE_FIRESTORE_API_USER_DATA_CONVERTER_H_

#include "Firestore/core/src/firebase/firestore/model/database_id.h"
#include "Firestore/core/src/firebase/firestore/objc/objc_class.h"

OBJC_CLASS(FSTFieldValue);

namespace firebase {
namespace firestore {
namespace core {

class ParsedSetData;
class ParsedUpdateData;

}  // namespace core

namespace api {

class SetOptions;

/**
 * An opaque type to hold user input. Different language bindings subclass this
 * type to embed values particular to that binding.
 *
 * The language binding should also subclass `UserDataConverter` and each
 * method will need to cast from `UserData` to the type that's specific to that
 * implementation.
 */
class UserData {
 public:
  virtual ~UserData() {
  }

  virtual bool has_value() const {
    return false;
  }

  static UserData Null() {
    return UserData();
  }
};

/**
 * An abstract class declaring how to convert user input to Firestore internal
 * types. User input is opaque to this interface, but the results are not.
 *
 * This makes it possible for different language bindings to effectively tunnel
 * language-specific input values into the core API without having to arrange
 * for conversion to happen purely at the boundary between the binding and the
 * core API.
 */
class UserDataConverter {
 public:
  explicit UserDataConverter(const model::DatabaseId* database_id)
      : database_id_(database_id) {
  }

  virtual ~UserDataConverter() {
  }

  /**
   * Parses the merge and field mask arguments in a set with merge fields call.
   */
  virtual SetOptions ParseSetOptions(bool merge,
                                     const UserData& fields) const = 0;

  /** Parses user data from a SetData call. */
  virtual core::ParsedSetData ParseSetData(const UserData& input,
                                           const SetOptions& options) const = 0;

  virtual core::ParsedSetData ParseSetData(const UserData& input,
                                           const UserData& fields) const;

  /** Parses user data from an UpdateData call. */
  virtual core::ParsedUpdateData ParseUpdateData(
      const UserData& input) const = 0;

  /** Parses user data for an argument to a Query function. */
  virtual FSTFieldValue* ParseQueryValue(const UserData& input) const = 0;

 protected:
  const model::DatabaseId* database_id_;
};

}  // namespace api
}  // namespace firestore
}  // namespace firebase

#endif  // FIRESTORE_CORE_SRC_FIREBASE_FIRESTORE_API_USER_DATA_CONVERTER_H_
