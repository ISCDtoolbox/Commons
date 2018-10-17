cmake_minimum_required(VERSION 3.5.1 FATAL_ERROR)

# Print a warning if the os is not unix
if (NOT UNIX)
    message("WARNING: the Commons library is currently intended for Unix ")
    message("systems since it has been tested merely on Linux and Mac OS. ")
    if (OPENMP)
        message("The commands 'cmake .. -DOPENMP=1' and 'make' may not work.")
    else ()
        message("The commands 'cmake ..' and 'make' may not work.")
    endif()
endif ()

# Print a warning if the compiler is not gcc or clang
if (NOT ${CMAKE_C_COMPILER_ID} MATCHES GNU
                AND NOT ${CMAKE_C_COMPILER_ID} MATCHES Clang 
                              AND NOT ${CMAKE_C_COMPILER_ID} MATCHES AppleClang)
    message("WARNING: the Commons library is currently intended to be ")
    message("compiled by gcc or clang since it has been tested merely on ")
    message("these two compilers.")
    if (OPENMP)
        message("The commands 'cmake .. -DOPENMP=1' and 'make' may not work.")
    else ()
        message("The commands 'cmake ..' and 'make' may not work.")
    endif()
endif ()

project(Commons LANGUAGES C)
set(CMAKE_BUILD_TYPE "Release")

# Add the source files to the Commons library
add_library(Commons SHARED sources/chrono.c
                           sources/eigen.c
                           sources/libmesh5.c
                           sources/lplib3.c
                           sources/solve.c
                           sources/sparse.c)

# The source files of the Commons library uses:
#
#    - Headers from the C standard library: assert.h
#                                           ctypes.h
#                                           errno.h
#                                           float.h
#                                           limits.h
#                                           math.h (it needs to be statically
#                                                                        linked)
#                                           stdarg.h
#                                           stdbool.h
#                                           stdio.h
#                                           stdlib.h
#                                           string.h
#                                           time.h
#
#    - Headers from the C POSIX library that are not already a
#      part of the C standard library: sys/resource.h
#                                      sys/time.h
#                                      unistd.h
#
#    - Headers from external library: omp.h (optional, it needs to be
#                                                  dynamically linked if active)
#                                     pthread.h (it needs to be dynamically
#                                                                        linked)
#
#    - Headers from the local sources directory: chrono.h
#                                                eigen.h
#                                                libmesh5.h
#                                                lplib3.h
#                                                sparse.h
#
# Find the Math libraries (libm.a on Ubuntu 16.04.4, add -lm with gcc compiler),
#      the Threads (libpthread-stubs0-dev on Ubuntu 16.04.4, add -pthread with
#                   gcc compiler), and
#      the OpenMp (libgomp1 on Ubuntu 16.04.4, add -fopenmp with gcc compiler),
#                  which is optional here, -DOPENMP=1 must be added in the
#                  "cmake .." command to take into account this parallelization
#                  procedure.
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
find_library(M_LIB m)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
if (OPENMP)
    find_package(OpenMP)

    # Print a warning to suggest what to do if the OpenMp library is not found
    if (NOT OPENMP_FOUND)
        if (APPLE)
            message("WARNING: check that the libomp library has been properly ")
            message("installed by typing for example 'brew install libomp' ")
            message("in your terminal window.")
            if (CMAKE_VERSION VERSION_LESS 3.12)
                message("WARNING: on mac os, your version of cmake ")
                message("(=${CMAKE_VERSION}) cannot be currently less than ")
                message("3.12 in order to target properly the OpenMp library.")
                message("Please, update your version of cmake by typing for ")
                message("example 'brew upgrade cmake' in your terminal window.")
            endif ()
        else ()
            if (${CMAKE_C_COMPILER_ID} MATCHES GNU)
                message("WARNING: check that the libgomp1 library has been ")
                message("properly installed by typing for example ")
                message("'sudo apt-get install libgomp1' in your terminal ")
                message("window.")
            elseif (${CMAKE_C_COMPILER_ID} MATCHES Clang)
                message("WARNING: check that the libomp-dev library has been ")
                message("properly installed by typing for example ")
                message("'sudo apt-get install libomp-dev' in your terminal ")
                message("window.")
            else ()
                message("WARNING: the Commons library is currently intended ")
                message("to be compiled by gcc or clang since it has been ")
                message("tested merely on these two compilers.")
            endif ()
        endif()
    endif()
endif ()

# Set all targets and properties of the Commons library
target_include_directories(Commons
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/sources>)
set_property(TARGET Commons PROPERTY C_STANDARD 99)
target_link_libraries(Commons PUBLIC ${M_LIB}
                                     Threads::Threads)
if (OPENMP_FOUND)
    if (CMAKE_VERSION VERSION_GREATER 3.9.6)
        target_link_libraries(Commons PUBLIC OpenMP::OpenMP_C)
    else ()
        target_link_libraries(Commons PUBLIC ${OpenMP_C_FLAGS})
    endif ()
    target_compile_options(Commons PUBLIC ${OpenMP_C_FLAGS})
endif ()

if (${CMAKE_C_COMPILER_ID} MATCHES GNU)
    target_compile_options(Commons PUBLIC -Wno-unused-result
                                          -Wunknown-pragmas)
elseif (${CMAKE_C_COMPILER_ID} MATCHES Clang
                                   OR ${CMAKE_C_COMPILER_ID} MATCHES AppleClang)
    target_compile_options(Commons PUBLIC -Wsource-uses-openmp)
endif ()

# Set the installation properties of the Commons library
install(TARGETS Commons LIBRARY DESTINATION "$ENV{HOME}/lib/iscd")
install(FILES sources/chrono.h
              sources/eigen.h
              sources/libmesh5.h
              sources/lplib3.h
              sources/sparse.h DESTINATION "$ENV{HOME}/include/iscd/Commons")

