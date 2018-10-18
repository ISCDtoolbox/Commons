# Commons [![Build Status](https://travis-ci.org/ISCDtoolbox/Commons.svg?branch=test_future_update)](https://travis-ci.org/ISCDtoolbox/Commons)

The Commons library contains some code written in C that is shared by many ISCD softwares (Linear algebra, Chrono, Input/Output mesh, ...).

## Install (Linux & Mac OS)

### Prerequisites

The compilation of the Commons library has currently been tested on Linux and Mac OS systems for merely the gcc and clang compilers.

On Linux systems (tested on Ubuntu 14.04.5 and Ubuntu 16.04.4), it is recommanded to have previously installed the following packages:

* gcc (version >= 4.8.4) or clang (version >= 3.8.0)
* make (version >= 4.1)
* cmake (version >= 3.5.1 is mandatory and version >= 3.9.1 is recommanded)
* git (version >= 2.7.4)
 
and optionally, if you want to use OpenMP and benefit from multithreading:

* libpthread-stubs0-dev (version >= 0.3-4) which is an additional multithreading library that may be used by OpenMp
* libgomp1 (version >= 5.4.0) if you use gcc or libomp-dev (version >= 3.7.0-3) if you use clang, which are the OpenMP libraries used by the respective compilers

On Mac OS systems (tested on Mac OS X 10.13.3), it is recommmanded to have previously installed the following packages:

* apple clang (version >= 9.1.0)
* make (version >= 4.1)
* cmake (version >= 3.5.1 is mandatory and version >= 3.12.1 is strongly recommanded)
* git (version >= 2.7.4)

and optionally if you want to use OpenMP and benefit from multithreading:

* libomp (version >= 6.0.1), which is the OpenMP library used by the apple clang compiler

### Compilation

To install the Commons library on your system, first navigate to the directory where you want to save the files. Then, type successively in a command prompt:
```
git clone https://github.com/ISCDtoolbox/Commons.git
```
to clone the repository on your computer (it is also possible to download the files manually from github in a *.zip format)
```
cd Commons
```
to enter the Commons directory you have just downloaded
```
mkdir build
```
to create the directory where we are going to build the Commons library
```
cd build
```
to enter the build directory you have just created
```
cmake ..
```
or
```
cmake .. -DOPENMP=1
```
to generate the Makefile with cmake (in order to use OpenMP and benefit from multithreading, you need to add -DOPENMP=1 in the cmake command)
```
make
```
to compile the Commons library with make
```
make install
```
to install the Commons library on your computer

Important remark: by typing "make install" in a prompt command, the Commons library will be installed by default in a lib/iscd/ subdirectory of your Home directory (type "echo ${HOME}" in a prompt command to get the full absolute path of your Home directory).

Similarly, the (public) headers files related to the Commons library will be installed by default in a include/iscd/Commons/ subdirectory of your Home directory.

If one wants to change the installation paths for the Commons library and associated (public) header files, one has to modify the CMakeLists.txt file and replace in the lines
```
# Set the installation properties of the Commons library
install(TARGETS Commons LIBRARY DESTINATION "$ENV{HOME}/lib/iscd")
install(FILES sources/chrono.h
              sources/eigen.h
              sources/libmesh5.h
              sources/lplib3.h
              sources/sparse.h DESTINATION "$ENV{HOME}/include/iscd/Commons")
```
the correct destination paths. For example, if ones wants to install the library (respectively the associated public header files) in a lib (resp. include) subdirectory of the Commons directory, just replace the above lines by
```
# Set the installation properties of the Commons library
install(TARGETS Commons LIBRARY DESTINATION "${PROJECT_SOURCE_DIR}/lib")
install(FILES sources/chrono.h
              sources/eigen.h
              sources/libmesh5.h
              sources/lplib3.h
              sources/sparse.h DESTINATION "${PROJECT_SOURCE_DIR}/include")
```
the CMakeLists.txt file of the Commons directory.

## Full ISCDtoolbox install

In order to install the full ISCDtoolbox suite on your system, download the [install.sh](https://raw.githubusercontent.com/ISCDtoolbox/Commons/master/install.sh) shell script on your computer (right click, save as...), then type in a command prompt:
```
sh install.sh
```
If no error occured, the ISCDtoolbox suite should be properly installed on your system, with sources present in ~/dev/ISCDtoolbox/ directory.
