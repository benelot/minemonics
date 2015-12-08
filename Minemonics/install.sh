#!/bin/sh

#TODO: This script still needs to be written in a more general way. Check with Luca how to do this.

# Install NVIDIA CUDA by hand to use caffe with CUDA. In case you want to use cuda and you change graphics drivers to NVIDIA proprietary drivers you need to install the following
#sudo apt-get install nvidia-cg-toolkit

#OGRE3D environment 1.9
#built after the tutorials:
#http://www.ogre3d.org/tikiwiki/tiki-index.php?page=Building+Ogre


sudo apt-get install git mercurial

mkdir dependencies
cd dependencies

# OGRE
#http://www.ogre3d.org/tikiwiki/tiki-index.php?page=Prerequisites&refresh=1&tikiversion=Linux
sudo apt-get install build-essential automake libtool # compiler and configuration tools
sudo apt-get install libfreetype6-dev libfreeimage-dev libzzip-dev libxrandr-dev libxaw7-dev freeglut3-dev libgl1-mesa-dev libglu1-mesa-dev nvidia-cg-dev 
sudo ln -s /usr/include/freetype2/ /usr/include/freetype # FIX: because cmake can not find freetype2 because it searches for freetype

# required dependencies
sudo apt-get install liblzma-dev
sudo apt-get install libsdl2-dev # install sdl2 for the input system
sudo apt-get install libboost-all-dev # because I need a lot of boost libraries
mkdir ogre1.9
cd ogre1.9
hg clone https://bitbucket.org/sinbad/ogre/ -u v1-9 .
mkdir build
cd build
# configure make files with cmake
cmake -G"Eclipse CDT4 - Unix Makefiles" -D CMAKE_BUILD_TYPE=Release ..
make -j8 # because I have 8 cores for parallel compilation
sudo make install
sudo ldconfig
cd ../..

# Bullet Physics 3
git clone https://github.com/bulletphysics/bullet3.git
cd bullet3
mkdir build
cd build
# configure make files with cmake
#for pure installation 
cmake -G"Eclipse CDT4 - Unix Makefiles" -DBUILD_SHARED_LIBS=ON -DCMAKE_BUILD_TYPE=Release -DBUILD_BULLET3=ON .. -DUSE_DOUBLE_PRECISION=ON ..
#for development
#mkdir build-single;cd build-single
#cmake -G"Eclipse CDT4 - Unix Makefiles" -DCMAKE_BUILD_TYPE=Release -DBUILD_BULLET2_DEMOS=ON -DBUILD_CPU_DEMOS=ON -DBUILD_BULLET3=ON -DBUILD_OPENGL3_DEMOS=ON -DBUILD_EXTRAS=ON -DBUILD_SHARED_LIBS=ON  -DINSTALL_EXTRA_LIBS=ON -DUSE_DOUBLE_PRECISION=OFF ..
#cd ..
#mkdir build-double;cd build-double
#cmake -G"Eclipse CDT4 - Unix Makefiles" -DCMAKE_BUILD_TYPE=Release -DBUILD_BULLET2_DEMOS=ON -DBUILD_CPU_DEMOS=ON -DBUILD_BULLET3=ON -DBUILD_OPENGL3_DEMOS=ON -DBUILD_EXTRAS=ON -DBUILD_SHARED_LIBS=ON  -DINSTALL_EXTRA_LIBS=ON -DUSE_DOUBLE_PRECISION=ON ..
make -j8 # because I have 8 cores for parallel compilation
sudo make install
sudo ldconfig

cd ../..

# Shark Machine Learning for Evolutionary Algorithms
# NOT USED ANYMORE
# According to: http://shark-project.sourceforge.net/GettingStarted.html
#sudo apt-get install cmake cmake-curses-gui libatlas-base-dev libboost-all-dev # from http://image.diku.dk/shark/sphinx_pages/build/html/rest_sources/getting_started/installation.html
#unzip shark-2.3.4.zip
# The current Shark 3.0 build is too new and does not (yet) contain any basic Evolutionary algorithm classes
#mkdir Shark
#cd Shark
#svn co https://svn.code.sf.net/p/shark-project/code/
#mkdir build
#cd build
# cmake -G"Eclipse CDT4 - Unix Makefiles" -D OPT_ENABLE_ATLAS=ON -D OPT_ENABLE_OPENMP=ON -D CMAKE_BUILD_TYPE=Release .. # I could not make it to work with Atlas LAPACK undefined reference to "clapack_dpotrf"
#cmake -G"Eclipse CDT4 - Unix Makefiles" -D OPT_ENABLE_OPENMP=ON -D CMAKE_BUILD_TYPE=Release ..
#cmake -G"Eclipse CDT4 - Unix Makefiles" -D CMAKE_BUILD_TYPE=Release ..
#make -j8 # because I have 8 cores for parallel compilation
#sudo make install
#sudo ldconfig 

