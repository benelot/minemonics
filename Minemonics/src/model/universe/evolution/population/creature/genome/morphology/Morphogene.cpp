//# corresponding header
#include <model/universe/evolution/population/creature/genome/morphology/Morphogene.hpp>

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
#include <model/universe/evolution/population/creature/genome/controller/ControllerGene.hpp>

//## view headers
//## utils headers
#include <utils/Randomness.hpp>

Morphogene::Morphogene(LimbPhysics::PrimitiveType primitiveType,
	Ogre::Vector3 dimensions, Ogre::Quaternion orientation, double restitution,
	double friction, bool intraBodyColliding, Ogre::ColourValue color,
	Ogre::Vector3 anchorDirection) :
	Gene(Gene::MorphoGene), mColorR(color.r), mColorG(color.g), mColorB(
		color.b), mPrimitiveType(primitiveType), mFollowUpGene(-1), mJointAnchorX(
		anchorDirection.x), mJointAnchorY(anchorDirection.y), mJointAnchorZ(
		anchorDirection.z), mSegmentShrinkFactor(1), mRepetitionLimit(0), mX(
		dimensions.x), mY(dimensions.y), mZ(dimensions.z), mOrientationW(
		orientation.w), mOrientationX(orientation.x), mOrientationY(
		orientation.y), mOrientationZ(orientation.z), mRestitution(restitution), mFriction(
		friction), mIntraBodyColliding(intraBodyColliding) {

	// limit min size
	if (dimensions.x < MorphologyConfiguration::LIMB_MIN_SIZE) {
		mX = MorphologyConfiguration::LIMB_MIN_SIZE;
	}

	// limit min size
	if (dimensions.y < MorphologyConfiguration::LIMB_MIN_SIZE) {
		mY = MorphologyConfiguration::LIMB_MIN_SIZE;
	}

	// limit min size
	if (dimensions.z < MorphologyConfiguration::LIMB_MIN_SIZE) {
		mZ = MorphologyConfiguration::LIMB_MIN_SIZE;
	}

}

Morphogene::Morphogene() :
	Gene(Gene::MorphoGene), mColorR(0), mColorG(0), mColorB(0), mPrimitiveType(
		LimbPhysics::UNKNOWN), mFollowUpGene(-1), mJointAnchorX(0), mJointAnchorY(
		0), mJointAnchorZ(0), mSegmentShrinkFactor(0), mRepetitionLimit(0), mX(
		0), mY(0), mZ(0), mOrientationW(1), mOrientationX(0), mOrientationY(0), mOrientationZ(
		0), mRestitution(0), mFriction(1), mIntraBodyColliding(true) {

}

Morphogene::Morphogene(const Morphogene& morphoGene) :
	Gene(Gene::MorphoGene) {
	mPrimitiveType = morphoGene.mPrimitiveType;
	mX = morphoGene.mX;
	mY = morphoGene.mY;
	mZ = morphoGene.mZ;
	mOrientationW = morphoGene.mOrientationW;
	mOrientationX = morphoGene.mOrientationX;
	mOrientationY = morphoGene.mOrientationY;
	mOrientationZ = morphoGene.mOrientationZ;
	mRestitution = morphoGene.mRestitution;
	mFriction = morphoGene.mFriction;
	mIntraBodyColliding = morphoGene.mIntraBodyColliding;
	mColorB = morphoGene.mColorB;
	mColorG = morphoGene.mColorG;
	mColorR = morphoGene.mColorR;

	mJointAnchorX = morphoGene.mJointAnchorX;
	mJointAnchorY = morphoGene.mJointAnchorY;
	mJointAnchorZ = morphoGene.mJointAnchorZ;

	mRepetitionLimit = morphoGene.mRepetitionLimit;
	mSegmentShrinkFactor = morphoGene.mSegmentShrinkFactor;
	mFollowUpGene = morphoGene.mFollowUpGene;

	for (std::vector<MorphogeneBranch*>::const_iterator mgbit =
		morphoGene.mGeneBranches.begin();
		mgbit != morphoGene.mGeneBranches.end(); mgbit++) {
		mGeneBranches.push_back((*mgbit)->clone());
	}
}

