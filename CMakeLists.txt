# Set the minimum version of cmake (and default installation rpath if needed)
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
if (APPLE)
    set(CMAKE_MACOSX_RPATH TRUE)
endif ()
#set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

# One may want to impose the C-compiler (for example with a specific version)
#set(CMAKE_C_COMPILER "/usr/bin/clang-3.8")
#set(CMAKE_C_COMPILER_ID Clang)

# Print a warning if the os is not unix (linux and mac to be more precise)
if (NOT UNIX)
    message("Warning: the Commons library is currently intended for Unix ")
    message("systems since it has been tested merely on Linux and Mac OS. ")
    if (OPENMP)
        if (FORCEIOMP)
            message("The commands 'cmake .. -DOPENMP=1 -DFORCEIOMP=1' and ")
            message("'make' may not work.")
        else ()
            message("The commands 'cmake .. -DOPENMP=1' and 'make' may not ")
            message("work.")
        endif ()
    else ()
        message("The commands 'cmake ..' and 'make' may not work.")
    endif ()
endif ()

# Define the project of the Commons library depending of the version of cmake
if (CMAKE_VERSION VERSION_GREATER 3.0)
    project(Commons LANGUAGES C)
else ()
    project(Commons C)
endif ()
set(CMAKE_BUILD_TYPE "Release")

# Print a warning if the compiler is not gcc or clang (apple clang on mac os)
if (NOT ${CMAKE_C_COMPILER_ID} MATCHES GNU
                 AND NOT ${CMAKE_C_COMPILER_ID} MATCHES Clang
                              AND NOT ${CMAKE_C_COMPILER_ID} MATCHES AppleClang)
    message("Warning: the Commons library is currently intended to be ")
    message("compiled by gcc or clang since it has been tested merely on ")
    message("these two compilers.")
    if (OPENMP)
        if (FORCEIOMP)
            message("The commands 'cmake .. -DOPENMP=1 -DFORCEIOMP=1' and ")
            message("'make' may not work.")
        else ()
            message("The commands 'cmake .. -DOPENMP=1' and 'make' may not ")
            message("work.")
        endif ()
    else ()
        message("The commands 'cmake ..' and 'make' may not work.")
    endif ()
endif ()

# Print a warning if a user tries to compile the Commons library with -DOPENMP=1
# cmake flag on an old version of (Apple) Clang that does not support OpenMP
if (OPENMP)
    if ( (${CMAKE_C_COMPILER_ID} MATCHES Clang OR
                    ${CMAKE_C_COMPILER_ID} MATCHES AppleClang)
                               AND ${CMAKE_C_COMPILER_VERSION} VERSION_LESS 3.8)
        message("Warning: your version of ${CMAKE_C_COMPILER_ID} ")
        message("(=${CMAKE_C_COMPILER_VERSION}) should not be currently less ")
        message("than 3.8 in order to properly support the OpenMP library. ")
        message("We recall that ${CMAKE_C_COMPILER_ID} was not originally ")
        message("supporting OpenMP but has been integrated to the llvm ")
        message("project for sufficiently recent of version of their ")
        message("C-compiler. If you really want to use OpenMP with the ")
        message("Commons library, you may have to compile it manually (using ")
        message("omp-clang for example) but for really old versions of ")
        message("${CMAKE_C_COMPILER_ID}, it will not be possible. Please, ")
        message("update your version of ${CMAKE_C_COMPILER_ID} by typing ")
        if (APPLE)
            message("'brew upgrade llvm' in your prompt window.")
        else ()
            message("'sudo apt-get install clang-3.8' your prompt window ")
            message("(you need administrator rights to do that).")
        endif ()
        if (FORCEIOMP)
            message("The commands 'cmake .. -DOPENMP=1 -DFORCEIOMP=1' and ")
            message("'make' may not work.")
        else ()
            message("The commands 'cmake .. -DOPENMP=1' and 'make' may not ")
            message("work.")
        endif ()
    endif ()
endif ()

