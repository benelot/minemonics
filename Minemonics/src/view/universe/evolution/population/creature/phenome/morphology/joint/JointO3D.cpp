//# corresponding header
#include <view/universe/evolution/population/creature/phenome/morphology/joint/JointO3D.hpp>

//# forward declarations
//# system headers
//## controller headers
//## model headers
//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers
#include <utils/ogre3D/Euler.hpp>
#include <utils/ogre3D/OgreBulletUtils.hpp>

JointO3D::JointO3D(const JointModel* const jointModel) :
		JointGraphics(jointModel), mLimbA(
		NULL), mLimbB(NULL) {

}

JointO3D::JointO3D(const JointO3D& jointO3D) :
		JointGraphics(jointO3D.mJointModel) {
	mLimbA = jointO3D.mLimbA;
	mLimbB = jointO3D.mLimbB;
	mLocalA = jointO3D.mLocalA;
	mLocalB = jointO3D.mLocalB;
}

JointO3D::~JointO3D() {

}

//TODO:Remove this if possible
void JointO3D::initialize(/*Limb* limbA,
 Limb* limbB/*, btTransform localA, btTransform localB*/) {
	//mLimbA = limbA;
	//mLimbB = limbB;
	//mLocalA = localA;
	//mLocalB = localB;
}

void JointO3D::update(double timeSinceLastTick) {
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
//	SimulationManager::getSingleton()->getDebugDrawer()->drawLine(limbACOM, limbAJoint,
//			Ogre::ColourValue(1, 1, 1));
//	SimulationManager::getSingleton()->getDebugDrawer()->drawLine(limbBCOM, limbBJoint,
//			Ogre::ColourValue(1, 1, 1));
//
//	SimulationManager::getSingleton()->getDebugDrawer()->drawLine(limbACOM, limbBCOM,
//			Ogre::ColourValue(1, 1, 1));

//	std::string text;
//	text.append("+");
//	InfoOverlayData* data = new InfoOverlayData(
//			mLimbA->getPosition(), text);
//	SimulationManager::getSingleton()->getInfoOverlay().addInfo(data);
//	text.clear();
//	text.append("x");
//	data = new InfoOverlayData(
//			mLimbB->getPosition(), text);
//	SimulationManager::getSingleton()->getInfoOverlay().addInfo(data);

}

void JointO3D::addToWorld() {

}

void JointO3D::removeFromWorld() {

}

JointO3D* JointO3D::clone() {
	return new JointO3D(*this);
}