Morphogene::~Morphogene() {
	while (!mGeneBranches.empty()) {
		MorphogeneBranch* f = mGeneBranches.back();
		mGeneBranches.pop_back();
		delete f;
	}
}

void Morphogene::initialize(const double branchiness) {

	// A random primitive from the available primitives
	mPrimitiveType =
		(LimbPhysics::PrimitiveType) Randomness::getSingleton()->nextUnifPosInt(
			1, LimbPhysics::NUM_PRIMITIVES);

	//Choose the dimensions of the segment with a bias toward larger dimensions
	mX = Randomness::getSingleton()->nextBiasedLogDouble(
		MorphologyConfiguration::LIMB_MIN_SIZE,
		MorphologyConfiguration::LIMB_MAX_SIZE);
	mY = Randomness::getSingleton()->nextBiasedLogDouble(
		MorphologyConfiguration::LIMB_MIN_SIZE,
		MorphologyConfiguration::LIMB_MAX_SIZE);
	mZ = Randomness::getSingleton()->nextBiasedLogDouble(
		MorphologyConfiguration::LIMB_MIN_SIZE,
		MorphologyConfiguration::LIMB_MAX_SIZE);

	// Choose the orientation of the limb
	Ogre::Quaternion q = Randomness::getSingleton()->nextQuaternion();
	mOrientationW = q.w;
	mOrientationX = q.x;
	mOrientationY = q.y;
	mOrientationZ = q.z;

	mRestitution = MorphologyConfiguration::LIMB_INITIAL_RESTITUTION; /**!< Set the restitution */
	mFriction = MorphologyConfiguration::LIMB_INITIAL_FRICTION; /**!< Set the friction */

	mIntraBodyColliding =
		MorphologyConfiguration::BODY_INTRACOLLISION ?
			Randomness::getSingleton()->nextUnifBoolean() :
			MorphologyConfiguration::BODY_INTRACOLLISION;

	// A random color RGB values between 0 and 1
	mColorR = Randomness::getSingleton()->nextUnifDouble(0.0f, 1.0f);
	mColorG = Randomness::getSingleton()->nextUnifDouble(0.0f, 1.0f);
	mColorB = Randomness::getSingleton()->nextUnifDouble(0.0f, 1.0f);

	Ogre::Vector3 anchorVector = Randomness::getSingleton()->nextVector();
	anchorVector.normalise();
	mJointAnchorX = anchorVector.x; // Set joint anchor X, Y and Z, where the anchor lies in the center of mass
	mJointAnchorY = anchorVector.y; // and the X, Y and Z form a vector, pointing to the point on the surface where
	mJointAnchorZ = anchorVector.z; // the joint will be attached. The vector contains three values between -1 and 1.

	mSegmentShrinkFactor = 1.0
		+ Randomness::getSingleton()->nextUnifDouble(
			MorphologyConfiguration::LIMB_SCALE_MIN,
			MorphologyConfiguration::LIMB_SCALE_MAX);

	// The maximum repetition of this gene in a root-to-leaf path. This can change later to a higher number than the initial type repeats.
	mRepetitionLimit = Randomness::getSingleton()->nextUnifPosInt(0,
		MorphologyConfiguration::LIMB_INITIAL_TYPE_REPEATS);

	mFollowUpGene = 0; /**!< The follow up gene follows instead if this gene's repetition limit is reached. */

	int branchQty = Randomness::getSingleton()->nextUnifPosInt(0, branchiness); /**!< The number of branches to be added */
	for (int i = 0; i < branchQty; i++) {
		MorphogeneBranch* branch = new MorphogeneBranch();
		branch->initialize();
		mGeneBranches.push_back(branch);
	}
}

Morphogene* Morphogene::clone() {
	return new Morphogene(*this);
}

