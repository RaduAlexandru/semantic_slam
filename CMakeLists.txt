cmake_minimum_required(VERSION 2.8.3)
project(baseline)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set(PROJECT_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/deps ${CMAKE_SOURCE_DIR}/deps/imgui )		# Header folder
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DAPC_CAPTURE_DEBUG=1")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")


find_package(catkin REQUIRED)
find_package(OpenCV REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(MPI REQUIRED)
find_package(GLFW REQUIRED)
#find_package(GLM REQUIRED)
find_package(OpenGL REQUIRED)
find_package(Boost REQUIRED COMPONENTS system thread)
find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
)


include_directories(${PROJECT_INCLUDE_DIR} ${catkin_INCLUDE_DIRS})
include_directories(${EIGEN3_INCLUDE_DIR})
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${Boost_INCLUDE_DIR})
include_directories(${OPENGL_INCLUDE_DIR})
include_directories(${GLFW_INCLUDE_DIR})
#include_directories(${GLM_INCLUDE_DIRS})
#add_definitions(${GLM_DEFINITIONS})



catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS
    roscpp
    geometry_msgs
    std_msgs
)

file(GLOB IMGUI_SRC ${CMAKE_SOURCE_DIR}/deps/imgui/*.cpp)
file(GLOB MY_SRC ${CMAKE_SOURCE_DIR}/src/*.cxx)

#message (${IMGUI_SRC})


add_executable(baseline ${MY_SRC} deps/glad/glad.c  ${IMGUI_SRC})
target_link_libraries(baseline ${catkin_LIBRARIES} ${Boost_LIBRARIES} ${OpenCV_LIBS} ${OPENGL_gl_LIBRARY} ${GLFW_LIBRARIES})
