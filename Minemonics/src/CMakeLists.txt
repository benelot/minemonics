#/*
#-----------------------------------------------------------------------------
#Filename:    CMakeLists.txt
#-----------------------------------------------------------------------------
#
#This source file is part of the
#   ___                 __    __ _ _    _ 
#  /___\__ _ _ __ ___  / / /\ \ (_) | _(_)
# //  // _` | '__/ _ \ \ \/  \/ / | |/ / |
#/ \_// (_| | | |  __/  \  /\  /| |   <| |
#\___/ \__, |_|  \___|   \/  \/ |_|_|\_\_|
#      |___/                              
#      Tutorial Framework
#      http://www.ogre3d.org/tikiwiki/
#-----------------------------------------------------------------------------
#*/
cmake_minimum_required(VERSION 2.6)
 
project(OgreApp)
 
if(WIN32)
	set(CMAKE_MODULE_PATH "$ENV{OGRE_HOME}/CMake/;${CMAKE_MODULE_PATH}")
	set(OGRE_SAMPLES_INCLUDEPATH
		$ENV{OGRE_HOME}/Samples/include
	)
endif(WIN32)
 
if(UNIX)
	if(EXISTS "/usr/local/lib/OGRE/cmake")

	  set(CMAKE_MODULE_PATH "/usr/local/lib/OGRE/cmake/;${CMAKE_MODULE_PATH}")
	  set(OGRE_SAMPLES_INCLUDEPATH "/usr/local/share/OGRE/samples/Common/include/") # We could just *assume* that developers uses this basepath : /usr/local

	elseif(EXISTS "/usr/lib/OGRE/cmake")

	  set(CMAKE_MODULE_PATH "/usr/lib/OGRE/cmake/;${CMAKE_MODULE_PATH}")
	  set(OGRE_SAMPLES_INCLUDEPATH "/usr/share/OGRE/samples/Common/include/") # Otherwise, this one

	else ()
	  message(SEND_ERROR "Failed to find module path.")
	endif(EXISTS "/usr/local/lib/OGRE/cmake")
	set(PROJECT_HOME .)
endif(UNIX)
 
if (CMAKE_BUILD_TYPE STREQUAL "")
  # CMake defaults to leaving CMAKE_BUILD_TYPE empty. This screws up
  # differentiation between debug and release builds.
  set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "Choose the type of build, options are: None (CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif ()
 
set(CMAKE_DEBUG_POSTFIX "_d")
 
set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/dist")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/Modules/")


######################################################################
# OGRE, OGRE Terrain
######################################################################

 
find_package(OGRE REQUIRED)

# USERADDED for terrain usage
# Add OgreTerrain.{so,dll,etc.} to our linked libraries
#   These variables are defined in FindOGRE.cmake, mine is
#   found at /usr/local/lib/OGRE/cmake/
if (OGRE_Terrain_FOUND)
# append OgreTerrain to the end of the OGRE_LIBRARIES variable
  set(OGRE_LIBRARIES ${OGRE_LIBRARIES} ${OGRE_Terrain_LIBRARIES})  
  message(STATUS "Found OGRE_Terrain: ${OGRE_Terrain_LIBRARIES}")
else (OGRE_Terrain_FOUND)
  message(SEND_ERROR "OgreTerrain Library not found.")
endif(OGRE_Terrain_FOUND)


if (OGRE_Paging_FOUND)
# append OgrePaging to the end of the OGRE_LIBRARIES variable
  set(OGRE_LIBRARIES ${OGRE_LIBRARIES} ${OGRE_Paging_LIBRARIES})  
  message(STATUS "Found OGRE_Paging: ${OGRE_Paging_LIBRARIES}")
else (OGRE_Paging_FOUND)
  message(SEND_ERROR "OgrePaging Library not found.")
endif(OGRE_Paging_FOUND)

if (OGRE_Overlay_FOUND)
# append OgreOverlay to the end of the OGRE_LIBRARIES variable
  set(OGRE_LIBRARIES ${OGRE_LIBRARIES} ${OGRE_Overlay_LIBRARIES})  
  message(STATUS "Found OGRE_Overlay: ${OGRE_Overlay_LIBRARIES}")
else (OGRE_Overlay_FOUND)
  message(SEND_ERROR "OgreOverlay Library not found.")
endif(OGRE_Overlay_FOUND)
 
######################################################################
# BOOST
######################################################################
 
