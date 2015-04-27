/*
 * GeneBranch.h
 *
 *  Created on: Mar 9, 2015
 *      Author: leviathan
 */

#ifndef MODEL_EVOLUTION_POPULATION_CREATURE_GENOME_MORPHOGENEBRANCH_H_
#define MODEL_EVOLUTION_POPULATION_CREATURE_GENOME_MORPHOGENEBRANCH_H_

//# corresponding header
#include "model/evolution/population/creature/genome/GeneBranch.h"

//# forward declarations
//# system headers
//## controller headers
//## model headers
// include headers that implement a archive in xml format
#include <boost/archive/tmpdir.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/version.hpp>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers

/**
 * @brief		Brief
 * @details		Details
 * @date		2015-04-27
 * @author		Benjamin Ellenberger
 */
class MorphogeneBranch: public GeneBranch {
public:
	MorphogeneBranch();
	virtual ~MorphogeneBranch();

	void initialize();

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
				<< morphogeneBranch.mJointRollMaxAngle;
	}

	/**
	 * Serializes the morphogene branch to an xml file.
	 * @param ar The archive.
	 * @param The file version.
	 */
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
						& BOOST_SERIALIZATION_NVP(mActuated);
	}

	// Accessor methods

	bool isActive() const {
		return mActive;
	}

	void setActive(bool active) {
		mActive = active;
	}

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

	bool isActuated() const {
		return mActuated;
	}

	void setActuated(bool actuated) {
		mActuated = actuated;
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

private:
	/**
	 * Determines if this branch is active.
	 */
	bool mActive;

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
	 * Actuated joint?
	 */
	bool mActuated;

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
