//# corresponding header
//# forward declarations
//# system headers
#include <iostream>
#include <iterator>
#include <vector>
#include <string>

//## controller headers
//## model headers
#include <boost/lexical_cast.hpp>

//## view headers
#include <OgreEntity.h>
#include <OgreSceneNode.h>
#include <OgreBlendMode.h>
#include <OgreColourValue.h>
#include <OgreCommon.h>
#include <OgreMaterial.h>
#include <OgreMaterialManager.h>
#include <OgreMovableObject.h>
#include <OgrePass.h>
#include <OgrePrerequisites.h>
#include <OgreRay.h>
#include <OgreResourceGroupManager.h>
#include <OgreSceneManager.h>
#include <OgreSceneQuery.h>
#include <OgreSingleton.h>
#include <OgreTechnique.h>
#include <OgreTextureUnitState.h>
#include <OgreVector3.h>

//# custom headers
//## base headers
#include <SimulationManager.hpp>

//## configuration headers
#include <configuration/PhysicsConfiguration.hpp>

//## controller headers
//## model headers
//## view headers
#include <view/picking/OgreMeshRay.hpp>
#include <view/universe/evolution/population/creature/phenome/morphology/limb/LimbO3D.hpp>
#include <view/visualization/procedural/ProceduralCapsuleGenerator.h>
#include <view/visualization/procedural/ProceduralMeshGenerator.h>

//## utils headers

LimbO3D::LimbO3D(const LimbModel* const limbModel) :
		LimbGraphics(limbModel) {

	Ogre::String name = boost::lexical_cast<std::string>(this) + "/" + "Limb";
	Ogre::String materialName = boost::lexical_cast<std::string>(this) + "/"
			+ "Limb";

	// add the true as the last parameter to make it a manual material
	Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().create(
			materialName,
			Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, false);

	Ogre::Pass *pass = material->getTechnique(0)->getPass(0);
	pass->setLightingEnabled(true);
	pass->setAmbient(limbModel->getColor());
	pass->setDiffuse(limbModel->getColor());
	//pass->setSpecular(limbModel->getColor());
	pass->setEmissive(limbModel->getColor());
	pass->setDepthCheckEnabled(true);
	pass->setDepthWriteEnabled(false);
	pass->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);

	Ogre::TextureUnitState *tex = pass->createTextureUnitState("MyCustomState",
			0);
	tex->setTextureName("honeycomb.png");
	tex->setTextureFiltering(Ogre::TFO_ANISOTROPIC);
	tex->setTextureAnisotropy(8);

	mLimbEntityNode = SimulationManager::getSingleton()->getSceneManager()->createSceneNode();
	switch (limbModel->getPrimitiveType()) {
	case LimbModel::BLOCK:

		tex->setTextureScale(4, 4);
		material->load();
		mLimbEntity = SimulationManager::getSingleton()->getSceneManager()->createEntity(
				Ogre::SceneManager::PT_CUBE);
		mLimbEntity->setMaterialName(materialName);

		mLimbEntityNode->attachObject(mLimbEntity);

		mLimbEntityNode->scale(
				limbModel->getDimensions().x
						* PhysicsConfiguration::BULLET_OGRE_BOX_SCALING_FACTOR,
				limbModel->getDimensions().y
						* PhysicsConfiguration::BULLET_OGRE_BOX_SCALING_FACTOR,
				limbModel->getDimensions().z
						* PhysicsConfiguration::BULLET_OGRE_BOX_SCALING_FACTOR);
		break;
	case LimbModel::CAPSULE:

		material->load();
		//because we can only scale bullet capsule that way, we do not scale this object differently
		Procedural::CapsuleGenerator().setPosition(0, 0, 0).setRadius(
				0.5f * limbModel->getDimensions().z).setHeight(
				limbModel->getDimensions().y).realizeMesh(name);
		mLimbEntity = SimulationManager::getSingleton()->getSceneManager()->createEntity(name);
		mLimbEntity->setMaterialName(materialName);
		mLimbEntityNode->attachObject(mLimbEntity);
		break;
	}

}

LimbO3D::LimbO3D(const LimbO3D& limbO3D) :
		LimbGraphics(limbO3D.mLimbModel) {
	Ogre::String name = boost::lexical_cast<std::string>(this) + "/" + "Limb";
	mLimbEntity = limbO3D.mLimbEntity->clone(name);
	mLimbEntityNode = SimulationManager::getSingleton()->getSceneManager()->createSceneNode();
	mLimbEntityNode->setPosition(limbO3D.mLimbModel->getPosition());
	mLimbEntityNode->setOrientation(limbO3D.mLimbModel->getOrientation());
}

