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
#include "test_msgs/srv/basic_types.h"
#include <gtest/gtest.h>
#include <rclc/rclc.h>

TEST(Test, rclc_service_init_default) {
  rclc_support_t support;
  rcl_ret_t rc;

  // preliminary setup
  rcl_allocator_t allocator = rcl_get_default_allocator();
  rc = rclc_support_init(&support, 0, nullptr, &allocator);
  const char * my_name = "test_name";
  const char * my_namespace = "test_namespace";
  rcl_node_t node = rcl_get_zero_initialized_node();
  rc = rclc_node_init_default(&node, my_name, my_namespace, &support);

  // test with valid arguments
  rcl_service_t service = rcl_get_zero_initialized_service();
  const rosidl_service_type_support_t * type_support =
    ROSIDL_GET_SRV_TYPE_SUPPORT(test_msgs, srv, BasicTypes);
  rc = rclc_service_init_default(&service, &node, type_support, "topic1");
  EXPECT_EQ(RCL_RET_OK, rc);
/*
  // tests with invalid arguments
  rc = rclc_service_init_default(nullptr, &node, type_support, "topic1");
  EXPECT_EQ(RCL_RET_INVALID_ARGUMENT, rc);
  rcutils_reset_error();
  rc = rclc_service_init_default(&service, nullptr, type_support, "topic1");
  EXPECT_EQ(RCL_RET_INVALID_ARGUMENT, rc);
  rcutils_reset_error();
  rc = rclc_service_init_default(&service, &node, nullptr, "topic1");
  EXPECT_EQ(RCL_RET_INVALID_ARGUMENT, rc);
  rcutils_reset_error();
  rc = rclc_service_init_default(&service, &node, type_support, nullptr);
  EXPECT_EQ(RCL_RET_INVALID_ARGUMENT, rc);
  rcutils_reset_error();

  */
  // clean up
  rc = rcl_service_fini(&service, &node);
  EXPECT_EQ(RCL_RET_OK, rc);
  rc = rcl_node_fini(&node);
  EXPECT_EQ(RCL_RET_OK, rc);
  rc = rclc_support_fini(&support);
  EXPECT_EQ(RCL_RET_OK, rc);
}

/*
TEST(Test, rclc_service_init_best_effort) {
  rclc_support_t support;
  rcl_ret_t rc;

  // preliminary setup
  rcl_allocator_t allocator = rcl_get_default_allocator();
  rc = rclc_support_init(&support, 0, nullptr, &allocator);
  const char * my_name = "test_name";
  const char * my_namespace = "test_namespace";
  rcl_node_t node = rcl_get_zero_initialized_node();
  rc = rclc_node_init_default(&node, my_name, my_namespace, &support);

  // test with valid arguments
  rcl_service_t service = rcl_get_zero_initialized_service();
  const rosidl_service_type_support_t * type_support =
    ROSIDL_GET_SRV_TYPE_SUPPORT(std_msgs, msg, Int32);
  rc = rclc_service_init_best_effort(&service, &node, type_support, "topic1");
  EXPECT_EQ(RCL_RET_OK, rc);

  // check for qos-option best effort
  const rcl_service_options_t * srv_options = rcl_service_get_options(&service);
  EXPECT_EQ(srv_options->qos.reliability, RMW_QOS_POLICY_RELIABILITY_BEST_EFFORT);
  // tests with invalid arguments
  rc = rclc_service_init_best_effort(nullptr, &node, type_support, "topic1");
  EXPECT_EQ(RCL_RET_INVALID_ARGUMENT, rc);
  rcutils_reset_error();
  rc = rclc_service_init_best_effort(&service, nullptr, type_support, "topic1");
  EXPECT_EQ(RCL_RET_INVALID_ARGUMENT, rc);
  rcutils_reset_error();
  rc = rclc_service_init_best_effort(&service, &node, nullptr, "topic1");
  EXPECT_EQ(RCL_RET_INVALID_ARGUMENT, rc);
  rcutils_reset_error();
  rc = rclc_service_init_best_effort(&service, &node, type_support, nullptr);
  EXPECT_EQ(RCL_RET_INVALID_ARGUMENT, rc);
  rcutils_reset_error();
  // clean up
  rc = rcl_service_fini(&service, &node);
  EXPECT_EQ(RCL_RET_OK, rc);
  rc = rcl_node_fini(&node);
  EXPECT_EQ(RCL_RET_OK, rc);
  rc = rclc_support_fini(&support);
  EXPECT_EQ(RCL_RET_OK, rc);
}
*/
