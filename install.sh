# Full ICStoolbox installation script
# Proceed with care ! Executing will erase every modification you made.

set -e

#Cleaning
rm -rf ~/lib/libCommons.so
rm -rf ~/lib/libNavierStokes.so
rm -rf ~/lib/libElas.so
rm -rf ~/lib/libVelex.so
rm -rf ~/lib/libAdvection.so
rm -rf ~/bin/nstokes
rm -rf ~/bin/elastic
rm -rf ~/bin/advect
rm -rf ~/bin/velext

#Cloning
mkdir -p ~/dev/ICStoolbox
cd ~/dev/ICStoolbox
rm -rf Commons NavierStokes LinearElasticity Advection VelocityExtension
git clone https://github.com/ICStoolbox/Commons.git
git clone https://github.com/ICStoolbox/LinearElasticity.git
git clone https://github.com/ICStoolbox/NavierStokes.git
git clone https://github.com/ICStoolbox/Advection.git
git clone https://github.com/ICStoolbox/VelocityExtension.git

#Compiling
mkdir -p Commons/build
cd Commons/build
cmake .. 
make
make install
cd -

mkdir -p LinearElasticity/build
cd LinearElasticity/build
cmake ..
make
make install
cd -

mkdir -p NavierStokes/build
cd NavierStokes/build
cmake ..
make
make install
cd -

mkdir -p Advection/build
cd Advection/build
cmake ..
make
make install
cd -

mkdir -p VelocityExtension/build
cd VelocityExtension/build
cmake ..
make
make install
cd -

#Testing
elastic LinearElasticity/demos/3d/8branch
nstokes NavierStokes/demos/2d/cavity
velext VelocityExtension/demos/disk.mesh -o VelocityExtension/demos/disk.new.sol
#advect Advection/demos/2d/test.mesh -dt 0.001 -s Advection/demos/2d/test.sol -c Advection/demos/2d/test.chi.sol -o Advection/demos/2d/test.chi.sol

#Output
echo ""
echo "#################################"
echo "ICStoolbox successfully installed"
echo "#################################"
echo ""