# Find Boost
if (WIN32 OR APPLE OR OGRE_STATIC)
	set(Boost_USE_STATIC_LIBS ON)
else ()
	# Statically linking boost to a dynamic Ogre build doesn't work on Linux 64bit
	set(Boost_USE_STATIC_LIBS OFF)
endif ()
if(OGRE_STATIC AND OGRE_BUILD_PLATFORM_APPLE_IOS)
        set(Boost_USE_MULTITHREADED OFF)
endif()
	
	
if (MINGW)
	# this is probably a bug in CMake: the boost find module tries to look for
	# boost libraries with name libboost_*, but CMake already prefixes library
	# search names with "lib". This is the workaround.
	set(CMAKE_FIND_LIBRARY_PREFIXES ${CMAKE_FIND_LIBRARY_PREFIXES} "")
endif ()
#include <OgreSceneManager.h>
  
set(MINEMONICS_BOOST_COMPONENTS log)
find_package(Boost COMPONENTS ${MINEMONICS_BOOST_COMPONENTS} REQUIRED)

set(OGRE_LIBRARIES ${OGRE_LIBRARIES} ${Boost_LIBRARIES})
set(OGRE_INCLUDE_DIRS ${OGRE_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})

if(Boost_FOUND)
	message(STATUS "Found Boost log: ${Boost_LIBRARIES}")
else ()
	message(SEND_ERROR "Failed to find Boost.")
endif(Boost_FOUND)

## OGRE dependencies

set(Boost_ADDITIONAL_VERSIONS "1.44" "1.44.0" "1.42" "1.42.0" "1.41.0" "1.41" "1.40.0" "1.40" "1.39.0" "1.39" "1.38.0" "1.38" "1.37.0" "1.37" )
# Components that need linking (NB does not include header-only components like bind)
## DEVELOPMENT: Minemonics needs log
set(OGRE_BOOST_COMPONENTS thread date_time)
find_package(Boost COMPONENTS ${OGRE_BOOST_COMPONENTS} REQUIRED)
if (NOT Boost_FOUND)
	# Try again with the other type of libs
	set(Boost_USE_STATIC_LIBS NOT ${Boost_USE_STATIC_LIBS})
	find_package(Boost COMPONENTS ${OGRE_BOOST_COMPONENTS} REQUIRED)
endif()
if (Boost_FOUND AND WIN32)
    if(Boost_VERSION GREATER 104700)
        set(OGRE_BOOST_COMPONENTS thread date_time regex system)
    endif(Boost_VERSION GREATER 104700)
    if(Boost_VERSION GREATER 104900)
        set(OGRE_BOOST_COMPONENTS thread date_time regex system chrono)
    endif(Boost_VERSION GREATER 104900)
    find_package(Boost COMPONENTS ${OGRE_BOOST_COMPONENTS} REQUIRED)
endif(Boost_FOUND AND WIN32)
find_package(Boost REQUIRED)

if(Boost_FOUND)
	message(STATUS "Found Boost: ${Boost_LIBRARIES}")
else ()
	message(SEND_ERROR "Failed to find Boost.")
endif(Boost_FOUND)
 
	# Set up referencing of Boost
include_directories(${Boost_INCLUDE_DIRS})
add_definitions(-DBOOST_ALL_NO_LIB)
add_definitions(-DBOOST_LOG_DYN_LINK)
set(OGRE_LIBRARIES ${OGRE_LIBRARIES} ${Boost_LIBRARIES})

######################################################################
# SDL2
######################################################################

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIR})
set(OGRE_LIBRARIES ${OGRE_LIBRARIES} ${SDL2_LIBRARY})


######################################################################
# CEGUI
######################################################################

find_package(CEGUI REQUIRED)

include_directories(${CEGUI_INCLUDE_DIR})
set(OGRE_LIBRARIES ${OGRE_LIBRARIES} ${CEGUI_LIBRARIES})
include_directories(${CEGUI_OgreRenderer_INCLUDE_DIRS})
set(OGRE_LIBRARIES ${OGRE_LIBRARIES} ${CEGUI_OgreRenderer_LIBRARIES})

######################################################################
# MathGL
######################################################################

find_package(MathGL2 REQUIRED)

include_directories(${MATHGL2_INCLUDE_DIR})
set(OGRE_LIBRARIES ${OGRE_LIBRARIES} ${MATHGL2_LIBRARIES})

