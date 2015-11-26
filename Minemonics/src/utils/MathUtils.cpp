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

bool MathUtils::isNaN(double d) {
	// Only NaN is not itself
	return d != d;
//	return std::isnan(d);
}

bool MathUtils::isNaN(const Ogre::Vector3& v) {
	return isNaN(v.x) || isNaN(v.y) || isNaN(v.z);
}

bool MathUtils::isNaN(const Ogre::Quaternion& q) {
	return isNaN(q.w) || isNaN(q.x) || isNaN(q.y) || isNaN(q.z);
}

bool MathUtils::isNaN(const btVector3& v) {
	return isNaN(v.w()) || isNaN(v.x()) || isNaN(v.y()) || isNaN(v.z());
}

bool MathUtils::isNaN(const btQuaternion& q) {
	return isNaN(q.w()) || isNaN(q.x()) || isNaN(q.y()) || isNaN(q.z());
}

bool MathUtils::isNaN(const btTransform& t) {
	btVector3 v = t.getOrigin();
	btQuaternion q = t.getRotation();
	return isNaN(v) || isNaN(q);
}

bool MathUtils::isInf(double d) {
	// Only Inf does pass this
	return (d/0.0f == d);
//	return std::isinf(d);
}

bool MathUtils::isInf(const Ogre::Vector3& v) {
	return isInf(v.x) || isInf(v.y) || isInf(v.z);
}

bool MathUtils::isInf(const Ogre::Quaternion& q) {
	return isInf(q.w) || isInf(q.x) || isInf(q.y) || isInf(q.z);
}

bool MathUtils::isInf(const btVector3& v) {
	return isInf(v.w()) || isInf(v.x()) || isInf(v.y()) || isInf(v.z());
}

bool MathUtils::isInf(const btQuaternion& q) {
	return isInf(q.w()) || isInf(q.x()) || isInf(q.y()) || isInf(q.z());
}

bool MathUtils::isInf(const btTransform& t) {
	btVector3 v = t.getOrigin();
	btMatrix3x3 m = t.getBasis();
	btQuaternion q;
	m.getRotation(q);
	bool isInf1 = isInf(v);
	bool isInf2 = isInf(q);
	return (isInf1 || isInf2);
}

bool MathUtils::isFinite(double d) {
	return !(isInf(d) || isNaN(d));
}

bool MathUtils::isFinite(const Ogre::Vector3& v) {
	return !(isInf(v) || isNaN(v));
}

bool MathUtils::isFinite(const Ogre::Quaternion& q) {
	return !(isInf(q) || isNaN(q));
}

bool MathUtils::isFinite(const btVector3& v) {
	return !(isInf(v) || isNaN(v));
}

bool MathUtils::isFinite(const btQuaternion& q) {
	return !(isInf(q) || isNaN(q));
}

bool MathUtils::isFinite(const btTransform& t) {
	return !(isInf(t) || isNaN(t));
}


