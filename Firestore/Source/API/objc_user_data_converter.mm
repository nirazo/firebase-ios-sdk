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

#include "Firestore/Source/API/objc_user_data_converter.h"

#include <string>
#include <utility>

#import "Firestore/Source/API/FIRDocumentReference+Internal.h"
#import "Firestore/Source/API/FIRFieldPath+Internal.h"
#import "Firestore/Source/API/FIRFieldValue+Internal.h"
#import "Firestore/Source/API/FIRFirestore+Internal.h"
#import "Firestore/Source/API/FIRGeoPoint+Internal.h"
#import "Firestore/Source/API/FIRTimestamp+Internal.h"
#import "Firestore/Source/API/FSTDocumentKeyReference.h"

#include "Firestore/core/src/firebase/firestore/api/set_options.h"
#include "Firestore/core/src/firebase/firestore/core/user_data.h"

NS_ASSUME_NONNULL_BEGIN

namespace firebase {
namespace firestore {
namespace api {

using core::ParseAccumulator;
using core::ParseContext;
using core::UserDataSource;
using model::ArrayTransform;
using model::DatabaseId;
using model::FieldMask;
using model::FieldPath;
using model::FieldValue;
using model::NumericIncrementTransform;
using model::ServerTimestampTransform;
using model::TransformOperation;

static const ObjcUserData& Cast(const UserData& api_input) {
  return static_cast<const ObjcUserData&>(api_input);
}

NSDictionary<id, id>* ObjcUserData::RequireDictionary() const {
  if (![input_ isKindOfClass:[NSDictionary class]]) {
    ThrowInvalidArgument("Data to be written must be an NSDictionary.");
  }
  return input_;
}

SetOptions ObjcUserDataConverter::ParseSetOptions(bool merge, const UserData& api_fields) const {
  if (!merge) {
    return SetOptions::Overwrite();
  }

  const ObjcUserData& fields = Cast(api_fields);
  if (!fields.has_value()) {
    // In the Objective-C API, mergeFields takes a nullable NSArray, where the
    // nil value means merge-all, and a non-nil value means a list of specific
    // fields to merge.
    return SetOptions::Merge();
  }

  ParseAccumulator accumulator{UserDataSource::Set};
  std::set<FieldPath> field_paths = ParseFieldMask(fields.Cast<NSArray<id>*>(), accumulator);
  return SetOptions::MergeFields(FieldMask(std::move(field_paths)));
}

core::ParsedSetData ObjcUserDataConverter::ParseSetData(const UserData& api_input,
                                                        const SetOptions& options) const {
  const ObjcUserData& input = Cast(api_input);
  input.RequireDictionary();

  UserDataSource source = options.merge() ? UserDataSource::MergeSet : UserDataSource::Set;
  ParseAccumulator accumulator{source};

  FSTFieldValue* value = ParseData(input.value(), accumulator.RootContext());
  auto object_value = static_cast<FSTObjectValue*>(value);

  if (!options.merge()) {
    return std::move(accumulator).SetData(object_value);
  }

  auto& field_mask = options.field_mask();
  if (!field_mask.has_value()) {
    return std::move(accumulator).MergeData(object_value);
  }

  return std::move(accumulator).MergeData(object_value, field_mask.value());
}

core::ParsedUpdateData ObjcUserDataConverter::ParseUpdateData(const UserData& api_input) const {
  const ObjcUserData& input = Cast(api_input);
  NSDictionary<id, id>* dict = input.RequireDictionary();

  ParseAccumulator accumulator{UserDataSource::Update};
  __block ParseContext context = accumulator.RootContext();
  __block FSTObjectValue* updateData = [FSTObjectValue objectValue];

  [dict enumerateKeysAndObjectsUsingBlock:^(id key, id value, BOOL* stop) {
    FieldPath path;

    if ([key isKindOfClass:[NSString class]]) {
      path = FieldPath::FromDotSeparatedString(util::MakeString(key));
    } else if ([key isKindOfClass:[FIRFieldPath class]]) {
      path = ((FIRFieldPath*)key).internalValue;
    } else {
      ThrowInvalidArgument("Dictionary keys in updateData: must be NSStrings or FIRFieldPaths.");
    }

    if ([value isKindOfClass:[FSTDeleteFieldValue class]]) {
      // Add it to the field mask, but don't add anything to updateData.
      context.AddToFieldMask(std::move(path));
    } else {
      FSTFieldValue* _Nullable parsedValue = ParseData(value, context.ChildContext(path));
      if (parsedValue) {
        context.AddToFieldMask(path);
        updateData = [updateData objectBySettingValue:parsedValue forPath:path];
      }
    }
  }];

  return std::move(accumulator).UpdateData(updateData);
}

FSTFieldValue* ObjcUserDataConverter::ParseQueryValue(const UserData& api_input) const {
  const ObjcUserData& input = Cast(api_input);

  ParseAccumulator accumulator{UserDataSource::Argument};

  FSTFieldValue* parsed = ParseData(input.value(), accumulator.RootContext());
  HARD_ASSERT(parsed, "Parsed data should not be nil.");
  HARD_ASSERT(accumulator.field_transforms().empty(),
              "Field transforms should have been disallowed.");
  return parsed;
}

std::set<FieldPath> ObjcUserDataConverter::ParseFieldMask(
    NSArray<id>* field_mask, const ParseAccumulator& accumulator) const {
  std::set<FieldPath> result;
  for (id field_path in field_mask) {
    FieldPath path = ParseFieldPath(field_path);

    // Verify that all elements specified in the field mask are part of the parsed context.
    if (!accumulator.Contains(path)) {
      ThrowInvalidArgument(
          "Field '%s' is specified in your field mask but missing from your input data.",
          path.CanonicalString());
    }

    result.insert(path);
  }

  return result;
}

FieldPath ObjcUserDataConverter::ParseFieldPath(id field_path) const {
  if ([field_path isKindOfClass:[NSString class]]) {
    return FieldPath::FromDotSeparatedString(util::MakeString(field_path));
  } else if ([field_path isKindOfClass:[FIRFieldPath class]]) {
    return ((FIRFieldPath*)field_path).internalValue;
  } else {
    ThrowInvalidArgument("All elements in mergeFields: must be NSStrings or FIRFieldPaths.");
  }
}

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
FSTFieldValue* _Nullable ObjcUserDataConverter::ParseData(id input, ParseContext&& context) const {
  if ([input isKindOfClass:[NSDictionary class]]) {
    return ParseDictionary(static_cast<NSDictionary<NSString*, id>*>(input), std::move(context));

  } else if ([input isKindOfClass:[FIRFieldValue class]]) {
    // FieldValues usually parse into transforms (except FieldValue.delete()) in which case we
    // do not want to include this field in our parsed data (as doing so will overwrite the field
    // directly prior to the transform trying to transform it). So we don't call appendToFieldMask
    // and we return nil as our parsing result.
    ParseSentinelFieldValue(static_cast<FIRFieldValue*>(input), std::move(context));
    return nil;

  } else {
    // If context path is unset we are already inside an array and we don't support field mask paths
    // more granular than the top-level array.
    if (context.path()) {
      context.AddToFieldMask(*context.path());
    }

    if ([input isKindOfClass:[NSArray class]]) {
      // TODO(b/34871131): Include the path containing the array in the error message.
      if (context.array_element()) {
        ThrowInvalidArgument("Nested arrays are not supported");
      }
      return ParseArray(static_cast<NSArray<id>*>(input), std::move(context));
    } else {
      return ParseScalarValue(input, std::move(context));
    }
  }
}

FSTFieldValue* ObjcUserDataConverter::ParseDictionary(NSDictionary<NSString*, id>* dict,
                                                      ParseContext&& context) const {
  NSMutableDictionary<NSString*, FSTFieldValue*>* result =
      [NSMutableDictionary dictionaryWithCapacity:dict.count];

  if ([dict count] == 0) {
    const FieldPath* path = context.path();
    if (path && !path->empty()) {
      context.AddToFieldMask(*path);
    }
    return [FSTObjectValue objectValue];
  } else {
    [dict enumerateKeysAndObjectsUsingBlock:^(NSString* user_key, id value, BOOL* stop) {
      std::string key = util::MakeString(user_key);
      FSTFieldValue* _Nullable parsed_value = ParseData(value, context.ChildContext(key));
      if (parsed_value) {
        result[user_key] = parsed_value;
      }
    }];
  }
  return [[FSTObjectValue alloc] initWithDictionary:result];
}

FSTFieldValue* ObjcUserDataConverter::ParseArray(NSArray<id>* array, ParseContext&& context) const {
  NSMutableArray<FSTFieldValue*>* result = [NSMutableArray arrayWithCapacity:array.count];
  [array enumerateObjectsUsingBlock:^(id entry, NSUInteger idx, BOOL* stop) {
    FSTFieldValue* _Nullable parsed_entry = ParseData(entry, context.ChildContext(idx));
    if (!parsed_entry) {
      // Just include nulls in the array for fields being replaced with a sentinel.
      parsed_entry = [FSTNullValue nullValue];
    }
    [result addObject:parsed_entry];
  }];
  return [[FSTArrayValue alloc] initWithValueNoCopy:result];
}

/**
 * "Parses" the provided FIRFieldValue, adding any necessary transforms to
 * context.fieldTransforms.
 */
void ObjcUserDataConverter::ParseSentinelFieldValue(FIRFieldValue* fieldValue,
                                                    ParseContext&& context) const {
  // Sentinels are only supported with writes, and not within arrays.
  if (!context.write()) {
    ThrowInvalidArgument("%s can only be used with updateData() and setData()%s",
                         fieldValue.methodName, context.FieldDescription());
  }
  if (!context.path()) {
    ThrowInvalidArgument("%s is not currently supported inside arrays", fieldValue.methodName);
  }

  if ([fieldValue isKindOfClass:[FSTDeleteFieldValue class]]) {
    if (context.data_source() == UserDataSource::MergeSet) {
      // No transform to add for a delete, but we need to add it to our fieldMask so it gets
      // deleted.
      context.AddToFieldMask(*context.path());

    } else if (context.data_source() == UserDataSource::Update) {
      HARD_ASSERT(context.path()->size() > 0,
                  "FieldValue.delete() at the top level should have already been handled.");
      ThrowInvalidArgument("FieldValue.delete() can only appear at the top level of your "
                           "update data%s",
                           context.FieldDescription());
    } else {
      // We shouldn't encounter delete sentinels for queries or non-merge setData calls.
      ThrowInvalidArgument(
          "FieldValue.delete() can only be used with updateData() and setData() with merge:true%s",
          context.FieldDescription());
    }

  } else if ([fieldValue isKindOfClass:[FSTServerTimestampFieldValue class]]) {
    context.AddToFieldTransforms(*context.path(), absl::make_unique<ServerTimestampTransform>(
                                                      ServerTimestampTransform::Get()));

  } else if ([fieldValue isKindOfClass:[FSTArrayUnionFieldValue class]]) {
    std::vector<FSTFieldValue*> parsedElements =
        ParseArrayTransformElements(static_cast<FSTArrayUnionFieldValue*>(fieldValue).elements);
    auto array_union = absl::make_unique<ArrayTransform>(TransformOperation::Type::ArrayUnion,
                                                         std::move(parsedElements));
    context.AddToFieldTransforms(*context.path(), std::move(array_union));

  } else if ([fieldValue isKindOfClass:[FSTArrayRemoveFieldValue class]]) {
    std::vector<FSTFieldValue*> parsedElements =
        ParseArrayTransformElements(static_cast<FSTArrayRemoveFieldValue*>(fieldValue).elements);
    auto array_remove = absl::make_unique<ArrayTransform>(TransformOperation::Type::ArrayRemove,
                                                          std::move(parsedElements));
    context.AddToFieldTransforms(*context.path(), std::move(array_remove));

  } else if ([fieldValue isKindOfClass:[FSTNumericIncrementFieldValue class]]) {
    NSNumber* number = static_cast<FSTNumericIncrementFieldValue*>(fieldValue).operand;
    FSTFieldValue* parsed = ParseQueryValue(ObjcUserData(number));
    auto numeric_increment =
        absl::make_unique<NumericIncrementTransform>(static_cast<FSTNumberValue*>(parsed));

    context.AddToFieldTransforms(*context.path(), std::move(numeric_increment));

  } else {
    HARD_FAIL("Unknown FIRFieldValue type: %s", NSStringFromClass([fieldValue class]));
  }
}

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
FSTFieldValue* _Nullable ObjcUserDataConverter::ParseScalarValue(id _Nullable input,
                                                                 ParseContext&& context) const {
  if (!input || [input isMemberOfClass:[NSNull class]]) {
    return [FSTNullValue nullValue];

  } else if ([input isKindOfClass:[NSNumber class]]) {
    // Recover the underlying type of the number, using the method described here:
    // http://stackoverflow.com/questions/2518761/get-type-of-nsnumber
    const char* cType = [input objCType];

    // Type Encoding values taken from
    // https://developer.apple.com/library/mac/documentation/Cocoa/Conceptual/ObjCRuntimeGuide/
    // Articles/ocrtTypeEncodings.html
    switch (cType[0]) {
      case 'q':
        return [FSTIntegerValue integerValue:[input longLongValue]];

      case 'i':  // Falls through.
      case 's':  // Falls through.
      case 'l':  // Falls through.
      case 'I':  // Falls through.
      case 'S':
        // Coerce integer values that aren't long long. Allow unsigned integer types that are
        // guaranteed small enough to skip a length check.
        return [FSTIntegerValue integerValue:[input longLongValue]];

      case 'L':  // Falls through.
      case 'Q':
        // Unsigned integers that could be too large. Note that the 'L' (long) case is handled here
        // because when compiled for LP64, unsigned long is 64 bits and could overflow int64_t.
        {
          unsigned long long extended = [input unsignedLongLongValue];

          if (extended > LLONG_MAX) {
            ThrowInvalidArgument("NSNumber (%s) is too large%s", [input unsignedLongLongValue],
                                 context.FieldDescription());

          } else {
            return [FSTIntegerValue integerValue:(int64_t)extended];
          }
        }

      case 'f':
        return [FSTDoubleValue doubleValue:[input doubleValue]];

      case 'd':
        // Double values are already the right type, so just reuse the existing boxed double.
        //
        // Note that NSNumber already performs NaN normalization to a single shared instance
        // so there's no need to treat NaN specially here.
        return [FSTDoubleValue doubleValue:[input doubleValue]];

      case 'B':  // Falls through.
      case 'c':  // Falls through.
      case 'C':
        // Boolean values are weird.
        //
        // On arm64, objCType of a BOOL-valued NSNumber will be "c", even though @encode(BOOL)
        // returns "B". "c" is the same as @encode(signed char). Unfortunately this means that
        // legitimate usage of signed chars is impossible, but this should be rare.
        //
        // Additionally, for consistency, map unsigned chars to bools in the same way.
        return FieldValue::FromBoolean([input boolValue]).Wrap();

      default:
        // All documented codes should be handled above, so this shouldn't happen.
        HARD_FAIL("Unknown NSNumber objCType %s on %s", cType, input);
    }

  } else if ([input isKindOfClass:[NSString class]]) {
    return FieldValue::FromString(util::MakeString(input)).Wrap();

  } else if ([input isKindOfClass:[NSDate class]]) {
    return [FSTTimestampValue timestampValue:[FIRTimestamp timestampWithDate:input]];

  } else if ([input isKindOfClass:[FIRTimestamp class]]) {
    return ParseTimestamp(static_cast<FIRTimestamp*>(input));

  } else if ([input isKindOfClass:[FIRGeoPoint class]]) {
    return [FSTGeoPointValue geoPointValue:input];

  } else if ([input isKindOfClass:[NSData class]]) {
    return [FSTBlobValue blobValue:input];

  } else if ([input isKindOfClass:[FIRDocumentReference class]]) {
    return ParseDocumentReference(static_cast<FIRDocumentReference*>(input), std::move(context));

  } else if ([input isKindOfClass:[FSTDocumentKeyReference class]]) {
    return ParseDocumentKeyReference(static_cast<FSTDocumentKeyReference*>(input),
                                     std::move(context));

  } else {
    ThrowInvalidArgument("Unsupported type: %s%s", NSStringFromClass([input class]),
                         context.FieldDescription());
  }
}

FSTFieldValue* ObjcUserDataConverter::ParseTimestamp(FIRTimestamp* originalTimestamp) const {
  FIRTimestamp* truncatedTimestamp =
      [FIRTimestamp timestampWithSeconds:originalTimestamp.seconds
                             nanoseconds:originalTimestamp.nanoseconds / 1000 * 1000];
  return [FSTTimestampValue timestampValue:truncatedTimestamp];
}

FSTFieldValue* ObjcUserDataConverter::ParseDocumentReference(FIRDocumentReference* ref,
                                                             ParseContext&& context) const {
  return ParseDocumentKeyReference(
      [[FSTDocumentKeyReference alloc] initWithKey:ref.key databaseID:ref.firestore.databaseID],
      std::move(context));
}

FSTFieldValue* ObjcUserDataConverter::ParseDocumentKeyReference(FSTDocumentKeyReference* ref,
                                                                ParseContext&& context) const {
  const DatabaseId& this_id = database_id();
  const DatabaseId& other_id = *ref.databaseID;
  if (this_id != other_id) {
    ThrowInvalidArgument(
        "Document Reference is for database %s/%s but should be for database %s/%s%s",
        other_id.project_id(), other_id.database_id(), this_id.project_id(), this_id.database_id(),
        context.FieldDescription());
  }
  return [FSTReferenceValue referenceValue:[FSTDocumentKey keyWithDocumentKey:ref.key]
                                databaseID:&this_id];
}

std::vector<FSTFieldValue*> ObjcUserDataConverter::ParseArrayTransformElements(
    NSArray<id>* elements) const {
  ParseAccumulator accumulator{UserDataSource::Argument};

  std::vector<FSTFieldValue*> values;
  for (NSUInteger i = 0; i < elements.count; i++) {
    id element = elements[i];
    // Although array transforms are used with writes, the actual elements being unioned or removed
    // are not considered writes since they cannot contain any FieldValue sentinels, etc.
    ParseContext context = accumulator.RootContext();

    FSTFieldValue* parsedElement = ParseData(element, context.ChildContext(i));
    HARD_ASSERT(parsedElement && accumulator.field_transforms().size() == 0,
                "Failed to properly parse array transform element: %s", element);
    values.push_back(parsedElement);
  }
  return values;
}

}  // namespace api
}  // namespace firestore
}  // namespace firebase

NS_ASSUME_NONNULL_END
