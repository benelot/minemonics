#ifndef MODEL_EVOLUTION_POPULATION_CREATURE_GENOME_MORPHOGENE_H_
#define MODEL_EVOLUTION_POPULATION_CREATURE_GENOME_MORPHOGENE_H_

//# corresponding headers
#include <model/universe/evolution/population/creature/genome/Gene.hpp>

//# forward declarations
class ControllerGene;
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
#include <OgreVector3.h>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/version.hpp>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
#include <model/universe/evolution/population/creature/genome/controller/SineControllerGene.hpp>
#include <model/universe/evolution/population/creature/genome/morphology/MorphogeneBranch.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/limb/LimbPhysics.hpp>

//## view headers
//## utils headers
#include <utils/ogre3D/Euler.hpp>

/**
 * @brief A gene is part of the complete genome of a creature. It encodes for a certain
 * part of it, be it a certain body part, sensor type, an actuator or a neural
 * network connection.
 * @details		Details
 * @date		2014-11-17
 * @author		Benjamin Ellenberger
 */
class Morphogene: public Gene {
public:
	Morphogene(Ogre::Vector3 position, Ogre::Quaternion orientation,
		Ogre::Vector3 anchorDirection, Ogre::Euler anchorOrientation,
		LimbPhysics::PrimitiveType primitiveType, Ogre::ColourValue color,
		double friction, double restitution, bool intraBodyColliding);
	Morphogene();
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

	//Accessor methods

	double getColorB() const {
		return mColorB;
	}

	void setColorB(const double colorB) {
		mColorB = colorB;
	}

	double getColorG() const {
		return mColorG;
	}

	void setColorG(const double colorG) {
		mColorG = colorG;
	}

	double getColorR() const {
		return mColorR;
	}

	void setColorR(const double colorR) {
		mColorR = colorR;
	}

	ControllerGene* const getControllerGene() const {
		return mControllerGene;
	}

