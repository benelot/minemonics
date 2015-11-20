#ifndef MODEL_EVOLUTION_POPULATION_CREATURE_GENOME_MORPHOGENE_H_
#define MODEL_EVOLUTION_POPULATION_CREATURE_GENOME_MORPHOGENE_H_

//# corresponding headers
#include <model/universe/evolution/population/creature/genome/Gene.hpp>

//# forward declarations
namespace boost {
namespace serialization {
class access;
} /* namespace serialization */
} /* namespace boost */

//# system headers
#include <iostream>
#include <iterator>
#include <vector>

//## controller headers
//## model headers
#include <OgreQuaternion.h>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/version.hpp>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
#include <model/universe/evolution/population/creature/genome/morphology/MorphogeneBranch.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/limb/LimbPhysics.hpp>

//## view headers
//## utils headers

/**
 * @brief 		A gene is part of the complete genome of a creature.
 * @details		It encodes for a certain part of it, be it a certain body part,
 *  			sensor type, an actuator or a neural network connection.
 * @date		2014-11-17
 * @author		Benjamin Ellenberger
 */
class Morphogene: public Gene {
public:
	Morphogene();
	Morphogene(LimbPhysics::PrimitiveType primitiveType,
		Ogre::Vector3 dimensions, Ogre::Quaternion orientation, double restitution,
		double friction, bool intraBodyColliding, Ogre::ColourValue color,
		Ogre::Vector3 anchorDirection);
	Morphogene(const Morphogene& morphoGene);
	virtual ~Morphogene();

	/**
	 * Initialize the morphogene defined by the branchiness.
	 * @param branchiness The branchiness defines the number of branches sprouting out of it.
	 */
	void initialize(const double branchiness);

	/**
	 * Mutate the morphogene.
	 */
	virtual void mutate();

	/**
	 * Grow more branches out of the morphogene.
	 * @param branchiness The branchiness defines the number of branches sprouting out of it.
	 */
	virtual void grow(int branchiness);

	/**
	 * Clone the morphogene.
	 * @return The cloned morphogene.
	 */
	virtual Morphogene* clone();

	/**
	 * Compare morphogene with another morphogene.
	 * @param morphogene
	 * 			Another morphogene.
	 * @return if the morphogene is equal to the other morphogene.
	 */
	bool equals(const Morphogene& morphogene) const;

	// Accessor methods ##########################

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

	int getFollowUpGene() const {
		return mFollowUpGene;
	}

	void setFollowUpGene(int followUpGene) {
		mFollowUpGene = followUpGene;
	}

	double getFriction() const {
		return mFriction;
	}

	void setFriction(double friction) {
		mFriction = friction;
	}

	const std::vector<MorphogeneBranch*>& getGeneBranches() const {
		return mGeneBranches;
	}

	std::vector<MorphogeneBranch*>& getGeneBranches() {
		return mGeneBranches;
	}

	void setGeneBranches(const std::vector<MorphogeneBranch*>& geneBranches) {
		mGeneBranches = geneBranches;
	}

	bool isIntraBodyColliding() const {
		return mIntraBodyColliding;
	}

