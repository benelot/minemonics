//# corresponding headers
//# forward declarations
//# system headers
#include <stddef.h>

//## controller headers
//## model headers
//## view headers
#include <OgreMath.h>
#include <OgreNode.h>
#include <OgreSceneNode.h>
#include <OgreVector3.h>

//# custom headers
//## base headers
//## configuration headers
#include <configuration/CameraConfiguration.hpp>

//## controller headers
#include <controller/viewcontroller/camera/CameraHandler.hpp>

//## model headers
//## view headers
//## utils headers

BoostLogger CameraHandler::mBoostLogger; /*<! initialize the boost logger*/
CameraHandler::_Init CameraHandler::_initializer;
CameraHandler::CameraHandler(SimulationManager* simulationMgr) :
		mCamNode(NULL), mSimulationMgr(simulationMgr), mMove(
				CameraConfiguration::CAMERA_MOVEMENT_SPEED), mRotate(
				CameraConfiguration::CAMERA_ROTATION_SPEED), mDirection(
				Ogre::Vector3::ZERO) {
}

CameraHandler::~CameraHandler() {
	delete mCamNode;
	mCamNode = NULL;

	mSimulationMgr = NULL;
}

void CameraHandler::reposition(float timeSinceLastFrame) {
	mCamNode->translate(mDirection * timeSinceLastFrame, Ogre::Node::TS_LOCAL);
}

void CameraHandler::rotate(int pitch, int yaw, int roll) {
	mCamNode->yaw(Ogre::Degree(-mRotate * yaw), Ogre::Node::TS_WORLD);
	mCamNode->pitch(Ogre::Degree(-mRotate * pitch), Ogre::Node::TS_LOCAL);
}

const Ogre::SceneNode* CameraHandler::getCamNode() const {
	return mCamNode;
}

void CameraHandler::setCamNode(Ogre::SceneNode* camNode) {
	mCamNode = camNode;
}

void CameraHandler::move(double x, double y, double z) {
	moveX(x);
	moveY(y);
	moveZ(z);
}

void CameraHandler::moveX(double x) {
	mDirection.x = mMove * x;
}

void CameraHandler::moveY(double y) {
	mDirection.y = mMove * y;
}

void CameraHandler::moveZ(double z) {
	mDirection.z = mMove * z;
}

