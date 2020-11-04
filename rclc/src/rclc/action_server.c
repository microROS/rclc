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

#include "rclc/action_client.h"

#include <rcl/error_handling.h>
#include <rcutils/logging_macros.h>

rcl_ret_t
rclc_action_server_init_default(
  rcl_action_server_t * action_server,
  const rcl_node_t * node,
  const rcl_clock_t * clock,
  const rosidl_action_type_support_t * type_support,
  const char * action_name)
{
  
  RCL_CHECK_FOR_NULL_WITH_MSG(
    action_server, "action client is a null pointer", return RCL_RET_INVALID_ARGUMENT);
  RCL_CHECK_FOR_NULL_WITH_MSG(
    node, "node is a null pointer", return RCL_RET_INVALID_ARGUMENT);
  RCL_CHECK_FOR_NULL_WITH_MSG(
    type_support, "type_support is a null pointer", return RCL_RET_INVALID_ARGUMENT);
  RCL_CHECK_FOR_NULL_WITH_MSG(
    action_name, "action_name is a null pointer", return RCL_RET_INVALID_ARGUMENT);

  rcl_action_server_options_t action_server_opt = rcl_action_server_get_default_options();
  rcl_ret_t rc = rcl_action_server_init(
    action_server,
    node,
    clock,
    type_support,
    action_name,
    &action_server_opt);
  if (rc != RCL_RET_OK) {
    PRINT_RCLC_ERROR(rclc_client_init_default, rcl_client_init);
  }
}
