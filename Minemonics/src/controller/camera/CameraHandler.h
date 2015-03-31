/*
 * CameraHandler.h
 *
 *  Created on: Feb 13, 2015
 *      Author: leviathan
 */

#ifndef CAMERAHANDLER_H_
#define CAMERAHANDLER_H_

//# corresponding header
//# forward declarations
//# system headers
//## controller headers
//## model headers
//## view headers
#include <OgreRoot.h>

//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers

class SimulationManager;

class CameraHandler {
public:
	CameraHandler(SimulationManager* simulationMgr);
	virtual ~CameraHandler();
	void reposition(float timeSinceLastFrame);
	void rotate(int pitch, int yaw, int roll);
	void move(double x, double y, double z);
	void moveX(double x);
	void moveY(double y);
	void moveZ(double z);
	const Ogre::SceneNode* getCamNode() const;
	void setCamNode(Ogre::SceneNode* camNode);

	Ogre::Real getMove() const {
		return mMove;
	}

	void setMove(Ogre::Real move) {
		mMove = move;
	}

private:
	SimulationManager* mSimulationMgr;

	/**
	 * The rotate constant
	 */
	Ogre::Real mRotate;
	/**
	 * The movement constant
	 */
	Ogre::Real mMove;

	/**
	 * The SceneNode the camera is currently attached to
	 */
	Ogre::SceneNode *mCamNode;

	/**
	 *  Value to move in the correct direction
	 */
	Ogre::Vector3 mDirection;
};

#endif /* CAMERAHANDLER_H_ */