void Morphogene::mutate() {
	// A random primitive from the available primitives
	mPrimitiveType =
		(LimbPhysics::PrimitiveType) Randomness::getSingleton()->nextUnifPosInt(
			1, LimbPhysics::NUM_PRIMITIVES);

	//Choose the dimensions of the segment with a bias toward larger dimensions
	double m1 = Randomness::getSingleton()->nextBiasedLogDouble(
		MorphologyConfiguration::LIMB_MIN_SIZE,
		MorphologyConfiguration::LIMB_MAX_SIZE);

	double m2 = Randomness::getSingleton()->nextBiasedLogDouble(
		MorphologyConfiguration::LIMB_MIN_SIZE,
		MorphologyConfiguration::LIMB_MAX_SIZE);

	mX = (abs(mX - m1) < abs(mX - m2)) ? m1 : m2;

	m1 = Randomness::getSingleton()->nextBiasedLogDouble(
		MorphologyConfiguration::LIMB_MIN_SIZE,
		MorphologyConfiguration::LIMB_MAX_SIZE);

	m2 = Randomness::getSingleton()->nextBiasedLogDouble(
		MorphologyConfiguration::LIMB_MIN_SIZE,
		MorphologyConfiguration::LIMB_MAX_SIZE);

	mY = (abs(mY - m1) < abs(mY - m2)) ? m1 : m2;

	m1 = Randomness::getSingleton()->nextBiasedLogDouble(
		MorphologyConfiguration::LIMB_MIN_SIZE,
		MorphologyConfiguration::LIMB_MAX_SIZE);

	m2 = Randomness::getSingleton()->nextBiasedLogDouble(
		MorphologyConfiguration::LIMB_MIN_SIZE,
		MorphologyConfiguration::LIMB_MAX_SIZE);

	mZ = (abs(mZ - m1) < abs(mZ - m2)) ? m1 : m2;

	// Choose the orientation of the limb
	Ogre::Quaternion q1 = Randomness::getSingleton()->nextQuaternion();
	Ogre::Quaternion q2 = Randomness::getSingleton()->nextQuaternion();
	Ogre::Quaternion q3(
		(abs(mOrientationW - q1.w) < abs(mOrientationW - q2.w)) ? q1.w : q2.w,
		(abs(mOrientationX - q1.x) < abs(mOrientationX - q2.x)) ? q1.x : q2.x,
		(abs(mOrientationY - q1.y) < abs(mOrientationY - q2.y)) ? q1.y : q2.y,
		(abs(mOrientationZ - q1.z) < abs(mOrientationZ - q2.z)) ? q1.z : q2.z);
	q3.normalise();
	mOrientationW = q3.w;
	mOrientationX = q3.x;
	mOrientationY = q3.y;
	mOrientationZ = q3.z;

	mRestitution = MorphologyConfiguration::LIMB_INITIAL_RESTITUTION; /**!< Set the restitution */
	mFriction = MorphologyConfiguration::LIMB_INITIAL_FRICTION; /**!< Set the friction */

	mIntraBodyColliding =
		MorphologyConfiguration::BODY_INTRACOLLISION ?
			Randomness::getSingleton()->nextUnifBoolean() :
			MorphologyConfiguration::BODY_INTRACOLLISION;

	// A random color RGB values between 0 and 1
	mColorR = Randomness::getSingleton()->nextUnifDouble(0.0f, 1.0f);
	mColorG = Randomness::getSingleton()->nextUnifDouble(0.0f, 1.0f);
	mColorB = Randomness::getSingleton()->nextUnifDouble(0.0f, 1.0f);

	Ogre::Vector3 anchorVector1 = Randomness::getSingleton()->nextVector();
	Ogre::Vector3 anchorVector2 = Randomness::getSingleton()->nextVector();
	Ogre::Vector3 anchorVector(
		(abs(mJointAnchorX - anchorVector1.x)
			< abs(mJointAnchorX - anchorVector2.x)) ?
			anchorVector1.x : anchorVector2.x,
		(abs(mJointAnchorY - anchorVector1.y)
			< abs(mJointAnchorY - anchorVector2.y)) ?
			anchorVector1.y : anchorVector2.y,
		(abs(mJointAnchorZ - anchorVector1.z)
			< abs(mJointAnchorZ - anchorVector2.z)) ?
			anchorVector1.z : anchorVector2.z);
	anchorVector.normalise();

	mJointAnchorX = anchorVector.x; // Set joint anchor X, Y and Z, where the anchor lies in the center of mass
	mJointAnchorY = anchorVector.y; // and the X, Y and Z form a vector, pointing to the point on the surface where
	mJointAnchorZ = anchorVector.z; // the joint will be attached. The vector contains three values between -1 and 1.

	mSegmentShrinkFactor = 1.0
		+ Randomness::getSingleton()->nextUnifDouble(
			MorphologyConfiguration::LIMB_SCALE_MIN,
			MorphologyConfiguration::LIMB_SCALE_MAX);

	// The maximum repetition of this gene in a root-to-leaf path. This can change later to a higher number than the initial type repeats.
	mRepetitionLimit = Randomness::getSingleton()->nextUnifPosInt(0,
		MorphologyConfiguration::LIMB_INITIAL_TYPE_REPEATS);

	mFollowUpGene = 0; /**!< The follow up gene follows instead if this gene's repetition limit is reached. */
}

