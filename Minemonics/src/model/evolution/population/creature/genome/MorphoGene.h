/*
 * Gene.h
 *
 *  Created on: Nov 17, 2014
 *      Author: leviathan
 */

#ifndef GENE_H_
#define GENE_H_

/**
 * A gene is part of the complete genome of a creature. It encodes for a certain
 * part of it, be it a certain body part, sensor type, an actuator or a neuronal
 * network connection.
 *
 * @author leviathan
 *
 */

//# forward declarations
//# system headers
#include <fstream>
#include <vector>

//## controller headers

//## model headers
// include headers that implement a archive in xml format
#include <boost/archive/tmpdir.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/version.hpp>
//## view headers

//# custom headers
//## base headers

//## configuration headers

//## controller headers
#include "model/evolution/population/creature/genome/controller/ControllerGene.h"
#include "model/evolution/population/creature/genome/controller/SineControllerGene.h"

//## model headers
#include "model/evolution/population/creature/genome/MorphoGeneBranch.h"

//## view headers

//## utils headers

class MorphoGene {
public:
	MorphoGene();
	virtual ~MorphoGene();
	void initialize(double bushiness);

	bool equals(const MorphoGene& morphoGene) const;

	/**
	 * Give access to boost serialization
	 */
	friend class boost::serialization::access;

	/**
	 * Serializes the gene to a string.
	 * @param os The ostream.
	 * @param gene The gene we want to serialize.
	 * @return A string containing all information about the gene.
	 */
	friend std::ostream & operator<<(std::ostream &os, const MorphoGene &gene) {
		os << "Gene: Size(" << gene.mX << "," << gene.mY << ","
				<< gene.mZ << ")/ShrinkFactor=" << gene.mSegmentShrinkFactor
				<< "/RepetitionLimit" << gene.mRepetitionLimit
				<< "/FollowUpGene=" << gene.mFollowUpGene << "/Color("
				<< gene.mColorR << "," << gene.mColorG << "," << gene.mColorB
				<< "/ControllerGene=" << gene.mControllerGene
				<< "/Joint Anchor:(" << gene.mJointAnchorX << ","
				<< gene.mJointAnchorY << "," << gene.mJointAnchorZ << ")"
				<< "/Joint Rotation:(" << gene.mJointPitch << ","
				<< gene.mJointYaw << "," << gene.mJointRoll
				<< ")/Gene Branches:";
		std::vector<MorphoGeneBranch>::const_iterator it;
		for (it = gene.mGeneBranches.begin(); it != gene.mGeneBranches.end();
				it++) {
			os << (*it);
		}
		return os;
	}

	/**
	 * Serializes the gene to an xml file.
	 * @param ar The archive.
	 * @param The file version.
	 */
	template<class Archive>
	void serialize(Archive & ar, const unsigned int /* file_version */) {
		ar.register_type(static_cast<SineControllerGene*>(NULL));
		ar & BOOST_SERIALIZATION_NVP(mX)& BOOST_SERIALIZATION_NVP(mY)
		& BOOST_SERIALIZATION_NVP(mZ)
		& BOOST_SERIALIZATION_NVP(mSegmentShrinkFactor)
		& BOOST_SERIALIZATION_NVP(mRepetitionLimit)
		& BOOST_SERIALIZATION_NVP(mFollowUpGene)
		& BOOST_SERIALIZATION_NVP(mColorR)
		& BOOST_SERIALIZATION_NVP(mColorG)
		& BOOST_SERIALIZATION_NVP(mColorB)
		& BOOST_SERIALIZATION_NVP(mControllerGene)
		& BOOST_SERIALIZATION_NVP(mJointAnchorX)
		& BOOST_SERIALIZATION_NVP(mJointAnchorY)
		& BOOST_SERIALIZATION_NVP(mJointAnchorZ)
		& BOOST_SERIALIZATION_NVP(mJointPitch)
		& BOOST_SERIALIZATION_NVP(mJointYaw)
		& BOOST_SERIALIZATION_NVP(mJointRoll)
		& BOOST_SERIALIZATION_NVP(mGeneBranches);
	}

	virtual void print();

	//Accessor methods

	double getColorB() const {
		return mColorB;
	}

	void setColorB(double colorB) {
		mColorB = colorB;
	}

	double getColorG() const {
		return mColorG;
	}

	void setColorG(double colorG) {
		mColorG = colorG;
	}

	double getColorR() const {
		return mColorR;
	}

	void setColorR(double colorR) {
		mColorR = colorR;
	}

	const ControllerGene* getControllerGene() {
		return mControllerGene;
	}

	void setControllerGene(ControllerGene*& controllerGene) {
		mControllerGene = controllerGene;
	}

	const MorphoGene* getFollowUpGene() {
		return mFollowUpGene;
	}

	void setFollowUpGene(MorphoGene*& followUpGene) {
		mFollowUpGene = followUpGene;
	}

	const std::vector<MorphoGeneBranch>& getGeneBranches() {
		return mGeneBranches;
	}

	void setGeneBranches(const std::vector<MorphoGeneBranch>& geneBranches) {
		mGeneBranches = geneBranches;
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

	int getRepetitionLimit() const {
		return mRepetitionLimit;
	}

	void setRepetitionLimit(int repetitionLimit) {
		mRepetitionLimit = repetitionLimit;
	}

	double getSegmentShrinkFactor() const {
		return mSegmentShrinkFactor;
	}

	void setSegmentShrinkFactor(double segmentShrinkFactor) {
		mSegmentShrinkFactor = segmentShrinkFactor;
	}

	double getX() const {
		return mX;
	}

	void setX(double x) {
		mX = x;
	}

	double getY() const {
		return mY;
	}

	void setY(double y) {
		mY = y;
	}

	double getZ() const {
		return mZ;
	}

	void setZ(double z) {
		mZ = z;
	}

private:

	/**
	 * The limit of repetitions the gene can have in one root-to-leaf path.
	 */
	int mRepetitionLimit;

	/**
	 * The gene type with which the growth should continue after the repetition limit. If a segment of a given
	 * type specifies that the same type should continue when repeats are exhausted, growth
	 * will simply terminate at that point in the tree. Alternatively, if the type of segment
	 * chosen to continue when repeats are exhausted has already had its own type's repeats
	 * exhausted, this will also terminate growth.
	 */
	MorphoGene* mFollowUpGene;

	/**
	 * Dimensions of the segment.
	 */
	double mX, mY, mZ;

	/**
	 * Spherical coordinates around the origin of the segment at the center of mass.
	 */
	double mJointAnchorX, mJointAnchorY, mJointAnchorZ;

	/**
	 * Direction of joint anchoring on the surface of the segment
	 */
	double mJointPitch, mJointYaw, mJointRoll;

	/**
	 * Segment shrink factor
	 */

	double mSegmentShrinkFactor;

	/**
	 * A vector of genetic branches
	 */
	std::vector<MorphoGeneBranch> mGeneBranches;

	/**
	 * Colors red, green, blue
	 */
	double mColorR, mColorG, mColorB;

	/**
	 * The controller of this gene
	 */
	ControllerGene* mControllerGene;
};
BOOST_CLASS_VERSION(MorphoGene, 1)

#endif /* GENE_H_ */
