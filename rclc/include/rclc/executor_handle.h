// Copyright (c) 2019 - for information on the respective copyright owner
// see the NOTICE file and/or the repository https://github.com/ros2/rclc.
// Copyright 2014 Open Source Robotics Foundation, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
#ifndef RCLC__EXECUTOR_HANDLE_H_
#define RCLC__EXECUTOR_HANDLE_H_

#if __cplusplus
extern "C"
{
#endif

#include <rcl/rcl.h>
#include <rcl_action/rcl_action.h>

/// TODO (jst3si) Where is this defined? - in my build environment this variable is not set.
// #define ROS_PACKAGE_NAME "rclc"

/// Enumeration for timer, subscription, guard conditions etc to be waited on.
typedef enum
{
  SUBSCRIPTION,
  TIMER,
  CLIENT,
  SERVICE,
  ACTION_CLIENT,
  GUARD_CONDITION,
  NONE
} rclc_executor_handle_type_t;

/// Enumeration for invocation type. ON_NEW_DATA calls a callback only when new data is available
/// ALWAYS calls the callback always, even if no data is available (e.g. for type FUNCTION_CALL)
typedef enum
{
  ON_NEW_DATA,
  ALWAYS
} rclc_executor_handle_invocation_t;


/// Type defintion for callback function.
typedef void (* rclc_callback_t)(const void *);

/// Type defintion for client callback function
/// First field: request message
/// Second field: request id
typedef void (* rclc_client_callback_t)(const void *, rmw_request_id_t *);

/// Type defintion for client callback function
/// First field: response message
/// Second field: request id
typedef void (* rclc_service_callback_t)(const void *, rmw_request_id_t *);

/// Type defintion for action client callbacks function
/// First field: request message
/// Second field: request id
typedef void (* rclc_action_client_goal_callback_t)(const void *, rmw_request_id_t *);
typedef void (* rclc_action_client_feedback_callback_t)(const void *);
typedef void (* rclc_action_client_result_callback_t)(const void *, rmw_request_id_t *);

/// Container for a handle.
typedef struct
{
  /// Type of handle
  rclc_executor_handle_type_t type;
  /// Invocation type determines when to execute the callback
  rclc_executor_handle_invocation_t invocation;
  /// Pointer to the handle
  union {
    rcl_subscription_t * subscription;
    rcl_timer_t * timer;
    rcl_client_t * client;
    rcl_service_t * service;
    rcl_guard_condition_t * gc;
    rcl_action_client_t * action_client;
  };

  /// Storage of data
  union {
    void * data;
    struct{
      void * ros_goal_response;
      rmw_request_id_t ros_goal_response_header;
      void * ros_feedback;
      void * ros_result_response;
      rmw_request_id_t ros_result_response_header;
    };
  };
  
  /// Storage for callbacks
  union {
    rclc_callback_t callback;
    struct {
      rclc_client_callback_t client_callback;
      rclc_service_callback_t service_callback;
    };
    struct {
      rclc_action_client_goal_callback_t action_client_goal_callback;
      rclc_action_client_feedback_callback_t action_client_feedback_callback;
      rclc_action_client_result_callback_t action_client_result_callback;
    };
  };

  /// Internal variable.
  /**  Denotes the index of this handle in the correspoding wait_set entry.
  *    (wait_set_subscriptions[index], wait_set_timers[index], ...
  *    is in the range [0,executor.max_handles), initialization: executor_max_handles
  *    because this value will never be assigned as an index in the wait_set.
  */
  size_t index;
  /// Internal variable. Flag, which is true, if the handle is initialized and therefore initialized
  bool initialized;
  /// Interval variable. Flag, which is true, if new data is available from DDS queue
  /// (is set after calling rcl_take)
  union {
    bool data_available;
    struct {
      bool feedback_available;
      bool status_available;
      bool goal_response_available;
      bool cancel_response_available;
      bool result_response_available;
    };
  };
  
} rclc_executor_handle_t;

/// Information about total number of subscriptions, guard_conditions, timers, subscription etc.
typedef struct
{
  /// Total number of subscriptions
  size_t number_of_subscriptions;
  /// Total number of timers
  size_t number_of_timers;
  /// Total number of clients
  size_t number_of_clients;
  /// Total number of services
  size_t number_of_services;
  /// Total number of action clients
  size_t number_of_action_clients;
  /// Total number of guard conditions
  size_t number_of_guard_conditions;
  /// Total number of events
  size_t number_of_events;
} rclc_executor_handle_counters_t;

/**
 * Initializes the counters of each handle type to zero.
 *
 * <hr>
 * Attribute          | Adherence
 * ------------------ | -------------
 * Allocates Memory   | No
 * Thread-Safe        | No
 * Uses Atomics       | No
 * Lock-Free          | Yes
 *
 * \param[inout] handle_counters preallocated rclc_executor_handle_counters_t
 * \return `RCL_RET_INVALID_ARGUMENT` if `handle_counters` is a null pointer
 */
rcl_ret_t
rclc_executor_handle_counters_zero_init(rclc_executor_handle_counters_t * handle_counters);

/**
 *  Initializes a handle with default values. The {@link rclc_executor_handle_t.index}
 *  is initialized with `max_handles`, which is a non-valid index. Note that, valid indicies
 *  are [0,max-handles-1]. The {@link rclc_executor_handle_t.invocation} is set to `ON_NEW_DATA`,
 *  so that a potential callback is invoced only whenever new data is received. All other member
 *  fields are set appropriate default values, like `none`, `NULL` or `false`.
 *
 *  * <hr>
 * Attribute          | Adherence
 * ------------------ | -------------
 * Allocates Memory   | No
 * Thread-Safe        | No
 * Uses Atomics       | No
 * Lock-Free          | Yes
 *
 * \param[inout] handle preallocated rclc_executor_handle_t
 * \param[in] max_handles maximum number of handles
 * \return `RCL_RET_OK` if the \p handle was initialized successfully
 * \return `RCL_RET_INVALID_ARGUMENT` if \p h is a null pointer
 */
rcl_ret_t
rclc_executor_handle_init(
  rclc_executor_handle_t * handle,
  size_t max_handles);

/**
 *  Resets a rclc_executor_handle_t. Compared to the function  {@link rclc_executor_handle_init()}
 *   only the {@link rclc_executor_handle_t.index} and {@link rclc_executor_handle_t.initialized}
 *   variables are reset to default values.
 *
 * <hr>
 * Attribute          | Adherence
 * ------------------ | -------------
 * Allocates Memory   | No
 * Thread-Safe        | No
 * Uses Atomics       | No
 * Lock-Free          | Yes
 *
 * \param[inout] handle a preallocated rclc_executor_handle_t
 * \param[in] max_handles maximum number of handles
 * \return `RCL_RET_OK` if \p h was cleared successfully
 * \return `RCL_RET_INVALID_ARGUMENT` if \p h is a null pointer
 */
rcl_ret_t
rclc_executor_handle_clear(
  rclc_executor_handle_t * handle,
  size_t max_handles);

/**
 *  Print out type name of a rclc_executor_handle_t.
 *
 * <hr>
 * Attribute          | Adherence
 * ------------------ | -------------
 * Allocates Memory   | No
 * Thread-Safe        | No
 * Uses Atomics       | No
 * Lock-Free          | Yes
 *
 * \param[inout] handle preallocated rclc_executor_handle_t
 * \return `RCL_RET_OK` if the handle was printed successfully
 * \return `RCL_RET_INVALID_ARGUMENT` if \p h is a null pointer
 */
rcl_ret_t
rclc_executor_handle_print(rclc_executor_handle_t * handle);

/**
 *  Returns a pointer to the rcl-handle stored in the rclc_executor_handle_t.
 *  That can be rcl_subscription_t or rcl_timer_t
 *
 *  If handle is NULL, then NULL is returned.
 *
 * <hr>
 * Attribute          | Adherence
 * ------------------ | -------------
 * Allocates Memory   | No
 * Thread-Safe        | No
 * Uses Atomics       | No
 * Lock-Free          | Yes
 *
 * \param[inout] handle preallocated rclc_executor_handle_t
 * \return pointer to the rcl-handle (rcl_subscription_t or rcl_timer_t)
 * \return NULL, if handle is a NULL pointer.
 */
void *
rclc_executor_handle_get_ptr(rclc_executor_handle_t * handle);

#if __cplusplus
}
#endif

#endif  // RCLC__EXECUTOR_HANDLE_H_
