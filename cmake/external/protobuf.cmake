# Copyright 2018 Google
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

include(ExternalProject)

if(TARGET protobuf)
  return()
endif()

# This ExternalProject unpacks itself inside the gRPC source tree. CMake clears
# the SOURCE_DIR when unpacking so this must come after grpc despite the fact
# that grpc logically depends upon this.

set(version 3.7.0)

ExternalProject_Add(
  protobuf
  DEPENDS
    grpc-download

  DOWNLOAD_DIR ${FIREBASE_DOWNLOAD_DIR}
  DOWNLOAD_NAME protobuf-v${version}.tar.gz
  URL https://github.com/google/protobuf/archive/v${version}.tar.gz
  URL_HASH SHA256=a19dcfe9d156ae45d209b15e0faed5c7b5f109b6117bfc1974b6a7b98a850320

  PREFIX ${PROJECT_BINARY_DIR}
  SOURCE_DIR ${PROJECT_BINARY_DIR}/src/grpc/third_party/protobuf

  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
  TEST_COMMAND ""
)
