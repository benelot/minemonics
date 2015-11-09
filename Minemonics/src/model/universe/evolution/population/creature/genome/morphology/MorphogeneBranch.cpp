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

//## controller headers
//## model headers
//## view headers
//## utils headers
#include <utils/Randomness.hpp>

#ifndef UNIV_EPS
#define UNIV_EPS 0.01f
#endif

MorphogeneBranch::MorphogeneBranch(Ogre::Vector3 anchorPosition,
	Ogre::Euler anchorOrientation, Ogre::Vector3 jointMinAngle,
	Ogre::Vector3 jointMaxAngle) :
	mBranchGeneType(-1), mFlipped(false), mJointAnchorX(anchorPosition.x), mJointAnchorY(
		anchorPosition.y), mJointAnchorZ(anchorPosition.z), mJointPitch(
		anchorOrientation.pitch().valueRadians()), mJointYaw(
		anchorOrientation.yaw().valueRadians()), mJointRoll(
		anchorOrientation.roll().valueRadians()), mJointPitchMinAngle(
		jointMinAngle.x), mJointPitchMaxAngle(jointMaxAngle.x), mJointYawMinAngle(
		jointMinAngle.y), mJointYawMaxAngle(jointMaxAngle.y), mJointRollMinAngle(
		jointMinAngle.z), mJointRollMaxAngle(jointMaxAngle.z), mMirrored(0), mSpringPitchDampingCoefficient(
		0), mJointPitchStiffness(0), mSpringYawDampingCoefficient(0), mJointYawStiffness(
		0), mSpringRollDampingCoefficient(0), mJointRollStiffness(0), mJointPitchMotorEnabled(
		false), mJointYawMotorEnabled(false), mJointRollMotorEnabled(false), mJointMaxPitchForce(
		0), mJointMaxPitchSpeed(0), mJointMaxYawForce(0), mJointMaxYawSpeed(0), mJointMaxRollForce(
		0), mJointMaxRollSpeed(0), mJointPitchXOffset(0), mJointPitchYOffset(0), mJointPitchAmplitude(
		0), mJointPitchFrequency(0), mJointYawXOffset(0), mJointYawYOffset(0), mJointYawAmplitude(
		0), mJointYawFrequency(0), mJointRollXOffset(0), mJointRollYOffset(0), mJointRollAmplitude(
		0), mJointRollFrequency(0), mJointPitchEnabled(true), mJointYawEnabled(
		true), mJointRollEnabled(true), mJointType(JointPhysics::HINGE_JOINT), mJointPitchAxisX(
		1), mJointPitchAxisY(1), mJointPitchAxisZ(1) {

}

MorphogeneBranch::MorphogeneBranch() :
	mBranchGeneType(-1), mFlipped(false), mJointAnchorX(0), mJointAnchorY(0), mJointAnchorZ(
		0), mJointPitch(0), mJointYaw(0), mJointRoll(0), mJointPitchMinAngle(0), mJointPitchMaxAngle(
		0), mJointYawMinAngle(0), mJointYawMaxAngle(0), mJointRollMinAngle(0), mJointRollMaxAngle(
		0), mMirrored(0), mSpringPitchDampingCoefficient(0), mJointPitchStiffness(
		0), mSpringYawDampingCoefficient(0), mJointYawStiffness(0), mSpringRollDampingCoefficient(
		0), mJointRollStiffness(0), mJointPitchMotorEnabled(false), mJointYawMotorEnabled(
		false), mJointRollMotorEnabled(false), mJointMaxPitchForce(0), mJointMaxPitchSpeed(
		0), mJointMaxYawForce(0), mJointMaxYawSpeed(0), mJointMaxRollForce(0), mJointMaxRollSpeed(
		0), mJointPitchXOffset(0), mJointPitchYOffset(0), mJointPitchAmplitude(
		0), mJointPitchFrequency(0), mJointYawXOffset(0), mJointYawYOffset(0), mJointYawAmplitude(
		0), mJointYawFrequency(0), mJointRollXOffset(0), mJointRollYOffset(0), mJointRollAmplitude(
		0), mJointRollFrequency(0), mJointPitchEnabled(true), mJointYawEnabled(
		true), mJointRollEnabled(true), mJointType(JointPhysics::HINGE_JOINT), mJointPitchAxisX(
		1), mJointPitchAxisY(1), mJointPitchAxisZ(1) {

}

