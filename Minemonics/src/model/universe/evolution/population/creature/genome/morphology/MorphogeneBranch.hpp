/*
 * GeneBranch.h
 *
 *  Created on: Mar 9, 2015
 *      Author: leviathan
 */

#ifndef MODEL_EVOLUTION_POPULATION_CREATURE_GENOME_MORPHOGENEBRANCH_H_
#define MODEL_EVOLUTION_POPULATION_CREATURE_GENOME_MORPHOGENEBRANCH_H_

//# corresponding header
#include <boost/archive/tmpdir.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/version.hpp>
#include <model/universe/evolution/population/creature/genome/GeneBranch.hpp>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers

/**
 * @brief		The morphogene branch defines how a certain morphogene class branches into another class.
 * @details		Details
 * @date		2015-04-27
 * @author		Benjamin Ellenberger
 */
class MorphogeneBranch: public GeneBranch {
public:
	MorphogeneBranch();
	virtual ~MorphogeneBranch();

	void initialize();

	virtual void mutate();

	virtual MorphogeneBranch* clone();

	bool equals(const MorphogeneBranch& geneBranch) const;

	/**
	 * Give access to boost serialization
	 */
	friend class boost::serialization::access;

	/**
	 * Serializes the gene branch to a string.
	 * @param os The ostream.
	 * @param morphoGeneBranch The morphogene branch we want to serialize.
	 * @return A string containing all information about the morphogene branch.
	 */
	friend std::ostream & operator<<(std::ostream &os,
			const MorphogeneBranch &morphogeneBranch) {
		return os << "MorphogeneBranch: isActive=" << morphogeneBranch.mActive
				<< "/GeneType=" << morphogeneBranch.mBranchGeneType
				<< "/isFlipped=" << morphogeneBranch.mFlipped << "/isMirrored="
				<< morphogeneBranch.mMirrored << "/Joint Anchor:("
				<< morphogeneBranch.mJointAnchorX << ","
				<< morphogeneBranch.mJointAnchorY << ","
				<< morphogeneBranch.mJointAnchorZ << ")" << "/Joint Rotation:("
				<< morphogeneBranch.mJointPitch << ","
				<< morphogeneBranch.mJointYaw << ","
				<< morphogeneBranch.mJointRoll << ")"
				<< "/Joint Limits (Min/Max)[Pitch:"
				<< morphogeneBranch.mJointPitchMinAngle << "/"
				<< morphogeneBranch.mJointPitchMaxAngle << "][Yaw:"
				<< morphogeneBranch.mJointYawMinAngle << "/"
				<< morphogeneBranch.mJointYawMaxAngle << "][Roll:"
				<< morphogeneBranch.mJointRollMinAngle << "/"
				<< morphogeneBranch.mJointRollMaxAngle
				<< "/SpringDamping: [Pitch:"
				<< morphogeneBranch.mSpringPitchDampingCoefficient << "][Yaw:"
				<< morphogeneBranch.mSpringYawDampingCoefficient << "][Roll:"
				<< morphogeneBranch.mSpringRollDampingCoefficient
				<< "/JointStiffness: [Pitch:"
				<< morphogeneBranch.mJointPitchStiffness << "][Yaw:"
				<< morphogeneBranch.mJointYawStiffness << "][Roll:"
				<< morphogeneBranch.mJointRollStiffness
				<< "/JointMotorEnabled: [Pitch:"
				<< morphogeneBranch.mJointPitchMotorEnabled << "][Yaw:"
				<< morphogeneBranch.mJointYawMotorEnabled << "][Roll:"
				<< morphogeneBranch.mJointRollMotorEnabled
				<< "/JointMaxForce: [Pitch:"
				<< morphogeneBranch.mJointMaxPitchForce << "][Yaw:"
				<< morphogeneBranch.mJointMaxYawForce << "][Roll:"
				<< morphogeneBranch.mJointMaxRollForce
				<< "/JointMaxSpeed: [Pitch:"
				<< morphogeneBranch.mJointMaxPitchSpeed << "][Yaw:"
				<< morphogeneBranch.mJointMaxYawSpeed << "][Roll:"
				<< morphogeneBranch.mJointMaxRollSpeed;
	}

