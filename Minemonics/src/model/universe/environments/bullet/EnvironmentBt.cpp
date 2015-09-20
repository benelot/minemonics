//# corresponding header
#include <model/universe/environments/bullet/EnvironmentBt.hpp>

//# forward declarations
//# system headers
//## controller headers
//## model headers
#include <BulletCollision/CollisionDispatch/btCollisionObject.h>
#include <BulletCollision/CollisionShapes/btConcaveShape.h>
#include <BulletCollision/CollisionShapes/btHeightfieldTerrainShape.h>
#include <BulletDynamics/Dynamics/btRigidBody.h>
#include <LinearMath/btDefaultMotionState.h>
#include <LinearMath/btQuaternion.h>
#include <LinearMath/btTransform.h>
#include <LinearMath/btVector3.h>

//## view headers
#include <OgreQuaternion.h>

//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
#include <model/universe/environments/bullet/EnvironmentBt.hpp>

//## view headers
//## utils headers

BoostLogger EnvironmentBt::mBoostLogger; /*<! initialize the boost logger*/
EnvironmentBt::_Init EnvironmentBt::_initializer;
EnvironmentBt::EnvironmentBt() :
	mGroundShape(NULL), mGroundBody(NULL) {
}

EnvironmentBt::~EnvironmentBt() {
	delete mGroundBody;
	mGroundBody = NULL;

	delete mGroundShape;
	mGroundShape = NULL;
}

void EnvironmentBt::createTerrainData(Ogre::SceneNode* const sceneNode,
	const float w, const float h, const float* const data, const float minH,
	const float maxH, const Ogre::Vector3& pos, const float scale,
	const float heightScale) {

	btVector3 localScaling(scale, heightScale, scale);

	mGroundShape = new btHeightfieldTerrainShape(btScalar(w), btScalar(h), data,
		1/*ignore*/, btScalar(minH), btScalar(maxH), 1, PHY_FLOAT, true);
	((btHeightfieldTerrainShape*) mGroundShape)->setUseDiamondSubdivision(true);
	mGroundShape->setLocalScaling(localScaling);

	mGroundBody = new btRigidBody(btScalar(0), new btDefaultMotionState(),
		mGroundShape);
	mGroundBody->getWorldTransform().setOrigin(
		btVector3(scale * (w - 1) / 2, heightScale / 2 * heightScale,
			scale * (w - 1) / 2));
	Ogre::Quaternion q = Ogre::Quaternion::IDENTITY;
	mGroundBody->getWorldTransform().setRotation(
		btQuaternion(q.x, q.y, q.z, q.w));
	mGroundBody->setCollisionFlags(
		mGroundBody->getCollisionFlags() | btCollisionObject::CF_STATIC_OBJECT);
	mGroundBody->setUserPointer(NULL);
	mGroundBody->setFriction(1.0f);

	//to get custom collision callbacks in CollisionHandler
	mGroundBody->setCollisionFlags(
		mGroundBody->getCollisionFlags()
			| btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);
}
