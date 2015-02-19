#!/bin/sh

#OGRE3D environment 1.9
#built after the tutorials:
#http://www.ogre3d.org/tikiwiki/tiki-index.php?page=Building+Ogre


# OGRE
#http://www.ogre3d.org/tikiwiki/tiki-index.php?page=Prerequisites&refresh=1&tikiversion=Linux
sudo apt-get install build-essential automake libtool # compiler and configuration tools
sudo apt-get install libfreetype6-dev libfreeimage-dev libzzip-dev libxrandr-dev libxaw7-dev freeglut3-dev libgl1-mesa-dev libglu1-mesa-dev nvidia-cg-dev # required dependencies
sudo apt-get install libois-dev # install OIS
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
sudo apt-get install libboost-all-dev # from http://ubuntuforums.org/showthread.php?t=1725216
mkdir Shark
cd Shark
svn co https://svn.code.sf.net/p/shark-project/code/
mkdir build
cd build
cmake -G"Eclipse CDT4 - Unix Makefiles" -D CMAKE_BUILD_TYPE=Release .
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

# ogrebullet 
echo "This part is currently not working..."
exit
cd ogrebullet-r2988

#patch some files
#https://docs.google.com/file/d/0B_6mnQttjwGuZDExMjdmNmItZDAxOC00MTM5LWFiZmUtMjIzZjgwNjhjNTcz/edit?ddrp=1&hl=en#
patch -p0 < ../linux_demo.patch
chmod 755 autogen.sh
./autogen.sh
