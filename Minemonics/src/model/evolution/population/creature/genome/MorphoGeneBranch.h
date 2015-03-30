/*
 * GeneBranch.h
 *
 *  Created on: Mar 9, 2015
 *      Author: leviathan
 */

#ifndef MODEL_EVOLUTION_POPULATION_CREATURE_GENOME_GENEBRANCH_H_
#define MODEL_EVOLUTION_POPULATION_CREATURE_GENOME_GENEBRANCH_H_

//# corresponding header

//# forward declarations
class MorphoGene;

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

class MorphoGeneBranch {
public:
	MorphoGeneBranch();
	virtual ~MorphoGeneBranch();

	void initialize();

	bool equals(const MorphoGeneBranch& geneBranch) const;

	/**
	 * Give access to boost serialization
	 */
	friend class boost::serialization::access;

	/**
	 * Serializes the gene branch to a string.
	 * @param os The ostream.
	 * @param geneBranch The creature we want to serialize.
	 * @return A string containing all information about the gene branch.
	 */
	friend std::ostream & operator<<(std::ostream &os,
			const MorphoGeneBranch &geneBranch) {
		return os << "GeneBranch: isActive=" << geneBranch.mActive
				<< "/GeneType=" << geneBranch.mBranchGeneType << "/isFlipped="
				<< geneBranch.mFlipped << "/isMirrored=" << geneBranch.mMirrored
				<< "/Joint Anchor:(" << geneBranch.mJointAnchorX << ","
				<< geneBranch.mJointAnchorY << "," << geneBranch.mJointAnchorZ
				<< ")" << "/Joint Rotation:(" << geneBranch.mJointPitch << ","
				<< geneBranch.mJointYaw << "," << geneBranch.mJointRoll << ")"
				<< "/Joint Limits (Min/Max)[Pitch:"
				<< geneBranch.mJointPitchMinAngle << "/"
				<< geneBranch.mJointPitchMaxAngle << "][Yaw:"
				<< geneBranch.mJointYawMinAngle << "/"
				<< geneBranch.mJointYawMaxAngle << "][Roll:"
				<< geneBranch.mJointRollMinAngle << "/"
				<< geneBranch.mJointRollMaxAngle;
	}

	/**
	 * Serializes the gene branch to an xml file.
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
BOOST_CLASS_VERSION(MorphoGeneBranch, 1)

#endif /* MODEL_EVOLUTION_POPULATION_CREATURE_GENOME_GENEBRANCH_H_ */
