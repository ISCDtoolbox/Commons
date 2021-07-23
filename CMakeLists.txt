cmake_minimum_required(VERSION 2.8)
set(CMAKE_BUILD_TYPE  "Release")
SET(CMAKE_C_FLAGS   "-w -g -O3 -funroll-loops")
set(CMAKE_MACOSX_RPATH 1)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

project(Commons)

set(CMAKE_CXX_STANDARD 17)

#Find libraries
if(OPENMP)
  find_package(OpenMP)
  if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
  endif()
endif()
FIND_LIBRARY(          M_LIB m)
SET(                   LIBRARIES ${M_LIB} "-lpthread")

#Commons library
SET(                   SOURCES_DIR sources)
file(                  GLOB_RECURSE source_files ${SOURCES_DIR}/*.c)
file(                  GLOB_RECURSE header_files ${SOURCES_DIR}/*.h)
include_directories(   ${SOURCES_DIR})
add_library(           Commons SHARED ${source_files})
TARGET_LINK_LIBRARIES( Commons ${LIBRARIES})

INSTALL(
  TARGETS Commons
  RUNTIME DESTINATION "$ENV{HOME}/lib"
  LIBRARY DESTINATION "$ENV{HOME}/lib")

INSTALL(               FILES   ${header_files} DESTINATION "$ENV{HOME}/include")
