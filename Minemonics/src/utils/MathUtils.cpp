//# corresponding headers
//# forward declarations
//# system headers
//## controller headers
//## model headers
//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers
#include <utils/MathUtils.hpp>
#include <utils/ogre3D/OgreBulletUtils.hpp>

bool MathUtils::isNaN(double d) {
	// Only NaN is not itself
	return d != d;
}

bool MathUtils::isNaN(Ogre::Vector3 v) {
	return isNaN(OgreBulletUtils::convert(v));
}

bool MathUtils::isNaN(Ogre::Quaternion q) {
	return isNaN(OgreBulletUtils::convert(q));
}

bool MathUtils::isNaN(btVector3 v) {
	return isNaN(v.w()) || isNaN(v.x()) || isNaN(v.y()) || isNaN(v.z());
}

bool MathUtils::isNaN(btQuaternion q) {
	return isNaN(q.w()) || isNaN(q.x()) || isNaN(q.y()) || isNaN(q.z());
}

bool MathUtils::isNaN(btTransform t) {
	return isNaN(t.getOrigin()) || isNaN(t.getRotation());
}

bool MathUtils::isInf(double d) {
	// Only Inf does pass this
	return (d/0.0f == d);
}

bool MathUtils::isInf(Ogre::Vector3 v) {
	return isInf(OgreBulletUtils::convert(v));
}

bool MathUtils::isInf(Ogre::Quaternion q) {
	return isInf(OgreBulletUtils::convert(q));
}

bool MathUtils::isInf(btVector3 v) {
	return isInf(v.w()) || isInf(v.x()) || isInf(v.y()) || isInf(v.z());
}

bool MathUtils::isInf(btQuaternion q) {
	return isInf(q.w()) || isInf(q.x()) || isInf(q.y()) || isInf(q.z());
}

bool MathUtils::isInf(btTransform t) {
	return isInf(t.getOrigin()) || isInf(t.getRotation());
}

bool MathUtils::isFinite(double d) {
	return !(isInf(d) && isNaN(d));
}

bool MathUtils::isFinite(Ogre::Vector3 v) {
	return !(isInf(OgreBulletUtils::convert(v)) && isNaN(OgreBulletUtils::convert(v)));
}

bool MathUtils::isFinite(Ogre::Quaternion q) {
	return !(isInf(OgreBulletUtils::convert(q)) && isNaN(OgreBulletUtils::convert(q)));
}

bool MathUtils::isFinite(btVector3 v) {
	return !(isInf(v) && isNaN(v));
}

bool MathUtils::isFinite(btQuaternion q) {
	return !(isInf(q)&& isNaN(q));
}

bool MathUtils::isFinite(btTransform t) {
	return !(isInf(t) && isNaN(t));
}


