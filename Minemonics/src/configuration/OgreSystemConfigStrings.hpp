#ifndef CONFIGURATION_OGRESYSTEMCONFIGSTRINGS_H_
#define CONFIGURATION_OGRESYSTEMCONFIGSTRINGS_H_


//# corresponding headers
//# forward declarations
//# system headers
//## controller headers
//## model headers
#include <OgreUTFString.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers

/**
 * @brief		The configuration of the Ogre Graphics System.
 * @details		Details
 * @date		2015-02-02
 * @author		Benjamin Ellenberger
 */
class OgreConf {
public:
	/** Ogre config strings */
	static const Ogre::UTFString VIDEO_MODE; /**!< Video mode string*/
	static const Ogre::UTFString FULL_SCREEN; /**!< Full screen string */
	static const Ogre::UTFString GAMMA_CONV; /**!< Gamma conversion string */

	static const std::string YES; /**!< Yes string */
	static const std::string NO; /**!< No string */
};

const Ogre::UTFString OgreConf::VIDEO_MODE("Video Mode");

const Ogre::UTFString OgreConf::FULL_SCREEN("Full Screen");
const Ogre::UTFString OgreConf::GAMMA_CONV("sRGB Gamma Conversion");

const std::string OgreConf::YES = "Yes";
const std::string OgreConf::NO = "No";

#endif /* CONFIGURATION_OGRESYSTEMCONFIGSTRINGS_H_ */
