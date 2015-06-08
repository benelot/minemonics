#ifndef MODEL_EVOLUTION_POPULATION_CREATURE_GENOME_MORPHOGENE_H_
#define MODEL_EVOLUTION_POPULATION_CREATURE_GENOME_MORPHOGENE_H_

//# corresponding headers
//# forward declarations
namespace boost {
namespace serialization {
class access;
} /* namespace serialization */
} /* namespace boost */

//# system headers
#include <stddef.h>
#include <iostream>
#include <iterator>
#include <vector>

//## controller headers
//## model headers
//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
#include <model/universe/evolution/population/creature/genome/controller/ControllerGene.hpp>
#include <model/universe/evolution/population/creature/genome/controller/SineControllerGene.hpp>
#include <model/universe/evolution/population/creature/genome/Gene.hpp>
#include <model/universe/evolution/population/creature/genome/morphology/MorphogeneBranch.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/limb/LimbModel.hpp>

//## view headers
//## utils headers

/**
 * @brief		Brief A gene is part of the complete genome of a creature. It encodes for a certain
 * part of it, be it a certain body part, sensor type, an actuator or a neural
 * network connection.
 * @details		Details
 * @date		2014-11-17
 * @author		Benjamin Ellenberger
 */
class Morphogene: public Gene {
public:
	Morphogene();
	virtual ~Morphogene();
	void initialize(double branchiness);

	virtual void mutate();

	virtual void grow(int branchiness);

	virtual Morphogene* clone();

	bool equals(const Morphogene& morphoGene) const;

	/**
	 * Give access to boost serialization
	 */
	friend class boost::serialization::access;

	/**
	 * Serializes the morphogene to a string.
	 * @param os The ostream.
	 * @param morphogene The morphogene we want to serialize.
	 * @return A string containing all information about the morphogene.
	 */
	friend std::ostream & operator<<(std::ostream &os,
			const Morphogene &morphogene) {
		os << "Gene: Size(" << morphogene.mX << "," << morphogene.mY << ","
				<< morphogene.mZ << ")/Orientation=("
				<< morphogene.mOrientationX << "," << morphogene.mOrientationY
				<< "," << morphogene.mOrientationZ << ","
				<< morphogene.mOrientationW << ")/ShrinkFactor="
				<< morphogene.mSegmentShrinkFactor << "/RepetitionLimit"
				<< morphogene.mRepetitionLimit << "/FollowUpGene="
				<< morphogene.mFollowUpGene << "/Color(" << morphogene.mColorR
				<< "," << morphogene.mColorG << "," << morphogene.mColorB
				<< "/PrimitiveType" << morphogene.mPrimitiveType
				<< "/ControllerGene=" << morphogene.mControllerGene
				<< "/Joint Anchor:(" << morphogene.mJointAnchorX << ","
				<< morphogene.mJointAnchorY << "," << morphogene.mJointAnchorZ
				<< ")" << "/Joint Rotation:(" << morphogene.mJointPitch << ","
				<< morphogene.mJointYaw << "," << morphogene.mJointRoll
				<< ")/Gene Branches=";
		std::vector<MorphogeneBranch*>::const_iterator it;
		for (it = morphogene.mGeneBranches.begin();
				it != morphogene.mGeneBranches.end(); it++) {
			os << (**it);
		}
		return os;
	}

	/**
	 * Serializes the morphogene to an xml file.
	 * @param ar The archive.
	 * @param The file version.
	 */
	template<class Archive>
	void serialize(Archive & ar, const unsigned int /* file_version */) {
		ar.register_type(static_cast<SineControllerGene*>(NULL));
		ar & BOOST_SERIALIZATION_NVP(mX)& BOOST_SERIALIZATION_NVP(mY)
		& BOOST_SERIALIZATION_NVP(mZ)
		& BOOST_SERIALIZATION_NVP(mOrientationX)
		& BOOST_SERIALIZATION_NVP(mOrientationY)
		& BOOST_SERIALIZATION_NVP(mOrientationZ)
		& BOOST_SERIALIZATION_NVP(mOrientationW)
		& BOOST_SERIALIZATION_NVP(mSegmentShrinkFactor)
		& BOOST_SERIALIZATION_NVP(mRepetitionLimit)
		& BOOST_SERIALIZATION_NVP(mFollowUpGene)
		& BOOST_SERIALIZATION_NVP(mColorR)
		& BOOST_SERIALIZATION_NVP(mColorG)
		& BOOST_SERIALIZATION_NVP(mColorB)
		& BOOST_SERIALIZATION_NVP(mPrimitiveType)
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

	void setControllerGene(ControllerGene* controllerGene) {
		mControllerGene = controllerGene;
	}

	const int getFollowUpGene() {
		return mFollowUpGene;
	}

	void setFollowUpGene(int followUpGene) {
		mFollowUpGene = followUpGene;
	}

	std::vector<MorphogeneBranch*>& getGeneBranches() {
		return mGeneBranches;
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

	LimbModel::PrimitiveType getPrimitiveType() const {
		return mPrimitiveType;
	}

	void setPrimitiveType(
			LimbModel::PrimitiveType primitiveType) {
		mPrimitiveType = primitiveType;
	}

	double getOrientationW() const {
		return mOrientationW;
	}

	void setOrientationW(double orientationW) {
		mOrientationW = orientationW;
	}

	double getOrientationX() const {
		return mOrientationX;
	}

	void setOrientationX(double orientationX) {
		mOrientationX = orientationX;
	}

	double getOrientationY() const {
		return mOrientationY;
	}

	void setOrientationY(double orientationY) {
		mOrientationY = orientationY;
	}

	double getOrientationZ() const {
		return mOrientationZ;
	}

	void setOrientationZ(double orientationZ) {
		mOrientationZ = orientationZ;
	}

	double getRestitution() const {
		return mRestitution;
	}

	void setRestitution(double restitution) {
		mRestitution = restitution;
	}

	double getFriction() const {
		return mFriction;
	}

	void setFriction(double friction) {
		mFriction = friction;
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
	int mFollowUpGene;

	/**
	 * Dimensions of the segment.
	 */
	double mX, mY, mZ;

	/**
	 * Orientation of the segment.
	 */
	double mOrientationX, mOrientationY, mOrientationZ, mOrientationW;

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
	 * Segment type
	 */
	LimbModel::PrimitiveType mPrimitiveType;

	/**
	 * A vector of genetic branches
	 */
	std::vector<MorphogeneBranch*> mGeneBranches;

	/**
	 * Colors red, green, blue
	 */
	double mColorR, mColorG, mColorB;

	/**
	 * Restitution is the amount of force that is reflected in a collision. It is similar to elasticity.
	 */
	double mRestitution;

	/**
	 * The friction of this segment.
	 */
	double mFriction;

	/**
	 * The controller of this gene
	 */
	ControllerGene* mControllerGene;
};
BOOST_CLASS_VERSION(Morphogene, 1)

#endif /* MODEL_EVOLUTION_POPULATION_CREATURE_GENOME_MORPHOGENEBRANCH_H_ */