######################################################################
# Shark 2
######################################################################

find_package(Shark2 REQUIRED)

include_directories(${Shark2_INCLUDE_DIRS})
set(OGRE_LIBRARIES ${OGRE_LIBRARIES} ${Shark2_LIBRARIES})

######################################################################
# Bullet physics
######################################################################

find_package(Bullet REQUIRED)

include_directories(${BULLET_INCLUDE_DIRS})
set(OGRE_LIBRARIES ${OGRE_LIBRARIES} ${BULLET_LIBRARIES})


######################################################################
# COMPILATION
######################################################################

#DEVELOPMENT INPUT
# Append header files here

set(MODELHDRS
	# model
	./model/environments/EnvironmentPhysics.h
	./model/environments/bullet/EnvironmentBt.h
	./model/environments/bullet/HillsBt.h
	./model/environments/bullet/PlaneBt.h
	
	./model/evolution/juries/Jury.h
	./model/evolution/juries/Ones.h
	./model/evolution/juries/Velocity.h
	
	./model/evolution/population/Population.h
	./model/evolution/population/creature/Creature.h
	./model/evolution/population/creature/genome/Genome.h
	./model/evolution/population/creature/genome/Gene.h
	./model/evolution/population/creature/genome/MorphoGene.h
    ./model/evolution/population/creature/genome/MorphoGeneBranch.h
    ./model/evolution/population/creature/genome/controller/ControllerGene.h
	./model/evolution/population/creature/genome/controller/SineControllerGene.h
	
	./model/evolution/population/creature/phenome/Phenome.h
	./model/evolution/population/creature/phenome/PhenotypeGenerator.h
	./model/evolution/population/creature/phenome/Component.h
)
set(MODELSRCS
    # model
    ./model/environments/EnvironmentPhysics.cpp
	./model/environments/bullet/EnvironmentBt.cpp
	./model/environments/bullet/HillsBt.cpp
	./model/environments/bullet/PlaneBt.cpp
   
	./model/evolution/juries/Jury.cpp
	./model/evolution/juries/Ones.cpp
	./model/evolution/juries/Velocity.cpp
	
	./model/evolution/population/Population.cpp
	./model/evolution/population/creature/Creature.cpp
	./model/evolution/population/creature/genome/Genome.cpp
	./model/evolution/population/creature/genome/Gene.cpp
	./model/evolution/population/creature/genome/MorphoGene.cpp
	./model/evolution/population/creature/genome/MorphoGeneBranch.cpp
	./model/evolution/population/creature/genome/controller/ControllerGene.cpp
	./model/evolution/population/creature/genome/controller/SineControllerGene.cpp
	
	./model/evolution/population/creature/phenome/Phenome.cpp
	./model/evolution/population/creature/phenome/PhenotypeGenerator.cpp
	./model/evolution/population/creature/phenome/Component.cpp
)
set(CONTROLLERHDRS
	# controller
	./controller/camera/CameraHandler.h
	./controller/input/ApplicationScancode.h
	./controller/input/ApplicationKeycode.h
	./controller/input/ApplicationMousecode.h
	./controller/input/SDL2InputHandler.h
	./controller/input/CEGUIInputHandler.h
	./controller/input/OgreInputHandler.h
	./controller/StateHandler.h
    ./controller/physics/PhysicsController.h
    ./controller/SaveController.h
)
set(CONTROLLERSRCS
	# controller
	./controller/camera/CameraHandler.cpp
	./controller/input/SDL2InputHandler.cpp
	./controller/input/CEGUIInputHandler.cpp
	./controller/input/OgreInputHandler.cpp
	./controller/StateHandler.cpp
	./controller/physics/PhysicsController.cpp
)
set(VIEWHDRS
	# view
	./view/environments/EnvironmentGraphics.h
	./view/environments/Environment.h
	./view/ogre3D/environments/envgenerators/PerlinNoiseTerrainGenerator.h
	./view/ogre3D/environments/EnvironmentO3D.h
	./view/ogre3D/environments/OpenSeaO3D.h
	./view/ogre3D/environments/PlaneO3D.h
	./view/ogre3D/environments/HillsO3D.h
	
	./view/ogre3D/bullet/OgreDebugDrawer.h
	./view/ogre3D/bullet/OgreBulletUtils.h
	./view/ogre3D/overlay/InfoOverlay.h
	./view/ogre3D/overlay/InfoOverlayData.h
	
    ## CEGUI
	./view/CEGUI/GUISheetHandler.h
	./view/CEGUI/ParamsPanel.h
	./view/CEGUI/CEGUIBuilder.h
	
	## MathGL
    ./view/MathGL/MathGLWindow.h
)
set(VIEWSRCS
	# view
	./view/environments/EnvironmentGraphics.cpp
    ./view/environments/Environment.cpp
    ./view/ogre3D/environments/envgenerators/PerlinNoiseTerrainGenerator.cpp
	./view/ogre3D/environments/EnvironmentO3D.cpp
	./view/ogre3D/environments/HillsO3D.cpp
	./view/ogre3D/environments/OpenSeaO3D.cpp
	./view/ogre3D/environments/PlaneO3D.cpp
	
	./view/ogre3D/bullet/OgreDebugDrawer.cpp
	./view/ogre3D/overlay/InfoOverlay.cpp
	./view/ogre3D/overlay/InfoOverlayData.cpp
	
	## CEGUI
	./view/CEGUI/GUISheetHandler.cpp
	./view/CEGUI/ParamsPanel.cpp
	./view/CEGUI/CEGUIBuilder.cpp
	
	## MathGL
	./view/MathGL/MathGLWindow.cpp
)
set(MISCHDRS
	# configuration
	./configuration/ApplicationConfiguration.h
	./configuration/CameraConfiguration.h
	./configuration/ControlConfiguration.h
	./configuration/PhysicsConfiguration.h
	./configuration/NeuronalNetworkConfiguration.h
	./configuration/MorphologyConfiguration.h
	./configuration/GeneticsConfiguration.h
	./configuration/FitnessConfiguration.h
	./configuration/EnvironmentConfiguration.h
	./configuration/EvolutionConfiguration.h
	./configuration/PopulationConfiguration.h
	./configuration/OgreSystemConfigStrings.h
	./configuration/CEGUIConfiguration.h
	
	# logger
	./utils/logging/Logger.h
	./utils/Randomness.h
	./utils/NameGenerator.h
)
set(MISCSRCS
	# logger
	./utils/logging/Logger.cpp
	./utils/Randomness.cpp
	./utils/NameGenerator.cpp
)

