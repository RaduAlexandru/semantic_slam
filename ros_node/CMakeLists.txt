cmake_minimum_required(VERSION 2.8.3)
project(semantic_slam)

set(CMAKE_BUILD_TYPE Release)
set(EXTERNAL_HEADERS ${CMAKE_SOURCE_DIR}/../external/libProfiler)
set(UTILS_HEADERS ${CMAKE_SOURCE_DIR}/../utils)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")

find_package(catkin REQUIRED)
find_package(OpenCV REQUIRED)
find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
)


include_directories(${catkin_INCLUDE_DIRS})
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${EXTERNAL_HEADERS})
include_directories(${UTILS_HEADERS})

message (${UTILS_HEADERS})


catkin_package(
  CATKIN_DEPENDS
    roscpp
    geometry_msgs
    std_msgs
)

file(GLOB MY_SRC ./*.cxx)


add_executable(ros_node_stereo ${MY_SRC})
target_link_libraries(ros_node_stereo ${catkin_LIBRARIES} )
