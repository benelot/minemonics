//# corresponding headers
#include <model/universe/evolution/population/creature/genome/morphology/MorphogeneBranch.hpp>

//# forward declarations
//# system headers
//## controller headers
//## model headers
#include <boost/math/constants/constants.hpp>

//## view headers
//# custom headers
//## base headers
//## configuration headers
#include <configuration/MorphologyConfiguration.hpp>
#include <configuration/ControlConfiguration.hpp>

//## controller headers
//## model headers
//## view headers
//## utils headers
#include <utils/Randomness.hpp>

#ifndef UNIV_EPS
#define UNIV_EPS 0.01f
#endif

MorphogeneBranch::MorphogeneBranch(JointPhysics::JointType jointType,
	bool flipped, bool mirrored, Ogre::Vector3 pitchAxis,
	Ogre::Vector3 jointMinAngle, Ogre::Vector3 jointMaxAngle,
	Ogre::Vector3 anchorDirection) :
	mBranchGeneType(-1), mFlipped(flipped), mJointAnchorX(anchorDirection.x), mJointAnchorY(
		anchorDirection.y), mJointAnchorZ(anchorDirection.z), mJointPitchMinAngle(
		jointMinAngle.x), mJointPitchMaxAngle(jointMaxAngle.x), mJointYawMinAngle(
		jointMinAngle.y), mJointYawMaxAngle(jointMaxAngle.y), mJointRollMinAngle(
		jointMinAngle.z), mJointRollMaxAngle(jointMaxAngle.z), mMirrored(
		mirrored), mJointType(jointType), mJointPitchAxisX(pitchAxis.x), mJointPitchAxisY(
		pitchAxis.y), mJointPitchAxisZ(pitchAxis.z) {

}

MorphogeneBranch::MorphogeneBranch() :
	mBranchGeneType(-1), mFlipped(false), mJointAnchorX(0), mJointAnchorY(0), mJointAnchorZ(
		0), mJointPitchMinAngle(0), mJointPitchMaxAngle(0), mJointYawMinAngle(
		0), mJointYawMaxAngle(0), mJointRollMinAngle(0), mJointRollMaxAngle(0), mMirrored(
		false), mJointType(JointPhysics::HINGE_JOINT), mJointPitchAxisX(1), mJointPitchAxisY(
		1), mJointPitchAxisZ(1) {

}

MorphogeneBranch::MorphogeneBranch(const MorphogeneBranch& morphogeneBranch) {

	for (std::vector<ControllerGene*>::const_iterator mgbit =
		morphogeneBranch.mControllerGenes.begin();
		mgbit != morphogeneBranch.mControllerGenes.end(); mgbit++) {
		mControllerGenes.push_back((*mgbit)->clone());
	}

	mActive = morphogeneBranch.mActive;
	mBranchGeneType = morphogeneBranch.mBranchGeneType;
	mFlipped = morphogeneBranch.mFlipped;
	mType = morphogeneBranch.mType;
	mJointAnchorX = morphogeneBranch.mJointAnchorX;
	mJointAnchorY = morphogeneBranch.mJointAnchorY;
	mJointAnchorZ = morphogeneBranch.mJointAnchorZ;

	mJointPitchMaxAngle = morphogeneBranch.mJointPitchMaxAngle;
	mJointPitchMinAngle = morphogeneBranch.mJointPitchMinAngle;

	mJointYawMaxAngle = morphogeneBranch.mJointYawMaxAngle;
	mJointYawMinAngle = morphogeneBranch.mJointYawMinAngle;

	mJointRollMaxAngle = morphogeneBranch.mJointRollMaxAngle;
	mJointRollMinAngle = morphogeneBranch.mJointRollMinAngle;

	mMirrored = morphogeneBranch.mMirrored;

	mJointPitchAxisX = morphogeneBranch.mJointPitchAxisX;
	mJointPitchAxisY = morphogeneBranch.mJointPitchAxisY;
	mJointPitchAxisZ = morphogeneBranch.mJointPitchAxisZ;
	mJointType = morphogeneBranch.mJointType;
}

MorphogeneBranch::~MorphogeneBranch() {
	//clean up necessary
	while (!mControllerGenes.empty()) {
		ControllerGene* f = mControllerGenes.back();
		mControllerGenes.pop_back();
		delete f;
	}
}

