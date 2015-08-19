//# corresponding header
//# forward declarations
//# system headers
#include <iostream>
#include <iterator>
#include <vector>

//## controller headers
//## model headers
#include <BulletDynamics/Dynamics/btRigidBody.h>
#include <LinearMath/btQuadWord.h>
#include <LinearMath/btVector3.h>
#include <boost/lexical_cast.hpp>

//## view headers
#include <OgreBlendMode.h>
#include <OgreCommon.h>
#include <OgreEntity.h>
#include <OgreMaterial.h>
#include <OgreMaterialManager.h>
#include <OgreMovableObject.h>
#include <OgrePass.h>
#include <OgrePrerequisites.h>
#include <OgreQuaternion.h>
#include <OgreRay.h>
#include <OgreResourceGroupManager.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
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
#include <model/universe/evolution/population/creature/phenome/morphology/limb/LimbBt.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/limb/LimbModel.hpp>

//## view headers
#include <view/picking/OgreMeshRay.hpp>
#include <view/universe/evolution/population/creature/phenome/morphology/limb/LimbO3D.hpp>
#include <view/visualization/procedural/ProceduralCapsuleGenerator.h>
#include <view/visualization/procedural/ProceduralMeshGenerator.h>

//## utils headers

LimbO3D::LimbO3D(const LimbModel* const limbModel) :
		LimbGraphics(limbModel) {

// add the true as the last parameter to make it a manual material
	Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().create(
			"", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, false);

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

	mLimbEntityNode =
			SimulationManager::getSingleton()->getSceneManager()->createSceneNode();
	switch (limbModel->getPrimitiveType()) {
	case LimbModel::BLOCK:

		tex->setTextureScale(4, 4);
		material->load();
		mLimbEntity =
				SimulationManager::getSingleton()->getSceneManager()->createEntity(
						Ogre::SceneManager::PT_CUBE);
		mLimbEntity->setMaterial(material);

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
		// capsule does not need to be scaled, it is exactly one to one as it seems.
		Ogre::MeshPtr mesh =
				Procedural::CapsuleGenerator().setPosition(0, 0, 0).setRadius(
						0.5f * limbModel->getDimensions().x).setHeight(
						limbModel->getDimensions().y).realizeMesh();
		mLimbEntity =
				SimulationManager::getSingleton()->getSceneManager()->createEntity(
						mesh);
		mLimbEntity->setMaterial(material);
		mLimbEntityNode->attachObject(mLimbEntity);
		break;
	}
	mLimbEntity->setCastShadows(SimulationManager::getSingleton()->getViewController().doesShowShadows());
}

LimbO3D::LimbO3D(const LimbO3D& limbO3D) :
		LimbGraphics(limbO3D.mLimbModel) {
	mLimbEntity = limbO3D.mLimbEntity->clone("");
	mLimbEntityNode =
			SimulationManager::getSingleton()->getSceneManager()->createSceneNode();
	mLimbEntityNode->setPosition(limbO3D.mLimbModel->getPosition());
	mLimbEntityNode->setOrientation(limbO3D.mLimbModel->getOrientation());
}

LimbO3D::~LimbO3D() {
	mLimbEntityNode->removeAndDestroyAllChildren();
	SimulationManager::getSingleton()->getSceneManager()->destroySceneNode(
			mLimbEntityNode);
	mLimbEntityNode = 0;
	delete mLimbEntity;
}

void LimbO3D::update(double timeSinceLastTick) {
	// get the rigid body of the limb
	btRigidBody* body =
			((LimbBt*) mLimbModel->getLimbPhysics())->getRigidBody();

	// if the limb's rigid body is existing
	if (body) {
		// update the position of the limb graphics
		Ogre::Vector3 point = mLimbModel->getPosition();
		if (!(std::isnan(point.x) || std::isnan(point.y) || std::isnan(point.z))) {
			mLimbEntityNode->setPosition(point);
		}

		// Get the Orientation of the rigid body as a bullet Quaternion
		// Convert it to an Ogre quaternion
		Ogre::Quaternion btq = mLimbModel->getOrientation();
		if (!(std::isnan(btq.x) || std::isnan(btq.y) || std::isnan(btq.z)
				|| std::isnan(btq.w))) {
			// update the orientation of the limb graphics
			mLimbEntityNode->setOrientation(btq);
		}
	}
	mLimbEntity->setCastShadows(SimulationManager::getSingleton()->getViewController().doesShowShadows());
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
			SimulationManager::getSingleton()->getSceneManager()->createRayQuery(
					Ogre::Ray());
	mRayScnQuery->setSortByDistance(true);
	mRayScnQuery->setRay(ray);

	Ogre::RaySceneQueryResult& result = mRayScnQuery->execute();

	double distance = 0;
	for (Ogre::RaySceneQueryResult::iterator it = result.begin();
			it != result.end(); it++) {
		std::cout << "Collision name:" << it->movable->getName() << std::endl;
		if (it->movable->getName() == mLimbEntity->getName()) {
			distance = it->distance;
			std::cout << "Distance from center" << distance << std::endl;
		}
	}
	SimulationManager::getSingleton()->getSceneManager()->destroyQuery(
			mRayScnQuery);

	return origin + direction * distance / direction.length();
}

Ogre::Vector3 LimbO3D::getLocalIntersection(Ogre::Vector3 origin,
		Ogre::Vector3 direction) {
	Ogre::Ray ray;
	ray.setOrigin(origin);
	ray.setDirection(direction);

	Ogre::RaySceneQuery* mRayScnQuery =
			SimulationManager::getSingleton()->getSceneManager()->createRayQuery(
					Ogre::Ray());
	mRayScnQuery->setSortByDistance(true);
	mRayScnQuery->setRay(ray);

	Ogre::RaySceneQueryResult& result = mRayScnQuery->execute();
	Ogre::RaySceneQueryResult::iterator it = result.begin();

	double distance = 0;
	for (; it != result.end(); it++) {
		if (it->movable->getName() == mLimbEntity->getName()) {
			distance = it->distance;
		}
	}
	SimulationManager::getSingleton()->getSceneManager()->destroyQuery(
			mRayScnQuery);

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
