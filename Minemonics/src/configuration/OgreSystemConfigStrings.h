/*
 * OgreSystemConfigStrings.h
 *
 *  Created on: Mar 2, 2015
 *      Author: leviathan
 */

#ifndef OGRESYSTEMCONFIGSTRINGS_H_
#define OGRESYSTEMCONFIGSTRINGS_H_

#include "OgreUTFString.h"

class OgreConf {
public:
	static const Ogre::UTFString VIDEO_MODE;
	static const Ogre::UTFString FULL_SCREEN;
	static const Ogre::UTFString GAMMA_CONV;

	static const std::string YES;
	static const std::string NO;
};

const Ogre::UTFString OgreConf::VIDEO_MODE("Video Mode");

const Ogre::UTFString OgreConf::FULL_SCREEN("Full Screen");
const Ogre::UTFString OgreConf::GAMMA_CONV("sRGB Gamma Conversion");

const std::string OgreConf::YES = "Yes";
const std::string OgreConf::NO = "No";

#endif /* OGRESYSTEMCONFIGSTRINGS_H_ */