	/**
	 * Serializes the morphogene branch to an xml file.
	 * @param ar The archive.
	 * @param The file version.
	 */
	//TODO::Fix serializing via serializing the base class
	template<class Archive>
	void serialize(Archive & ar, const unsigned int /* file_version */) {
		ar
				& BOOST_SERIALIZATION_NVP(
						mActive) & BOOST_SERIALIZATION_NVP(mBranchGeneType)
						& BOOST_SERIALIZATION_NVP(mFlipped)
						& BOOST_SERIALIZATION_NVP(mMirrored)
						& BOOST_SERIALIZATION_NVP(mJointAnchorX)
						& BOOST_SERIALIZATION_NVP(mJointAnchorY)
						& BOOST_SERIALIZATION_NVP(mJointAnchorZ)
						& BOOST_SERIALIZATION_NVP(mJointPitch)
						& BOOST_SERIALIZATION_NVP(mJointYaw)
						& BOOST_SERIALIZATION_NVP(mJointRoll)
						& BOOST_SERIALIZATION_NVP(mJointPitchMinAngle)
						& BOOST_SERIALIZATION_NVP(mJointPitchMaxAngle)
						& BOOST_SERIALIZATION_NVP(mJointYawMinAngle)
						& BOOST_SERIALIZATION_NVP(mJointYawMaxAngle)
						& BOOST_SERIALIZATION_NVP(mJointRollMinAngle)
						& BOOST_SERIALIZATION_NVP(mJointRollMaxAngle)
						& BOOST_SERIALIZATION_NVP(mSpringPitchDampingCoefficient)
						& BOOST_SERIALIZATION_NVP(mSpringYawDampingCoefficient)
						& BOOST_SERIALIZATION_NVP(mSpringRollDampingCoefficient)
						& BOOST_SERIALIZATION_NVP(mJointPitchStiffness)
						& BOOST_SERIALIZATION_NVP(mJointYawStiffness)
						& BOOST_SERIALIZATION_NVP(mJointRollStiffness)
						& BOOST_SERIALIZATION_NVP(mJointPitchMotorEnabled)
						& BOOST_SERIALIZATION_NVP(mJointYawMotorEnabled)
						& BOOST_SERIALIZATION_NVP(mJointRollMotorEnabled)
						& BOOST_SERIALIZATION_NVP(mJointMaxPitchForce)
						& BOOST_SERIALIZATION_NVP(mJointMaxYawForce)
						& BOOST_SERIALIZATION_NVP(mJointMaxRollForce)
						& BOOST_SERIALIZATION_NVP(mJointMaxPitchSpeed)
						& BOOST_SERIALIZATION_NVP(mJointMaxYawSpeed)
						& BOOST_SERIALIZATION_NVP(mJointMaxRollSpeed);
	}

	// Accessor methods
	const int getBranchGeneType() {
		return mBranchGeneType;
	}

	void setBranchGeneType(int branchGeneType) {
		mBranchGeneType = branchGeneType;
	}

	bool isFlipped() const {
		return mFlipped;
	}

	void setFlipped(bool flipped) {
		mFlipped = flipped;
	}

	double getJointAnchorX() const {
		return mJointAnchorX;
	}

	void setJointAnchorX(double jointAnchorX) {
		mJointAnchorX = jointAnchorX;
	}

	double getJointAnchorY() const {
		return mJointAnchorY;
	}

	void setJointAnchorY(double jointAnchorY) {
		mJointAnchorY = jointAnchorY;
	}

	double getJointAnchorZ() const {
		return mJointAnchorZ;
	}

	void setJointAnchorZ(double jointAnchorZ) {
		mJointAnchorZ = jointAnchorZ;
	}

	double getJointPitch() const {
		return mJointPitch;
	}

	void setJointPitch(double jointPitch) {
		mJointPitch = jointPitch;
	}

	double getJointRoll() const {
		return mJointRoll;
	}

	void setJointRoll(double jointRoll) {
		mJointRoll = jointRoll;
	}

	double getJointYaw() const {
		return mJointYaw;
	}

	void setJointYaw(double jointYaw) {
		mJointYaw = jointYaw;
	}

	bool isMirrored() const {
		return mMirrored;
	}

	void setMirrored(bool mirrored) {
		mMirrored = mirrored;
	}

	double getJointPitchMaxAngle() const {
		return mJointPitchMaxAngle;
	}

	void setJointPitchMaxAngle(double jointPitchMaxAngle) {
		mJointPitchMaxAngle = jointPitchMaxAngle;
	}

	double getJointPitchMinAngle() const {
		return mJointPitchMinAngle;
	}

	void setJointPitchMinAngle(double jointPitchMinAngle) {
		mJointPitchMinAngle = jointPitchMinAngle;
	}

	double getJointRollMaxAngle() const {
		return mJointRollMaxAngle;
	}

	void setJointRollMaxAngle(double jointRollMaxAngle) {
		mJointRollMaxAngle = jointRollMaxAngle;
	}

	double getJointRollMinAngle() const {
		return mJointRollMinAngle;
	}

	void setJointRollMinAngle(double jointRollMinAngle) {
		mJointRollMinAngle = jointRollMinAngle;
	}

	double getJointYawMaxAngle() const {
		return mJointYawMaxAngle;
	}

	void setJointYawMaxAngle(double jointYawMaxAngle) {
		mJointYawMaxAngle = jointYawMaxAngle;
	}

	double getJointYawMinAngle() const {
		return mJointYawMinAngle;
	}

	void setJointYawMinAngle(double jointYawMinAngle) {
		mJointYawMinAngle = jointYawMinAngle;
	}

	double getJointPitchStiffness() const {
		return mJointPitchStiffness;
	}

	void setJointPitchStiffness(double jointPitchStiffness) {
		mJointPitchStiffness = jointPitchStiffness;
	}

	double getJointRollStiffness() const {
		return mJointRollStiffness;
	}

	void setJointRollStiffness(double jointRollStiffness) {
		mJointRollStiffness = jointRollStiffness;
	}