set(TESTHDRS
    ${MODELHDRS}
    #${VIEWHDRS}
    #${CONTROLLERHDRS}
    ${MISCHDRS}
)
set(TESTSRCS
    ${MODELSRCS}
    #${VIEWSRCS}
    #${CONTROLLERSRCS}
    ${MISCSRCS}
    ./model/evolution/juries/Velocity_test.cpp
    ./model/evolution/juries/Ones_test.cpp
    ./model/evolution/population/creature/genome/controller/SineControllerGene_test.cpp
    ./model/evolution/population/creature/genome/MorphoGeneBranch_test.cpp
    ./model/evolution/population/creature/genome/MorphoGene_test.cpp
    ./model/evolution/population/creature/genome/Genome_test.cpp
    ./model/evolution/population/creature/Creature_test.cpp
    ./model/evolution/population/Population_test.cpp
    ./utils/NameGenerator_test.cpp
    
    #test runner
    ./test/TestRunner.cpp
)
set(HDRS
    ${MODELHDRS}
    ${VIEWHDRS}
    ${CONTROLLERHDRS}
    ${MISCHDRS}
    
    # base
	./BaseApplication.h
	./SimulationManager.h
)

# Append source files here
set(SRCS
    ${MODELSRCS}
    ${VIEWSRCS}
    ${CONTROLLERSRCS}
    ${MISCSRCS}
    
    # base
	./BaseApplication.cpp
	./SimulationManager.cpp	
)
 
include_directories(
	${OGRE_INCLUDE_DIRS}
	${OGRE_SAMPLES_INCLUDEPATH}
	${OGRE_Terrain_INCLUDE_DIRS}
	${OGRE_Paging_INCLUDE_DIRS}
	${OGRE_Overlay_INCLUDE_DIRS}
	${PROJECT_HOME}
)

add_executable(OgreApp WIN32 ${HDRS} ${SRCS})
 
set_target_properties(OgreApp PROPERTIES DEBUG_POSTFIX _d)

######################################################################
# LINKING
######################################################################
 
