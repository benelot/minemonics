//# corresponding header
#include <model/universe/environments/bullet/HillsBt.hpp>

//# forward declarations
//# system headers
#include <cstring>

//## controller headers
//## model headers
#include <BulletCollision/CollisionDispatch/btCollisionObject.h>
#include <BulletCollision/CollisionShapes/btConcaveShape.h>
#include <BulletCollision/CollisionShapes/btHeightfieldTerrainShape.h>
#include <BulletDynamics/Dynamics/btRigidBody.h>
#include <LinearMath/btDefaultMotionState.h>
#include <LinearMath/btQuaternion.h>
#include <LinearMath/btScalar.h>
#include <LinearMath/btTransform.h>
#include <LinearMath/btVector3.h>
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

BoostLogger HillsBt::mBoostLogger; /*<! initialize the boost logger*/
HillsBt::_Init HillsBt::_initializer;
HillsBt::HillsBt() {
}

HillsBt::~HillsBt() {
}

void HillsBt::initialize(Ogre::Terrain* terrain) {

	float* terrainHeightData = terrain->getHeightData();
	Ogre::Vector3 terrainPosition = terrain->getPosition();

	btScalar* dataConvert =
		new btScalar[terrain->getSize() * terrain->getSize()];
	for (int i = 0; i < terrain->getSize(); i++)
		memcpy(dataConvert + terrain->getSize() * i, // source
		terrainHeightData + terrain->getSize() * (terrain->getSize() - i - 1), // target
		sizeof(float) * (terrain->getSize()) // size
			);

	float metersBetweenVertices = terrain->getWorldSize()
		/ (terrain->getSize() - 1); //edit: fixed 0 -> 1 on 2010-08-13
	btVector3 localScaling(metersBetweenVertices, 1, metersBetweenVertices);

#ifdef BT_USE_DOUBLE_PRECISION
	btHeightfieldTerrainShape* groundShape = new btHeightfieldTerrainShape(
		terrain->getSize(), terrain->getSize(), dataConvert,
		btScalar(1/*ignore*/), btScalar(terrain->getMinHeight()),
		btScalar(terrain->getMaxHeight()), 1, PHY_DOUBLE, true);
#else
	btHeightfieldTerrainShape* groundShape = new btHeightfieldTerrainShape(
		terrain->getSize(), terrain->getSize(), dataConvert,
		btScalar(1/*ignore*/), btScalar(terrain->getMinHeight()),
		btScalar(terrain->getMaxHeight()), 1, PHY_FLOAT, true);
#endif

	groundShape->setUseDiamondSubdivision(true);
	groundShape->setLocalScaling(localScaling);

	mGroundBody = new btRigidBody(btScalar(0.0f), new btDefaultMotionState(),
		groundShape);

	mGroundBody->getWorldTransform().setOrigin(
		btVector3(terrainPosition.x,
			terrainPosition.y
				+ (terrain->getMaxHeight() - terrain->getMinHeight()) / 2,
			terrainPosition.z));

	mGroundBody->getWorldTransform().setRotation(
		btQuaternion(Ogre::Quaternion::IDENTITY.x, Ogre::Quaternion::IDENTITY.y,
			Ogre::Quaternion::IDENTITY.z, Ogre::Quaternion::IDENTITY.w));

	// disable debug visualization
	mGroundBody->setCollisionFlags(
		mGroundBody->getCollisionFlags()
			| btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT);
}

