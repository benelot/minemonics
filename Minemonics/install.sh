#!/bin/sh

#OGRE3D environment 1.9
#built after the tutorials:
#http://www.ogre3d.org/tikiwiki/tiki-index.php?page=Building+Ogre


# OGRE
#http://www.ogre3d.org/tikiwiki/tiki-index.php?page=Prerequisites&refresh=1&tikiversion=Linux
sudo apt-get install build-essential automake libtool # compiler and configuration tools
sudo apt-get install libfreetype6-dev libfreeimage-dev libzzip-dev libxrandr-dev libxaw7-dev freeglut3-dev libgl1-mesa-dev libglu1-mesa-dev nvidia-cg-dev # required dependencies
sudo apt-get install libsdl2-dev # install sdl2 for the input system
sudo apt-get install libboost-all-dev # because I need a lot of boost libraries
mkdir ogre1.9
cd ogre1.9
hg clone https://bitbucket.org/sinbad/ogre/ -u v1-9
mkdir build
cd build
sudo ln -s /usr/include/freetype2/ /usr/include/freetype # FIX: because cmake can not find freetype2 because it searches for freetype
# configure make files with cmake
cmake -G"Eclipse CDT4 - Unix Makefiles" -D CMAKE_BUILD_TYPE=Debug ..
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
cmake -G"Eclipse CDT4 - Unix Makefiles" -DBUILD_SHARED_LIBS=ON -DCMAKE_BUILD_TYPE=Release -DBUILD_BULLET2_DEMOS=ON -DBUILD_BULLET3=ON -DBUILD_EXTRAS=ON -DINSTALL_EXTRA_LIBS=ON ..
make -j8 # because I have 8 cores for parallel compilation
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
make -j8 # because I have 8 cores for parallel compilation
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
make -j8 # because I have 8 cores for parallel compilation
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


# FFMpeg
# According to: http://trac.ffmpeg.org/wiki/CompilationGuide/Ubuntu
cd ..
sudo apt-get -y --force-yes install autoconf automake build-essential libass-dev libfreetype6-dev libgpac-dev \
  libsdl1.2-dev libtheora-dev libtool libva-dev libvdpau-dev libvorbis-dev libxcb1-dev libxcb-shm0-dev \
  libxcb-xfixes0-dev pkg-config texi2html zlib1g-dev
sudo apt-get install yasm libx264-dev libopus-dev libmp3lame-dev
git clone https://github.com/FFmpeg/FFmpeg.git
cd FFmpeg
PATH="$HOME/bin:$PATH" PKG_CONFIG_PATH="$HOME/ffmpeg_build/lib/pkgconfig" ./configure   --prefix="$HOME/ffmpeg_build"   --extra-cflags="-I$HOME/ffmpeg_build/include"   --extra-ldflags="-L$HOME/ffmpeg_build/lib"   --bindir="$HOME/bin"   --enable-gpl   --enable-libass --enable-libfreetype   --enable-libmp3lame   --enable-libopus   --enable-libtheora   --enable-libvorbis   --enable-libx264   --enable-nonfree
PATH="$HOME/bin:$PATH" make
sudo make install
sudo ldconfig
