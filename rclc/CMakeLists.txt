cmake_minimum_required(VERSION 3.5)

project(rclc LANGUAGES C)

find_program(CLANG_TIDY clang-tidy)
if(CLANG_TIDY)
  set(CMAKE_CXX_CLANG_TIDY clang-tidy -checks=*)
endif()

find_package(ament_cmake_ros REQUIRED)
find_package(rcl REQUIRED)
find_package(rmw REQUIRED)
find_package(rmw_implementation REQUIRED)
find_package(rosidl_generator_c REQUIRED)
find_package(rosidl_typesupport_c REQUIRED)

ament_export_include_directories(include)

set(${PROJECT_NAME}_SRCS
  src/functions.c
  )

add_library(${PROJECT_NAME}
  ${${PROJECT_NAME}_SRCS}
  )

target_include_directories(${PROJECT_NAME}
  PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
  )

set_target_properties(${PROJECT_NAME} PROPERTIES
  C_STANDARD
    99
  C_STANDARD_REQUIRED
    YES
  )

ament_target_dependencies(${PROJECT_NAME}
  "rcl"
  "rosidl_typesupport_c"
  "rosidl_generator_c"
  )

target_compile_definitions(${PROJECT_NAME}
  PRIVATE
    "RCLC_BUILDING_DLL"
  )

ament_export_include_directories(${PROJECT_SOURCE_DIR}/include)
ament_export_libraries(${PROJECT_NAME})
ament_export_dependencies(
  rcl
  rosidl_typesupport_c
  rosidl_generator_c
  )

# if(BUILD_TESTING)
#   find_package(ament_lint_auto REQUIRED)
#   ament_lint_auto_find_test_dependencies()

#   add_subdirectory(test)
# endif()

ament_package()

install(
  TARGETS
    ${PROJECT_NAME}
  ARCHIVE DESTINATION
    lib
  LIBRARY DESTINATION
    lib
  RUNTIME DESTINATION
    bin
  )

install(
  DIRECTORY
    include/
  DESTINATION
    include
  )