void Morphogene::grow(const int branchiness) {
	int branchQty = Randomness::getSingleton()->nextUnifPosInt(0, branchiness);

	for (int i = 0; i < branchQty; i++) {
		MorphogeneBranch* branch = new MorphogeneBranch();
		branch->initialize();
		mGeneBranches.push_back(branch);
	}
}

bool Morphogene::equals(const Morphogene& morphoGene) const {

	if (!Gene::equals(morphoGene)) {
		return false;
	}

	if (mPrimitiveType != morphoGene.mPrimitiveType) {
		return false;
	}

	if (mX != morphoGene.mX || mY != morphoGene.mY || mZ != morphoGene.mZ) {
		return false;
	}

	if (mOrientationW != morphoGene.mOrientationW
		|| mOrientationX != morphoGene.mOrientationX
		|| mOrientationY != morphoGene.mOrientationY
		|| mOrientationZ != morphoGene.mOrientationZ) {
		return false;
	}

	if (mRestitution != morphoGene.mRestitution) {
		return false;
	}

	if (mFriction != morphoGene.mFriction) {
		return false;
	}

	if (mIntraBodyColliding != morphoGene.mIntraBodyColliding) {
		return false;
	}

	if (mColorR != morphoGene.mColorR || mColorG != morphoGene.mColorG
		|| mColorB != morphoGene.mColorB) {
		return false;
	}

	if (mJointAnchorX != morphoGene.mJointAnchorX
		|| mJointAnchorY != morphoGene.mJointAnchorY
		|| mJointAnchorZ != morphoGene.mJointAnchorZ) {
		return false;
	}

	if (mSegmentShrinkFactor != morphoGene.mSegmentShrinkFactor) {
		return false;
	}

	if (mRepetitionLimit != morphoGene.mRepetitionLimit) {
		return false;
	}

	if (mFollowUpGene != morphoGene.mFollowUpGene) {
		return false;
	}

	if (mGeneBranches.size() != morphoGene.mGeneBranches.size()) { /**!< Compare morphogene branches */
		return false;
	}

	std::vector<MorphogeneBranch*>::const_iterator it3 = mGeneBranches.begin();
	std::vector<MorphogeneBranch*>::const_iterator it4 =
		morphoGene.mGeneBranches.begin();
	for (; it3 != mGeneBranches.end(), it4 != morphoGene.mGeneBranches.end();
		it3++, it4++) {
		if (!(*it3)->equals(**it4)) {
			return false;
		}
	}

	return true;
}

