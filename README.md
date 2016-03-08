# Commons [![Build Status](https://travis-ci.org/ICStoolbox/Commons.svg?branch=master)](https://travis-ci.org/ICStoolbox/Commons)

Contains common codes used for ICS softwares (Linear algebra, Chrono, I/O...)

# Install (Linux & Mac OS)

To install the Commons library on your system, first download or clone the repository on your computer:
```
git clone https://github.com/ICStoolbox/Commons.git
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