MorphogeneBranch::MorphogeneBranch(const MorphogeneBranch& morphogeneBranch) {
	mActive = morphogeneBranch.mActive;
	mBranchGeneType = morphogeneBranch.mBranchGeneType;
	mFlipped = morphogeneBranch.mFlipped;
	mType = morphogeneBranch.mType;
	mJointAnchorX = morphogeneBranch.mJointAnchorX;
	mJointAnchorY = morphogeneBranch.mJointAnchorY;
	mJointAnchorZ = morphogeneBranch.mJointAnchorZ;
	mJointMaxPitchForce = morphogeneBranch.mJointMaxPitchForce;
	mJointMaxPitchSpeed = morphogeneBranch.mJointMaxPitchSpeed;
	mJointMaxRollForce = morphogeneBranch.mJointMaxRollForce;
	mJointMaxRollSpeed = morphogeneBranch.mJointMaxRollSpeed;
	mJointMaxYawForce = morphogeneBranch.mJointMaxYawForce;
	mJointMaxYawSpeed = morphogeneBranch.mJointMaxYawSpeed;

	mJointPitch = morphogeneBranch.mJointPitch;
	mJointPitchMaxAngle = morphogeneBranch.mJointPitchMaxAngle;
	mJointPitchMinAngle = morphogeneBranch.mJointPitchMinAngle;
	mJointPitchMotorEnabled = morphogeneBranch.mJointPitchMotorEnabled;
	mJointPitchStiffness = morphogeneBranch.mJointPitchStiffness;
	mJointYaw = morphogeneBranch.mJointYaw;
	mJointYawMaxAngle = morphogeneBranch.mJointYawMaxAngle;
	mJointYawMinAngle = morphogeneBranch.mJointYawMinAngle;
	mJointYawMotorEnabled = morphogeneBranch.mJointYawMotorEnabled;
	mJointYawStiffness = morphogeneBranch.mJointYawStiffness;
	mJointRoll = morphogeneBranch.mJointRoll;
	mJointRollMaxAngle = morphogeneBranch.mJointRollMaxAngle;
	mJointRollMinAngle = morphogeneBranch.mJointRollMinAngle;
	mJointRollMotorEnabled = morphogeneBranch.mJointRollMotorEnabled;
	mJointRollStiffness = morphogeneBranch.mJointRollStiffness;
	mMirrored = morphogeneBranch.mMirrored;
	mSpringPitchDampingCoefficient =
		morphogeneBranch.mSpringPitchDampingCoefficient;
	mSpringYawDampingCoefficient =
		morphogeneBranch.mSpringYawDampingCoefficient;
	mSpringRollDampingCoefficient =
		morphogeneBranch.mSpringRollDampingCoefficient;

	mJointPitchEnabled = morphogeneBranch.mJointPitchEnabled;
	mJointYawEnabled = morphogeneBranch.mJointYawEnabled;
	mJointRollEnabled = morphogeneBranch.mJointRollEnabled;
	mJointPitchAxisX = morphogeneBranch.mJointPitchAxisX;
	mJointPitchAxisY = morphogeneBranch.mJointPitchAxisY;
	mJointPitchAxisZ = morphogeneBranch.mJointPitchAxisZ;
	mJointType = morphogeneBranch.mJointType;

	mJointPitchXOffset = morphogeneBranch.mJointPitchXOffset;
	mJointPitchYOffset = morphogeneBranch.mJointPitchYOffset;
	mJointPitchAmplitude = morphogeneBranch.mJointPitchAmplitude;
	mJointPitchFrequency = morphogeneBranch.mJointPitchFrequency;
	mJointYawXOffset = morphogeneBranch.mJointYawXOffset;
	mJointYawYOffset = morphogeneBranch.mJointYawYOffset;
	mJointYawAmplitude = morphogeneBranch.mJointYawAmplitude;
	mJointYawFrequency = morphogeneBranch.mJointYawFrequency;
	mJointRollXOffset = morphogeneBranch.mJointRollXOffset;
	mJointRollYOffset = morphogeneBranch.mJointRollYOffset;
	mJointRollAmplitude = morphogeneBranch.mJointRollAmplitude;
	mJointRollFrequency = morphogeneBranch.mJointRollFrequency;
}

