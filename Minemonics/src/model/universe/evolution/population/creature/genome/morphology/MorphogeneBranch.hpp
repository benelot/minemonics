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
#include <OgreVector3.h>
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
#include <model/universe/evolution/population/creature/phenome/morphology/joint/JointPhysics.hpp>

//## view headers
//## utils headers
#include <utils/ogre3D/Euler.hpp>

/**
 * @brief		The morphogene branch defines how a certain morphogene class branches into another class.
 * @details		Details
 * @date		2015-03-09
 * @author		Benjamin Ellenberger
 */
class MorphogeneBranch: public GeneBranch {
public:
	MorphogeneBranch(Ogre::Vector3 anchorPosition,
		Ogre::Euler anchorOrientation, Ogre::Vector3 jointMinAngle,
		Ogre::Vector3 jointMaxAngle);
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

	void setSpringRollDampingCoefficient(
		const double springRollDampingCoefficient) {
		mSpringRollDampingCoefficient = springRollDampingCoefficient;
	}

	double getSpringYawDampingCoefficient() const {
		return mSpringYawDampingCoefficient;
	}

	void setSpringYawDampingCoefficient(
		const double springYawDampingCoefficient) {
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

	double getJointPitchFrequency() const {
		return mJointPitchFrequency;
	}

	double getJointRollFrequency() const {
		return mJointRollFrequency;
	}

	double getJointYawFrequency() const {
		return mJointYawFrequency;
	}

	double getJointPitchAmplitude() const {
		return mJointPitchAmplitude;
	}

	double getJointPitchYOffset() const {
		return mJointPitchYOffset;
	}

	double getJointRollAmplitude() const {
		return mJointRollAmplitude;
	}

	double getJointRollYOffset() const {
		return mJointRollYOffset;
	}

	double getJointYawAmplitude() const {
		return mJointYawAmplitude;
	}

	double getJointYawYOffset() const {
		return mJointYawYOffset;
	}

	double getJointPitchXOffset() const {
		return mJointPitchXOffset;
	}

	double getJointRollXOffset() const {
		return mJointRollXOffset;
	}

	double getJointYawXOffset() const {
		return mJointYawXOffset;
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

		<< "MorphogeneBranch: isActive=" << morphogeneBranch.mActive /**If the morphogene branch is active or not*/

		<< "/GeneType=" << morphogeneBranch.mBranchGeneType /**The type of gene the branch leads to*/

		<< "/isFlipped=" << morphogeneBranch.mFlipped /**If the morphogene branch is flipped on the morphogene to the other side.*/

		<< "/isMirrored=" << morphogeneBranch.mMirrored /**If the morphogene branch is mirrored on the morphogene.*/

		<< "/Joint Type=" << morphogeneBranch.mJointType /**< The joint type */
		<< "/Joint Anchor:(" /**The joint anchor position on the morphogene branching into.*/
		<< morphogeneBranch.mJointAnchorX << ","
			<< morphogeneBranch.mJointAnchorY << ","
			<< morphogeneBranch.mJointAnchorZ << ")"

			<< "/Joint Rotation:(" << morphogeneBranch.mJointPitch << "," /**The joint anchor orientation on the morphogene branching into*/
			<< morphogeneBranch.mJointYaw << "," << morphogeneBranch.mJointRoll
			<< ")"

			<< "/Joint Enabled:(" << morphogeneBranch.mJointPitchEnabled << "," /** If the joint Dof is enabled*/
			<< morphogeneBranch.mJointYawEnabled << ","
			<< morphogeneBranch.mJointRollEnabled << ")"

			<< "/Joint Limits (Min/Max)[Pitch:" /**The joint limits in all directions*/
			<< morphogeneBranch.mJointPitchMinAngle << "/"
			<< morphogeneBranch.mJointPitchMaxAngle << "][Yaw:"
			<< morphogeneBranch.mJointYawMinAngle << "/"
			<< morphogeneBranch.mJointYawMaxAngle << "][Roll:"
			<< morphogeneBranch.mJointRollMinAngle << "/"
			<< morphogeneBranch.mJointRollMaxAngle

			<< "/SpringDamping: [Pitch:" /**The spring damping coefficients of the joint*/
			<< morphogeneBranch.mSpringPitchDampingCoefficient << "][Yaw:"
			<< morphogeneBranch.mSpringYawDampingCoefficient << "][Roll:"
			<< morphogeneBranch.mSpringRollDampingCoefficient

			<< "/JointStiffness: [Pitch:" /**The joint stiffness*/
			<< morphogeneBranch.mJointPitchStiffness << "][Yaw:"
			<< morphogeneBranch.mJointYawStiffness << "][Roll:"
			<< morphogeneBranch.mJointRollStiffness

			<< "/JointMotorEnabled: [Pitch:" /**If the joint motors is enabled or not*/
			<< morphogeneBranch.mJointPitchMotorEnabled << "][Yaw:"
			<< morphogeneBranch.mJointYawMotorEnabled << "][Roll:"
			<< morphogeneBranch.mJointRollMotorEnabled

			<< "/JointMaxForce: [Pitch:" /**The maximum joint forces*/
			<< morphogeneBranch.mJointMaxPitchForce << "][Yaw:"
			<< morphogeneBranch.mJointMaxYawForce << "][Roll:"
			<< morphogeneBranch.mJointMaxRollForce

			<< "/JointMaxSpeed: [Pitch:" /**The maximum joint speeds*/
			<< morphogeneBranch.mJointMaxPitchSpeed << "][Yaw:"
			<< morphogeneBranch.mJointMaxYawSpeed << "][Roll:"
			<< morphogeneBranch.mJointMaxRollSpeed;
	}

	bool isJointPitchEnabled() const {
		return mJointPitchEnabled;
	}

	void setJointPitchEnabled(bool jointPitchEnabled) {
		mJointPitchEnabled = jointPitchEnabled;
	}

	bool isJointRollEnabled() const {
		return mJointRollEnabled;
	}

	void setJointRollEnabled(bool jointRollEnabled) {
		mJointRollEnabled = jointRollEnabled;
	}

	JointPhysics::JointType getJointType() const {
		return mJointType;
	}

	void setJointType(JointPhysics::JointType jointType) {
		mJointType = jointType;
	}

	bool isJointYawEnabled() const {
		return mJointYawEnabled;
	}

	void setJointYawEnabled(bool jointYawEnabled) {
		mJointYawEnabled = jointYawEnabled;
	}

	double getJointPitchAxisY() const {
		return mJointPitchAxisY;
	}

	void setJointPitchAxisY(double jointPitchAxisY) {
		mJointPitchAxisY = jointPitchAxisY;
	}

	double getJointPitchAxisX() const {
		return mJointPitchAxisX;
	}

	void setJointPitchAxisX(double jointPitchAxisX) {
		mJointPitchAxisX = jointPitchAxisX;
	}

	double getJointPitchAxisZ() const {
		return mJointPitchAxisZ;
	}

	void setJointPitchAxisZ(double jointPitchAxisZ) {
		mJointPitchAxisZ = jointPitchAxisZ;
	}

	/**
	 * Serializes the morphogene branch to an xml file.
	 * @param ar The archive.
	 * @param The file version.
	 */
	template<class Archive>
	void serialize(Archive & ar, const unsigned int /* file_version */) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(GeneBranch) /**!< Serialize the base object */

		& BOOST_SERIALIZATION_NVP(mFlipped) /**!< If the morphogene branch is flipped on the morphogene to the other side.*/

		& BOOST_SERIALIZATION_NVP(mMirrored) /**If the morphogene branch is mirrored on the morphogene.*/

		& BOOST_SERIALIZATION_NVP(mJointType) /**The joint type */
		& BOOST_SERIALIZATION_NVP(mJointAnchorX) /**The joint anchor position on the morphogene branching into.*/
		& BOOST_SERIALIZATION_NVP(mJointAnchorY)
			& BOOST_SERIALIZATION_NVP(mJointAnchorZ)

			& BOOST_SERIALIZATION_NVP(mJointPitch) /**!< Direction of joint anchoring on the surface of the segment */
			& BOOST_SERIALIZATION_NVP(mJointYaw)
			& BOOST_SERIALIZATION_NVP(mJointRoll)

			& BOOST_SERIALIZATION_NVP(mJointPitchAxisX) /**!< Direction of the joint pitch axis */
			& BOOST_SERIALIZATION_NVP(mJointPitchAxisY)
			& BOOST_SERIALIZATION_NVP(mJointPitchAxisZ)

			& BOOST_SERIALIZATION_NVP(mJointPitchEnabled) /**!< If the joint Dof is enabled.*/
			& BOOST_SERIALIZATION_NVP(mJointYawEnabled)
			& BOOST_SERIALIZATION_NVP(mJointRollEnabled)

			& BOOST_SERIALIZATION_NVP(mJointPitchMinAngle) /**!< The joint limits in pitch direction*/
			& BOOST_SERIALIZATION_NVP(mJointPitchMaxAngle)

			& BOOST_SERIALIZATION_NVP(mJointYawMinAngle) /**!< The joint limits in yaw direction*/
			& BOOST_SERIALIZATION_NVP(mJointYawMaxAngle)

			& BOOST_SERIALIZATION_NVP(mJointRollMinAngle) /**!< The joint limits in roll direction*/
			& BOOST_SERIALIZATION_NVP(mJointRollMaxAngle)

			& BOOST_SERIALIZATION_NVP(mSpringPitchDampingCoefficient) /**!< The spring damping coefficients of the joint*/
			& BOOST_SERIALIZATION_NVP(mSpringYawDampingCoefficient)
			& BOOST_SERIALIZATION_NVP(mSpringRollDampingCoefficient)

			& BOOST_SERIALIZATION_NVP(mJointPitchStiffness) /**!< The joint stiffness*/
			& BOOST_SERIALIZATION_NVP(mJointYawStiffness)
			& BOOST_SERIALIZATION_NVP(mJointRollStiffness)

			& BOOST_SERIALIZATION_NVP(mJointPitchMotorEnabled) /**!< If the joint motors is enabled or not*/
			& BOOST_SERIALIZATION_NVP(mJointYawMotorEnabled)
			& BOOST_SERIALIZATION_NVP(mJointRollMotorEnabled)

			& BOOST_SERIALIZATION_NVP(mJointMaxPitchForce) /**!< The maximum joint forces*/
			& BOOST_SERIALIZATION_NVP(mJointMaxYawForce)
			& BOOST_SERIALIZATION_NVP(mJointMaxRollForce)

			& BOOST_SERIALIZATION_NVP(mJointMaxPitchSpeed) /**!< The maximum joint speeds*/
			& BOOST_SERIALIZATION_NVP(mJointMaxYawSpeed)
			& BOOST_SERIALIZATION_NVP(mJointMaxRollSpeed)

			& BOOST_SERIALIZATION_NVP(mJointPitchFrequency) /**!< The joint frequency*/
			& BOOST_SERIALIZATION_NVP(mJointYawFrequency)
			& BOOST_SERIALIZATION_NVP(mJointRollFrequency)

			& BOOST_SERIALIZATION_NVP(mJointPitchAmplitude) /**!< The joint amplitude*/
			& BOOST_SERIALIZATION_NVP(mJointYawAmplitude)
			& BOOST_SERIALIZATION_NVP(mJointRollAmplitude)

			& BOOST_SERIALIZATION_NVP(mJointPitchXOffset) /**!< The joint x offset*/
			& BOOST_SERIALIZATION_NVP(mJointYawXOffset)
			& BOOST_SERIALIZATION_NVP(mJointRollXOffset)

			& BOOST_SERIALIZATION_NVP(mJointPitchYOffset) /**!< The joint y offset*/
			& BOOST_SERIALIZATION_NVP(mJointYawYOffset)
			& BOOST_SERIALIZATION_NVP(mJointRollYOffset)

			& BOOST_SERIALIZATION_NVP(mBranchGeneType); /**!< The type of gene the branch leads to*/

	}

private:
	bool mMirrored; /**!< Determines if this branch is mirrored through the center of mass of its segment. */

