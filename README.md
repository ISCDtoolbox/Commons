# Commons [![Build Status](https://travis-ci.org/ISCDtoolbox/Commons.svg?branch=test_future_update)](https://travis-ci.org/ISCDtoolbox/Commons)

The Commons library contains some code written in C that is shared by many ISCD softwares (Linear algebra, Chrono, Input/Output mesh, ...).

## Install (Linux & Mac OS)

### Prerequisites

The compilation of the Commons library has currently been tested on Linux and Mac OS systems for merely the gcc and clang compilers.

On Linux systems (tested on Ubuntu 14.04.5 and Ubuntu 16.04.4), it is recommmanded to have previously installed the following packages:

* gcc (version >= 4.8.4) or clang (version >= 3.8.0);
* make (version >= 4.1);
* cmake (version >= 3.5.1 is mandatory and version >= 3.9.1 is recommanded);
* git (version >= 2.7.4);
 
and optionally, if you want to use OpenMP and benefit from multithreading:

* libgomp1 (version >= 5.4.0) if you use gcc or libomp-dev (version >= 3.7.0-3) if you use clang, which are the OpenMP libraries used by the respective compilers.

On Mac OS systems (tested on Mac OS X 10.13.3), it is recommmanded to have previously installed the following packages:

* AppleClang (version >= 9.1.0);
* make (version >= 4.1);
* cmake (version >= 3.5.1 is mandatory and version >= 3.12.1 is recommanded);
* git (version >= 2.7.4);
 
and optionally if you want to use OpenMP and benefit from multithreading:

* libomp (version >= 6.0.1), which is the OpenMP library used by the AppleClang compiler.

### Compilation

To install the Commons library on your system, first navigate to the directory where you want to put the files. Then, download the files on your computer or simply clone the repository by typing in a command prompt:
```
git clone https://github.com/ISCDtoolbox/Commons.git
```

Then, in a command prompt type successively:
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




Remark: In the case where the commands inside the install.sh file failed, we list precisely below the needed external libraries (and of course their dependencies, this is normally treated automatically with any package manager):



## Full ISCDtoolbox install

In order to install the full ISCDtoolbox suite on your system, download the [install.sh](https://raw.githubusercontent.com/ISCDtoolbox/Commons/master/install.sh) shell script on your computer (right click, save as...), then type in a command prompt:
```
sh install.sh
```
If no error occured, the ISCDtoolbox suite should be properly installed on your system, with sources present in ~/dev/ISCDtoolbox/ directory.