MorphogeneBranch::~MorphogeneBranch() {
}

void MorphogeneBranch::initialize() {
	GeneBranch::initialize(GeneBranch::MORPHOGENE_BRANCH);

	Ogre::Vector3 anchorVector = Randomness::getSingleton()->nextVector();
	mJointAnchorX = anchorVector.x; // Set joint anchor X, Y and Z, where the anchor lies in the center of mass
	mJointAnchorY = anchorVector.y; // and the X, Y and Z form a vector, pointing to the point on the surface where
	mJointAnchorZ = anchorVector.z; // the joint will be attached.

	mJointPitchEnabled = Randomness::getSingleton()->nextUnifBoolean();
	mJointYawEnabled = Randomness::getSingleton()->nextUnifBoolean();
	mJointRollEnabled = Randomness::getSingleton()->nextUnifBoolean();

	Ogre::Vector3 pitchAxisVector = Randomness::getSingleton()->nextVector();
	mJointPitchAxisX = pitchAxisVector.x;
	mJointPitchAxisY = pitchAxisVector.y;
	mJointPitchAxisZ = pitchAxisVector.z;

	//TODO: Change if other joint control becomes available
	mJointType = JointPhysics::HINGE_JOINT;
//	mJointType =
//		(JointPhysics::JointType) Randomness::getSingleton()->nextUnifPosInt(1,
//			JointPhysics::NUM_JOINTS);
	/**
	 * The yaw, pitch and roll values representing a correction in angle of the joint anchor on the surface.
	 */
	mJointYaw = Randomness::getSingleton()->nextUnifDouble(
		-boost::math::constants::pi<double>(),
		boost::math::constants::pi<double>());
	mJointPitch = Randomness::getSingleton()->nextUnifDouble(
		-boost::math::constants::pi<double>(),
		boost::math::constants::pi<double>());
	mJointRoll = Randomness::getSingleton()->nextUnifDouble(
		-boost::math::constants::pi<double>(),
		boost::math::constants::pi<double>());

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

	/**
	 * Set whether the branch should be mirrored or flipped to the other side.
	 */
	mMirrored = Randomness::getSingleton()->nextUnifBoolean();
	mFlipped = Randomness::getSingleton()->nextUnifBoolean();
	mActive = Randomness::getSingleton()->nextUnifBoolean();

	mBranchGeneType = 0;

	/**
	 * The spring damping coefficient
	 */
	mSpringPitchDampingCoefficient = Randomness::getSingleton()->nextUnifDouble(
		MorphologyConfiguration::JOINT_MIN_SPRING_COEFFICIENT,
		MorphologyConfiguration::JOINT_MAX_SPRING_COEFFICIENT);
	mSpringYawDampingCoefficient = Randomness::getSingleton()->nextUnifDouble(
		MorphologyConfiguration::JOINT_MIN_SPRING_COEFFICIENT,
		MorphologyConfiguration::JOINT_MAX_SPRING_COEFFICIENT);
	mSpringRollDampingCoefficient = Randomness::getSingleton()->nextUnifDouble(
		MorphologyConfiguration::JOINT_MIN_SPRING_COEFFICIENT,
		MorphologyConfiguration::JOINT_MAX_SPRING_COEFFICIENT);

	/**
	 * The joint stiffness
	 */
	mJointPitchStiffness = Randomness::getSingleton()->nextUnifDouble(
		MorphologyConfiguration::JOINT_MIN_STIFFNESS,
		MorphologyConfiguration::JOINT_MAX_STIFFNESS);
	mJointYawStiffness = Randomness::getSingleton()->nextUnifDouble(
		MorphologyConfiguration::JOINT_MIN_STIFFNESS,
		MorphologyConfiguration::JOINT_MAX_STIFFNESS);
	mJointRollStiffness = Randomness::getSingleton()->nextUnifDouble(
		MorphologyConfiguration::JOINT_MIN_STIFFNESS,
		MorphologyConfiguration::JOINT_MAX_STIFFNESS);

	/**
	 * Whether the joint motors are enabled or not.
	 */
	mJointPitchMotorEnabled = Randomness::getSingleton()->nextUnifBoolean();
	mJointYawMotorEnabled = Randomness::getSingleton()->nextUnifBoolean();
	mJointRollMotorEnabled = Randomness::getSingleton()->nextUnifBoolean();

	/**
	 * The maximum joint speed
	 */
	mJointMaxPitchSpeed = Randomness::getSingleton()->nextUnifDouble(
		MorphologyConfiguration::JOINT_MIN_SPEED,
		MorphologyConfiguration::JOINT_MAX_SPEED);
	mJointMaxYawSpeed = Randomness::getSingleton()->nextUnifDouble(
		MorphologyConfiguration::JOINT_MIN_SPEED,
		MorphologyConfiguration::JOINT_MAX_SPEED);
	mJointMaxRollSpeed = Randomness::getSingleton()->nextUnifDouble(
		MorphologyConfiguration::JOINT_MIN_SPEED,
		MorphologyConfiguration::JOINT_MAX_SPEED);

	/**
	 * The joint frequency
	 */
	mJointPitchFrequency = Randomness::getSingleton()->nextUnifDouble(
		MorphologyConfiguration::JOINT_MIN_FREQUENCY,
		MorphologyConfiguration::JOINT_MAX_FREQUENCY);
	mJointYawFrequency = Randomness::getSingleton()->nextUnifDouble(
		MorphologyConfiguration::JOINT_MIN_FREQUENCY,
		MorphologyConfiguration::JOINT_MAX_FREQUENCY);
	mJointRollFrequency = Randomness::getSingleton()->nextUnifDouble(
		MorphologyConfiguration::JOINT_MIN_FREQUENCY,
		MorphologyConfiguration::JOINT_MAX_FREQUENCY);

	/**
	 * The joint amplitude
	 */
	mJointPitchAmplitude = Randomness::getSingleton()->nextUnifDouble(
		MorphologyConfiguration::JOINT_MIN_AMPLITUDE,
		MorphologyConfiguration::JOINT_MAX_AMPLITUDE);
	mJointYawAmplitude = Randomness::getSingleton()->nextUnifDouble(
		MorphologyConfiguration::JOINT_MIN_AMPLITUDE,
		MorphologyConfiguration::JOINT_MAX_AMPLITUDE);
	mJointRollAmplitude = Randomness::getSingleton()->nextUnifDouble(
		MorphologyConfiguration::JOINT_MIN_AMPLITUDE,
		MorphologyConfiguration::JOINT_MAX_AMPLITUDE);

	/**
	 * The joint x offset
	 */
	mJointPitchXOffset = Randomness::getSingleton()->nextUnifDouble(
		MorphologyConfiguration::JOINT_MIN_X_OFFSET,
		MorphologyConfiguration::JOINT_MAX_X_OFFSET);
	mJointYawXOffset = Randomness::getSingleton()->nextUnifDouble(
		MorphologyConfiguration::JOINT_MIN_X_OFFSET,
		MorphologyConfiguration::JOINT_MAX_X_OFFSET);
	mJointRollXOffset = Randomness::getSingleton()->nextUnifDouble(
		MorphologyConfiguration::JOINT_MIN_X_OFFSET,
		MorphologyConfiguration::JOINT_MAX_X_OFFSET);

	/**
	 * The joint y offset
	 */
	mJointPitchYOffset = Randomness::getSingleton()->nextUnifDouble(
		MorphologyConfiguration::JOINT_MIN_Y_OFFSET,
		MorphologyConfiguration::JOINT_MAX_Y_OFFSET);
	mJointYawYOffset = Randomness::getSingleton()->nextUnifDouble(
		MorphologyConfiguration::JOINT_MIN_Y_OFFSET,
		MorphologyConfiguration::JOINT_MAX_Y_OFFSET);
	mJointRollYOffset = Randomness::getSingleton()->nextUnifDouble(
		MorphologyConfiguration::JOINT_MIN_Y_OFFSET,
		MorphologyConfiguration::JOINT_MAX_Y_OFFSET);
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

	if (mJointPitchEnabled != geneBranch.mJointPitchEnabled) {
		return false;
	}

	if (mJointYawEnabled != geneBranch.mJointYawEnabled) {
		return false;
	}

	if (mJointRollEnabled != geneBranch.mJointRollEnabled) {
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

	if (mJointPitch != geneBranch.mJointPitch) {
		return false;
	}

	if (mJointYaw != geneBranch.mJointYaw) {
		return false;
	}

	if (mJointRoll != geneBranch.mJointRoll) {
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

	if (mSpringPitchDampingCoefficient
		!= geneBranch.mSpringPitchDampingCoefficient) {
		return false;
	}

	if (mSpringYawDampingCoefficient
		!= geneBranch.mSpringYawDampingCoefficient) {
		return false;
	}

	if (mSpringRollDampingCoefficient
		!= geneBranch.mSpringRollDampingCoefficient) {
		return false;
	}

	if (mJointPitchStiffness != geneBranch.mJointPitchStiffness) {
		return false;
	}

	if (mJointYawStiffness != geneBranch.mJointYawStiffness) {
		return false;
	}

	if (mJointRollStiffness != geneBranch.mJointRollStiffness) {
		return false;
	}

	if (mJointPitchMotorEnabled != geneBranch.mJointPitchMotorEnabled) {
		return false;
	}

	if (mJointYawMotorEnabled != geneBranch.mJointYawMotorEnabled) {
		return false;
	}

	if (mJointRollMotorEnabled != geneBranch.mJointRollMotorEnabled) {
		return false;
	}

	if (mJointMaxPitchForce != geneBranch.mJointMaxPitchForce) {
		return false;
	}

	if (mJointMaxYawForce != geneBranch.mJointMaxYawForce) {
		return false;
	}

	if (mJointMaxRollForce != geneBranch.mJointMaxRollForce) {
		return false;
	}

	if (mJointMaxPitchSpeed != geneBranch.mJointMaxPitchSpeed) {
		return false;
	}

	if (mJointMaxYawSpeed != geneBranch.mJointMaxYawSpeed) {
		return false;
	}

	if (mJointMaxRollSpeed != geneBranch.mJointMaxRollSpeed) {
		return false;
	}

	if (mJointPitchFrequency != geneBranch.mJointPitchFrequency) {
		return false;
	}

	if (mJointYawFrequency != geneBranch.mJointYawFrequency) {
		return false;
	}

	if (mJointRollFrequency != geneBranch.mJointRollFrequency) {
		return false;
	}

	if (mJointPitchAmplitude != geneBranch.mJointPitchAmplitude) {
		return false;
	}

	if (mJointYawAmplitude != geneBranch.mJointYawAmplitude) {
		return false;
	}

	if (mJointRollAmplitude != geneBranch.mJointRollAmplitude) {
		return false;
	}

	if (mJointPitchXOffset != geneBranch.mJointPitchXOffset) {
		return false;
	}

	if (mJointYawXOffset != geneBranch.mJointYawXOffset) {
		return false;
	}

	if (mJointRollXOffset != geneBranch.mJointRollXOffset) {
		return false;
	}

	if (mJointPitchYOffset != geneBranch.mJointPitchYOffset) {
		return false;
	}

	if (mJointYawYOffset != geneBranch.mJointYawYOffset) {
		return false;
	}

	if (mJointRollYOffset != geneBranch.mJointRollYOffset) {
		return false;
	}

	if (mBranchGeneType != geneBranch.mBranchGeneType) {
		return false;
	}

	return true;
}

MorphogeneBranch* MorphogeneBranch::clone() {
	return new MorphogeneBranch(*this);
}

void MorphogeneBranch::mutate() {

	//no clean up necessary

	initialize();
}