#cd ../..

# CeGUI for a nice Graphical User Interface
# According to: http://cegui.org.uk/wiki/Building_CEGUI_for_Ogre_/_OgreRenderer#CEGUI_0.8.x
#sudo apt-get install libglew-dev libglm-dev
mkdir CeGUI
cd CeGUI
hg clone https://bitbucket.org/cegui/cegui . -r c60fe39a5b27
mkdir build
cd build
cmake -G"Eclipse CDT4 - Unix Makefiles" -D CMAKE_BUILD_TYPE=Release -D CEGUI_BUILD_PYTHON_MODULES=OFF -D CEGUI_BUILD_RENDERER_OGRE=ON .. # add -D CEGUI_SAMPLES_ENABLE=ON for samples
make -j8 # because I have 8 cores for parallel compilation
sudo make install
sudo ldconfig

cd ../..

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

cd ../..

# FFMpeg
# According to: http://trac.ffmpeg.org/wiki/CompilationGuide/Ubuntu
sudo apt-get -y --force-yes install autoconf automake build-essential libass-dev libfreetype6-dev libgpac-dev libsdl1.2-dev libtheora-dev libtool libva-dev libvdpau-dev libvorbis-dev libxcb1-dev libxcb-shm0-dev libxcb-xfixes0-dev pkg-config texi2html zlib1g-dev
sudo apt-get install yasm libx264-dev libopus-dev libmp3lame-dev
mkdir FFmpeg
cd FFmpeg
git clone https://github.com/FFmpeg/FFmpeg.git . -o 0773f6739538db9cbe2712bfffd4de47639a685e
PATH="/usr/local/bin:$PATH" PKG_CONFIG_PATH="/usr/local/lib/pkgconfig" ./configure   --prefix="/usr/local"   --extra-cflags="-I/usr/local/include"   --extra-ldflags="-L/usr/local/lib"   --bindir="/usr/local/bin"  --disable-vaapi --enable-shared
#PATH="/usr/local/bin:$PATH" PKG_CONFIG_PATH="/usr/local/lib/pkgconfig" ./configure   --prefix="/usr/local"   --extra-cflags="-I/usr/local/include"   --extra-ldflags="-L/usr/local/lib"   --bindir="/usr/local/bin"  --disable-vaapi  --#enable-gpl   --enable-libass --enable-libfreetype   --enable-libmp3lame   --enable-libopus   --enable-libtheora   --enable-libvorbis   --enable-libx264   --enable-nonfree 
PATH="/usr/local/bin:$PATH" make -j8
sudo make install
sudo ldconfig

cd ..

# gtest
sudo apt-get install libgtest-dev
#Stop distributing static library (although still build it, to ensure gtest works).
mkdir gtest
cd gtest
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=RELEASE /usr/src/gtest/
make
sudo mv libg* /usr/lib/

cd ../..

# CUDA installation is missing
## Download CUDA .deb from Nvidia. 
# cuda-repo-ubuntu1504-7-5-local_7.5-18_amd64.deb
#sudo dpkg -i cuda-repo-ubuntu1504-7-5-local_7.5-18_amd64.deb
#sudo apt-get update
#sudo apt-get install cuda

#OpenBLAS
## According to https://github.com/xianyi/OpenBLAS/wiki/Installation-Guide
# Download the development version of OpenBLAS
git clone git://github.com/xianyi/OpenBLAS
cd OpenBLAS
make FC=gfortran
sudo make PREFIX=/usr/local/OPENBLAS install

cd ..

# OpenCV
## According to http://docs.opencv.org/doc/tutorials/introduction/linux_install/linux_install.html#linux-installation
sudo apt-get install build-essential
sudo apt-get install cmake git libgtk2.0-dev pkg-config # We use FFmpeg libavcodec-dev libavformat-dev libswscale-dev
sudo apt-get install python-dev python-numpy libtbb2 libtbb-dev libjpeg-dev libpng-dev libtiff-dev libjasper-dev libdc1394-22-dev
git clone https://github.com/Itseez/opencv.git
cd opencv
mkdir build
cd build
cmake -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local ..
make -j8
sudo make install

cd ../..


# Caffe
## According to http://caffe.berkeleyvision.org/installation.html
sudo apt-get install protobuf, glog, gflags
sudo apt-get install hdf5, leveldb, snappy, lmdb # IO libraries
git clone https://github.com/BVLC/caffe.git

