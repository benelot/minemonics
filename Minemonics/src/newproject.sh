#!/bin/sh
echo "This will be the name of the project:"
echo $1
echo ""
echo "This will be the path of the project:"
echo $2
echo ""
unzip clean_ogre_cmake_project_1-9.zip -d $2
wrzlprmpft
mv $2/clean_ogre_cmake_project/* "$2/$1"
rmdir $2/clean_ogre_cmake_project
cd $2/$1
mkdir build
cd build
cmake ..
make -j4
make install