	void setIntraBodyColliding(bool intraBodyColliding) {
		mIntraBodyColliding = intraBodyColliding;
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

	LimbPhysics::PrimitiveType getPrimitiveType() const {
		return mPrimitiveType;
	}

	void setPrimitiveType(LimbPhysics::PrimitiveType primitiveType) {
		mPrimitiveType = primitiveType;
	}

	int getRepetitionLimit() const {
		return mRepetitionLimit;
	}

	void setRepetitionLimit(int repetitionLimit) {
		mRepetitionLimit = repetitionLimit;
	}

	double getRestitution() const {
		return mRestitution;
	}

	void setRestitution(double restitution) {
		mRestitution = restitution;
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

	// Serialization ##########################

	friend class boost::serialization::access; /**!< Give access to boost serialization */

	/**
	 * Serializes the morphogene to a string.
	 * @param os The ostream.
	 * @param morphogene The morphogene we want to serialize.
	 * @return A string containing all information about the morphogene.
	 */
	friend std::ostream & operator<<(std::ostream &os,
		const Morphogene &morphogene) {
		os << "Morphogene: " /**!< Name of the class*/
			<< static_cast<const Gene &>(morphogene)
		<< "/PrimitiveType" << morphogene.mPrimitiveType /**!< The 3D primitive type of this morphogene.*/
		<< "Size(" /**!< The size of the morphogene*/
		<< morphogene.mX << "," /**!< The size of the morphogene*/
		<< morphogene.mY << "," /**!< The size of the morphogene*/
		<< morphogene.mZ << ")" << "/Orientation=(" /**!< The orientation of the morphogene*/
		<< morphogene.mOrientationX << "," /**!< The orientation of the morphogene*/
		<< morphogene.mOrientationY << "," /**!< The orientation of the morphogene*/
		<< morphogene.mOrientationZ << "," /**!< The orientation of the morphogene*/
		<< morphogene.mOrientationW << ")" << "/Color(" /**!< The color of this morphogene.*/
		<< morphogene.mColorR << "," /**!< The color of this morphogene.*/
		<< morphogene.mColorG << "," /**!< The color of this morphogene.*/
		<< morphogene.mColorB << ")"

		<< "/Restitution=" << morphogene.mRestitution /**!< The restitution of this morphogene*/
		<< "/Friction=" << morphogene.mFriction /**!< The friction of this morphogene.*/
		<< "/IntraBodyCollision=" << morphogene.mIntraBodyColliding /**!< If the limb will be colliding with others */

		<< "/Joint Anchor:(" /**!< The position of the joint anchor.*/
		<< morphogene.mJointAnchorX << "," /**!< The position of the joint anchor.*/
		<< morphogene.mJointAnchorY << "," /**!< The position of the joint anchor.*/
		<< morphogene.mJointAnchorZ << ")"

		<< "/ShrinkFactor=" << morphogene.mSegmentShrinkFactor /**!< The shrink factor propagated along the branches of the morphogene*/
		<< "/RepetitionLimit" << morphogene.mRepetitionLimit /**!< The number of repetitions of this gene one after another.*/
		<< "/FollowUpGene=" << morphogene.mFollowUpGene /**!< The gene that follows this one after the repetitions.*/

		<< "/Gene Branches="; /**The gene branches of this gene*/
		for (std::vector<MorphogeneBranch*>::const_iterator it =
			morphogene.mGeneBranches.begin();
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
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Gene) /**!< Serialize the base object */
		& BOOST_SERIALIZATION_NVP(mPrimitiveType) /**!< The 3D primitive type of this morphogene.*/
		& BOOST_SERIALIZATION_NVP(mX) /**!< The size X of the morphogene*/
		& BOOST_SERIALIZATION_NVP(mY) /**!< The size Y of the morphogene*/
		& BOOST_SERIALIZATION_NVP(mZ) /**!< The size Z of the morphogene*/
		& BOOST_SERIALIZATION_NVP(mOrientationX) /**!< The orientation of the morphogene*/
		& BOOST_SERIALIZATION_NVP(mOrientationY)
		& BOOST_SERIALIZATION_NVP(mOrientationZ)
		& BOOST_SERIALIZATION_NVP(mOrientationW)
		& BOOST_SERIALIZATION_NVP(mRestitution) /**!< The restitution of the morphogene*/
		& BOOST_SERIALIZATION_NVP(mFriction) /**!< The friction of the morphogene*/
		& BOOST_SERIALIZATION_NVP(mIntraBodyColliding) /**!< If the limb will be colliding with others */
		& BOOST_SERIALIZATION_NVP(mColorR) /**!< The color of this morphogene.*/
		& BOOST_SERIALIZATION_NVP(mColorG)
		& BOOST_SERIALIZATION_NVP(mColorB)

		& BOOST_SERIALIZATION_NVP(mJointAnchorX) /**!< The position of the joint anchor.*/
		& BOOST_SERIALIZATION_NVP(mJointAnchorY)
		& BOOST_SERIALIZATION_NVP(mJointAnchorZ)

		& BOOST_SERIALIZATION_NVP(mSegmentShrinkFactor) /** !< The shrink factor propagated along the branches of the morphogene*/
		& BOOST_SERIALIZATION_NVP(mRepetitionLimit) /** !< The number of repetitions of this gene one after another.*/
		& BOOST_SERIALIZATION_NVP(mFollowUpGene) /** !< The gene that follows this one after the repetitions.*/
		& BOOST_SERIALIZATION_NVP(mGeneBranches); /**!< The gene branches of this gene*/
	}

private:
	/** Limb physical properties */
	LimbPhysics::PrimitiveType mPrimitiveType; /**!< Segment type */
	double mX, mY, mZ; /**!< Dimensions of the segment.*/
	double mOrientationX, mOrientationY, mOrientationZ, mOrientationW; /**!< Orientation of the segment. */
	double mRestitution; /**!< Restitution is the amount of force that is reflected in a collision. It is similar to elasticity.*/
	double mFriction; /**!< The friction of this segment. */
	bool mIntraBodyColliding; /**!< If this limb collides with the other limbs. */
	double mColorR, mColorG, mColorB; /**!< Colors red, green, blue */

	/** Joint physical properties */
	double mJointAnchorX, mJointAnchorY, mJointAnchorZ; /**!< Spherical coordinates around the origin of the segment at the center of mass. */

	/** Limb branching properties */
	double mSegmentShrinkFactor; /**!< Segment shrink factor */
	int mRepetitionLimit; /**!< The limit of repetitions the gene can have in one root-to-leaf path. */

	int mFollowUpGene; /**!< The gene type with which the growth should continue after the repetition limit. If a segment of a given
	 * type specifies that the same type should continue when repeats are exhausted, growth will simply terminate at that point in the
	 * tree. Alternatively, if the type of segment chosen to continue when repeats are exhausted has already had its own type's repeats
	 * exhausted, this will also terminate growth.
	 */

	std::vector<MorphogeneBranch*> mGeneBranches; /**!< A vector of genetic branches */

};
BOOST_CLASS_VERSION(Morphogene, 1)

#endif /* MODEL_EVOLUTION_POPULATION_CREATURE_GENOME_MORPHOGENEBRANCH_H_ */
