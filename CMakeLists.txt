cmake_minimum_required(VERSION 3.9)

project(quickselect
  LANGUAGES C)

set (CMAKE_C_STANDARD 11)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")


add_library( quickselect32 quickselect.c quickselect.h )

target_include_directories(quickselect32 PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set_target_properties(quickselect32 PROPERTIES PUBLIC_HEADER "quickselect.h")
INSTALL(TARGETS quickselect32)