target_link_libraries(OgreApp ${OGRE_LIBRARIES} ${OGRE_Overlay_LIBRARIES})
 
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/dist/bin)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/dist/media)
 
 
######################################################################
# POST COMPILATION (INSTALLATION etc.)
######################################################################

# post-build copy for win32
if(WIN32 AND NOT MINGW)
	add_custom_command( TARGET OgreApp PRE_BUILD
		COMMAND if not exist .\\dist\\bin mkdir .\\dist\\bin )
	add_custom_command( TARGET OgreApp POST_BUILD
		COMMAND copy \"$(TargetPath)\" .\\dist\\bin )
endif(WIN32 AND NOT MINGW)

if(MINGW OR UNIX)
	set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/dist/bin)
endif(MINGW OR UNIX)
 
if(WIN32)
 
	install(TARGETS OgreApp
		RUNTIME DESTINATION bin
		CONFIGURATIONS All)
 
	install(DIRECTORY ${CMAKE_SOURCE_DIR}/dist/Media
		DESTINATION ./
		CONFIGURATIONS Release RelWithDebInfo Debug
	)
 
	install(FILES ${CMAKE_SOURCE_DIR}/dist/bin/plugins.cfg
		${CMAKE_SOURCE_DIR}/dist/bin/resources.cfg
		DESTINATION bin
		CONFIGURATIONS Release RelWithDebInfo
	)
 
	install(FILES ${CMAKE_SOURCE_DIR}/dist/bin/plugins_d.cfg
		${CMAKE_SOURCE_DIR}/dist/bin/resources_d.cfg
		DESTINATION bin
		CONFIGURATIONS Debug
	)
 
        # NOTE: for the 1.7.1 sdk the OIS dll is called OIS.dll instead of libOIS.dll
        # so you'll have to change that to make it work with 1.7.1
	install(FILES ${OGRE_PLUGIN_DIR_REL}/OgreMain.dll
		${OGRE_PLUGIN_DIR_REL}/RenderSystem_Direct3D9.dll
		${OGRE_PLUGIN_DIR_REL}/RenderSystem_GL.dll
		${OGRE_PLUGIN_DIR_REL}/libOIS.dll
		DESTINATION bin
		CONFIGURATIONS Release RelWithDebInfo
	)
 
	install(FILES ${OGRE_PLUGIN_DIR_DBG}/OgreMain_d.dll
		${OGRE_PLUGIN_DIR_DBG}/RenderSystem_Direct3D9_d.dll
		${OGRE_PLUGIN_DIR_DBG}/RenderSystem_GL_d.dll
		${OGRE_PLUGIN_DIR_DBG}/libOIS_d.dll
		DESTINATION bin
		CONFIGURATIONS Debug
	)
 
   # as of sdk 1.7.2 we need to copy the boost dll's as well
   # because they're not linked statically (it worked with 1.7.1 though)
   install(FILES ${Boost_DATE_TIME_LIBRARY_RELEASE}
      ${Boost_THREAD_LIBRARY_RELEASE}
      DESTINATION bin
      CONFIGURATIONS Release RelWithDebInfo
   )
 
   install(FILES ${Boost_DATE_TIME_LIBRARY_DEBUG}
      ${Boost_THREAD_LIBRARY_DEBUG}
      DESTINATION bin
      CONFIGURATIONS Debug
   )
endif(WIN32)

if(UNIX)
 
	install(TARGETS OgreApp
		RUNTIME DESTINATION bin
		CONFIGURATIONS All)
 
	install(DIRECTORY ${CMAKE_SOURCE_DIR}/dist/media
		DESTINATION ./
		CONFIGURATIONS Release RelWithDebInfo Debug
	)
 
	install(FILES ${CMAKE_SOURCE_DIR}/dist/bin/plugins.cfg
		${CMAKE_SOURCE_DIR}/dist/bin/resources.cfg
		DESTINATION bin
		CONFIGURATIONS Release RelWithDebInfo Debug
	)
 
endif(UNIX)

# Setup testing
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})

# Add test cpp file
add_executable(runUnitTests
    ${TESTHDRS}
    ${TESTSRCS}
)

# Link test executable against gtest & gtest_main
target_link_libraries(runUnitTests ${GTEST_BOTH_LIBRARIES} ${OGRE_LIBRARIES} ${OGRE_Overlay_LIBRARIES})

add_test(
    NAME runUnitTests
    COMMAND runUnitTests
)
 