void MorphogeneBranch::initialize() {
	GeneBranch::initialize(GeneBranch::MORPHOGENE_BRANCH);

	//TODO: Change if other joint control becomes available
	mJointType = JointPhysics::HINGE_JOINT;
//	mJointType =
//		(JointPhysics::JointType) Randomness::getSingleton()->nextUnifPosInt(1,
//			JointPhysics::NUM_JOINTS);

	/**
	 * Set whether the branch should be mirrored or flipped to the other side.
	 */
	mMirrored = Randomness::getSingleton()->nextUnifBoolean();
	mFlipped = Randomness::getSingleton()->nextUnifBoolean();

	Ogre::Vector3 pitchAxisVector = Randomness::getSingleton()->nextVector();
	mJointPitchAxisX = pitchAxisVector.x;
	mJointPitchAxisY = pitchAxisVector.y;
	mJointPitchAxisZ = pitchAxisVector.z;

	/**
	 * The joint limits in each direction (pitch=1=Y,yaw=2=Z, roll=0=X)
	 *   6DOF constraint uses Euler angles and to define limits
	 * it is assumed that rotational order is :
	 * Z - first, allowed limits are (-PI+epsilon,PI-epsilon);
	 * new position of Y - second (allowed limits are
	 * (-PI/2 + epsilon, PI/2 - epsilon), where epsilon is a small positive number
	 * used to prevent constraint from instability on poles;
	 * new position of X, allowed limits are (-PI+epsilon,PI-epsilon);
	 * So to simulate ODE Universal joint we should use parent
	 * axis as Z, child axis as Y and limit all other DOFs
	 */
	//TODO: Revise the correct joint limits
	mJointPitchMinAngle = Randomness::getSingleton()->nextUnifDouble(
		-boost::math::constants::pi<double>() / 2.0f + UNIV_EPS,
		boost::math::constants::pi<double>() / 2.0f - UNIV_EPS);
	mJointPitchMaxAngle = Randomness::getSingleton()->nextUnifDouble(
		-boost::math::constants::pi<double>() / 2.0f + UNIV_EPS,
		boost::math::constants::pi<double>() / 2.0f - UNIV_EPS);
	mJointYawMinAngle = Randomness::getSingleton()->nextUnifDouble(
		-boost::math::constants::pi<double>() + UNIV_EPS,
		boost::math::constants::pi<double>() - UNIV_EPS);
	mJointYawMaxAngle = Randomness::getSingleton()->nextUnifDouble(
		-boost::math::constants::pi<double>() + UNIV_EPS,
		boost::math::constants::pi<double>() - UNIV_EPS);
	mJointRollMinAngle = Randomness::getSingleton()->nextUnifDouble(
		-boost::math::constants::pi<double>() + UNIV_EPS,
		boost::math::constants::pi<double>() - UNIV_EPS);
	mJointRollMaxAngle = Randomness::getSingleton()->nextUnifDouble(
		-boost::math::constants::pi<double>() + UNIV_EPS,
		boost::math::constants::pi<double>() - UNIV_EPS);

	// create instances of the sine controller gene for the morphogene.
	switch (ControlConfiguration::CONTROLLER_TYPE) {
	case ControllerGene::SineControllerGene:
		// create instances of the sine controller gene for the morphogene.
		for (int i = 0; i < 3; i++) {
			SineControllerGene* sineController = new SineControllerGene();
			sineController->initialize();
			mControllerGenes.push_back(sineController);
		}
		break;
	case ControllerGene::ChaoticControllerGene:
		// create instances of the chaotic controller gene for the morphogene.
		for (int i = 0; i < 3; i++) {
			ChaoticControllerGene* chaoticController =
				new ChaoticControllerGene();
			chaoticController->initialize();
			mControllerGenes.push_back(chaoticController);
		}
	}

	Ogre::Vector3 anchorVector = Randomness::getSingleton()->nextVector();
	mJointAnchorX = anchorVector.x; // Set joint anchor X, Y and Z, where the anchor lies in the center of mass
	mJointAnchorY = anchorVector.y; // and the X, Y and Z form a vector, pointing to the point on the surface where
	mJointAnchorZ = anchorVector.z; // the joint will be attached.

	mBranchGeneType = 0;
}

bool MorphogeneBranch::equals(const MorphogeneBranch& geneBranch) const {

	if (!GeneBranch::equals(geneBranch)) {
		return false;
	}

	if (mFlipped != geneBranch.mFlipped) {
		return false;
	}

	if (mMirrored != geneBranch.mMirrored) {
		return false;
	}

	if (mJointType != geneBranch.mJointType) {
		return false;
	}

	if (mJointAnchorX != geneBranch.mJointAnchorX) {
		return false;
	}

	if (mJointAnchorY != geneBranch.mJointAnchorY) {
		return false;
	}

	if (mJointAnchorZ != geneBranch.mJointAnchorZ) {
		return false;
	}

	if (mJointPitchAxisX != geneBranch.mJointPitchAxisX) {
		return false;
	}

	if (mJointPitchAxisY != geneBranch.mJointPitchAxisY) {
		return false;
	}

	if (mJointPitchAxisZ != geneBranch.mJointPitchAxisZ) {
		return false;
	}

	if (mJointPitchMinAngle != geneBranch.mJointPitchMinAngle) {
		return false;
	}

	if (mJointPitchMaxAngle != geneBranch.mJointPitchMaxAngle) {
		return false;
	}

	if (mJointYawMinAngle != geneBranch.mJointYawMinAngle) {
		return false;
	}

	if (mJointYawMaxAngle != geneBranch.mJointYawMaxAngle) {
		return false;
	}

	if (mJointRollMinAngle != geneBranch.mJointRollMinAngle) {
		return false;
	}

	if (mJointRollMaxAngle != geneBranch.mJointRollMaxAngle) {
		return false;
	}

	if (mBranchGeneType != geneBranch.mBranchGeneType) {
		return false;
	}

	std::vector<ControllerGene*>::const_iterator it1 = mControllerGenes.begin();
	std::vector<ControllerGene*>::const_iterator it2 =
		geneBranch.mControllerGenes.begin();
	for (;
		it1 != mControllerGenes.end(), it2 != geneBranch.mControllerGenes.end();
		it1++, it2++) {
		if (!(*it1)->equals(**it2)) {
			return false;
		} else {
			switch ((*it1)->getControllerType()) {
			case ControllerGene::SineControllerGene:
				if (!((SineControllerGene*) (*it1))->equals(
					((SineControllerGene&) (**it2)))) {
					return false;
				}
				break;
			case ControllerGene::ChaoticControllerGene:
				if (!((ChaoticControllerGene*) (*it1))->equals(
					((ChaoticControllerGene&) (**it2)))) {
					return false;
				}
				break;
			default:
				break;
			}
		}
	}

	return true;
}

MorphogeneBranch* MorphogeneBranch::clone() {
	return new MorphogeneBranch(*this);
}

void MorphogeneBranch::mutate() {

	//clean up necessary
	while (!mControllerGenes.empty()) {
		ControllerGene* f = mControllerGenes.back();
		mControllerGenes.pop_back();
		delete f;
	}

	initialize();
}
