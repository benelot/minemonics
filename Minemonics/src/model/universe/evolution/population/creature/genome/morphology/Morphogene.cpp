//# corresponding header
//# forward declarations
//# system headers
//## controller headers
//## model headers
#include <boost/math/constants/constants.hpp>
#include <OgreQuaternion.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
#include <configuration/MorphologyConfiguration.hpp>

//## controller headers
//## model headers
#include <model/universe/evolution/population/creature/genome/morphology/Morphogene.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/limb/LimbPhysics.hpp>

//## view headers
//## utils headers
#include <utils/Randomness.hpp>

Morphogene::Morphogene() :
		mColorR(0), mColorG(0), mColorB(0), mPrimitiveType(
				LimbPhysics::UNKNOWN), mControllerGene(
		NULL), mFollowUpGene(-1), mJointAnchorX(0), mJointAnchorY(0), mJointAnchorZ(
				0), mJointPitch(0), mJointYaw(0), mJointRoll(0), mSegmentShrinkFactor(
				0), mRepetitionLimit(0), mX(0), mY(0), mZ(0), mOrientationW(1), mOrientationX(
				0), mOrientationY(0), mOrientationZ(0), mRestitution(0), mFriction(
				1) {

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
	//TODO: Fix biased log
//	mX = Randomness::getSingleton()->nextBiasedLog(MorphologyConfiguration::LIMB_MIN_SIZE,
//			MorphologyConfiguration::LIMB_MAX_SIZE);
//	mY = Randomness::getSingleton()->nextBiasedLog(MorphologyConfiguration::LIMB_MIN_SIZE,
//			MorphologyConfiguration::LIMB_MAX_SIZE);
//	mZ = Randomness::getSingleton()->nextBiasedLog(MorphologyConfiguration::LIMB_MIN_SIZE,
//			MorphologyConfiguration::LIMB_MAX_SIZE);
	mX = Randomness::getSingleton()->nextUnifDouble(
			MorphologyConfiguration::LIMB_MIN_SIZE,
			MorphologyConfiguration::LIMB_MAX_SIZE);
	mY = Randomness::getSingleton()->nextUnifDouble(
			MorphologyConfiguration::LIMB_MIN_SIZE,
			MorphologyConfiguration::LIMB_MAX_SIZE);
	mZ = Randomness::getSingleton()->nextUnifDouble(
			MorphologyConfiguration::LIMB_MIN_SIZE,
			MorphologyConfiguration::LIMB_MAX_SIZE);

	mSegmentShrinkFactor = 1.0
			+ Randomness::getSingleton()->nextUnifDouble(
					MorphologyConfiguration::LIMB_SCALE_MIN,
					MorphologyConfiguration::LIMB_SCALE_MAX);

	//set restitution and friction
	mRestitution = MorphologyConfiguration::LIMB_INITIAL_RESTITUTION;
	mFriction = MorphologyConfiguration::LIMB_INITIAL_FRICTION;

	/* Set joint anchor X, Y and Z, where the anchor lies in the center of mass
	 and the X, Y and Z form a vector, pointing to the point on the surface where
	 the joint will be attached. The vector contains three values between -1 and 1.
	 */
	do {
		mJointAnchorX = Randomness::getSingleton()->nextUnifDouble(-1, 1);
		mJointAnchorY = Randomness::getSingleton()->nextUnifDouble(-1, 1);
		mJointAnchorZ = Randomness::getSingleton()->nextUnifDouble(-1, 1);
	} while (mJointAnchorX == 0 && mJointAnchorY == 0 && mJointAnchorZ == 0);

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

	//The follow up gene follows instead if this gene's repetition limit is reached.
	mFollowUpGene = -1;

	int branchQty = Randomness::getSingleton()->nextUnifPosInt(0, branchiness);

	for (int i = 0; i < branchQty; i++) {
		MorphogeneBranch* branch = new MorphogeneBranch();
		branch->initialize();
		mGeneBranches.push_back(branch);
	}

	// create an instance of the sine controller gene for the morphogene.
	mControllerGene = new SineControllerGene();
	mControllerGene->initialize();

	Ogre::Quaternion q = Randomness::getSingleton()->nextQuaternion();
	mOrientationW = q.w;
	mOrientationX = q.x;
	mOrientationY = q.y;
	mOrientationZ = q.z;
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
					Randomness::getSingleton()->nextUnifPosInt(0, branchiness) :
					0;

	for (int i = 0; i < branchQty; i++) {
		MorphogeneBranch* branch = new MorphogeneBranch();
		branch->initialize();
		mGeneBranches.push_back(branch);
	}
}

void Morphogene::print() {
	// print the gene to the standard output
	std::cout << this;
}

bool Morphogene::equals(const Morphogene& morphoGene) const {

	if(!Gene::equals(morphoGene)){
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

	if(mRestitution != morphoGene.mRestitution){
		return false;
	}

	if(mFriction != morphoGene.mFriction){
		return false;
	}

	/**Compare morphogene branches */
	if (mGeneBranches.size() != morphoGene.mGeneBranches.size()) {
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

