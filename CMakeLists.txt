cmake_minimum_required(VERSION 3.5.1 FATAL_ERROR)

project(Commons LANGUAGES C)
set(CMAKE_BUILD_TYPE "Release")

# Add the source files to the Commons library
add_library(Commons SHARED sources/chrono.c
                           sources/eigen.c
                           sources/libmesh5.c
                           sources/lplib3.c
                           sources/solve.c
                           sources/sparse.c)

# Find the OpenMp (libgomp1 on Ubuntu 16.04.4, add -fopenmp with gcc compiler),
#                  which is optional here, -DOPENMP=1 must be added in the
#                  "cmake .." command to take into account this parallelization
#                  procedure, 
#      the Threads (libpthread-stubs0-dev on Ubuntu 16.04.4, add -pthread with
#                   gcc compiler), and
#      the Math libraries (libm.a on Ubuntu 16.04.4, add -lm with gcc compiler).
#
# IMPORTANT REMARK: when -fopenmp option is set in gcc, the preprocessor
#                   compiler creates a preprocessor constant _OPENMP yyyymmdd
#                   where yyyy is the year mm the month and dd the day of the
#                   preprocessor compilation. This preprocessor constant is used
#                   in sparse.c to include (or not) the omp.h file and thus
#                   considering or not the parallelization.
#
# MINOR REMARK: adding -lpthread option with gcc only links the pthread library
#               while the pre-defined macros do not get defined. The -pthread
#               option tells the compiler to link in the pthread library as well
#               as configure the compilation for threads. Tendancy is to add
#               -pthread option instead of -lpthread
if (OPENMP)
    find_package(OpenMP)
endif ()
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
find_library(M_LIB m)

# Set all targets and properties of the Commons library
target_include_directories(Commons
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/sources>)

set_property(TARGET Commons PROPERTY C_STANDARD 99)
if (OPENMP_FOUND)
    target_compile_options(Commons PUBLIC ${OpenMP_C_FLAGS})
    target_link_libraries(Commons PUBLIC ${OpenMP_C_FLAGS})
endif ()
if (APPLE)
    target_compile_options(Commons PUBLIC -Wsource-uses-openmp)
else ()
#if (CMAKE_COMPILER_IS_GNUCC)
    message("hello")
    target_compile_options(Commons PUBLIC -Wno-unused-result
                                          -Wunknown-pragmas)
#elseif (${CMAKE_C_COMPILER} MATCHES Clang OR ${CMAKE_C_COMPILER} MATCHES clang)

endif ()
target_link_libraries(Commons PUBLIC ${M_LIB}
                                     Threads::Threads)

# Set the installation properties of the Commons library
install(TARGETS Commons LIBRARY DESTINATION "$ENV{HOME}/lib/iscd")
install(FILES sources/chrono.h
              sources/eigen.h
              sources/libmesh5.h
              sources/lplib3.h
              sources/sparse.h DESTINATION "$ENV{HOME}/include/iscd/Commons")

