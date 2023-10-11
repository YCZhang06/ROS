cmake_minimum_required(VERSION 3.0.2)
project(communicate)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  message_generation
)

add_message_files(
  FILES
  Person.msg
)

add_service_files(
  FILES
  Multi.srv
)

generate_messages(
  DEPENDENCIES
  std_msgs
)

catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS roscpp std_msgs message_runtime
)

include_directories(
  ${catkin_INCLUDE_DIRS}
  ${PROJECT_SOURCE_DIR}/include
)

add_executable(topic src/topic.cpp src/topic_node.cpp)
add_dependencies(topic ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(topic
  ${catkin_LIBRARIES}
)
add_executable(server src/server.cpp src/server_node.cpp)
add_dependencies(server ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(server
  ${catkin_LIBRARIES}
)
add_executable(param src/param.cpp src/param_node.cpp)
add_dependencies(param ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(param
  ${catkin_LIBRARIES}
)