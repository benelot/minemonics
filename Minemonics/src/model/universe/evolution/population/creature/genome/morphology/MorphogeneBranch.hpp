#ifndef MODEL_EVOLUTION_POPULATION_CREATURE_GENOME_MORPHOGENEBRANCH_H_
#define MODEL_EVOLUTION_POPULATION_CREATURE_GENOME_MORPHOGENEBRANCH_H_

//# corresponding headers
//# forward declarations
namespace boost {
namespace serialization {
class access;
} /* namespace serialization */
} /* namespace boost */

//# system headers
#include <iostream>

//## controller headers
//## model headers
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/version.hpp>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
#include <model/universe/evolution/population/creature/genome/GeneBranch.hpp>

//## view headers
//## utils headers

/**
 * @brief		The morphogene branch defines how a certain morphogene class branches into another class.
 * @details		Details
 * @date		2015-03-09
 * @author		Benjamin Ellenberger
 */
class MorphogeneBranch: public GeneBranch {
public:
	MorphogeneBranch();
	MorphogeneBranch(const MorphogeneBranch& morphogeneBranch);

	virtual ~MorphogeneBranch();

	/**
	 * Initialize the morphogene branch.
	 */
	void initialize();

	/**
	 * Mutate the morphogene branch.
	 */
	virtual void mutate();

	/**
	 * Clone the morphogene branch.
	 * @return The cloned morphogene branch.
	 */
	virtual MorphogeneBranch* clone();

	/**
	 * Compare gene branch with another gene branch.
	 * @param geneBranch
	 * 			Another gene branch.
	 * @return if the gene branch is equal to the other gene branch.
	 */
	bool equals(const MorphogeneBranch& geneBranch) const;

	// Accessor methods

	const int getBranchGeneType() {
		return mBranchGeneType;
	}

	void setBranchGeneType(const int branchGeneType) {
		mBranchGeneType = branchGeneType;
	}

	bool isFlipped() const {
		return mFlipped;
	}

	void setFlipped(const bool flipped) {
		mFlipped = flipped;
	}

	double getJointAnchorX() const {
		return mJointAnchorX;
	}

	void setJointAnchorX(const double jointAnchorX) {
		mJointAnchorX = jointAnchorX;
	}

	double getJointAnchorY() const {
		return mJointAnchorY;
	}

	void setJointAnchorY(const double jointAnchorY) {
		mJointAnchorY = jointAnchorY;
	}

	double getJointAnchorZ() const {
		return mJointAnchorZ;
	}

	void setJointAnchorZ(const double jointAnchorZ) {
		mJointAnchorZ = jointAnchorZ;
	}

	double getJointPitch() const {
		return mJointPitch;
	}

	void setJointPitch(const double jointPitch) {
		mJointPitch = jointPitch;
	}

	double getJointRoll() const {
		return mJointRoll;
	}

	void setJointRoll(const double jointRoll) {
		mJointRoll = jointRoll;
	}

	double getJointYaw() const {
		return mJointYaw;
	}

	void setJointYaw(const double jointYaw) {
		mJointYaw = jointYaw;
	}

	bool isMirrored() const {
		return mMirrored;
	}

	void setMirrored(const bool mirrored) {
		mMirrored = mirrored;
	}

	double getJointPitchMaxAngle() const {
		return mJointPitchMaxAngle;
	}

	void setJointPitchMaxAngle(const double jointPitchMaxAngle) {
		mJointPitchMaxAngle = jointPitchMaxAngle;
	}

	double getJointPitchMinAngle() const {
		return mJointPitchMinAngle;
	}

	void setJointPitchMinAngle(const double jointPitchMinAngle) {
		mJointPitchMinAngle = jointPitchMinAngle;
	}

	double getJointRollMaxAngle() const {
		return mJointRollMaxAngle;
	}

	void setJointRollMaxAngle(const double jointRollMaxAngle) {
		mJointRollMaxAngle = jointRollMaxAngle;
	}

	double getJointRollMinAngle() const {
		return mJointRollMinAngle;
	}

	void setJointRollMinAngle(const double jointRollMinAngle) {
		mJointRollMinAngle = jointRollMinAngle;
	}

	double getJointYawMaxAngle() const {
		return mJointYawMaxAngle;
	}

	void setJointYawMaxAngle(const double jointYawMaxAngle) {
		mJointYawMaxAngle = jointYawMaxAngle;
	}

	double getJointYawMinAngle() const {
		return mJointYawMinAngle;
	}

