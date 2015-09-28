/*
 * Definitions.hpp
 *
 *  Created on: Sep 20, 2015
 *      Author: leviathan
 */

#ifndef CONFIGURATION_DEFINITIONS_HPP_
#define CONFIGURATION_DEFINITIONS_HPP_

// This tries to turn off the OGRE debug output
#ifndef OGRE_DEBUG_MODE
#define OGRE_DEBUG_MODE 0
#endif

// This tries to turn off the CEGUI debug information
#ifndef DEBUG
#define DEBUG 0
#endif

// Uncomment this if you are using a double precision build of bullet
#ifndef BT_USE_DOUBLE_PRECISION
#define BT_USE_DOUBLE_PRECISION 1
#endif

#endif /* CONFIGURATION_DEFINITIONS_HPP_ */
