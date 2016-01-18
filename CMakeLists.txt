cmake_minimum_required(VERSION 2.8)
project(Commons)
set(CMAKE_BUILD_TYPE "Release")

SET(SOURCES_DIR sources)
include_directories(${SOURCES_DIR})

file(GLOB_RECURSE source_files ${SOURCES_DIR}/*.c)
file(GLOB_RECURSE header_files ${SOURCES_DIR}/*.h)

#Find math and pthread libraries
IF (NOT WIN32)
  FIND_LIBRARY(M_LIB m)
  SET( LIBRARIES ${M_LIB})
ENDIF()
SET( LIBRARIES "-lpthread" ${LIBRARIES})

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "$ENV{HOME}/lib")
add_library(${PROJECT_NAME} SHARED ${source_files})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${LIBRARIES})


