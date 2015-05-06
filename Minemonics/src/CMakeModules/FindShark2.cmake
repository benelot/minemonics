# - FindShark.cmake
# This module can be used to find Shark 2.*.
#
# The following variables will be defined for your use:
#
#  Shark2_FOUND           = Shark 2.* found
#  Shark2_INCLUDE_DIRS    = The Shark 2.* include directories
#  Shark2_LIBRARIES       = The libraries to link against to use Shark 2.*
#
# Typical usage could be something like this:
#   find_package(Shark2 REQUIRED)
#   include_directories(${Shark2_INCLUDE_DIRS})
#   add_executable(myexe main.cpp)
#   target_link_libraries(myexe ${Shark2_LIBRARIES})
#
#=============================================================================
# Copyright (c) 2014 Benjamin Ellenberger <be.ellenberger@gmail.com>
#
# Distributed under the OSI-approved BSD License (the "License");
# see accompanying file COPYING-CMAKE-MODULES for details.
#
# This software is distributed WITHOUT ANY WARRANTY; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the License for more information.
#=============================================================================


####
# Include LibFindMacros directly into this file
# The original LibFindMacros can be found on the internet as LibFindMacros.txt
####
# Works the same as find_package, but forwards the "REQUIRED" and "QUIET" arguments
# used for the current package. For this to work, the first parameter must be the
# prefix of the current package, then the prefix of the new package etc, which are
# passed to find_package.
macro (libfind_package PREFIX)
  set (LIBFIND_PACKAGE_ARGS ${ARGN})
  if (${PREFIX}_FIND_QUIETLY)
    set (LIBFIND_PACKAGE_ARGS ${LIBFIND_PACKAGE_ARGS} QUIET)
  endif (${PREFIX}_FIND_QUIETLY)
  if (${PREFIX}_FIND_REQUIRED)
    set (LIBFIND_PACKAGE_ARGS ${LIBFIND_PACKAGE_ARGS} REQUIRED)
  endif (${PREFIX}_FIND_REQUIRED)
  find_package(${LIBFIND_PACKAGE_ARGS})
endmacro (libfind_package)

# CMake developers made the UsePkgConfig system deprecated in the same release (2.6)
# where they added pkg_check_modules. Consequently I need to support both in my scripts
# to avoid those deprecated warnings. Here's a helper that does just that.
# Works identically to pkg_check_modules, except that no checks are needed prior to use.
macro (libfind_pkg_check_modules PREFIX PKGNAME)
  if (${CMAKE_MAJOR_VERSION} EQUAL 2 AND ${CMAKE_MINOR_VERSION} EQUAL 4)
    include(UsePkgConfig)
    pkgconfig(${PKGNAME} ${PREFIX}_INCLUDE_DIRS ${PREFIX}_LIBRARY_DIRS ${PREFIX}_LDFLAGS ${PREFIX}_CFLAGS)
  else (${CMAKE_MAJOR_VERSION} EQUAL 2 AND ${CMAKE_MINOR_VERSION} EQUAL 4)
    find_package(PkgConfig)
    if (PKG_CONFIG_FOUND)
      pkg_check_modules(${PREFIX} ${PKGNAME})
    endif (PKG_CONFIG_FOUND)
  endif (${CMAKE_MAJOR_VERSION} EQUAL 2 AND ${CMAKE_MINOR_VERSION} EQUAL 4)
endmacro (libfind_pkg_check_modules)

# Do the final processing once the paths have been detected.
# If include dirs are needed, ${PREFIX}_PROCESS_INCLUDES should be set to contain
# all the variables, each of which contain one include directory.
# Ditto for ${PREFIX}_PROCESS_LIBS and library files.
# Will set ${PREFIX}_FOUND, ${PREFIX}_INCLUDE_DIRS and ${PREFIX}_LIBRARIES.
# Also handles errors in case library detection was required, etc.
macro (libfind_process PREFIX)
  # Skip processing if already processed during this run
  if (NOT ${PREFIX}_FOUND)
    # Start with the assumption that the library was found
    set (${PREFIX}_FOUND TRUE)

    # Process all includes and set _FOUND to false if any are missing
    foreach (i ${${PREFIX}_PROCESS_INCLUDES})
      if (${i})
        set (${PREFIX}_INCLUDE_DIRS ${${PREFIX}_INCLUDE_DIRS} ${${i}})
        mark_as_advanced(${i})
      else (${i})
        set (${PREFIX}_FOUND FALSE)
      endif (${i})
    endforeach (i)

    # Process all libraries and set _FOUND to false if any are missing
    foreach (i ${${PREFIX}_PROCESS_LIBS})
      if (${i})
        set (${PREFIX}_LIBRARIES ${${PREFIX}_LIBRARIES} ${${i}})
        mark_as_advanced(${i})
      else (${i})
        set (${PREFIX}_FOUND FALSE)
      endif (${i})
    endforeach (i)

    # Print message and/or exit on fatal error
    if (${PREFIX}_FOUND)
      if (NOT ${PREFIX}_FIND_QUIETLY)
        message (STATUS "Found ${PREFIX} ${${PREFIX}_VERSION}: ${${PREFIX}_LIBRARIES}")
      endif (NOT ${PREFIX}_FIND_QUIETLY)
    else (${PREFIX}_FOUND)
      if (${PREFIX}_FIND_REQUIRED)
        foreach (i ${${PREFIX}_PROCESS_INCLUDES} ${${PREFIX}_PROCESS_LIBS})
          message("${i}=${${i}}")
        endforeach (i)
        message (FATAL_ERROR "Required library ${PREFIX} NOT FOUND.\nInstall the library (dev version) and try again. If the library is already installed, use ccmake to set the missing variables manually.")
      endif (${PREFIX}_FIND_REQUIRED)
    endif (${PREFIX}_FOUND)
  endif (NOT ${PREFIX}_FOUND)
