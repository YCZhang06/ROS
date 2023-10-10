cmake_minimum_required(VERSION 3.8)
project(communicate)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(plumbing REQUIRED)

add_executable(topic src/topic.cpp src/topic_node.cpp)
add_executable(server src/server.cpp src/server_node.cpp)
target_include_directories(topic PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
target_include_directories(server PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
target_compile_features(topic PUBLIC c_std_99 cxx_std_17)  
ament_target_dependencies(
  topic
  "rclcpp"
  "std_msgs"
  "plumbing"
)
ament_target_dependencies(
  server
  "rclcpp"
  "std_msgs"
  "plumbing"
)

install(TARGETS 
  topic
  server
  DESTINATION lib/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
