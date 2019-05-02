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

#ifndef FIRESTORE_CORE_SRC_FIREBASE_FIRESTORE_API_SET_OPTIONS_H_
#define FIRESTORE_CORE_SRC_FIREBASE_FIRESTORE_API_SET_OPTIONS_H_

#include <utility>

#include "Firestore/core/src/firebase/firestore/model/field_mask.h"
#include "absl/types/optional.h"

namespace firebase {
namespace firestore {
namespace api {

class SetOptions {
 public:
  /**
   * Returns an instance that can be used to change the behavior of set() calls
   * to that overwrites the entire document.
   */
  static SetOptions Overwrite();

  /**
   * Returns an instance that can be used to change the behavior of set() calls
   * to only replace the values specified in its data argument. Fields omitted
   * from the set() call will remain untouched.
   */
  static SetOptions Merge(bool merge = true);

  /**
   * Returns an instance that can be used to change the behavior of set() calls
   * to only replace the fields under field_mask. Any field that does not match
   * the field_mask is ignored and remains untouched.
   *
   * @param field_mask The mask of fields to merge.
   */
  static SetOptions MergeFields(model::FieldMask field_mask);

  bool merge() const {
    return merge_;
  }

  const absl::optional<model::FieldMask>& field_mask() const& {
    return field_mask_;
  }

  absl::optional<model::FieldMask> field_mask() && {
    return std::move(field_mask_);
  }

 private:
  SetOptions(bool merge, absl::optional<model::FieldMask> field_mask)
      : merge_(merge), field_mask_(std::move(field_mask)) {
  }

  bool merge_ = false;
  absl::optional<model::FieldMask> field_mask_;
};

bool operator==(const SetOptions& lhs, const SetOptions& rhs);

}  // namespace api
}  // namespace firestore
}  // namespace firebase

#endif  // FIRESTORE_CORE_SRC_FIREBASE_FIRESTORE_API_SET_OPTIONS_H_