# Add the source files to the Commons library which also uses:
#    * headers from the C standard library:
#        - assert.h
#        - ctype.h
#        - errno.h
#        - float.h
#        - limits.h
#        - math.h (the associated static library needs to be linked)
#        - stdarg.h
#        - stdbool.h
#        - stdio.h
#        - stdlib.h
#        - string.h
#        - time.h
#
#    * headers from the C POSIX library that are not already a part of the
#      C standard library:
#        - pthread.h (the associated dynamic library needs to be linked)
#        - sys/resource.h
#        - sys/time.h
#        - unistd.h
#
#    * headers from external libraries:
#        - omp.h (optional, the associated dynamic library needs to be linked
#                 if the -DOPENMP=1 flag is added to the "cmake .." command)
#
#    * headers from the local source directory:
#        - chrono.h
#        - eigen.h
#        - libmesh5.h
#        - lplib3.h
#        - sparse.h
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
#set(CMAKE_THREAD_PREFER_PTHREAD ON)       # To be set only for systems with
                                           # multiple thread libraries
if (CMAKE_VERSION VERSION_GREATER 3.1)
    set(THREADS_PREFER_PTHREAD_FLAG ON)    # Replace -lpthread flag by -pthread
endif ()
find_package(Threads REQUIRED)

# Find the OpenMP library (libgomp1 on Ubuntu 16.04.4, add -fopenmp with gcc
#                          compiler), which is optional here, -DOPENMP=1 flag
#                          must be added to the "cmake .." command to take into
#                          account this parallelization procedure.
# Remark: when -fopenmp option is set in gcc, the preprocessor compiler creates
#         a preprocessor constant _OPENMP yyyymmdd where yyyy is the year
#         mm the month and dd the day of the preprocessor compilation. This
#         preprocessor constant is used in sparse.c to include (or not) the
#         omp.h file and thus considering or not the parallelization.
if (OPENMP)
    find_package(OpenMP)

    # Print a warning to suggest what to do if the OpenMP library is not found
    # (and if the flag -DFORCEIOMP=1 has not been set)
    if (NOT FORCEIOMP AND NOT OPENMP_FOUND)
        if (APPLE)
            message("Warning: check that the libomp library has been properly ")
            message("installed by typing for example 'brew install libomp' ")
            message("in your prompt window. Note that the older name of ")
            message("this library is libiomp5 so you may have to replace ")
            message("libomp by libiomp in the brew install command line ")
            message("(and then add the -DFORCEIOMP=1 flag in the cmake ")
            message("command line if it is the case).")
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
                message("'sudo apt-get install libgomp1' in your prompt ")
                message("window (you need administrator rights to do that).")
            elseif (${CMAKE_C_COMPILER_ID} MATCHES Clang)
                message("Warning: check that the libomp-dev library has been ")
                message("properly installed by typing for example ")
                message("'sudo apt-get install libomp-dev' in your prompt ")
                message("window (you need administrator rights to do that).")
                message("Note that the older name of this library is ")
                message("libiomp5 so you may have to replace libomp-dev by ")
                message("libiomp-dev in the sudo apt-get install command line ")
                message("(and then add the -DFORCEIOMP=1 flag in the cmake ")
                message("command line if it is the case).")
            endif ()
        endif ()
    endif ()
endif ()

# Set all the targets of the Commons library
target_include_directories(Commons
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/sources>)
        # Remark: the user can add directly the path(s) for header file(s) in
        #         the above target_include_directories command (like omp.h
        #         if it has not been not found)

if (CMAKE_VERSION VERSION_GREATER 3.8)
    target_compile_features(Commons PRIVATE c_std_99)
elseif (CMAKE_VERSION VERSION_GREATER 3.1)
    set_property(TARGET Commons PROPERTY C_STANDARD 99)
else ()
    target_compile_options(Commons PRIVATE -std=gnu99)
endif ()

if (${CMAKE_C_COMPILER_ID} MATCHES GNU)
    target_compile_options(Commons PRIVATE -Wunknown-pragmas
                                           -Wno-unused-result)
    #target_compile_options(Commons PRIVATE -Wall -Wextra -Wpedantic)
elseif (${CMAKE_C_COMPILER_ID} MATCHES Clang
                                   OR ${CMAKE_C_COMPILER_ID} MATCHES AppleClang)
    target_compile_options(Commons PRIVATE -Wsource-uses-openmp)
    #target_compile_options(Commons PRIVATE -Weverything)
