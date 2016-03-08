cmake_minimum_required(VERSION 2.8)
set(CMAKE_BUILD_TYPE  "Release")
SET(CMAKE_C_FLAGS   "-w -g -O2 -fopenmp")

set(CMAKE_MACOSX_RPATH 1)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

project(Commons)

#Find math and pthread libraries
FIND_PACKAGE(          OpenMP)
FIND_LIBRARY(          M_LIB m)
SET(                   LIBRARIES ${M_LIB})
SET(                   LIBRARIES "-lpthread" ${LIBRARIES})

#Commons library
SET(                   SOURCES_DIR sources)
file(                  GLOB_RECURSE source_files ${SOURCES_DIR}/*.c)
file(                  GLOB_RECURSE header_files ${SOURCES_DIR}/*.h)
include_directories(   ${SOURCES_DIR})
add_library(           Commons SHARED ${source_files})
TARGET_LINK_LIBRARIES( Commons ${LIBRARIES})
INSTALL(               TARGETS Commons LIBRARY DESTINATION "$ENV{HOME}/lib")
INSTALL(               FILES   ${header_files} DESTINATION "$ENV{HOME}/include")