	double getJointYawStiffness() const {
		return mJointYawStiffness;
	}

	void setJointYawStiffness(double jointYawStiffness) {
		mJointYawStiffness = jointYawStiffness;
	}

	double getSpringPitchDampingCoefficient() const {
		return mSpringPitchDampingCoefficient;
	}

	void setSpringPitchDampingCoefficient(
			double springPitchDampingCoefficient) {
		mSpringPitchDampingCoefficient = springPitchDampingCoefficient;
	}

	double getSpringRollDampingCoefficient() const {
		return mSpringRollDampingCoefficient;
	}

	void setSpringRollDampingCoefficient(double springRollDampingCoefficient) {
		mSpringRollDampingCoefficient = springRollDampingCoefficient;
	}

	double getSpringYawDampingCoefficient() const {
		return mSpringYawDampingCoefficient;
	}

	void setSpringYawDampingCoefficient(double springYawDampingCoefficient) {
		mSpringYawDampingCoefficient = springYawDampingCoefficient;
	}

	bool isJointPitchMotorEnabled() const {
		return mJointPitchMotorEnabled;
	}

	void setJointPitchMotorEnabled(bool jointPitchMotorEnabled) {
		mJointPitchMotorEnabled = jointPitchMotorEnabled;
	}

	bool isJointRollMotorEnabled() const {
		return mJointRollMotorEnabled;
	}

	void setJointRollMotorEnabled(bool jointRollMotorEnabled) {
		mJointRollMotorEnabled = jointRollMotorEnabled;
	}

	bool isJointYawMotorEnabled() const {
		return mJointYawMotorEnabled;
	}

	void setJointYawMotorEnabled(bool jointYawMotorEnabled) {
		mJointYawMotorEnabled = jointYawMotorEnabled;
	}

	double getJointMaxPitchForce() const {
		return mJointMaxPitchForce;
	}

	void setJointMaxPitchForce(double jointMaxPitchForce) {
		mJointMaxPitchForce = jointMaxPitchForce;
	}

	double getJointMaxPitchSpeed() const {
		return mJointMaxPitchSpeed;
	}

	void setJointMaxPitchSpeed(double jointMaxPitchSpeed) {
		mJointMaxPitchSpeed = jointMaxPitchSpeed;
	}

	double getJointMaxRollForce() const {
		return mJointMaxRollForce;
	}

	void setJointMaxRollForce(double jointMaxRollForce) {
		mJointMaxRollForce = jointMaxRollForce;
	}

	double getJointMaxRollSpeed() const {
		return mJointMaxRollSpeed;
	}

	void setJointMaxRollSpeed(double jointMaxRollSpeed) {
		mJointMaxRollSpeed = jointMaxRollSpeed;
	}

	double getJointMaxYawForce() const {
		return mJointMaxYawForce;
	}

	void setJointMaxYawForce(double jointMaxYawForce) {
		mJointMaxYawForce = jointMaxYawForce;
	}

	double getJointMaxYawSpeed() const {
		return mJointMaxYawSpeed;
	}

	void setJointMaxYawSpeed(double jointMaxYawSpeed) {
		mJointMaxYawSpeed = jointMaxYawSpeed;
	}

private:
	/**
	 * Spherical coordinates around the origin of the segment at the center of mass.
	 */
	double mJointAnchorX, mJointAnchorY, mJointAnchorZ;

	/**
	 * Direction of joint anchoring on the surface of the segment
	 */
	double mJointPitch, mJointYaw, mJointRoll;

	/**
	 * Joint limits for each degree of freedom
	 */
	double mJointPitchMaxAngle, mJointYawMaxAngle, mJointRollMaxAngle;
	double mJointPitchMinAngle, mJointYawMinAngle, mJointRollMinAngle;

	/**
	 * The spring damping coefficient of the joint springs.
	 */
	double mSpringPitchDampingCoefficient, mSpringYawDampingCoefficient,
			mSpringRollDampingCoefficient;

	/**
	 * The stiffness of the joint.
	 */
	double mJointPitchStiffness, mJointYawStiffness, mJointRollStiffness;

	/**
	 * If the angular motor is enabled.
	 */
	bool mJointPitchMotorEnabled, mJointYawMotorEnabled, mJointRollMotorEnabled;

	/**
	 * The maximum force of the joint
	 */
	double mJointMaxPitchForce, mJointMaxYawForce, mJointMaxRollForce;

	/**
	 * The maximum speed of the joint
	 */
	double mJointMaxPitchSpeed, mJointMaxYawSpeed, mJointMaxRollSpeed;

	/**
	 * Determines if this branch is mirrored through the center of mass of its segment.
	 */
	bool mMirrored;

	/**
	 * Determines if this branch is mirrored along the axis defined by the parent gene branch of this branch.
	 */
	bool mFlipped;

	/**
	 * The gene type it branches into.
	 */
	int mBranchGeneType;
};
BOOST_CLASS_VERSION(MorphogeneBranch, 1)

#endif /* MODEL_EVOLUTION_POPULATION_CREATURE_GENOME_MORPHOGENEBRANCH_H_ */
