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

Morphogene::Morphogene(Ogre::Vector3 position, Ogre::Quaternion orientation,
	Ogre::Vector3 anchorDirection, Ogre::Euler anchorOrientation,
	LimbPhysics::PrimitiveType primitiveType, Ogre::ColourValue color,
	double friction, double restitution, bool intraBodyColliding) :
	mColorR(color.r), mColorG(color.g), mColorB(color.b), mPrimitiveType(
		primitiveType), mControllerGene(
	NULL), mFollowUpGene(-1), mJointAnchorX(anchorDirection.x), mJointAnchorY(
		anchorDirection.y), mJointAnchorZ(anchorDirection.z), mJointPitch(
		anchorOrientation.pitch().valueRadians()), mJointYaw(anchorOrientation.yaw().valueRadians()), mJointRoll(
		anchorOrientation.roll().valueRadians()), mSegmentShrinkFactor(1), mRepetitionLimit(0), mX(
		position.x), mY(position.y), mZ(position.z), mOrientationW(
		orientation.w), mOrientationX(orientation.x), mOrientationY(
		orientation.y), mOrientationZ(orientation.z), mRestitution(restitution), mFriction(
		friction), mIntraBodyColliding(intraBodyColliding) {

}

Morphogene::Morphogene() :
	mColorR(0), mColorG(0), mColorB(0), mPrimitiveType(LimbPhysics::UNKNOWN), mControllerGene(
	NULL), mFollowUpGene(-1), mJointAnchorX(0), mJointAnchorY(0), mJointAnchorZ(
		0), mJointPitch(0), mJointYaw(0), mJointRoll(0), mSegmentShrinkFactor(
		0), mRepetitionLimit(0), mX(0), mY(0), mZ(0), mOrientationW(1), mOrientationX(
		0), mOrientationY(0), mOrientationZ(0), mRestitution(0), mFriction(1), mIntraBodyColliding(
		true) {

}

Morphogene::Morphogene(const Morphogene& morphoGene) {
	mColorB = morphoGene.mColorB;
	mColorG = morphoGene.mColorG;
	mColorR = morphoGene.mColorR;

	mControllerGene = morphoGene.mControllerGene->clone();
	mFollowUpGene = morphoGene.mFollowUpGene;
	mType = morphoGene.mType;
	mJointAnchorX = morphoGene.mJointAnchorX;
	mJointAnchorY = morphoGene.mJointAnchorY;
	mJointAnchorZ = morphoGene.mJointAnchorZ;
	mJointPitch = morphoGene.mJointPitch;
	mJointRoll = morphoGene.mJointRoll;
	mJointYaw = morphoGene.mJointYaw;
	mOrientationW = morphoGene.mOrientationW;
	mOrientationX = morphoGene.mOrientationX;
	mOrientationY = morphoGene.mOrientationY;
	mOrientationZ = morphoGene.mOrientationZ;
	mPrimitiveType = morphoGene.mPrimitiveType;
	mRepetitionLimit = morphoGene.mRepetitionLimit;
	mSegmentShrinkFactor = morphoGene.mSegmentShrinkFactor;
	mX = morphoGene.mX;
	mY = morphoGene.mY;
	mZ = morphoGene.mZ;
	mFriction = morphoGene.mFriction;
	mRestitution = morphoGene.mRestitution;
	mIntraBodyColliding = morphoGene.mIntraBodyColliding;

	std::vector<MorphogeneBranch*>::const_iterator mgbit =
		morphoGene.mGeneBranches.begin();
	for (; mgbit != morphoGene.mGeneBranches.end(); mgbit++) {
		mGeneBranches.push_back((*mgbit)->clone());
	}
}

Morphogene::~Morphogene() {
	if (mControllerGene != NULL) {
		delete mControllerGene;
		mControllerGene = NULL;
	}

	while (!mGeneBranches.empty()) {
		MorphogeneBranch* f = mGeneBranches.back();
		mGeneBranches.pop_back();
		delete f;
	}
}

