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

#include "rclc/client.h"

#include <rcl/error_handling.h>
#include <rcutils/logging_macros.h>

rcl_ret_t
rclc_client_init_default(
  rcl_client_t * client,
  const rcl_node_t * node,
  const rosidl_service_type_support_t * type_support,
  const char * topic_name)
{
  /*
  RCL_CHECK_FOR_NULL_WITH_MSG(
    client, "client is a null pointer", return RCL_RET_INVALID_ARGUMENT);
  RCL_CHECK_FOR_NULL_WITH_MSG(
    node, "node is a null pointer", return RCL_RET_INVALID_ARGUMENT);
  RCL_CHECK_FOR_NULL_WITH_MSG(
    type_support, "type_support is a null pointer", return RCL_RET_INVALID_ARGUMENT);
  RCL_CHECK_FOR_NULL_WITH_MSG(
    topic_name, "topic_name is a null pointer", return RCL_RET_INVALID_ARGUMENT);

  rcl_client_options_t client_opt = rcl_client_get_default_options();
  rcl_ret_t rc = rcl_client_init(
    client,
    node,
    type_support,
    topic_name,
    &client_opt);
  if (rc != RCL_RET_OK) {
    PRINT_RCLC_ERROR(rclc_client_init_default, rcl_client_init);
  }
  */
  rcl_ret_t rc = RCL_RET_OK;
  return rc;
}

rcl_ret_t
rclc_client_init_best_effort(
  rcl_client_t * client,
  const rcl_node_t * node,
  const rosidl_service_type_support_t * type_support,
  const char * topic_name)
{
  /*
  RCL_CHECK_FOR_NULL_WITH_MSG(
    client, "client is a null pointer", return RCL_RET_INVALID_ARGUMENT);
  RCL_CHECK_FOR_NULL_WITH_MSG(
    node, "node is a null pointer", return RCL_RET_INVALID_ARGUMENT);
  RCL_CHECK_FOR_NULL_WITH_MSG(
    type_support, "type_support is a null pointer", return RCL_RET_INVALID_ARGUMENT);
  RCL_CHECK_FOR_NULL_WITH_MSG(
    topic_name, "topic_name is a null pointer", return RCL_RET_INVALID_ARGUMENT);

  rcl_client_options_t client_opt = rcl_client_get_default_options();
  client_opt.qos.reliability = RMW_QOS_POLICY_RELIABILITY_BEST_EFFORT;
  rcl_ret_t rc = rcl_client_init(
    client,
    node,
    type_support,
    topic_name,
    &client_opt);
  if (rc != RCL_RET_OK) {
    PRINT_RCLC_ERROR(rclc_client_init_best_effort, rcl_client_init);
  }
  */
  rcl_ret_t rc = RCL_RET_OK;
  return rc;
}
