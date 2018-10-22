# Set the minimum version of cmake
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

# Define the project of the Commons library depending of the version of cmake
if (CMAKE_VERSION VERSION_GREATER 3.0)
    project(Commons LANGUAGES C)
else ()
    project(Commons)
endif ()
set(CMAKE_BUILD_TYPE "Release")

# One may want to force the c-compiler (for example with a specific version)
#include (CMakeForceCompiler)
#CMAKE_FORCE_C_COMPILER("/usr/bin/clang-3.8" Clang)

# Print a warning if the os is not unix (linux and mac to be more precise)
if (NOT UNIX)
    message("Warning: the Commons library is currently intended for Unix ")
    message("systems since it has been tested merely on Linux and Mac OS. ")
    if (OPENMP)
        message("The commands 'cmake .. -DOPENMP=1' and 'make' may not work.")
    else ()
        message("The commands 'cmake ..' and 'make' may not work.")
    endif ()
endif ()

# Print a warning if the compiler is not gcc or clang (apple clang on mac)
if (NOT ${CMAKE_C_COMPILER_ID} MATCHES GNU
                 AND NOT ${CMAKE_C_COMPILER_ID} MATCHES Clang
                              AND NOT ${CMAKE_C_COMPILER_ID} MATCHES AppleClang)
    message("Warning: the Commons library is currently intended to be ")
    message("compiled by gcc or clang since it has been tested merely on ")
    message("these two compilers.")
    if (OPENMP)
        message("The commands 'cmake .. -DOPENMP=1' and 'make' may not work.")
    else ()
        message("The commands 'cmake ..' and 'make' may not work.")
    endif ()
endif ()

# Print a warning if the user tries to compile the Commons library with OPENMP=1
# on an old version of Clang or Apple Clang that does not support OpenMP
if (OPENMP)
    if ( (${CMAKE_C_COMPILER_ID} MATCHES Clang OR
                    ${CMAKE_C_COMPILER_ID} MATCHES AppleClang)
                               AND ${CMAKE_C_COMPILER_VERSION} VERSION_LESS 3.8)
        if (APPLE)
            message("Warning: your version of Apple Clang ")
        else ()
            message("Warning: your version of Clang ")
        endif ()
        message("(=${CMAKE_C_COMPILER_VERSION}) should not be currently less ")
        message("than 3.8 in order to properly support the OpenMP library. ")
        if (APPLE)
            message("We recall that Apple Clang was not originally supporting")
        else ()
            message("We recall that Clang was not originally supporting")
        endif ()
        message("OpenMP but has integrated to the llvm project for ")
        message("sufficiently recent of version of their C-compiler. ")
        message("If you really want to use OpenMP with the Commons library, ")
        message("you may have to compile it manually using omp-clang ")
        if (APPLE)
            message("but for really old versions of Apple Clang, it will not ")
            message("be possible. Please, update your version of Apple Clang ")
            message("by typing 'brew upgrade llvm' in your prompt window.")
        else ()
            message("but for really old versions of Clang, it will not be ")
            message("possible. Please, update your version of Clang by typing ")
            message("'sudo apt-get install clang-3.8' in your prompt window ")
            message("(you need administrator rights to do that).")
        endif ()
        message("The commands 'cmake .. -DOPENMP=1' and 'make' may not work.")
    endif()
endif ()

# Add the source files to the Commons library which also uses:
#
#    * headers from the C standard library:
#        - assert.h
#        - ctype.h
#        - errno.h
#        - float.h
#        - limits.h
#        - math.h (the associated library needs to be statically linked)
#        - stdarg.h
#        - stdbool.h
#        - stdio.h
#        - stdlib.h
#        - string.h
#        - time.h
#
#    * headers from the C POSIX library that are not already a part of the
#      C standard library:
#        - pthread.h (the associated library needs to be dynamically linked)
#        - sys/resource.h
#        - sys/time.h
#        - unistd.h
#
#    * headers from external libraries:
#        - omp.h (optional, the associated library needs to be dynamically
#                 linked if the OPENMP cmake variable has been properly defined)
#
#    * headers from the local source directory:
#        - chrono.h
#        - eigen.h
#        - libmesh5.h
#        - lplib3.h
#        - sparse.h
#
add_library(Commons SHARED sources/chrono.c
                           sources/eigen.c
                           sources/libmesh5.c
                           sources/lplib3.c
                           sources/solve.c
                           sources/sparse.c)

# Find the Math library (libm.a on Ubuntu 16.04.4, add -lm with gcc compiler)
find_library(MATH_LIBRARY m)

# Find the Threads library (libpthread-stubs0-dev on Ubuntu 16.04.4,
#                           add -(l)pthread with gcc compiler)
# Remark: adding -lpthread option with gcc only links the pthread library while
#         the pre-defined macros do not get defined. The -pthread option tells
#         the compiler to link in the pthread library as well as configure the
#         compilation for threads. Tendancy is to add -pthread option instead
#         of -lpthread
#
#set(CMAKE_THREAD_PREFER_PTHREAD ON) # To be set only for systems with
                                     # multiple thread libraries
if (CMAKE_VERSION VERSION_GREATER 3.1)
    set(THREADS_PREFER_PTHREAD_FLAG ON)
endif ()
find_package(Threads REQUIRED)

