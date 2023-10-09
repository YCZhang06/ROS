cmake_minimum_required(VERSION 3.8)
project(communicate)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(plumbing REQUIRED)

add_executable(communicate src/communicate.cpp src/communicate_node.cpp)
target_include_directories(communicate PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
target_compile_features(communicate PUBLIC c_std_99 cxx_std_17)  
ament_target_dependencies(
  communicate
  "rclcpp"
  "std_msgs"
  "plumbing"
)

install(TARGETS communicate
  DESTINATION lib/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
