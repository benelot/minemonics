//# corresponding headers
#include <controller/viewcontroller/camera/CameraHandler.hpp>

//# forward declarations
//# system headers
//## controller headers
//## model headers
//## view headers
#include <OgreCamera.h>
#include <OgreMath.h>
#include <OgreNode.h>
#include <OgreRenderSystem.h>
#include <OgreRenderSystemCapabilities.h>
#include <OgreRoot.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>

//# custom headers
//## base headers
#include <SimulationManager.hpp>

//## configuration headers
#include <configuration/CameraConfiguration.hpp>
#include <configuration/EvolutionConfiguration.hpp>

//## controller headers
//## model headers
//## view headers
//## utils headers

BoostLogger CameraHandler::mBoostLogger; /*<! initialize the boost logger*/
CameraHandler::_Init CameraHandler::_initializer;
CameraHandler::CameraHandler() :
	mCamNode(NULL), mDirection(Ogre::Vector3::ZERO), mCamera(NULL) {
}

CameraHandler::~CameraHandler() {
// Do not kill the node, ogre does
//	delete mCamNode;
//	mCamNode = NULL;
//Do not kill the camera, ogre does
//	delete mCamera;
//	mCamera = NULL;
}

void CameraHandler::reposition(float timeSinceLastFrame) {
	mCamNode->translate(mDirection * timeSinceLastFrame, Ogre::Node::TS_LOCAL);
}

void CameraHandler::rotate(int pitch, int yaw, int roll) {
	mCamNode->yaw(
		Ogre::Degree(-CameraConfiguration::CAMERA_ROTATION_SPEED * yaw),
		Ogre::Node::TS_WORLD);
	mCamNode->pitch(
		Ogre::Degree(-CameraConfiguration::CAMERA_ROTATION_SPEED * pitch),
		Ogre::Node::TS_LOCAL);
}

void CameraHandler::move(double x, double y, double z) {
	moveX(x);
	moveY(y);
	moveZ(z);
}

void CameraHandler::moveX(double x) {
	mDirection.x = CameraConfiguration::CAMERA_MOVEMENT_SPEED * x;
}

void CameraHandler::moveY(double y) {
	mDirection.y = CameraConfiguration::CAMERA_MOVEMENT_SPEED * y;
}

void CameraHandler::initialize() {
	// Create the camera controlling node
	mCamNode =
		SimulationManager::getSingleton()->getSceneManager()->getRootSceneNode()->createChildSceneNode(
			"ObserverCameraNode",
			EvaluationConfiguration::ROOT_POSITION + CameraConfiguration::CAMERA_ROOT_DISPLACEMENT);

	mCamera->setPosition(
		EvaluationConfiguration::ROOT_POSITION + CameraConfiguration::CAMERA_ROOT_DISPLACEMENT);
	mCamNode->attachObject(mCamera);
	mCamNode->lookAt(EvaluationConfiguration::ROOT_POSITION,
		Ogre::Node::TS_WORLD);
	mCamera->setNearClipDistance(0.1);
	mCamera->setFarClipDistance(12000);
	mCamera->setFOVy(Ogre::Degree(60.0f));

	if (SimulationManager::getSingleton()->getRoot()->getRenderSystem()->getCapabilities()->hasCapability(
		Ogre::RSC_INFINITE_FAR_PLANE)) {
		mCamera->setFarClipDistance(0); /**!< enable infinite far clip distance if we can */
	}
}

void CameraHandler::moveZ(double z) {
	mDirection.z = CameraConfiguration::CAMERA_MOVEMENT_SPEED * z;
}

