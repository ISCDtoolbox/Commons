# Commons [![Build Status](https://travis-ci.org/ISCDtoolbox/Commons.svg?branch=test_future_update)](https://travis-ci.org/ISCDtoolbox/Commons)

The Commons library contains some code written in C that is shared by many ISCD softwares (Linear algebra, basic chronograph, input/output mesh, multi-threading).

In the first two sections, we provide informations about how to install the Commons library, while in a third part, we explain how to install the full ISCDtoolbox suite. Authors, contributors, credits, and licenses are detailed at the end of this file.

## Quick install (Linux & Mac OS)

To install the Commons library on your system, some basic softwares (gcc/clang, make, cmake, git) and optional packages (libgomp/libomp to benefit from OpenMP) must have been previously installed. In a command prompt, first navigate to the directory where you want to save the files and type successively:
```
git clone https://github.com/ISCDtoolbox/Commons.git
cd Commons
mkdir build
cd build
```
Then, depending on whether or not you want to benefit from OpenMP parallel features, type in the command prompt
```
cmake ..
```
or
```
cmake .. -DOPENMP=1
```
Finally, compile and install the Commons library on your computer by typing successively in the command prompt
```
make
make install
```

## Detailed installation guide

We try to provide here some details about how you can properly install the Commons library if the above procedure did not work. First, we describe what is needed before, distinguishing Linux from Mac OS systems. Then, we detail the compilation part and we finally focus on the installation and linking paths.

### Prerequisites

The compilation of the Commons library has been tested on Linux and Mac OS systems for merely the gcc and clang compilers.

#### Linux systems (tested on Ubuntu 14.04.5 and Ubuntu 16.04.4)

In order to know precisely the version of your operating system, you can type in a command prompt
```
lsb_release -a
```
We now list the different packages that are recommended to be installed before compiling the Commons library on Linux systems. We also specify between parenthesis the versions of the packages we have used to perform successful compilation tests. Hence, it is recommmanded to have versions that are greater or equal than the ones given below.

##### Required softwares

* gcc (version >= 4.8.4) or clang (version >= 3.8.0 is strongly recommanded)
* make (version >= 3.81)
* cmake (version >= 2.8(.12.2) is mandatory and version >= 3.9 is recommanded)
* git (version >= 1.9.1)

We mention that git is only used here to clone the Commons repository on your computer but it is also possible to download the files manually from github in a *.zip format if git is not installed on your computer (just go to the upper right part of the current page, click on the button Clone or download, and then Download ZIP).

In order to get the current version of a specific software installed on your computer (or simply to know if such a software is installed), you can type in a command prompt
```
nameOfTheSoftware --version
```
If one of the above software is not installed, you can use your favorite package manager to install it (you will need administrator rights to do that). We describe now how to do that (if you are not familiar with Linux). For example, on Debian systems such as Ubuntu, you can use the apt software as follows. First type in a command prompt
```
sudo apt-add-repository main
```
in order to let your system access the main repository that contain the canonical-supported free and open-source softwares such as gcc, make, or cmake (normally this should be already active by default). Similarly, type in a command prompt
```
sudo apt-add-repository universe
```
which is the repository that contains community-maintained free and open-source softwares such as clang-3.8. We recall that the sudo word implies that you will run a command using the administrator rights. If you do not have the password for this, you may have to contact your system administrator in order to install it properly. Then, you may also have to update the repositories which can be done by typing in a command prompt
```
sudo apt-get update
```
For example, we had to do it for finding the git software in the main repository of one of our system (Ubuntu 14.04.5). You can search for a specific package name by typing in a command prompt
```
apt-cache search approximateNameOfYourPackageOrNameOfYourSearch
```
We recall that you cannot use blank spaces in your search or if you want to do so, simply put some " " to begin and end your search. Finally, when you have found the precise name of the software/package you want to install, you can type in a command prompt
```
sudo apt-get install softwareOrPackageYouWantToInstall
```
If the software/package is already installed, you may want to upgrade the version by typing in a command prompt
```
sudo apt-get upgrade softwareOrPackageYouWantToUpgrade
```

