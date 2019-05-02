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

#include "Firestore/core/src/firebase/firestore/api/set_options.h"

namespace firebase {
namespace firestore {
namespace api {

using model::FieldMask;

SetOptions SetOptions::Overwrite() {
  return Merge(false);
}

SetOptions SetOptions::Merge(bool merge) {
  return SetOptions(merge, absl::nullopt);
}

SetOptions SetOptions::MergeFields(FieldMask field_mask) {
  return SetOptions(/*merge=*/true, std::move(field_mask));
}

bool operator==(const SetOptions& lhs, const SetOptions& rhs);

}  // namespace api
}  // namespace firestore
}  // namespace firebase