	void setJointYawMinAngle(const double jointYawMinAngle) {
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

	void setJointRollStiffness(const double jointRollStiffness) {
		mJointRollStiffness = jointRollStiffness;
	}

	double getJointYawStiffness() const {
		return mJointYawStiffness;
	}

	void setJointYawStiffness(const double jointYawStiffness) {
		mJointYawStiffness = jointYawStiffness;
	}

	double getSpringPitchDampingCoefficient() const {
		return mSpringPitchDampingCoefficient;
	}

	void setSpringPitchDampingCoefficient(
			const double springPitchDampingCoefficient) {
		mSpringPitchDampingCoefficient = springPitchDampingCoefficient;
	}

	double getSpringRollDampingCoefficient() const {
		return mSpringRollDampingCoefficient;
	}

	void setSpringRollDampingCoefficient(const double springRollDampingCoefficient) {
		mSpringRollDampingCoefficient = springRollDampingCoefficient;
	}

	double getSpringYawDampingCoefficient() const {
		return mSpringYawDampingCoefficient;
	}

	void setSpringYawDampingCoefficient(const double springYawDampingCoefficient) {
		mSpringYawDampingCoefficient = springYawDampingCoefficient;
	}

	bool isJointPitchMotorEnabled() const {
		return mJointPitchMotorEnabled;
	}

	void setJointPitchMotorEnabled(const bool jointPitchMotorEnabled) {
		mJointPitchMotorEnabled = jointPitchMotorEnabled;
	}

	bool isJointRollMotorEnabled() const {
		return mJointRollMotorEnabled;
	}

	void setJointRollMotorEnabled(const bool jointRollMotorEnabled) {
		mJointRollMotorEnabled = jointRollMotorEnabled;
	}

	bool isJointYawMotorEnabled() const {
		return mJointYawMotorEnabled;
	}

	void setJointYawMotorEnabled(const bool jointYawMotorEnabled) {
		mJointYawMotorEnabled = jointYawMotorEnabled;
	}

	double getJointMaxPitchForce() const {
		return mJointMaxPitchForce;
	}

	void setJointMaxPitchForce(const double jointMaxPitchForce) {
		mJointMaxPitchForce = jointMaxPitchForce;
	}

	double getJointMaxPitchSpeed() const {
		return mJointMaxPitchSpeed;
	}

	void setJointMaxPitchSpeed(const double jointMaxPitchSpeed) {
		mJointMaxPitchSpeed = jointMaxPitchSpeed;
	}

	double getJointMaxRollForce() const {
		return mJointMaxRollForce;
	}

	void setJointMaxRollForce(const double jointMaxRollForce) {
		mJointMaxRollForce = jointMaxRollForce;
	}

	double getJointMaxRollSpeed() const {
		return mJointMaxRollSpeed;
	}

	void setJointMaxRollSpeed(const double jointMaxRollSpeed) {
		mJointMaxRollSpeed = jointMaxRollSpeed;
	}

	double getJointMaxYawForce() const {
		return mJointMaxYawForce;
	}

	void setJointMaxYawForce(const double jointMaxYawForce) {
		mJointMaxYawForce = jointMaxYawForce;
	}

	double getJointMaxYawSpeed() const {
		return mJointMaxYawSpeed;
	}

	void setJointMaxYawSpeed(const double jointMaxYawSpeed) {
		mJointMaxYawSpeed = jointMaxYawSpeed;
	}

	//Serialization
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
		return os
		/**If the morphogene branch is active or not*/
		<< "MorphogeneBranch: isActive=" << morphogeneBranch.mActive

		/**The type of gene the branch leads to*/
		<< "/GeneType=" << morphogeneBranch.mBranchGeneType

		/**If the morphogene branch is flipped on the morphogene to the other side.*/
		<< "/isFlipped=" << morphogeneBranch.mFlipped

		/**If the morphogene branch is mirrored on the morphogene.*/
		<< "/isMirrored=" << morphogeneBranch.mMirrored

		/**The joint anchor position on the morphogene branching into.*/
		<< "/Joint Anchor:(" << morphogeneBranch.mJointAnchorX << ","
				<< morphogeneBranch.mJointAnchorY << ","
				<< morphogeneBranch.mJointAnchorZ << ")"

				/**The joint anchor orientation on the morphogene branching into*/
				<< "/Joint Rotation:(" << morphogeneBranch.mJointPitch << ","
				<< morphogeneBranch.mJointYaw << ","
				<< morphogeneBranch.mJointRoll << ")"

				/**The joint limits in all directions*/
				<< "/Joint Limits (Min/Max)[Pitch:"
				<< morphogeneBranch.mJointPitchMinAngle << "/"
				<< morphogeneBranch.mJointPitchMaxAngle << "][Yaw:"
				<< morphogeneBranch.mJointYawMinAngle << "/"
				<< morphogeneBranch.mJointYawMaxAngle << "][Roll:"
				<< morphogeneBranch.mJointRollMinAngle << "/"
				<< morphogeneBranch.mJointRollMaxAngle

				/**The spring damping coefficients of the joint*/
				<< "/SpringDamping: [Pitch:"
				<< morphogeneBranch.mSpringPitchDampingCoefficient << "][Yaw:"
				<< morphogeneBranch.mSpringYawDampingCoefficient << "][Roll:"
				<< morphogeneBranch.mSpringRollDampingCoefficient

				/**The joint stiffness*/
				<< "/JointStiffness: [Pitch:"
				<< morphogeneBranch.mJointPitchStiffness << "][Yaw:"
				<< morphogeneBranch.mJointYawStiffness << "][Roll:"
				<< morphogeneBranch.mJointRollStiffness

				/**If the joint motors is enabled or not*/
				<< "/JointMotorEnabled: [Pitch:"
				<< morphogeneBranch.mJointPitchMotorEnabled << "][Yaw:"
				<< morphogeneBranch.mJointYawMotorEnabled << "][Roll:"
				<< morphogeneBranch.mJointRollMotorEnabled

				/**The maximum joint forces*/
				<< "/JointMaxForce: [Pitch:"
				<< morphogeneBranch.mJointMaxPitchForce << "][Yaw:"
				<< morphogeneBranch.mJointMaxYawForce << "][Roll:"
				<< morphogeneBranch.mJointMaxRollForce

				/**The maximum joint speeds*/
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
	template<class Archive>
	void serialize(Archive & ar, const unsigned int /* file_version */) {
		ar
		/** Serialize the base object */
		& BOOST_SERIALIZATION_BASE_OBJECT_NVP(GeneBranch)

		/**If the morphogene branch is active or not*/
		& BOOST_SERIALIZATION_NVP(
				mActive)

		/**The type of gene the branch leads to*/
		& BOOST_SERIALIZATION_NVP(mBranchGeneType)

		/**If the morphogene branch is flipped on the morphogene to the other side.*/
		& BOOST_SERIALIZATION_NVP(mFlipped)

		/**If the morphogene branch is mirrored on the morphogene.*/
		& BOOST_SERIALIZATION_NVP(mMirrored)

		/**The joint anchor position on the morphogene branching into.*/
		& BOOST_SERIALIZATION_NVP(mJointAnchorX)
		& BOOST_SERIALIZATION_NVP(mJointAnchorY)
		& BOOST_SERIALIZATION_NVP(mJointAnchorZ)

		/**The joint anchor orientation on the morphogene branching into*/
		& BOOST_SERIALIZATION_NVP(mJointPitch)
		& BOOST_SERIALIZATION_NVP(mJointYaw)
		& BOOST_SERIALIZATION_NVP(mJointRoll)

		/**The joint limits in pitch direction*/
		& BOOST_SERIALIZATION_NVP(mJointPitchMinAngle)
		& BOOST_SERIALIZATION_NVP(mJointPitchMaxAngle)

		/**The joint limits in yaw direction*/
		& BOOST_SERIALIZATION_NVP(mJointYawMinAngle)
		& BOOST_SERIALIZATION_NVP(mJointYawMaxAngle)

		/**The joint limits in roll direction*/
		& BOOST_SERIALIZATION_NVP(mJointRollMinAngle)
		& BOOST_SERIALIZATION_NVP(mJointRollMaxAngle)

		/**The spring damping coefficients of the joint*/
		& BOOST_SERIALIZATION_NVP(mSpringPitchDampingCoefficient)
		& BOOST_SERIALIZATION_NVP(mSpringYawDampingCoefficient)
		& BOOST_SERIALIZATION_NVP(mSpringRollDampingCoefficient)

		/**The joint stiffness*/
		& BOOST_SERIALIZATION_NVP(mJointPitchStiffness)
		& BOOST_SERIALIZATION_NVP(mJointYawStiffness)
		& BOOST_SERIALIZATION_NVP(mJointRollStiffness)

		/**If the joint motors is enabled or not*/
		& BOOST_SERIALIZATION_NVP(mJointPitchMotorEnabled)
		& BOOST_SERIALIZATION_NVP(mJointYawMotorEnabled)
		& BOOST_SERIALIZATION_NVP(mJointRollMotorEnabled)

		/**The maximum joint forces*/
		& BOOST_SERIALIZATION_NVP(mJointMaxPitchForce)
		& BOOST_SERIALIZATION_NVP(mJointMaxYawForce)
		& BOOST_SERIALIZATION_NVP(mJointMaxRollForce)

		/**The maximum joint speeds*/
		& BOOST_SERIALIZATION_NVP(mJointMaxPitchSpeed)
		& BOOST_SERIALIZATION_NVP(mJointMaxYawSpeed)
		& BOOST_SERIALIZATION_NVP(mJointMaxRollSpeed);
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
