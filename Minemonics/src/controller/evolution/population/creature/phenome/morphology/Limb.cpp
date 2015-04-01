/*
 * Limb.cpp
 *
 *  Created on: Dec 19, 2014
 *      Author: leviathan
 */

//# corresponding header
#include "Limb.h"

//# forward declarations
//# system headers
//## controller headers
#include <btBulletDynamicsCommon.h>

//## model headers
//## view headers
#include <boost/lexical_cast.hpp>

//# custom headers
//## base headers
#include "SimulationManager.h"

//## configuration headers
#include "configuration/PhysicsConfiguration.h"
#include "configuration/MorphologyConfiguration.h"

//## controller headers
//## model headers
#include "model/evolution/population/creature/phenome/morphology/LimbBt.h"

//## view headers
#include "view/ogre3D/evolution/population/creature/phenome/morphology/LimbO3D.h"

//## utils headers

#ifndef NULL
#define NULL 0
#endif

Limb::Limb() :
		mLimbGraphics(NULL), mLimbPhysics(NULL) {
	// TODO Auto-generated constructor stub

}

Limb::~Limb() {
	// TODO Auto-generated destructor stub
}

void Limb::initialize(SimulationManager* simulationManager,
		MorphologyConfiguration::PrimitiveType type, Ogre::Vector3 position,
		Ogre::Quaternion orientation, Ogre::Vector3 size, double mass) {
	Component::initialize(Component::Limb);
	mLimbGraphics = new LimbO3D();
	((LimbO3D*) mLimbGraphics)->initialize(simulationManager, type, size);

	mLimbPhysics = new LimbBt();
	((LimbBt*) mLimbPhysics)->initialize(
			simulationManager->getPhysicsController().getDynamicsWorld(), type,
			btVector3(position.x, position.y, position.z),
			btQuaternion(orientation.x, orientation.y, orientation.z,
					orientation.w), btVector3(size.x, size.y, size.z),
			btScalar(mass));

	update();

}

void Limb::update() {
	btRigidBody* body = ((LimbBt*) mLimbPhysics)->getRigidBody();

	if (body) {

		btVector3 Point = body->getCenterOfMassPosition();
		mLimbGraphics->setPosition(
				Ogre::Vector3((float) Point[0], (float) Point[1],
						(float) Point[2]));

		// Get the Orientation of the rigidbody as a bullet Quaternion
		// Convert it to an Ogre quaternion
		btQuaternion btq = body->getOrientation();
		Ogre::Quaternion quart = Ogre::Quaternion(btq.w(), btq.x(), btq.y(),
				btq.z());

		// Set the orientation of the rendered Object
		mLimbGraphics->setOrientation(quart);
	}

	mLimbGraphics->update();
}

std::string Limb::getInfo() {
	std::string text;
	text.append("Box coordinate: ");
	text.append(
			boost::lexical_cast<std::string>(mLimbGraphics->getPosition().x));
	text.append(",");
	text.append(
			boost::lexical_cast<std::string>(mLimbGraphics->getPosition().y));
	text.append(",");
	text.append(
			boost::lexical_cast<std::string>(mLimbGraphics->getPosition().z));
	text.append(",\n");
	text.append("---------");
	return text;
}

LimbO3D* Limb::getLimbGraphics() {
	return ((LimbO3D*) mLimbGraphics);

}

LimbBt* Limb::getLimbPhysics() {
	return ((LimbBt*) mLimbPhysics);
}

void Limb::addToWorld() {
	mLimbGraphics->addToWorld();
	mLimbPhysics->addToWorld();
}

void Limb::removeFromWorld() {
	mLimbGraphics->removeFromWorld();
	mLimbPhysics->removeFromWorld();
}

Ogre::Vector3 Limb::getIntersection(Ogre::Vector3 origin,
		Ogre::Vector3 direction) {
	return mLimbGraphics->getIntersection(origin, direction);
}