##### Additional packages (optional)

The previous softwares were needed to load and compile properly the Commons library but we also need to link some additional libraries. Normally, by default, the C-standard library libc.so, the Math library libm.so, and the Thread library libpthread.so should already be installed by default on your Linux system as well as their associated header files.

Optionally, you may want to benefit from multi-threading by using the OpenMP library, whose name depends on the compiler you are using (libgomp.so with gcc and libomp.so with clang). This library as well as its associated header files should also be already installed on your computer but contrarily to the previous libraries, this one is only optional.

Hence, you should not have to install any further packages but we give here some hints on how to do it if such libraries are not found on your system during the installation procedure of the Commons library.

* libc6-dev (version 2.23) package which contains the GNU C Library (development libraries and header files) and in particular the Math library (and normally also the Thread library)

* libpthread-stubs0-dev (version >= 0.3-4) package which contains pthread stubs not provided by native libc, development files (you can install it if the Thread library is not found at installation)

* libgomp1 (version >= 5.4.0) if you use gcc or libomp-dev (version >= 3.7.0-3) if you use clang, which are the OpenMP libraries used by the respective compilers.

Important remark: the previous name of the libomp.so library was the libiomp5.so one. Hence, on old versions of Linux, you may have to search for the libiomp-dev package instead of the libomp-dev one. Moreover, your version of clang should not be currently less than 3.8 in order to properly support the OpenMP library (if you want to do so, we recall this is only optional here). We recall that contrarily to the gcc compiler, clang was not originally supporting OpenMP but has been integrated to the llvm project for sufficiently recent version of their c-compiler (i.e. clang). If you really want to use OpenMP with the Commons library compiled with an old version of clang, you may have to do it manually (using omp-clang for example) but for really old versions of clang, it will simply not be possible. That is why we recommand to compile the Commons library with gcc compiler on Linux systems.

If you are not familiar with Linux, we refer to the previous section for hints about how to search, install or upgrade a package with apt. We now detail how to search for libraries in a Linux system. First of all, in the case you want to use multi-threading, you can obtain the total number of cpu of your system by typing in a command prompt
```
lscpu
```
You can also use the 'locate' command to quickly search for a library but you may first have to update the cache file by typing in a command prompt (you need administrator rights to do that)
```
sudo updatedb
```
Then, you can search for a library (such as the previous required ones libc.so, libm.so, libpthread.so, and the optional ones libgomp.so/libomp.so or libiomp5.so) or simply a file (such as their associated headers like stdlib.h, math.h, pthread.h, omp.h) by typing in a command prompt
```
locate NameOfTheLibraryOrTheFileYouWantToSearch
```

#### Mac OS systems (tested on Mac OS X 10.13.3 and Mac OS X 10.13.6)

In order to know precisely the version of your operating system, you can type in a command prompt
```
sw_vers
```
We now list the different packages that are recommended to be installed before compiling the Commons library on Mac OS systems. We also specify between parenthesis the versions of the packages we have used to perform successful compilation tests. Hence, it is recommmanded to have versions that are greater or equal than the ones given below.

##### Required softwares

* apple clang (version >= 9.1.0)
* make (version >= 3.81)
* cmake (version >= 3.11.4 (>= 2.8 is mandatory) and version >= 3.12 is strongly recommanded)
* git (version >= 2.17.1)

Important remark: if one uses the basic installation of Xcode, which is the software Apple imposes you to install from the Apple Store in order to deal with any development tools, the gcc and clang compilers are not the real ones. In fact, they are only symbolic links to the apple clang compiler. For user who are really using clang or gcc, the installation of the Commons library should also work in this case (although not currently tested). We refer to the previous similar Linux section to get details about the associated libraries that need to be linked.

We also mention that git is only used here to clone the repository on your computer but it is also possible to download the files manually from github in a *.zip format if git is not installed on your computer (just go to the upper right part of the current page, click on the button Clone or download, and then Download ZIP).

