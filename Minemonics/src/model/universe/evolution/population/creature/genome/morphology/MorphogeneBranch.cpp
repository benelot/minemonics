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
#include <configuration/PhysicsConfiguration.hpp>

//## controller headers
//## model headers
//## view headers
//## utils headers
#include <utils/Randomness.hpp>

MorphogeneBranch::MorphogeneBranch(JointPhysics::JointType jointType,
	bool flipped, bool mirrored, Ogre::Vector3 pitchAxis, Ogre::Vector3 yawAxis,
	Ogre::Vector3 jointStiffness, Ogre::Vector3 jointDamping,
	Ogre::Vector3 jointMinAngle, Ogre::Vector3 jointMaxAngle,
	Ogre::Vector3 anchorDirection) :
	mBranchGeneType(-1), mFlipped(flipped), mJointAnchorX(anchorDirection.x), mJointAnchorY(
		anchorDirection.y), mJointAnchorZ(anchorDirection.z), mJointPitchMinAngle(
		jointMinAngle.x), mJointPitchMaxAngle(jointMaxAngle.x), mJointYawMinAngle(
		jointMinAngle.y), mJointYawMaxAngle(jointMaxAngle.y), mJointRollMinAngle(
		jointMinAngle.z), mJointRollMaxAngle(jointMaxAngle.z), mMirrored(
		mirrored), mJointType(jointType), mJointPitchAxisX(pitchAxis.x), mJointPitchAxisY(
		pitchAxis.y), mJointPitchAxisZ(pitchAxis.z), mJointYawAxisX(yawAxis.x), mJointYawAxisY(
		yawAxis.y), mJointYawAxisZ(yawAxis.z), mPitchStiffnessCoefficient(
		jointStiffness.x), mYawStiffnessCoefficient(jointStiffness.y), mRollStiffnessCoefficient(
		jointStiffness.z), mPitchDampingCoefficient(jointDamping.x), mYawDampingCoefficient(
		jointDamping.y), mRollDampingCoefficient(jointDamping.z) {

}

