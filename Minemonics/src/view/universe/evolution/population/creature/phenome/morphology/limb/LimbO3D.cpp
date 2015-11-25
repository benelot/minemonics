//# corresponding header
//# forward declarations
//# system headers
#include <iostream>
#include <iterator>
#include <vector>

//## controller headers
//## model headers
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
#include <model/universe/evolution/population/creature/phenome/morphology/limb/SRBLimbBt.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/limb/SRBLimbModel.hpp>
#include <view/universe/evolution/population/creature/phenome/morphology/limb/LimbO3D.hpp>
#include <view/visualization/procedural/ProceduralCapsuleGenerator.h>
#include <view/visualization/procedural/ProceduralMeshGenerator.h>

//## utils headers
#include <utils/Debugger.hpp>

BoostLogger LimbO3D::mBoostLogger; /*<! initialize the boost logger*/
LimbO3D::_Init LimbO3D::_initializer;
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
	case LimbPhysics::BLOCK:

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
	case LimbPhysics::CAPSULE:

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
	mLimbEntity->setCastShadows(
		SimulationManager::getSingleton()->getViewController().doesShowShadows());
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

	// update the position of the limb graphics
	Ogre::Vector3 limbPosition = mLimbModel->getPosition();
	if (Debugger::isFinite(limbPosition)) {
		mLimbEntityNode->setPosition(limbPosition);
	} else {
		BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::fatal) << "NaN detected in limb position:" << limbPosition;
	}

	// Get the Orientation of the rigid body as a bullet Quaternion
	// Convert it to an Ogre quaternion
	Ogre::Quaternion limbOrientation = mLimbModel->getOrientation();
	if (Debugger::isFinite(limbOrientation)) {
		// update the orientation of the limb graphics
		mLimbEntityNode->setOrientation(limbOrientation);

		mLimbEntity->setCastShadows(
			SimulationManager::getSingleton()->getViewController().doesShowShadows());
	} else {
		BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::fatal) << "NaN detected in limb orientation:" << limbOrientation;
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

LimbO3D * LimbO3D::clone() {
	return new LimbO3D(*this);
}