In order to get the current version of a specific software installed on your computer (or simply to know is such a software is installed), you can type in a command prompt
```
nameOfTheSoftware --version
```
If one of the above software is not installed, you can use your favorite package manager in order to install it. We describe now how to do that (if you are not familiar with Mac OS). For example, you can use the homebrew software as follows. First, you may have to update the local repository containing the list of available packages. This can be done by typing in a command prompt
```
brew update
```
Then, you can search for a specific package name by typing in a command prompt
```
brew search approximateNameOfYourPackageOrNameOfYourSearch
```
We recall that you cannot use blank spaces in your search or if you want to do so, simply put some " " to begin and end your search. Finally, when you have found the precise name of the software/package you want to install, you can type in a command prompt
```
brew install softwareOrPackageYouWantToInstall
```
If the software/package is already installed, you may want to upgrade the version by typing in a command prompt
```
brew upgrade softwareOrPackageYouWantToUpgrade
```

##### Additional packages (optional)

The previous softwares were needed to load and compile properly the Commons library but we also need to link some additional libraries. Normally, by default, the C-standard library libc.dylib, the Math library libm.dylib, and the Thread library libpthread.dylib should already be installed by default on your Mac OS system (and pointing to the libSystem.B.dylib library) as well as their associated header files.

Optionally, you may want to benefit from multi-threading by using the OpenMP library (libomp.dylib with apple clang). This library as well as its associated header files should not be installed on your computer by default, contrarily to the previous libraries. It is only optional and for installing it, just type in a command prompt
```
brew install libomp
```
Important remark: the previous name of the libomp.dylib library was the libiomp5.dylib one. Hence, on old versions of Mac OS, you way have to search for the libiomp package instead of the libomp one. Moreover, your version of apple clang should not be currently less than 3.8 in order to properly support the OpenMP library (if you want to do so, we recall this is only optional here). We recall that contrarily to the gcc compiler, clang was not originally supporting OpenMP but has been integrated to the llvm project for sufficiently recent version of their c-compiler (i.e. clang). If you really want to use OpenMP with the Commons library compiled with an old version of clang, you may have to do it manually (using omp-clang for example) but for really old versions of clang, it will simply not be possible. Similarly, we recommand to use the most recent available version of cmake (>=3.12) if one wants the OpenMP library to be properly targetted at the compilation of the Commons library.

If you are not familiar with Mac OS, we refer to the previous section for hints about how to search, install or upgrade a package with homebrew. We now detail how to search for libraries in a Mac OS system. First of all, in the case you want to use multi-threading, you can obtain the total number of cpu of your system by typing in a command prompt
```
sysctl hw
```
You can also use the 'locate' command to quickly search for a library but you may first have to update the cache file by typing in a command prompt (you need administrator rights to do that)
```
sudo /usr/libexec/locate.updatedb
```
Then, you can search for a library (such as the previous required ones libc.dylib, libm.dylib, libpthread.dylib, and the optional ones libgomp.dylib/libomp.dylib or libiomp5.dylib) or simply a file (such as their associated headers like stdlib.h, math.h, pthread.h, omp.h) by typing in a command prompt
```
locate NameOfTheLibraryOrTheFileYouWantToSearch
```

### Compilation

To install the Commons library on your system, first navigate in a command prompt to the directory where you want to save the files (thanks to the 'cd' and 'ls' commands, cf. the end of next installation paths section if you are not familiar with that). Then, type successively in a command prompt:
```
git clone https://github.com/ISCDtoolbox/Commons.git
```
to clone the repository on your computer (we recall that it is also possible to download the files manually from github in a *.zip format if the git software is not installed on your computer, just go to the upper right part of the current page, click on the button Clone or download, and then Download ZIP)
```
cd Commons
```
to enter the Commons/ directory you have just downloaded
```
mkdir build
```
to create the directory where we are going to build the Commons library
```
cd build
```
to enter the build/ directory you have just created
```
cmake ..
```
or
```
cmake .. -DOPENMP=1
```
to generate the Makefile with cmake (in order to use OpenMP and benefit from multithreading, you need to add -DOPENMP=1 in the cmake command; note that if you use the older name of the OpenMP library i.e. libiomp, you also have to add a second -DFORCEIOMP=1 flag in the cmake command)
```
make
```
to compile the Commons library with make
```
make install
```
to install the Commons library on your computer. Depending on where are located your installation paths, you may also need the administrator rights in order to do that. In this case, you need to type in the command prompt
```
sudo make install
```