LimbO3D::~LimbO3D() {
	delete mLimbEntityNode;
	delete mLimbEntity;
}

void LimbO3D::update() {
	// get the rigid body of the limb
	btRigidBody* body =
			((LimbBt*) mLimbModel->getLimbPhysics())->getRigidBody();

	// if the limb's rigid body is existing
	if (body) {

		// update the position of the limb graphics
		btVector3 point = body->getCenterOfMassPosition();
		mLimbEntityNode->setPosition(mLimbModel->getPosition());

		// Get the Orientation of the rigid body as a bullet Quaternion
		// Convert it to an Ogre quaternion
		btQuaternion btq = body->getOrientation();
		Ogre::Quaternion quart = Ogre::Quaternion(btq.w(), btq.x(), btq.y(),
				btq.z());

		// update the orientation of the limb graphics
		mLimbEntityNode->setOrientation(mLimbModel->getOrientation());
	}
}

void LimbO3D::addToWorld() {
	if (!isInWorld()) {
		SimulationManager::getSingleton()->getSceneManager()->getRootSceneNode()->addChild(
				mLimbEntityNode);
		setInWorld(true);
	}
}

void LimbO3D::removeFromWorld() {
	if (isInWorld()) {
		SimulationManager::getSingleton()->getSceneManager()->getRootSceneNode()->removeChild(
				mLimbEntityNode);
		setInWorld(false);
	}
}

Ogre::Vector3 LimbO3D::getIntersection(Ogre::Vector3 origin,
		Ogre::Vector3 direction) {
	Ogre::Ray ray;
	ray.setOrigin(origin);
	ray.setDirection(direction);

	Ogre::RaySceneQuery* mRayScnQuery =
			SimulationManager::getSingleton()->getSceneManager()->createRayQuery(Ogre::Ray());
	mRayScnQuery->setSortByDistance(true);
	mRayScnQuery->setRay(ray);

	Ogre::RaySceneQueryResult& result = mRayScnQuery->execute();
	Ogre::RaySceneQueryResult::iterator it = result.begin();

	//Ogre::SceneNode* curObject;
	double distance = 0;
	for (; it != result.end(); it++) {
		std::cout << "Collision name:" << it->movable->getName() << std::endl;
		if (it->movable->getName() == mLimbEntity->getName()) {
			distance = it->distance;
			std::cout << "Distance from center" << distance << std::endl;
			//curObject = it->movable->getParentSceneNode();
		}
	}
	SimulationManager::getSingleton()->getSceneManager()->destroyQuery(mRayScnQuery);

	return origin + direction * distance / direction.length();
}

Ogre::Vector3 LimbO3D::getLocalIntersection(Ogre::Vector3 origin,
		Ogre::Vector3 direction) {
	Ogre::Ray ray;
	ray.setOrigin(origin);
	ray.setDirection(direction);

	Ogre::RaySceneQuery* mRayScnQuery =
			SimulationManager::getSingleton()->getSceneManager()->createRayQuery(Ogre::Ray());
	mRayScnQuery->setSortByDistance(true);
	mRayScnQuery->setRay(ray);

	Ogre::RaySceneQueryResult& result = mRayScnQuery->execute();
	Ogre::RaySceneQueryResult::iterator it = result.begin();

	//Ogre::SceneNode* curObject;
	double distance = 0;
	for (; it != result.end(); it++) {
		if (it->movable->getName() == mLimbEntity->getName()) {
			distance = it->distance;
			//curObject = it->movable->getParentSceneNode();
		}
	}
	SimulationManager::getSingleton()->getSceneManager()->destroyQuery(mRayScnQuery);

	return direction * distance / direction.length();
}

Ogre::Vector3 LimbO3D::getLocalPreciseIntersection(Ogre::Vector3 origin,
		Ogre::Vector3 direction) {
	OgreMeshRay ray(SimulationManager::getSingleton()->getSceneManager());
	Ogre::Vector3 result;
	ray.raycastFromPoint(origin, direction, result, mLimbEntity->getName());

	return result;
}

LimbO3D* LimbO3D::clone() {
	return new LimbO3D(*this);
}
