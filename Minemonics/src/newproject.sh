#!/bin/sh

# Write some information to the console
echo "This will be the name of the project:"
echo $1
echo ""
echo "This will be the path of the project:"
echo $2
echo ""

# Unzip and put into the proper folder
unzip clean_ogre_cmake_project_1-9.zip -d $2
mkdir $2/$1/src
mv $2/clean_ogre_cmake_project/* "$2/$1/src"
rmdir $2/clean_ogre_cmake_project
cd $2/$1

# make a build folder parallel to the src folder
mkdir build
cd build
# to use cmake projects with version control
cmake -G"Eclipse CDT4 - Unix Makefiles" -D CMAKE_BUILD_TYPE=Debug ../src
make -j4
make install