MorphogeneBranch::MorphogeneBranch() :
	mBranchGeneType(-1), mFlipped(false), mJointAnchorX(0), mJointAnchorY(0), mJointAnchorZ(
		0), mJointPitchMinAngle(0), mJointPitchMaxAngle(0), mJointYawMinAngle(
		0), mJointYawMaxAngle(0), mJointRollMinAngle(0), mJointRollMaxAngle(0), mMirrored(
		false), mJointType(JointPhysics::HINGE_JOINT), mJointPitchAxisX(1), mJointPitchAxisY(
		0), mJointPitchAxisZ(0), mJointYawAxisX(0), mJointYawAxisY(1), mJointYawAxisZ(
		0), mPitchStiffnessCoefficient(0), mYawStiffnessCoefficient(0), mRollStiffnessCoefficient(
		0), mPitchDampingCoefficient(0), mYawDampingCoefficient(0), mRollDampingCoefficient(
		0) {

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

	mJointYawAxisX = morphogeneBranch.mJointYawAxisX;
	mJointYawAxisY = morphogeneBranch.mJointYawAxisY;
	mJointYawAxisZ = morphogeneBranch.mJointYawAxisZ;
	mJointType = morphogeneBranch.mJointType;

	mPitchStiffnessCoefficient = morphogeneBranch.mPitchStiffnessCoefficient;
	mYawStiffnessCoefficient = morphogeneBranch.mYawStiffnessCoefficient;
	mRollStiffnessCoefficient = morphogeneBranch.mRollStiffnessCoefficient;

	mPitchDampingCoefficient = morphogeneBranch.mPitchDampingCoefficient;
	mYawDampingCoefficient = morphogeneBranch.mYawDampingCoefficient;
	mRollDampingCoefficient = morphogeneBranch.mRollDampingCoefficient;
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

	Ogre::Vector3 randomAxisVector = Randomness::getSingleton()->nextVector();
	Ogre::Vector3 yawAxisVector = pitchAxisVector.crossProduct(
		randomAxisVector);
	mJointYawAxisX = yawAxisVector.x;
	mJointYawAxisY = yawAxisVector.y;
	mJointYawAxisZ = yawAxisVector.z;

	/**
	 * The joint limits in each direction (pitch=1=Y,yaw=2=Z, roll=0=X)
	 *   6DOF constraint uses Euler angles and to define limits
	 * it is assumed that rotational order is :
	 * Z - first, allowed limits are (-PI+epsilon,PI-epsilon);
	 * new position of Y - second (allowed limits are
	 * (-PI + epsilon, PI - epsilon), where epsilon is a small positive number
	 * used to prevent constraint from instability on poles;
	 * new position of X, allowed limits are (-PI+epsilon,PI-epsilon);
	 * So to simulate ODE Universal joint we should use parent
	 * axis as Z, child axis as Y and limit all other DOFs
	 * Based on:
	 *  http://ode-wiki.org/wiki/index.php?title=Manual:_Joint_Types_and_Functions
	 *  http://bulletphysics.org/Bullet/phpBB3/viewtopic.php?f=9&t=10938&p=36662&hilit=limits#p36662
	 */
	mJointPitchMinAngle = Randomness::getSingleton()->nextUnifDouble(
		-boost::math::constants::pi<double>() + PhysicsConfiguration::UNIV_EPS,
		boost::math::constants::pi<double>() - PhysicsConfiguration::UNIV_EPS);
	mJointPitchMaxAngle = Randomness::getSingleton()->nextUnifDouble(
		-boost::math::constants::pi<double>() + PhysicsConfiguration::UNIV_EPS,
		boost::math::constants::pi<double>() - PhysicsConfiguration::UNIV_EPS);
	mJointYawMinAngle = Randomness::getSingleton()->nextUnifDouble(
		-boost::math::constants::pi<double>() + PhysicsConfiguration::UNIV_EPS,
		boost::math::constants::pi<double>() - PhysicsConfiguration::UNIV_EPS);
	mJointYawMaxAngle = Randomness::getSingleton()->nextUnifDouble(
		-boost::math::constants::pi<double>() + PhysicsConfiguration::UNIV_EPS,
		boost::math::constants::pi<double>() - PhysicsConfiguration::UNIV_EPS);
	mJointRollMinAngle = Randomness::getSingleton()->nextUnifDouble(
		-boost::math::constants::pi<double>() + PhysicsConfiguration::UNIV_EPS,
		boost::math::constants::pi<double>() - PhysicsConfiguration::UNIV_EPS);
	mJointRollMaxAngle = Randomness::getSingleton()->nextUnifDouble(
		-boost::math::constants::pi<double>() + PhysicsConfiguration::UNIV_EPS,
		boost::math::constants::pi<double>() - PhysicsConfiguration::UNIV_EPS);

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

	mPitchStiffnessCoefficient = 0;
	mPitchDampingCoefficient = Randomness::getSingleton()->nextUnifDouble(
		MorphologyConfiguration::JOINT_MIN_DAMPING_COEFFICIENT,
		MorphologyConfiguration::JOINT_MAX_DAMPING_COEFFICIENT);
	mYawStiffnessCoefficient = 0;
	mYawDampingCoefficient = Randomness::getSingleton()->nextUnifDouble(
		MorphologyConfiguration::JOINT_MIN_DAMPING_COEFFICIENT,
		MorphologyConfiguration::JOINT_MAX_DAMPING_COEFFICIENT);
	mRollStiffnessCoefficient = 0;
	mRollDampingCoefficient = Randomness::getSingleton()->nextUnifDouble(
		MorphologyConfiguration::JOINT_MIN_DAMPING_COEFFICIENT,
		MorphologyConfiguration::JOINT_MAX_DAMPING_COEFFICIENT);
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

	Ogre::Vector3 pitchAxisVector1 = Randomness::getSingleton()->nextVector();
	Ogre::Vector3 pitchAxisVector2 = Randomness::getSingleton()->nextVector();
	Ogre::Vector3 pitchAxisVector(
		(abs(mJointAnchorX - pitchAxisVector1.x)
			< abs(mJointAnchorX - pitchAxisVector2.x)) ?
			pitchAxisVector1.x : pitchAxisVector2.x,
		(abs(mJointAnchorY - pitchAxisVector1.y)
			< abs(mJointAnchorY - pitchAxisVector2.y)) ?
			pitchAxisVector1.y : pitchAxisVector2.y,
		(abs(mJointAnchorZ - pitchAxisVector1.z)
			< abs(mJointAnchorZ - pitchAxisVector2.z)) ?
			pitchAxisVector1.z : pitchAxisVector2.z);
	pitchAxisVector.normalise();
	mJointPitchAxisX = pitchAxisVector.x;
	mJointPitchAxisY = pitchAxisVector.y;
	mJointPitchAxisZ = pitchAxisVector.z;

	Ogre::Vector3 randomAxisVector = Randomness::getSingleton()->nextVector();
	Ogre::Vector3 yawAxisVector = pitchAxisVector.crossProduct(
		randomAxisVector);
	mJointYawAxisX = yawAxisVector.x;
	mJointYawAxisY = yawAxisVector.y;
	mJointYawAxisZ = yawAxisVector.z;

	/**
	 * The joint limits in each direction (pitch=1=Y,yaw=2=Z, roll=0=X)
	 *   6DOF constraint uses Euler angles and to define limits
	 * it is assumed that rotational order is :
	 * Z - first, allowed limits are (-PI+epsilon,PI-epsilon);
	 * new position of Y - second (allowed limits are
	 * (-PI + epsilon, PI - epsilon), where epsilon is a small positive number
	 * used to prevent constraint from instability on poles;
	 * new position of X, allowed limits are (-PI+epsilon,PI-epsilon);
	 * So to simulate ODE Universal joint we should use parent
	 * axis as Z, child axis as Y and limit all other DOFs
	 * Based on:
	 *  http://ode-wiki.org/wiki/index.php?title=Manual:_Joint_Types_and_Functions
	 *  http://bulletphysics.org/Bullet/phpBB3/viewtopic.php?f=9&t=10938&p=36662&hilit=limits#p36662
	 */
	mJointPitchMinAngle = Randomness::getSingleton()->nextUnifDouble(
		-boost::math::constants::pi<double>() + PhysicsConfiguration::UNIV_EPS,
		boost::math::constants::pi<double>() - PhysicsConfiguration::UNIV_EPS);
	mJointPitchMaxAngle = Randomness::getSingleton()->nextUnifDouble(
		-boost::math::constants::pi<double>() + PhysicsConfiguration::UNIV_EPS,
		boost::math::constants::pi<double>() - PhysicsConfiguration::UNIV_EPS);
	mJointYawMinAngle = Randomness::getSingleton()->nextUnifDouble(
		-boost::math::constants::pi<double>() + PhysicsConfiguration::UNIV_EPS,
		boost::math::constants::pi<double>() - PhysicsConfiguration::UNIV_EPS);
	mJointYawMaxAngle = Randomness::getSingleton()->nextUnifDouble(
		-boost::math::constants::pi<double>() + PhysicsConfiguration::UNIV_EPS,
		boost::math::constants::pi<double>() - PhysicsConfiguration::UNIV_EPS);
	mJointRollMinAngle = Randomness::getSingleton()->nextUnifDouble(
		-boost::math::constants::pi<double>() + PhysicsConfiguration::UNIV_EPS,
		boost::math::constants::pi<double>() - PhysicsConfiguration::UNIV_EPS);
	mJointRollMaxAngle = Randomness::getSingleton()->nextUnifDouble(
		-boost::math::constants::pi<double>() + PhysicsConfiguration::UNIV_EPS,
		boost::math::constants::pi<double>() - PhysicsConfiguration::UNIV_EPS);

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

	Ogre::Vector3 anchorVector1 = Randomness::getSingleton()->nextVector();
	Ogre::Vector3 anchorVector2 = Randomness::getSingleton()->nextVector();
	Ogre::Vector3 anchorVector(
		(abs(mJointAnchorX - anchorVector1.x)
			< abs(mJointAnchorX - anchorVector2.x)) ?
			anchorVector1.x : anchorVector2.x,
		(abs(mJointAnchorY - anchorVector1.y)
			< abs(mJointAnchorY - anchorVector2.y)) ?
			anchorVector1.y : anchorVector2.y,
		(abs(mJointAnchorZ - anchorVector1.z)
			< abs(mJointAnchorZ - anchorVector2.z)) ?
			anchorVector1.z : anchorVector2.z);
	anchorVector.normalise();
	mJointAnchorX = anchorVector.x; // Set joint anchor X, Y and Z, where the anchor lies in the center of mass
	mJointAnchorY = anchorVector.y; // and the X, Y and Z form a vector, pointing to the point on the surface where
	mJointAnchorZ = anchorVector.z; // the joint will be attached.

	mBranchGeneType = 0;

	mPitchStiffnessCoefficient = 0;
	mPitchDampingCoefficient = Randomness::getSingleton()->nextUnifDouble(
		MorphologyConfiguration::JOINT_MIN_DAMPING_COEFFICIENT,
		MorphologyConfiguration::JOINT_MAX_DAMPING_COEFFICIENT);
	mYawStiffnessCoefficient = 0;
	mYawDampingCoefficient = Randomness::getSingleton()->nextUnifDouble(
		MorphologyConfiguration::JOINT_MIN_DAMPING_COEFFICIENT,
		MorphologyConfiguration::JOINT_MAX_DAMPING_COEFFICIENT);
	mRollStiffnessCoefficient = 0;
	mRollDampingCoefficient = Randomness::getSingleton()->nextUnifDouble(
		MorphologyConfiguration::JOINT_MIN_DAMPING_COEFFICIENT,
		MorphologyConfiguration::JOINT_MAX_DAMPING_COEFFICIENT);
}
