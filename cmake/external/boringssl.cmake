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

if(TARGET boringssl)
  return()
endif()

# This ExternalProject unpacks itself inside the gRPC source tree. CMake clears
# the SOURCE_DIR when unpacking so this must come after grpc despite the fact
# that grpc logically depends upon this.

# This commit is from chromium-stable-with-bazel@{2018-10-26}. It matches gRPC
# v1.20.1.

# chromium-stable-with-bazel@{2018-10-26}
set(commit afc30d43eef92979b05776ec0963c9cede5fb80f)

ExternalProject_Add(
  boringssl
  DEPENDS
    grpc-download

  DOWNLOAD_DIR ${FIREBASE_DOWNLOAD_DIR}
  DOWNLOAD_NAME boringssl-${commit}.tar.gz
  URL https://github.com/google/boringssl/archive/${commit}.tar.gz
  URL_HASH SHA256=2b18e1c1ad15cc180529ababde8a62885ac35005131e9a797cdaf0e07d76a767

  PREFIX ${PROJECT_BINARY_DIR}
  SOURCE_DIR ${PROJECT_BINARY_DIR}/src/grpc/third_party/boringssl

  CONFIGURE_COMMAND ""
  BUILD_COMMAND     ""
  INSTALL_COMMAND   ""
  TEST_COMMAND      ""
)
