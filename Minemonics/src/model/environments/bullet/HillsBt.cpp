/*
 * HillsBt.cpp
 *
 *  Created on: Mar 17, 2015
 *      Author: leviathan
 */

//# corresponding header
#include <BulletCollision/CollisionShapes/btHeightfieldTerrainShape.h>
#include <model/environments/bullet/HillsBt.hpp>

//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers

HillsBt::HillsBt() :
		mGroundBody(NULL), mGroundMotionState(NULL), mGroundShape(NULL) {
	// TODO Auto-generated constructor stub

}

HillsBt::~HillsBt() {
	// TODO Auto-generated destructor stub
}

void HillsBt::initialize(Ogre::Terrain* terrain) {

	float* terrainHeightData = terrain->getHeightData();
	Ogre::Vector3 terrainPosition = terrain->getPosition();

	float * dataConvert = new float[terrain->getSize() * terrain->getSize()];
	for (int i = 0; i < terrain->getSize(); i++)
		memcpy(dataConvert + terrain->getSize() * i, // source
		terrainHeightData + terrain->getSize() * (terrain->getSize() - i - 1), // target
		sizeof(float) * (terrain->getSize()) // size
				);

	float metersBetweenVertices = terrain->getWorldSize()
			/ (terrain->getSize() - 1); //edit: fixed 0 -> 1 on 2010-08-13
	btVector3 localScaling(metersBetweenVertices, 1, metersBetweenVertices);

	btHeightfieldTerrainShape* groundShape = new btHeightfieldTerrainShape(
			terrain->getSize(), terrain->getSize(), dataConvert, 1/*ignore*/,
			terrain->getMinHeight(), terrain->getMaxHeight(), 1, PHY_FLOAT,
			true);

	groundShape->setUseDiamondSubdivision(true);
	groundShape->setLocalScaling(localScaling);

	mGroundBody = new btRigidBody(0, new btDefaultMotionState(), groundShape);

	mGroundBody->getWorldTransform().setOrigin(
			btVector3(terrainPosition.x,
					terrainPosition.y
							+ (terrain->getMaxHeight()
									- terrain->getMinHeight()) / 2,
					terrainPosition.z));

	mGroundBody->getWorldTransform().setRotation(
			btQuaternion(Ogre::Quaternion::IDENTITY.x,
					Ogre::Quaternion::IDENTITY.y, Ogre::Quaternion::IDENTITY.z,
					Ogre::Quaternion::IDENTITY.w));

	// disable debug visualization
	mGroundBody->setCollisionFlags(mGroundBody->getCollisionFlags() | btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT);
}

