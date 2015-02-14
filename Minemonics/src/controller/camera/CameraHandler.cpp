/*
 * CameraHandler.cpp
 *
 *  Created on: Feb 13, 2015
 *      Author: leviathan
 */

#include "CameraHandler.h"
#include "configuration/CameraConfiguration.h"
#include "SimulationManager.h"

CameraHandler::CameraHandler(SimulationManager* simulationMgr) :
		mCamNode(NULL),mSimulationMgr(simulationMgr) {
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
	mCamNode->yaw(Ogre::Degree(-mRotate * yaw),
			Ogre::Node::TS_WORLD);
	mCamNode->pitch(Ogre::Degree(-mRotate * pitch),
			Ogre::Node::TS_LOCAL);
}

const Ogre::SceneNode* CameraHandler::getCamNode() const {
	return mCamNode;
}

void CameraHandler::setCamNode(Ogre::SceneNode* camNode) {
	mCamNode = camNode;
}

void CameraHandler::move(double x,double y, double z) {
	mDirection.x = mMove*x;
	mDirection.y = mMove*y;
	mDirection.z = mMove*z;
}

