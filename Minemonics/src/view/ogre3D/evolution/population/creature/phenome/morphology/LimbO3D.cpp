/*
 * LimbO3D.cpp
 *
 *  Created on: Dec 19, 2014
 *      Author: leviathan
 */

//# corresponding header
#include "LimbO3D.h"

//# forward declarations
//# system headers
#include <boost/lexical_cast.hpp>

//## controller headers
//## model headers
//## view headers
#include "utils/procedural/ProceduralCapsuleGenerator.h"

//# custom headers
//## base headers
#include "SimulationManager.h"

//## configuration headers
//## controller headers
#include "controller/evolution/population/creature/phenome/morphology/Limb.h"

//## model headers
//## view headers
//## utils headers

#ifndef NULL
#define NULL 0
#endif

LimbO3D::LimbO3D() :
		mEntity(NULL), mEntityNode(NULL), mSimulationManager(NULL) {

}

LimbO3D::~LimbO3D() {
	delete mEntityNode;
	delete mEntity;
}

void LimbO3D::initialize(SimulationManager* simulationManager,
		Limb::PrimitiveType type, Ogre::Vector3 scale) {
	mSimulationManager = simulationManager;

	switch (type) {
	case Limb::BLOCK:
		mEntity = mSimulationManager->getSceneManager()->createEntity(
				Ogre::SceneManager::PT_CUBE);
		mEntity->setMaterialName("honeycomb");
		mEntityNode =
				mSimulationManager->getSceneManager()->getRootSceneNode()->createChildSceneNode();
		mEntityNode->attachObject(mEntity);

		mEntityNode->scale(
				scale.x * PhysicsConfiguration::BULLET_OGRE_BOX_SCALING_FACTOR,
				scale.y * PhysicsConfiguration::BULLET_OGRE_BOX_SCALING_FACTOR,
				scale.z * PhysicsConfiguration::BULLET_OGRE_BOX_SCALING_FACTOR);
		break;
	case Limb::CAPSULE:
		Ogre::String name = boost::lexical_cast<std::string>(this) + "/"
						+ "Limb";

		//because we can only scale bullet capsule that way, we do not scale this object differently
		Procedural::CapsuleGenerator().setPosition(0, 0, 0).setRadius(0.5f*scale.z).setHeight(scale.y).realizeMesh(
				name);
		mEntity = mSimulationManager->getSceneManager()->createEntity(name);
		mEntity->setMaterialName("honeycomb");
		mEntityNode =
				mSimulationManager->getSceneManager()->getRootSceneNode()->createChildSceneNode();
		mEntityNode->attachObject(mEntity);
		break;
	}
}

void LimbO3D::update() {
	mEntityNode->setPosition(mPosition);
	mEntityNode->setOrientation(mOrientation);
}

