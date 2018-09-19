/*
 * Copyright 2018 Google
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

#ifndef FIRESTORE_CORE_SRC_FIREBASE_FIRESTORE_REMOTE_CONNECTIVITY_MONITOR_H_
#define FIRESTORE_CORE_SRC_FIREBASE_FIRESTORE_REMOTE_CONNECTIVITY_MONITOR_H_

#include <functional>
#include <memory>
#include <utility>
#include <vector>

#include "Firestore/core/src/firebase/firestore/util/async_queue.h"
#include "absl/types/optional.h"

namespace firebase {
namespace firestore {
namespace remote {

/**
 * A base class for monitoring changes in network connectivity; it is expected
 * that each platform will have its own system-dependent implementation.
 */
class ConnectivityMonitor {
 public:
   /**
    * The set of network states is deliberately simplified -- we only care about
    * states such that transition between them should break currently
    * established connections.
    */
  enum class NetworkStatus {
    Unavailable,
    Available,
    AvailableViaCellular,
  };

  using CallbackT = std::function<void(NetworkStatus)>;

  /** Creates a platform-specific connectivity monitor. */
  static std::unique_ptr<ConnectivityMonitor> Create(
      util::AsyncQueue* worker_queue);

  explicit ConnectivityMonitor(util::AsyncQueue* worker_queue)
      : worker_queue_{worker_queue} {
  }

  virtual ~ConnectivityMonitor() {
  }

  void AddCallback(CallbackT&& callback) {
    callbacks_.push_back(std::move(callback));
  }
  // TODO(varconst): RemoveCallback.

 protected:
  // The status may be retrieved asynchronously.
  void SetInitialStatus(NetworkStatus new_status);

  // Invokes callbacks on the worker queue if the status changed.
  void MaybeInvokeCallbacks(NetworkStatus new_status);

 private:
  util::AsyncQueue* worker_queue_ = nullptr;
  std::vector<CallbackT> callbacks_;
  absl::optional<NetworkStatus> status_;
};

}  // namespace remote
}  // namespace firestore
}  // namespace firebase

#endif  // FIRESTORE_CORE_SRC_FIREBASE_FIRESTORE_REMOTE_CONNECTIVITY_MONITOR_H_