	void setControllerGene(ControllerGene* const controllerGene) {
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

	const std::vector<MorphogeneBranch*>& getGeneBranches() const {
		return mGeneBranches;
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

	int getRepetitionLimit() const {
		return mRepetitionLimit;
	}

	void setRepetitionLimit(const int repetitionLimit) {
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

	void setX(const double x) {
		mX = x;
	}

	double getY() const {
		return mY;
	}

	void setY(const double y) {
		mY = y;
	}

	double getZ() const {
		return mZ;
	}

	void setZ(const double z) {
		mZ = z;
	}

	LimbPhysics::PrimitiveType getPrimitiveType() const {
		return mPrimitiveType;
	}

	void setPrimitiveType(const LimbPhysics::PrimitiveType primitiveType) {
		mPrimitiveType = primitiveType;
	}

	double getOrientationW() const {
		return mOrientationW;
	}

	void setOrientationW(const double orientationW) {
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

	void setOrientationY(const double orientationY) {
		mOrientationY = orientationY;
	}

	double getOrientationZ() const {
		return mOrientationZ;
	}

	void setOrientationZ(const double orientationZ) {
		mOrientationZ = orientationZ;
	}

	double getRestitution() const {
		return mRestitution;
	}

	void setRestitution(const double restitution) {
		mRestitution = restitution;
	}

	double getFriction() const {
		return mFriction;
	}

	void setFriction(const double friction) {
		mFriction = friction;
	}

	//Serialization
	friend class boost::serialization::access; /**!< Give access to boost serialization */

	/**
	 * Serializes the morphogene to a string.
	 * @param os The ostream.
	 * @param morphogene The morphogene we want to serialize.
	 * @return A string containing all information about the morphogene.
	 */
	friend std::ostream & operator<<(std::ostream &os,
		const Morphogene &morphogene) {
		os << "Morphogene: " << "Size(" /**!< The size of the morphogene*/
		<< morphogene.mX << "," << morphogene.mY << "," << morphogene.mZ << ")"

		<< "/Orientation=(" /**!< The orientation of the morphogene*/
		<< morphogene.mOrientationX << "," << morphogene.mOrientationY << ","
			<< morphogene.mOrientationZ << "," << morphogene.mOrientationW
			<< ")"

			<< "/ShrinkFactor=" << morphogene.mSegmentShrinkFactor /**!< The shrink factor propagated along the branches of the morphogene*/

			<< "/RepetitionLimit" << morphogene.mRepetitionLimit /**!< The number of repetitions of this gene one after another.*/

			<< "/FollowUpGene=" << morphogene.mFollowUpGene /**!< The gene that follows this one after the repetitions.*/

			<< "/Color(" /**!< The color of this morphogene.*/
			<< morphogene.mColorR << "," << morphogene.mColorG << ","
			<< morphogene.mColorB

			<< "/PrimitiveType" << morphogene.mPrimitiveType /**!< The 3D primitive type of this morphogene.*/

			<< "/ControllerGene=" << morphogene.mControllerGene /**!< The controller gene of this morphogene's joint.*/

			<< "/Joint Anchor:(" /**!< The position of the joint anchor.*/
			<< morphogene.mJointAnchorX << "," << morphogene.mJointAnchorY
			<< "," << morphogene.mJointAnchorZ << ")"

			<< "/Joint Rotation:(" /**!< The orientation of the joint anchor.*/
			<< morphogene.mJointPitch << "," << morphogene.mJointYaw << ","
			<< morphogene.mJointRoll << ")"

			<< "/Restitution=" << morphogene.mRestitution /**!< The restitution of this morphogene*/

			<< "/Friction=" << morphogene.mFriction /**!< The friction of this morphogene.*/

			<< "/Gene Branches="; /**The gene branches of this gene*/
		for (std::vector<MorphogeneBranch*>::const_iterator it =
			morphogene.mGeneBranches.begin();
			it != morphogene.mGeneBranches.end(); it++) {
			os << (**it);
		}

		return os;
	}

	bool isIntraBodyColliding() const {
		return mIntraBodyColliding;
	}

	void setIntraBodyColliding(bool intraBodyColliding) {
		mIntraBodyColliding = intraBodyColliding;
	}

	/**
	 * Serializes the morphogene to an xml file.
	 * @param ar The archive.
	 * @param The file version.
	 */
	template<class Archive>
	void serialize(Archive & ar, const unsigned int /* file_version */) {
		//in order to detect a derived class type from a base type for serialization,
		//you have to register the derived class type in beforehand.
		ar.register_type(static_cast<SineControllerGene*>(NULL));
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Gene) /**!< Serialize the base object */
		& BOOST_SERIALIZATION_NVP(mX) /**!< The size of the morphogene*/
		& BOOST_SERIALIZATION_NVP(mY) & BOOST_SERIALIZATION_NVP(mZ)

		& BOOST_SERIALIZATION_NVP(mOrientationX) /**!< The orientation of the morphogene*/
		& BOOST_SERIALIZATION_NVP(mOrientationY)
		& BOOST_SERIALIZATION_NVP(mOrientationZ)
		& BOOST_SERIALIZATION_NVP(mOrientationW)

		& BOOST_SERIALIZATION_NVP(mIntraBodyColliding) /**!< If the limb will be colliding with others */
		& BOOST_SERIALIZATION_NVP(mSegmentShrinkFactor) /** !< The shrink factor propagated along the branches of the morphogene*/

		& BOOST_SERIALIZATION_NVP(mRepetitionLimit) /** !< The number of repetitions of this gene one after another.*/

		& BOOST_SERIALIZATION_NVP(mFollowUpGene) /** !< The gene that follows this one after the repetitions.*/

		& BOOST_SERIALIZATION_NVP(mColorR) /**!< The color of this morphogene.*/
		& BOOST_SERIALIZATION_NVP(mColorG)
		& BOOST_SERIALIZATION_NVP(mColorB)

		& BOOST_SERIALIZATION_NVP(mPrimitiveType) /**!< The 3D primitive type of this morphogene.*/

		& BOOST_SERIALIZATION_NVP(mControllerGene) /**!< The controller gene of this morphogene's joint.*/

		& BOOST_SERIALIZATION_NVP(mJointAnchorX) /**!< The position of the joint anchor.*/
		& BOOST_SERIALIZATION_NVP(mJointAnchorY)
		& BOOST_SERIALIZATION_NVP(mJointAnchorZ)

		& BOOST_SERIALIZATION_NVP(mJointPitch) /**!< The orientation of the joint anchor.*/
		& BOOST_SERIALIZATION_NVP(mJointYaw)
		& BOOST_SERIALIZATION_NVP(mJointRoll)

		& BOOST_SERIALIZATION_NVP(mRestitution) /**!< The restitution of the morphogene*/

		& BOOST_SERIALIZATION_NVP(mFriction) /**!< The friction of the morphogene*/

		& BOOST_SERIALIZATION_NVP(mGeneBranches); /**!< The gene branches of this gene*/
	}

private:
	double mX, mY, mZ; /**!< Dimensions of the segment.*/

	double mOrientationX, mOrientationY, mOrientationZ, mOrientationW; /**!< Orientation of the segment. */

	double mSegmentShrinkFactor; /**!< Segment shrink factor */

	int mRepetitionLimit; /**!< The limit of repetitions the gene can have in one root-to-leaf path. */

	int mFollowUpGene; /**!< The gene type with which the growth should continue after the repetition limit. If a segment of a given
	 * type specifies that the same type should continue when repeats are exhausted, growth
	 * will simply terminate at that point in the tree. Alternatively, if the type of segment
	 * chosen to continue when repeats are exhausted has already had its own type's repeats
	 * exhausted, this will also terminate growth.
	 */

	bool mIntraBodyColliding; /**!< If this limb collides with the other limbs. */

	double mColorR, mColorG, mColorB; /**!< Colors red, green, blue */

	LimbPhysics::PrimitiveType mPrimitiveType; /**!< Segment type */

	ControllerGene* mControllerGene; /**!< The controller of this gene */

	double mJointAnchorX, mJointAnchorY, mJointAnchorZ; /**!< Spherical coordinates around the origin of the segment at the center of mass. */

	double mJointPitch, mJointYaw, mJointRoll; /**!< Direction of joint anchoring on the surface of the segment */

	double mRestitution; /**!< Restitution is the amount of force that is reflected in a collision. It is similar to elasticity.*/

	double mFriction; /**!< The friction of this segment. */

	std::vector<MorphogeneBranch*> mGeneBranches; /**!< A vector of genetic branches */

};
BOOST_CLASS_VERSION(Morphogene, 1)

#endif /* MODEL_EVOLUTION_POPULATION_CREATURE_GENOME_MORPHOGENEBRANCH_H_ */
