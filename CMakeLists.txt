project(Commons)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_BUILD_TYPE "Release")

SET(SOURCES_DIR sources)
include_directories(${SOURCES_DIR})
file(GLOB_RECURSE source_files ${SOURCES_DIR}/*.c)
file(GLOB_RECURSE header_files ${SOURCES_DIR}/*.h)

#Find math and pthread libraries
FIND_LIBRARY(M_LIB m)
SET( LIBRARIES ${M_LIB})
SET( LIBRARIES "-lpthread" ${LIBRARIES})

add_library(Commons SHARED ${source_files})
TARGET_LINK_LIBRARIES(Commons ${LIBRARIES})

INSTALL(TARGETS Commons LIBRARY DESTINATION "$ENV{HOME}/lib")