	bool mFlipped; /**!< Determines if this branch is mirrored along the axis defined by the parent gene branch of this branch. */

	double mJointAnchorX, mJointAnchorY, mJointAnchorZ; /**!< Spherical coordinates around the origin of the segment at the center of mass. */

	double mJointPitch, mJointYaw, mJointRoll; /**!< Direction of joint anchoring on the surface of the segment */

	bool mJointPitchEnabled, mJointYawEnabled, mJointRollEnabled; /**!< If the DoF is enabled or not. */

	JointPhysics::JointType mJointType; /**!< The type of joint */

	double mJointPitchAxisX, mJointPitchAxisY, mJointPitchAxisZ; /**!< The direction of the joint pitch axis */

	double mJointPitchMaxAngle, mJointYawMaxAngle, mJointRollMaxAngle; /**!< Joint limits for each degree of freedom */
	double mJointPitchMinAngle, mJointYawMinAngle, mJointRollMinAngle;

	double mSpringPitchDampingCoefficient, mSpringYawDampingCoefficient, /** !< The spring damping coefficient of the joint springs. */
	mSpringRollDampingCoefficient;

	double mJointPitchStiffness, mJointYawStiffness, mJointRollStiffness; /**!< The stiffness of the joint. */

	bool mJointPitchMotorEnabled, mJointYawMotorEnabled, mJointRollMotorEnabled; /**!< If the angular motor is enabled. */

	double mJointMaxPitchForce, mJointMaxYawForce, mJointMaxRollForce; /**!< The maximum force of the joint */

	double mJointMaxPitchSpeed, mJointMaxYawSpeed, mJointMaxRollSpeed; /**!< The maximum speed of the joint */

	double mJointPitchFrequency, mJointYawFrequency, mJointRollFrequency; /**!< The frequency at which the sine controller runs. */

	double mJointPitchAmplitude, mJointYawAmplitude, mJointRollAmplitude; /**!< The amplitude at which the sine controller runs. */

	double mJointPitchXOffset, mJointYawXOffset, mJointRollXOffset; /**!< The x offset at which the sine controller runs. */

	double mJointPitchYOffset, mJointYawYOffset, mJointRollYOffset; /**!< The y offset at which the sine controller runs. */

	int mBranchGeneType; /**!< The gene type it branches into. */
};
BOOST_CLASS_VERSION(MorphogeneBranch, 1)

#endif /* MODEL_EVOLUTION_POPULATION_CREATURE_GENOME_MORPHOGENEBRANCH_H_ */
