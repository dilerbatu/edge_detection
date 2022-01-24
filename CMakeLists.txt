cmake_minimum_required(VERSION 3.5)

project(edge_detection)
set(TARGET_NAME ${PROJECT_NAME})

find_package( OpenCV REQUIRED )

file(GLOB_RECURSE CPP_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)

include_directories(
	include
)
include_directories(${OpenCV_INCLUDE_DIRS})

set(SOURCES ${CPP_FILES})
add_library(TARGET_NAME SHARED ${SOURCES})
target_include_directories(TARGET_NAME PUBLIC ${INCLUDE_DIRECTORIES} )
target_link_libraries(TARGET_NAME  ${OpenCV_LIBS}) # fill this up with the dependencies you want for eg opencv

add_executable(edge_detection_bin src/EdgeDetector.cpp)
target_include_directories(edge_detection_bin PUBLIC ${INCLUDE_DIRECTORIES} )
target_link_libraries(edge_detection_bin TARGET_NAME ${OpenCV_LIBS}) 