# Find the OpenMP library (libgomp1 on Ubuntu 16.04.4, add -fopenmp with gcc
#                          compiler), which is optional here, -DOPENMP=1 must
#                          be added in the "cmake .." command to take into
#                          account this parallelization procedure.
# Remark: when -fopenmp option is set in gcc, the preprocessor compiler creates
#         a preprocessor constant _OPENMP yyyymmdd where yyyy is the year
#         mm the month and dd the day of the preprocessor compilation. This
#         preprocessor constant is used in sparse.c to include (or not) the
#         omp.h file and thus considering or not the parallelization.
#
if (OPENMP)
    find_package(OpenMP)

    # Print a warning to suggest what to do if the OpenMP library is not found
    if (NOT OPENMP_FOUND)
        if (APPLE)
            message("Warning: check that the libomp library has been properly ")
            message("installed by typing for example 'brew install libomp' ")
            message("in your terminal window. ")
            if (CMAKE_VERSION VERSION_LESS 3.12)
                message("Warning: on mac os, your version of cmake ")
                message("(=${CMAKE_VERSION}) should not be currently less ")
                message("than 3.12 in order to target properly OpenMP.")
                message("Please, update your version of cmake by typing for ")
                message("example 'brew upgrade cmake' in your prompt window.")
            endif ()
        else ()
            if (${CMAKE_C_COMPILER_ID} MATCHES GNU)
                message("Warning: check that the libgomp1 library has been ")
                message("properly installed by typing for example ")
                message("'sudo apt-get install libgomp1' in your terminal ")
                message("window (you need administrator rights to do that).")
            elseif (${CMAKE_C_COMPILER_ID} MATCHES Clang)
                message("Warning: check that the libomp-dev library has been ")
                message("properly installed by typing for example ")
                message("'sudo apt-get install libomp-dev' in your terminal ")
                message("window (you need administrator rights to do that).")
                message("Note that the older name of this library is ")
                message("libiomp5 so you may have to replace libomp-dev by ")
                message("libiomp-dev in the sudo apt-get install command line.")
            endif ()
        endif ()
    endif ()
endif ()

# Set all the targets of the Commons library
target_include_directories(Commons
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/sources>)

if (CMAKE_VERSION VERSION_GREATER 3.8)
    target_compile_features(Commons PUBLIC c_std_99)
elseif (CMAKE_VERSION VERSION_GREATER 3.1)
    set_property(TARGET Commons PROPERTY C_STANDARD 99)
else ()
    target_compile_options(Commons PUBLIC -std=gnu99)
endif ()

if (${CMAKE_C_COMPILER_ID} MATCHES GNU)
    target_compile_options(Commons PUBLIC -Wunknown-pragmas
                                          -Wno-unused-result)
#    target_compile_options(Commons PUBLIC -Wall -Wextra -Wpedantic)
elseif (${CMAKE_C_COMPILER_ID} MATCHES Clang
                                   OR ${CMAKE_C_COMPILER_ID} MATCHES AppleClang)
    target_compile_options(Commons PUBLIC -Wsource-uses-openmp)
    #target_compile_options(Commons PUBLIC -Weverything)
endif ()

target_link_libraries(Commons PUBLIC ${MATH_LIBRARY})

if (CMAKE_VERSION VERSION_GREATER 3.1)
    target_link_libraries(Commons PUBLIC Threads::Threads)
else ()
    target_link_libraries(Commons PUBLIC ${CMAKE_THREAD_LIBS_INIT})
endif ()

if (OPENMP_FOUND)
    if (CMAKE_VERSION VERSION_GREATER 3.9)
        # Try to link if the OpenMP library is libiomp5 instead of libomp for
        # clang (useful for older version of Ubuntu for example 14.04)
        # The flag -DIOMP must be set to one
        if (FORCEIOMP AND NOT APPLE AND ${CMAKE_C_COMPILER_ID} MATCHES Clang)
            message("Warning: we try to set the iomp5 library instead of iomp.")
            target_compile_options(Commons PUBLIC -fopenmp=libiomp5)
            target_link_libraries(Commons PUBLIC "-liomp5")
        else ()
            target_link_libraries(Commons PUBLIC OpenMP::OpenMP_C)
        endif ()
    else ()
        if (NOT APPLE AND ${CMAKE_C_COMPILER_ID} MATCHES Clang)
            if (FORCEIOMP)
                message("Warning: we try to set the iomp5 library instead of ")
                message("the iomp one.")
                target_compile_options(Commons PUBLIC -fopenmp=libiomp5)
                target_link_libraries(Commons PUBLIC "-liomp5")
            else ()
                target_compile_options(Commons PUBLIC -fopenmp=libomp)
                target_link_libraries(Commons PUBLIC "-lomp")
            endif ()
        elseif (APPLE AND ${CMAKE_C_COMPILER_ID} MATCHES AppleClang)
            target_compile_options(Commons PUBLIC -Xclang -fopenmp)
            target_link_libraries(Commons PUBLIC "-lomp")
        else ()
            target_compile_options(Commons PUBLIC ${OpenMP_C_FLAGS})
            target_link_libraries(Commons PUBLIC ${OpenMP_C_FLAGS})
        endif ()
    endif ()
endif ()

# Set the installation properties of the Commons library
install(TARGETS Commons LIBRARY DESTINATION "$ENV{HOME}/lib/iscd")
install(FILES sources/chrono.h
              sources/eigen.h
              sources/libmesh5.h
              sources/lplib3.h
              sources/sparse.h DESTINATION "$ENV{HOME}/include/iscd/Commons")