endif ()

# Remark: the user can add directly here the path for linking the math library
#         (if it has not been not found with the above find_library command)
target_link_libraries(Commons PUBLIC ${MATH_LIBRARY})

# Remark: the user can add directly here the path for linking the Thread library
#         (if it has not been not found with the above find_package command, and
#          do not forget to remove it if you specify directly here the path)
if (CMAKE_VERSION VERSION_GREATER 3.1)
    target_link_libraries(Commons PUBLIC Threads::Threads)
else ()
    target_link_libraries(Commons PUBLIC ${CMAKE_THREAD_LIBS_INIT})
endif ()

if (OPENMP)
    # Remark 1: if the flag -DFORCEIOMP=1 is added to the cmake command
    #           it will try to link the old name of the OpenMP library (libiomp)
    #           instead of libomp for apple clang or clang (can be useful for
    #           older versions of Ubuntu for example 14.04 where the version of
    #           OpenMP is libiomp5 by default).
    #
    # Remark 2: The user can also use add directly the correct path for linking
    #           the OpenMP library by modifying below the target_compile_options
    #           and target_link_libraries commands at the place corresponding to
    #           its OS, C-compiler and cmake version
    if (FORCEIOMP)
        if (${CMAKE_C_COMPILER_ID} MATCHES Clang
                                   OR ${CMAKE_C_COMPILER_ID} MATCHES AppleClang)
            if (APPLE)
                message("-- We try to set the iomp library instead of omp.")
                target_compile_options(Commons PUBLIC -Xclang -fopenmp)
                target_link_libraries(Commons PUBLIC "-liomp")
            else ()
                message("-- We try to link the iomp5 library instead of omp.")
                target_compile_options(Commons PUBLIC -fopenmp=libiomp5)
                target_link_libraries(Commons PUBLIC "-liomp5")
            endif ()
        else ()
            message("Warning: you should not be using the -DFORCEIOMP=1 cmake ")
            message("flags on other compilers than Clang or Apple Clang.")
        endif ()
    else ()
        if (OPENMP_FOUND)
            if (CMAKE_VERSION VERSION_GREATER 3.9)
                target_link_libraries(Commons PUBLIC OpenMP::OpenMP_C)
            else ()
                if (${CMAKE_C_COMPILER_ID} MATCHES Clang
                                   OR ${CMAKE_C_COMPILER_ID} MATCHES AppleClang)
                    target_link_libraries(Commons PUBLIC "-lomp")
                    if (APPLE)
                        target_compile_options(Commons PUBLIC -Xclang -fopenmp)
                    else ()
                        target_compile_options(Commons PUBLIC -fopenmp=libomp)
                    endif ()
                else ()
                    target_compile_options(Commons PUBLIC ${OpenMP_C_FLAGS})
                    target_link_libraries(Commons PUBLIC "${OpenMP_C_FLAGS}")
                endif ()
            endif ()
        else ()
            if (${CMAKE_C_COMPILER_ID} MATCHES Clang
                                   OR ${CMAKE_C_COMPILER_ID} MATCHES AppleClang)
                message("-- We try to link the omp library even if not found.")
                target_link_libraries(Commons PUBLIC "-lomp")
                if (APPLE)
                    target_compile_options(Commons PUBLIC -Xclang -fopenmp)
                else ()
                    target_compile_options(Commons PUBLIC -fopenmp=libomp)
                endif ()
            else ()
                message("-- We try to link the gomp library even if not found.")
                target_compile_options(Commons PUBLIC -fopenmp)
                target_link_libraries(Commons PUBLIC "-lgomp")
            endif ()
        endif ()
    endif ()
endif ()

# Set the installation properties of the Commons library
# Remark: the user can change here the paths where the Commons library and
#         associated header files will be installed at 'cmake install' command
install(TARGETS Commons LIBRARY DESTINATION "$ENV{HOME}/lib/iscd")
install(FILES sources/chrono.h
              sources/eigen.h
              sources/libmesh5.h
              sources/lplib3.h
              sources/sparse.h DESTINATION "$ENV{HOME}/include/iscd/Commons")

