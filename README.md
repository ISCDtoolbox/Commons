# Commons
Contains common codes used for ICS softwares (Linear algebra, Chrono, I/O...)

##Usage with Cmake
In order to use the common tools in an other project developed at ICS , please include the following lines to your CMakeLists.txt:
```
#Commons library
include(ExternalProject)
ExternalProject_Add(
  commons
  PREFIX "./commons/"
  GIT_REPOSITORY https://github.com/ICStoolbox/Commons.git
  BUILD_COMMAND "make"
  INSTALL_COMMAND ""
  LOG_DOWNLOAD ON
  LOG_INSTALL ON
)
```

Then, add the newly created cmake dependency to your library or executable:
```
ADD_DEPENDENCIES(myTarget commons)
```

and specify the newly created include directory (for an out-of-source build):
```
INCLUDE_DIRECTORIES(pathtothebuilddirectory/commons/src/commons/sources)
```

Cmake will download and automatically build a shared library containing the common codes.

You can now work with the functions provided in this library, i.e.:
```
#import "libmesh5.h"
GmfCloseMesh(myMeshIdentifier)
```

##Usage with make
To install this library on your system, download or clone this repository:
```
git clone https://github.com/ICStoolbox/Commons.git
```
Navigate to the downloaded directory, and type in a command prompt:
```
mkdir build
cd build
cmake ..
make
```
A dynamic library will be created in your ~/lib/ directory.

To link this library with your project, link the .so or .dylib file with your compiler options, and add the "sources" directory to your compiler include path, i.e:
```
gcc -I path/to/sources/directory/ -l ~/lib/libCommons.so (or .dylib for MAC users)
```
