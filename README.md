# Commons [![Build Status](https://travis-ci.org/ISCDtoolbox/Commons.svg?branch=master)](https://travis-ci.org/ISCDtoolbox/Commons)

Contains common codes used for ISCD softwares (Linear algebra, Chrono, I/O...)

## Install (Linux & Mac OS)

To install the Commons library on your system, first download or clone the repository on your computer:
```
git clone https://github.com/ISCDtoolbox/Commons.git
```
Then, navigate to the directory where you downloaded the code, and in a command prompt type:
```
mkdir build
cd build
cmake ..
make
make install
```
In order to use OpenMP and benefit from multithreading, replace the cmake command with:
```
cmake .. -DOPENMP=1
```

## Full ISCDtoolbox install

In order to install the full ISCDtoolbox suite on your system, download the [install.sh](https://raw.githubusercontent.com/ISCDtoolbox/Commons/master/install.sh) shell script on your computer (right click, save as...), then type in a command prompt:
```
sh install.sh
```
If no error occured, the ISCDtoolbox suite should be properly installed on your system, with sources present in ~/dev/ISCDtoolbox/ directory.
