#ifndef UTILS_MATHUTILS_HPP_
#define UTILS_MATHUTILS_HPP_

//# corresponding headers
//# forward declarations
//# system headers
//## controller headers
//## model headers
#include <OgreVector3.h>
#include <OgreQuaternion.h>
#include <LinearMath/btVector3.h>
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

	static bool isNaN(const Ogre::Vector3& v);

	static bool isNaN(const Ogre::Quaternion& q);

	static bool isNaN(const btVector3& v);

	static bool isNaN(const btQuaternion& q);

	static bool isNaN(const btTransform& t);

	static bool isInf(double d);

	static bool isInf(const Ogre::Vector3& v);

	static bool isInf(const Ogre::Quaternion& q);

	static bool isInf(const btVector3& v);

	static bool isInf(const btQuaternion& q);

	static bool isInf(const btTransform& t);

	static bool isFinite(double d);

	static bool isFinite(const Ogre::Vector3& v);

	static bool isFinite(const Ogre::Quaternion& q);

	static bool isFinite(const btVector3& v);

	static bool isFinite(const btQuaternion& q);

	static bool isFinite(const btTransform& t);
};

#endif /* UTILS_MATHUTILS_HPP_ */
