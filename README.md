# Commons
Contains common codes used for ICS softwares (Linear algebra, Chrono, I/O...)

# Install

## Script install (Recommended)
In order to automatically install libCommons in an ICS project, please add to the install.sh script of your project the following lines:
```
#!/bin/bash
#Preparing directories
mkdir -p ~/include/
mkdir -p ~/lib/
```
And in order to install the Commons library on your system:
```
#Installing Commons
if [ \( ! -f ~/lib/libCommons.so \) -a \( ! -f ~/lib/libCommons.dylib \) ]
then
    echo "-- Installing Commons"
    git clone https://github.com/ICStoolbox/Commons.git Commons
    mkdir Commons/build
    cd Commons/build
    cmake ..
    make install
    cd -
    rm -rf Commons/
else
	echo "-- Commons already installed. Skipping..."
fi
```

## Standalone library
To install as a standalone library, first download or clone the repository on your computer:
```
git clone https://github.com/ICStoolbox/Commons.git
```
Then, navigate to the directory where you downloaded the code, and in a command prompt type:
```
mkdir build
cd build
cmake ..
make install
```
