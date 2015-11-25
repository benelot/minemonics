#ifndef UTILS_MATHUTILS_HPP_
#define UTILS_MATHUTILS_HPP_

#include <OgreVector3.h>
#include <OgreQuaternion.h>
#include <LinearMath/btVector3.h>


//# corresponding headers
//# forward declarations
//# system headers
//## controller headers
//## model headers
#include <LinearMath/btQuaternion.h>
#include <LinearMath/btTransform.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers

/**
 * @brief		MathUtils helps you to detect NaN and Infs.
 * @details		Details
 * @date		2015-11-25
 * @author		Benjamin Ellenberger
 */
class MathUtils {
public:
	static bool isNaN(double d);

	static bool isNaN(Ogre::Vector3 v);

	static bool isNaN(Ogre::Quaternion q);

	static bool isNaN(btVector3 v);

	static bool isNaN(btQuaternion q);

	static bool isNaN(btTransform t);

	static bool isInf(double d);

	static bool isInf(Ogre::Vector3 v);

	static bool isInf(Ogre::Quaternion q);

	static bool isInf(btVector3 v);

	static bool isInf(btQuaternion q);

	static bool isInf(btTransform t);

	static bool isFinite(double d);

	static bool isFinite(Ogre::Vector3 v);

	static bool isFinite(Ogre::Quaternion q);

	static bool isFinite(btVector3 v);

	static bool isFinite(btQuaternion q);

	static bool isFinite(btTransform t);
};

#endif /* UTILS_MATHUTILS_HPP_ */