### Installation paths
By typing "make install" in a command prompt, the Commons library will be installed by default  in a lib/iscd/ subdirectory of your home directory. You can type
```
echo ${HOME}
```
in a command prompt to get the full absolute path of your home directory. Similarly, the public header files related to the Commons library will be installed by default in a include/iscd/Commons/ subdirectory of your home directory.

If one wants to change the installation paths for the Commons library and associated public header files, one has to modify the CMakeLists.txt file located in the Commons/ directory, and correct the lines
```
# Set the installation properties of the Commons library
install(TARGETS Commons LIBRARY DESTINATION "$ENV{HOME}/lib/iscd")
install(FILES sources/chrono.h
              sources/eigen.h
              sources/libmesh5.h
              sources/lplib3.h
              sources/sparse.h DESTINATION "$ENV{HOME}/include/iscd/Commons")
```
with the destination paths the user wants to set. For example, if ones wants to install the library (respectively the associated public header files) in a lib/ (resp. include/) subdirectory of the Commons/ directory, just replace the above lines by
```
# Set the installation properties of the Commons library
install(TARGETS Commons LIBRARY DESTINATION "${PROJECT_SOURCE_DIR}/lib")
install(FILES sources/chrono.h
              sources/eigen.h
              sources/libmesh5.h
              sources/lplib3.h
              sources/sparse.h DESTINATION "${PROJECT_SOURCE_DIR}/include")
```
in the CMakeLists.txt file located in the Commons/ directory. Then, you may need to re-install the Commons library. First, locate yourself in the build directory in a command prompt thanks to the 'cd' and 'ls' commands. You can also check in which directory you are by typing
```
pwd
```
You can go in a specific directory by typing
```
cd subdirectoryWhereYouWantToGo
```
and
```
ls
```
to see the content of the current directory. Similarly, you can move to the upper directory by typing
```
cd ..
```
Once you are in the correct build directory, you then have to remove all the previous files by typing
```
rm -r ./*
```
Finally, type again the commands described in the compilation part above.

### Linking paths
You can also check that the needed libraries were correctly linked to the Commons one by typing in a command prompt
```
ldd pathWhereYourCommonsLibraryHasBeenInstalled/libCommons.so
```
if you are on Linux or
```
otool -L pathWhereYourCommonsLibraryHasBeenInstalled/libCommons.dylib
```
if you are on Mac OS.

## Full ISCDtoolbox install (section under construction, needs to be updated)

In order to install the full ISCDtoolbox suite on your system, download the [install.sh](https://raw.githubusercontent.com/ISCDtoolbox/Commons/master/install.sh) shell script on your computer (right click, save as...), then type in a command prompt:
```
sh install.sh
```
If no error occured, the ISCDtoolbox suite should be properly installed on your system, with sources present in ~/dev/ISCDtoolbox/ directory.

## Authors & contributors

The Commons library contains a set of tools developped and maintained by [Pascal Frey](https://www.ljll.math.upmc.fr/frey/) (Sorbonne Université) and [Loïc Maréchal](http://pages.saclay.inria.fr/loic.marechal/About_Me.html) (INRIA Saclay).

The github page has been created and maintained by [Loïc Norgeot](https://fr.linkedin.com/in/lnorgeot) and is currently updated by [Jérémy Dalphin](http://pelikano.free.fr/JeremyDalphin.html).

Contributors to any ISCD project are warmly welcomed.

## Credits

The github pages of the libmesh and lplib libraries

* [libmesh](https://github.com/LoicMarechal/libMeshb)
* [lplib](https://github.com/LoicMarechal/LPlib)

## License

The Commons library is given under the terms of the [GNU Lesser General Public License](https://github.com/ISCDtoolbox/Commons/blob/master/LICENSE).

