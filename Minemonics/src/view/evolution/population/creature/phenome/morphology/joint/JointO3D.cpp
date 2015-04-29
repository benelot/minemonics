/*
 * JointO3D.cpp
 *
 *  Created on: Apr 14, 2015
 *      Author: leviathan
 */

//# corresponding header
#include <view/bullet/OgreBulletUtils.h>
#include <view/evolution/population/creature/phenome/morphology/joint/JointO3D.h>
#include "SimulationManager.h"

//## configuration headers
//## controller headers
//## model headers
//## view headers
#include "utils/ogre3D/Euler.h"

JointO3D::JointO3D() :
		mSimulationManager(NULL), mLimbA(NULL), mLimbB(NULL) {

}

JointO3D::~JointO3D() {

}

void JointO3D::initialize(SimulationManager* simulationManager, Limb* limbA,
		Limb* limbB, btTransform localA, btTransform localB) {
	mSimulationManager = simulationManager;
	mLimbA = limbA;
	mLimbB = limbB;
	mLocalA = localA;
	mLocalB = localB;
}

void JointO3D::update() {
	//TODO:: Fix local to global frame rotation
//	Ogre::Vector3 limbACOM(mLimbA->getPosition());
//	Ogre::Euler euler(OgreBulletUtils::convert(mLocalA.getRotation()));
//	Ogre::Vector3 limbAJoint(
//			limbACOM + /*euler */OgreBulletUtils::convert(mLocalA.getOrigin()));
//	Ogre::Vector3 limbBCOM(mLimbB->getPosition());
//	Ogre::Euler euler2(OgreBulletUtils::convert(mLocalB.getRotation()));
//	Ogre::Vector3 limbBJoint(
//			limbBCOM
//					+ /*euler2 */OgreBulletUtils::convert(mLocalB.getOrigin()));
//
//	mSimulationManager->getDebugDrawer()->drawLine(limbACOM, limbAJoint,
//			Ogre::ColourValue(1, 1, 1));
//	mSimulationManager->getDebugDrawer()->drawLine(limbBCOM, limbBJoint,
//			Ogre::ColourValue(1, 1, 1));
//
//	mSimulationManager->getDebugDrawer()->drawLine(limbACOM, limbBCOM,
//			Ogre::ColourValue(1, 1, 1));

	std::string text;
	text.append("+");
	InfoOverlayData* data = new InfoOverlayData(
			mLimbA->getPosition(), text);
	mSimulationManager->getInfoOverlay().addInfo(data);
	text.clear();
	text.append("x");
	data = new InfoOverlayData(
			mLimbB->getPosition(), text);
	mSimulationManager->getInfoOverlay().addInfo(data);

}

void JointO3D::addToWorld() {

}

void JointO3D::removeFromWorld() {

}