endmacro (libfind_process)

macro(libfind_library PREFIX basename)
  set(TMP "")
  if(MSVC80)
    set(TMP -vc80)
  endif(MSVC80)
  if(MSVC90)
    set(TMP -vc90)
  endif(MSVC90)
  set(${PREFIX}_LIBNAMES ${basename}${TMP})
  if(${ARGC} GREATER 2)
    set(${PREFIX}_LIBNAMES ${basename}${TMP}-${ARGV2})
    string(REGEX REPLACE "\\." "_" TMP ${${PREFIX}_LIBNAMES})
    set(${PREFIX}_LIBNAMES ${${PREFIX}_LIBNAMES} ${TMP})
  endif(${ARGC} GREATER 2)
  find_library(${PREFIX}_LIBRARY
    NAMES ${${PREFIX}_LIBNAMES}
    PATHS ${${PREFIX}_PKGCONF_LIBRARY_DIRS}
  )
endmacro(libfind_library)

################################################################################
# Display a status message unless FIND_QUIETLY is set
################################################################################
macro(pkg_message PREFIX)
    if (NOT ${PREFIX}_FIND_QUIETLY)
        message(STATUS ${ARGN})
    endif ()
endmacro(pkg_message)

############
# Main
############

pkg_message(Shark "Looking for Shark 2.* dependencies...")

#map default build type to release
IF(NOT CMAKE_BUILD_TYPE)
       SET(CMAKE_BUILD_TYPE "Release")
ENDIF(NOT CMAKE_BUILD_TYPE)
IF((CMAKE_BUILD_TYPE MATCHES "debug") OR (CMAKE_BUILD_TYPE MATCHES "DEBUG"))
	SET(CMAKE_BUILD_TYPE "Debug")
ENDIF((CMAKE_BUILD_TYPE MATCHES "debug") OR (CMAKE_BUILD_TYPE MATCHES "DEBUG"))
IF((CMAKE_BUILD_TYPE MATCHES "release") OR (CMAKE_BUILD_TYPE MATCHES "RELEASE"))
	SET(CMAKE_BUILD_TYPE "Release")
ENDIF((CMAKE_BUILD_TYPE MATCHES "release") OR (CMAKE_BUILD_TYPE MATCHES "RELEASE"))


SET(Boost_USE_MULTITHREADED ON)
ADD_DEFINITIONS( -DBOOST_PARAMETER_MAX_ARITY=15 -DBOOST_FILESYSTEM_VERSION=3 )

# Dependencies of Shark
libfind_package(Shark2 Boost 1.48.0 COMPONENTS system date_time filesystem 
program_options serialization thread unit_test_framework)


# Use pkg-config to get hints about paths
MESSAGE("Trying to hints about where to locate Shark 2.* from pkg-config...")
libfind_pkg_check_modules(Shark2_PKGCONF Shark2)

pkg_message(Shark2 "Looking for Shark 2.*...")

#Find the Include directory
find_path(Shark2_INCLUDE_DIR 
  NAMES Population.h
  HINTS
  $ENV{SHARKDIR}
  PATH_SUFFIXES EALib
   PATHS
  ${Shark_PKGCONF_INCLUDE_DIRS}
  ~/Library/Frameworks
  /Library/Frameworks
  /usr/local/include
  /usr/include
)
get_filename_component(Shark2_INCLUDE_DIR ${Shark2_INCLUDE_DIR} DIRECTORY)
#MESSAGE("Shark2_INCLUDE_DIR is ${Shark2_INCLUDE_DIR}")

# Find the Library
FIND_LIBRARY(Shark2_LIBRARY
  NAMES libshark.so libshark
  HINTS
  $ENV{SharkDIR} 
  PATHS
  ${Shark2_PKGCONF_LIBRARY_DIRS}
  /usr/lib
)
MESSAGE("Shark2_LIBRARY is ${Shark2_LIBRARY}")

# Set the include dir variables and the libraries and let libfind_process do the rest.
# NOTE: Singular variables for this library, plural for librarires this lib dependes on.
set(Shark2_PROCESS_INCLUDES Shark2_INCLUDE_DIR Boost_INCLUDE_DIRS)
set(Shark2_PROCESS_LIBS Shark2_LIBRARY Boost_LIBRARIES)

libfind_process(Shark2)