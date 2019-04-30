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

#include "Firestore/core/src/firebase/firestore/api/user_data_converter.h"

#include <utility>

#include "Firestore/core/src/firebase/firestore/api/set_options.h"
#include "Firestore/core/src/firebase/firestore/core/user_data.h"
#include "Firestore/core/src/firebase/firestore/model/database_id.h"

namespace firebase {
namespace firestore {
namespace api {

core::ParsedSetData UserDataConverter::ParseSetData(
    const UserData& input, const UserData& fields) const {
  SetOptions options = ParseSetOptions(true, fields);
  return ParseSetData(input, std::move(options));
}

}  // namespace api
}  // namespace firestore
}  // namespace firebase
