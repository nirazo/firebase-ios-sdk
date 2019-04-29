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

#import <Foundation/Foundation.h>

#include "Firestore/core/src/firebase/firestore/core/user_data.h"
#include "Firestore/core/src/firebase/firestore/model/database_id.h"

@class FSTObjectValue;
@class FSTFieldValue;
@class FSTMutation;

namespace core = firebase::firestore::core;
namespace model = firebase::firestore::model;

NS_ASSUME_NONNULL_BEGIN

/**
 * An interface that allows arbitrary pre-converting of user data.
 *
 * Returns the converted value (can return back the input to act as a no-op).
 */
typedef id _Nullable (^FSTPreConverterBlock)(id _Nullable);

/**
 * Helper for parsing raw user input (provided via the API) into internal model classes.
 */
@interface FSTUserDataConverter : NSObject

- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithDatabaseID:(const model::DatabaseId *)databaseID
                      preConverter:(FSTPreConverterBlock)preConverter NS_DESIGNATED_INITIALIZER;

/** Parse document data from a non-merge setData call.*/
- (core::ParsedSetData)parsedSetData:(id)input;

/** Parse document data from a setData call with `merge:YES`. */
- (core::ParsedSetData)parsedMergeData:(id)input fieldMask:(nullable NSArray<id> *)fieldMask;

/** Parse update data from an updateData call. */
- (core::ParsedUpdateData)parsedUpdateData:(id)input;

/** Parse a "query value" (e.g. value in a where filter or a value in a cursor bound). */
- (FSTFieldValue *)parsedQueryValue:(id)input;

@end

NS_ASSUME_NONNULL_END
