#!/bin/sh

#OGRE3D environment 1.9
#built after the tutorials:
#http://www.ogre3d.org/tikiwiki/tiki-index.php?page=Building+Ogre


# OGRE
#http://www.ogre3d.org/tikiwiki/tiki-index.php?page=Prerequisites&refresh=1&tikiversion=Linux
sudo apt-get install build-essential automake libtool # compiler and configuration tools
sudo apt-get install libfreetype6-dev libfreeimage-dev libzzip-dev libxrandr-dev libxaw7-dev freeglut3-dev libgl1-mesa-dev libglu1-mesa-dev nvidia-cg-dev # required dependencies
sudo apt-get install libsdl2-dev # install sdl2 for the input system
#sudo apt-get install libois-dev # install OIS
sudo apt-get install libboost-all-dev # because I need a lot of boost libraries
mkdir ogre1.9
cd ogre1.9
hg clone https://bitbucket.org/sinbad/ogre/ -u v1-9
mkdir build
cd build
sudo ln -s /usr/include/freetype2/ /usr/include/freetype # FIX: because cmake can not find freetype2 because it searches for freetype
# configure make files with cmake
cmake -G"Eclipse CDT4 - Unix Makefiles" -D CMAKE_BUILD_TYPE=Debug ..
make -j4 # because I have 4 cores for parallel compilation
sudo make install
sudo ldconfig
cd ../..

# Bullet
tar xvzf bullet-2.82-r2704.tgz
cd bullet-2.82-r2704
mkdir build
cd build
# configure make files with cmake
cmake -G"Eclipse CDT4 - Unix Makefiles" -DBUILD_SHARED_LIBS=ON -DCMAKE_BUILD_TYPE=RelWithDebugInfo -DBUILD_EXTRAS=ON -DINSTALL_EXTRA_LIBS=ON ..
make -j4 # because I have 4 cores for parallel compilation
sudo make install
sudo ldconfig

cd ..

# Shark Machine Learning for Evolutionary Algorithms
# According to: http://shark-project.sourceforge.net/GettingStarted.html
sudo apt-get install cmake cmake-curses-gui libatlas-base-dev libboost-all-dev # from http://image.diku.dk/shark/sphinx_pages/build/html/rest_sources/getting_started/installation.html
unzip shark-2.3.4.zip
# The current Shark 3.0 build is too new and does not (yet) contain any basic Evolutionary algorithm classes
#mkdir Shark
cd Shark
#svn co https://svn.code.sf.net/p/shark-project/code/
mkdir build
cd build
# cmake -G"Eclipse CDT4 - Unix Makefiles" -D OPT_ENABLE_ATLAS=ON -D OPT_ENABLE_OPENMP=ON -D CMAKE_BUILD_TYPE=Release .. # I could not make it to work with Atlas LAPACK undefined reference to "clapack_dpotrf"
#cmake -G"Eclipse CDT4 - Unix Makefiles" -D OPT_ENABLE_OPENMP=ON -D CMAKE_BUILD_TYPE=Release ..
cmake -G"Eclipse CDT4 - Unix Makefiles" -D CMAKE_BUILD_TYPE=Release ..
make -j4 # because I have 4 cores for parallel compilation
sudo make install
sudo ldconfig

cd ..

# CeGUI for a nice Graphical User Interface
# According to: http://cegui.org.uk/wiki/Building_CEGUI_for_Ogre_/_OgreRenderer#CEGUI_0.8.x
mkdir CeGUI
cd CeGUI
hg clone https://underworldguardian@bitbucket.org/cegui/cegui
mkdir build
cd build
cmake -G"Eclipse CDT4 - Unix Makefiles" -D CMAKE_BUILD_TYPE=Release -D CEGUI_BUILD_PYTHON_MODULES=off ..
make -j4 # because I have 4 cores for parallel compilation
sudo make install
sudo ldconfig

cd ..
#MathGL
sudo apt-get install swig liboctave-dev libgif-dev
wget http://downloads.sourceforge.net/project/mathgl/mathgl/mathgl%202.3.2/mathgl-2.3.2.tar.gz
tar xvzf mathgl-2.3.2.tar.gz
cd mathgl-2.3.2
mkdir build
cd build
cmake -G"Eclipse CDT4 - Unix Makefiles" -D CMAKE_BUILD_TYPE=Release -D enable-jpeg=on -D enable-gif=on -D enable-hdf5=on -D enable-octave=on ..
make
sudo make install
sudo ldconfig



# ogrebullet 
echo "This part is currently not working..."
exit
cd ogrebullet-r2988

#patch some files
#https://docs.google.com/file/d/0B_6mnQttjwGuZDExMjdmNmItZDAxOC00MTM5LWFiZmUtMjIzZjgwNjhjNTcz/edit?ddrp=1&hl=en#
patch -p0 < ../linux_demo.patch
chmod 755 autogen.sh
./autogen.sh