void Morphogene::initialize(const double branchiness) {
	mType = Gene::MorphoGene;

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

	mSegmentShrinkFactor = 1.0
		+ Randomness::getSingleton()->nextUnifDouble(
			MorphologyConfiguration::LIMB_SCALE_MIN,
			MorphologyConfiguration::LIMB_SCALE_MAX);

	mRestitution = MorphologyConfiguration::LIMB_INITIAL_RESTITUTION; /**!< Set the restitution */
	mFriction = MorphologyConfiguration::LIMB_INITIAL_FRICTION; /**!< Set the friction */

	Ogre::Vector3 anchorVector = Randomness::getSingleton()->nextVector();
	mJointAnchorX = anchorVector.x; // Set joint anchor X, Y and Z, where the anchor lies in the center of mass
	mJointAnchorY = anchorVector.y; // and the X, Y and Z form a vector, pointing to the point on the surface where
	mJointAnchorZ = anchorVector.z; // the joint will be attached. The vector contains three values between -1 and 1.

	//The yaw, pitch and roll values representing a correction in angle of the joint anchor on the surface.
	mJointYaw = Randomness::getSingleton()->nextUnifDouble(
		-boost::math::constants::pi<double>() / 2.0,
		boost::math::constants::pi<double>() / 2.0);
	mJointPitch = Randomness::getSingleton()->nextUnifDouble(
		-boost::math::constants::pi<double>() / 2.0,
		boost::math::constants::pi<double>() / 2.0);
	mJointRoll = Randomness::getSingleton()->nextUnifDouble(
		-boost::math::constants::pi<double>() / 2.0,
		boost::math::constants::pi<double>() / 2.0);

	// A random color RGB values between 0 and 1
	mColorR = Randomness::getSingleton()->nextUnifDouble(0.0f, 1.0f);
	mColorG = Randomness::getSingleton()->nextUnifDouble(0.0f, 1.0f);
	mColorB = Randomness::getSingleton()->nextUnifDouble(0.0f, 1.0f);

	// A random primitive from the available primitives
	mPrimitiveType =
		(LimbPhysics::PrimitiveType) Randomness::getSingleton()->nextUnifPosInt(
			1, LimbPhysics::NUM_PRIMITIVES);

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

	//TODO: How to change from one controller gene to another? Also make it react differently depending on the type of gene
	// create an instance of the sine controller gene for the morphogene.
	mControllerGene = new SineControllerGene();
	mControllerGene->initialize();

	Ogre::Quaternion q = Randomness::getSingleton()->nextQuaternion();
	mOrientationW = q.w;
	mOrientationX = q.x;
	mOrientationY = q.y;
	mOrientationZ = q.z;

	mIntraBodyColliding = Randomness::getSingleton()->nextUnifBoolean();
}

Morphogene* Morphogene::clone() {
	return new Morphogene(*this);
}

void Morphogene::mutate() {
	//clean up necessary
	if (mControllerGene != NULL) {
		delete mControllerGene;
		mControllerGene = NULL;
	}

	while (!mGeneBranches.empty()) {
		MorphogeneBranch* f = mGeneBranches.back();
		mGeneBranches.pop_back();
		delete f;
	}

	//TODO: Add reasonable numbers
	initialize(Randomness::getSingleton()->nextUnifDouble(10, 30));
}

void Morphogene::grow(const int branchiness) {
	int branchQty =
		(branchiness != 0) ?
			Randomness::getSingleton()->nextUnifPosInt(0, branchiness) : 0;

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

	if (mX != morphoGene.mX) {
		return false;
	}

	if (mY != morphoGene.mY) {
		return false;
	}

	if (mZ != morphoGene.mZ) {
		return false;
	}

	if (mOrientationW != morphoGene.mOrientationW) {
		return false;
	}

	if (mOrientationX != morphoGene.mOrientationX) {
		return false;
	}

	if (mOrientationY != morphoGene.mOrientationY) {
		return false;
	}

	if (mOrientationZ != morphoGene.mOrientationZ) {
		return false;
	}

	if (mIntraBodyColliding != morphoGene.mIntraBodyColliding) {
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

	if (mColorR != morphoGene.mColorR) {
		return false;
	}

	if (mColorG != morphoGene.mColorG) {
		return false;
	}

	if (mColorB != morphoGene.mColorB) {
		return false;
	}

	if (mPrimitiveType != morphoGene.mPrimitiveType) {
		return false;
	}

	if ((mControllerGene == NULL && morphoGene.mControllerGene != NULL)
		|| (mControllerGene != NULL && morphoGene.mControllerGene == NULL)) {
		return false;
	} else if (mControllerGene != NULL && morphoGene.mControllerGene != NULL
		&& mControllerGene->equals(*morphoGene.mControllerGene)) {
		switch (mControllerGene->getControllerGeneType()) {
		case ControllerGene::SineControllerGene:
			if (!((SineControllerGene*) mControllerGene)->equals(
				((SineControllerGene&) (*morphoGene.mControllerGene)))) {
				return false;
			}
			break;
		default:
			break;
		}
	}

	if (mJointAnchorX != morphoGene.mJointAnchorX) {
		return false;
	}

	if (mJointAnchorY != morphoGene.mJointAnchorY) {
		return false;
	}

	if (mJointAnchorZ != morphoGene.mJointAnchorZ) {
		return false;
	}

	if (mJointPitch != morphoGene.mJointPitch) {
		return false;
	}

	if (mJointYaw != morphoGene.mJointYaw) {
		return false;
	}

	if (mJointRoll != morphoGene.mJointRoll) {
		return false;
	}

	if (mRestitution != morphoGene.mRestitution) {
		return false;
	}

	if (mFriction != morphoGene.mFriction) {
		return false;
	}

	if (mGeneBranches.size() != morphoGene.mGeneBranches.size()) { /**!< Compare morphogene branches */
		return false;
	}

	std::vector<MorphogeneBranch*>::const_iterator it = mGeneBranches.begin();
	std::vector<MorphogeneBranch*>::const_iterator it2 =
		morphoGene.mGeneBranches.begin();
	for (; it != mGeneBranches.end(), it2 != morphoGene.mGeneBranches.end();
		it++, it2++) {
		if (!(*it)->equals(**it2)) {
			return false;
		}
	}

	return true;
}

