#ifndef MODEL_BULLET_OGREBULLETUTILS_H_
#define MODEL_BULLET_OGREBULLETUTILS_H_

//# corresponding headers
#include <configuration/Definitions.hpp>

//# forward declarations
//# system headers
//## controller headers
//## model headers
#include <LinearMath/btQuadWord.h>
#include <LinearMath/btQuaternion.h>
#include <LinearMath/btVector3.h>
#include <OgreColourValue.h>
#include <OgreQuaternion.h>
#include <OgreVector3.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers

/**
 * @brief		OgreBulletUtils provide conversion capabilities between Ogre3D and Bullet.
 * @details		Details
 * @date		2015-03-19
 * @author		Benjamin Ellenberger
 */
class OgreBulletUtils {
public:
	static btVector3 convert(const Ogre::Vector3& V) {
		return btVector3(V.x, V.y, V.z);
	}

	static Ogre::Vector3 convert(const btVector3& V) {
		return Ogre::Vector3(V.x(), V.y(), V.z());
	}

	static btQuaternion convert(const Ogre::Quaternion& Q) {
		return btQuaternion(Q.x, Q.y, Q.z, Q.w);
	}

	static Ogre::Quaternion convert(const btQuaternion& Q) {
		return Ogre::Quaternion(Q.w(), Q.x(), Q.y(), Q.z());
	}

	static btVector3 convert(const Ogre::ColourValue& c) {
		return btVector3(c.r, c.g, c.b);
	}

};

#endif /* MODEL_BULLET_OGREBULLETUTILS_H_ */
