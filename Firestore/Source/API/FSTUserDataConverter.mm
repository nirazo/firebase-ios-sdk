/*
 * Copyright 2017 Google
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

#import "Firestore/Source/API/FSTUserDataConverter.h"

#include <memory>

#import "Firestore/Source/API/objc_user_data_converter.h"

#include "Firestore/core/src/firebase/firestore/api/set_options.h"

NS_ASSUME_NONNULL_BEGIN

namespace util = firebase::firestore::util;
using firebase::firestore::api::ObjcUserData;
using firebase::firestore::api::ObjcUserDataConverter;
using firebase::firestore::api::SetOptions;
using firebase::firestore::api::UserDataConverter;
using firebase::firestore::core::ParsedSetData;
using firebase::firestore::core::ParsedUpdateData;
using firebase::firestore::model::DatabaseId;
using firebase::firestore::model::DocumentKey;

using Objc = firebase::firestore::api::ObjcUserData;

@implementation FSTUserDataConverter {
  std::shared_ptr<UserDataConverter> _wrapped;
}

- (instancetype)initWithDatabaseID:(const DatabaseId *)databaseID {
  self = [super init];
  if (self) {
    _wrapped = std::make_shared<ObjcUserDataConverter>(databaseID);
  }
  return self;
}

- (ParsedSetData)parsedSetData:(id)input {
  return _wrapped->ParseSetData(Objc(input), SetOptions::Overwrite());
}

- (ParsedSetData)parsedMergeData:(id)input fieldMask:(nullable NSArray<id> *)fieldMask {
  return _wrapped->ParseSetData(Objc(input), Objc(fieldMask));
}

- (ParsedUpdateData)parsedUpdateData:(id)input {
  return _wrapped->ParseUpdateData(Objc(input));
}

- (FSTFieldValue *)parsedQueryValue:(id)input {
  return _wrapped->ParseQueryValue(Objc(input));
}

@end

NS_ASSUME_NONNULL_END
