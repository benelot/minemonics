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
#include <OgreSceneNode.h>

//# custom headers
//## base headers
#include "SimulationManager.h"

//## configuration headers
//## controller headers
#include "controller/evolution/population/creature/phenome/morphology/Limb.h"

//## model headers
//## view headers
#include "view/procedural/ProceduralCapsuleGenerator.h"

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
		MorphologyConfiguration::PrimitiveType type, Ogre::Vector3 scale) {
	mSimulationManager = simulationManager;

	switch (type) {
	case MorphologyConfiguration::BLOCK:
		mEntity = mSimulationManager->getSceneManager()->createEntity(
				Ogre::SceneManager::PT_CUBE);
		mEntity->setMaterialName("honeycomb");
		mEntityNode = mSimulationManager->getSceneManager()->createSceneNode();
		mEntityNode->attachObject(mEntity);

		mEntityNode->scale(
				scale.x * PhysicsConfiguration::BULLET_OGRE_BOX_SCALING_FACTOR,
				scale.y * PhysicsConfiguration::BULLET_OGRE_BOX_SCALING_FACTOR,
				scale.z * PhysicsConfiguration::BULLET_OGRE_BOX_SCALING_FACTOR);
		break;
	case MorphologyConfiguration::CAPSULE:
		Ogre::String name = boost::lexical_cast<std::string>(this) + "/"
				+ "Limb";

		//because we can only scale bullet capsule that way, we do not scale this object differently
		Procedural::CapsuleGenerator().setPosition(0, 0, 0).setRadius(
				0.5f * scale.z).setHeight(scale.y).realizeMesh(name);
		mEntity = mSimulationManager->getSceneManager()->createEntity(name);
		mEntity->setMaterialName("honeycomb");
		mEntityNode = mSimulationManager->getSceneManager()->createSceneNode();
		mEntityNode->attachObject(mEntity);
		break;
	}
}

void LimbO3D::update() {
	mEntityNode->setPosition(mPosition);
	mEntityNode->setOrientation(mOrientation);
}

void LimbO3D::addToWorld() {
	mSimulationManager->getSceneManager()->getRootSceneNode()->addChild(
			mEntityNode);
}

void LimbO3D::removeFromWorld() {
	mSimulationManager->getSceneManager()->getRootSceneNode()->removeChild(
			mEntityNode);
}

Ogre::Vector3 LimbO3D::getIntersection(Ogre::Vector3 origin,
		Ogre::Vector3 direction) {
	Ogre::Ray ray;
	ray.setOrigin(origin);
	ray.setDirection(direction);

	Ogre::RaySceneQuery* mRayScnQuery =
			mSimulationManager->getSceneManager()->createRayQuery(Ogre::Ray());
	mRayScnQuery->setSortByDistance(true);
	mRayScnQuery->setRay(ray);

	Ogre::RaySceneQueryResult& result = mRayScnQuery->execute();
	Ogre::RaySceneQueryResult::iterator it = result.begin();

	//Ogre::SceneNode* curObject;
	double distance = 0;
	for (; it != result.end(); it++) {
		if (it->movable->getName() == mEntity->getName()) {
			distance = it->distance;
			//curObject = it->movable->getParentSceneNode();
		}
	}
	mSimulationManager->getSceneManager()->destroyQuery(mRayScnQuery);

	return origin + direction * distance / direction.length();
}

Ogre::Vector3 LimbO3D::getLocalIntersection(Ogre::Vector3 origin,
		Ogre::Vector3 direction) {
	Ogre::Ray ray;
	ray.setOrigin(origin);
	ray.setDirection(direction);

	Ogre::RaySceneQuery* mRayScnQuery =
			mSimulationManager->getSceneManager()->createRayQuery(Ogre::Ray());
	mRayScnQuery->setSortByDistance(true);
	mRayScnQuery->setRay(ray);

	Ogre::RaySceneQueryResult& result = mRayScnQuery->execute();
	Ogre::RaySceneQueryResult::iterator it = result.begin();

	//Ogre::SceneNode* curObject;
	double distance = 0;
	for (; it != result.end(); it++) {
		if (it->movable->getName() == mEntity->getName()) {
			distance = it->distance;
			//curObject = it->movable->getParentSceneNode();
		}
	}
	mSimulationManager->getSceneManager()->destroyQuery(mRayScnQuery);

	return direction * distance / direction.length();
}
