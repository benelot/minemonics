/*
 * JointO3D.cpp
 *
 *  Created on: Apr 14, 2015
 *      Author: leviathan
 */

//# corresponding header
#include "JointO3D.h"

//# forward declarations
//# system headers
//## controller headers
//## model headers
//## view headers
//# custom headers
//## base headers
#include "SimulationManager.h"

//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers

JointO3D::JointO3D() :
		mSimulationManager(NULL),mLimbA(NULL),mLimbB(NULL) {

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
	btVector3 limbACOM(mLimbA->getPosition().x, mLimbA->getPosition().y,
			mLimbA->getPosition().z);
	btVector3 limbAJoint(limbACOM + mLocalA.getOrigin());
	btVector3 limbBCOM(mLimbB->getPosition().x, mLimbB->getPosition().y,
			mLimbB->getPosition().z);
	btVector3 limbBJoint(limbBCOM + mLocalB.getOrigin());
	mSimulationManager->getDebugDrawer()->drawLine(limbACOM, limbAJoint,
			btVector3(255, 0, 0));
	mSimulationManager->getDebugDrawer()->drawLine(limbBCOM, limbBJoint,
			btVector3(255, 0, 0));
//	std::string text;
//	text.append("+");
//	InfoOverlayData* data = new InfoOverlayData(
//			mLimbA->getPosition(), text);
//	mSimulationManager->getInfoOverlay().addInfo(data);
//	text.clear();
//	text.append("x");
//	data = new InfoOverlayData(
//			mLimbB->getPosition(), text);
//	mSimulationManager->getInfoOverlay().addInfo(data);

}

void JointO3D::addToWorld() {

}

void JointO3D::removeFromWorld() {

}

