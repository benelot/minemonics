/*
 * CameraHandler.cpp
 *
 *  Created on: Feb 13, 2015
 *      Author: leviathan
 */

//# corresponding header
#include "CameraHandler.h"

//# forward declarations
//# system headers
//## controller headers
//## model headers
//## view headers
//# custom headers
//## base headers
#include "SimulationManager.h"

//## configuration headers
#include "configuration/CameraConfiguration.h"

//## controller headers
//## model headers
//## view headers
//## utils headers

CameraHandler::CameraHandler(SimulationManager* simulationMgr) :
		mCamNode(NULL), mSimulationMgr(simulationMgr) {
	// set the rotation and move speed
	mMove = CameraConfiguration::CAMERA_MOVEMENT_SPEED;
	mRotate = CameraConfiguration::CAMERA_ROTATION_SPEED;

	mDirection = Ogre::Vector3::ZERO;

}

CameraHandler::~CameraHandler() {
	// TODO Auto-generated destructor stub
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

