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
#include "view/ogre3D/picking/OgreMeshRay.h"

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
		MorphologyConfiguration::PrimitiveType type, Ogre::Vector3 scale,Ogre::ColourValue color) {
	mSimulationManager = simulationManager;

	Ogre::String name = boost::lexical_cast<std::string>(this) + "/"
					+ "Limb";
	Ogre::String materialName = boost::lexical_cast<std::string>(this) + "/"
					+ "Limb";

	// add the true as the last parameter to make it a manual material
	Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().create(materialName, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, true
	);

	Ogre::Pass *pass = material->getTechnique(0)->getPass(0);
	pass->setLightingEnabled(true);
	pass->setAmbient(color);
	pass->setDiffuse(color);
	//pass->setSpecular(color);
	pass->setEmissive(color);
	pass->setDepthCheckEnabled(true);
	pass->setDepthWriteEnabled(false);
	pass->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);

	Ogre::TextureUnitState *tex = pass->createTextureUnitState("MyCustomState",
			0);
	tex->setTextureName("honeycomb.png");
	tex->setTextureFiltering(Ogre::TFO_ANISOTROPIC);
	tex->setTextureAnisotropy(8);

	switch (type) {
	case MorphologyConfiguration::BLOCK:

		tex->setTextureScale(4,4);
		material->load();
		mEntity = mSimulationManager->getSceneManager()->createEntity(
				Ogre::SceneManager::PT_CUBE);
		mEntity->setMaterialName(materialName);
		mEntityNode = mSimulationManager->getSceneManager()->createSceneNode();
		mEntityNode->attachObject(mEntity);

		mEntityNode->scale(
				scale.x * PhysicsConfiguration::BULLET_OGRE_BOX_SCALING_FACTOR,
				scale.y * PhysicsConfiguration::BULLET_OGRE_BOX_SCALING_FACTOR,
				scale.z * PhysicsConfiguration::BULLET_OGRE_BOX_SCALING_FACTOR);
		break;
	case MorphologyConfiguration::CAPSULE:

		material->load();
		//because we can only scale bullet capsule that way, we do not scale this object differently
		Procedural::CapsuleGenerator().setPosition(0, 0, 0).setRadius(
				0.5f * scale.z).setHeight(scale.y).realizeMesh(name);
		mEntity = mSimulationManager->getSceneManager()->createEntity(name);
		mEntity->setMaterialName(materialName);
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
		std::cout << "Collision name:" << it->movable->getName() << std::endl;
		if (it->movable->getName() == mEntity->getName()) {
			distance = it->distance;
			std::cout << "Distance from center" << distance << std::endl;
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

Ogre::Vector3 LimbO3D::getLocalPreciseIntersection(Ogre::Vector3 origin,
		Ogre::Vector3 direction) {
	OgreMeshRay ray(mSimulationManager->getSceneManager());
	Ogre::Vector3 result;
	ray.raycastFromPoint(origin, direction, result, mEntity->getName());

	return result;
}
