//# corresponding headers
#include <model/universe/evolution/population/creature/genome/morphology/Morphogene.hpp>

//# forward declarations
//# system headers
#include <iostream>

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
#include <model/universe/evolution/population/creature/phenome/morphology/limb/LimbModel.hpp>

//## view headers
//## utils headers
#include <utils/Randomness.hpp>

Morphogene::Morphogene() :
		mColorR(0), mColorG(0), mColorB(0), mPrimitiveType(LimbModel::UNKNOWN), mControllerGene(
		NULL), mFollowUpGene(-1), mJointAnchorX(0), mJointAnchorY(0), mJointAnchorZ(
				0), mJointPitch(0), mJointYaw(0), mJointRoll(0), mSegmentShrinkFactor(
				0), mRepetitionLimit(0), mX(0), mY(0), mZ(0), mOrientationW(1), mOrientationX(
				0), mOrientationY(0), mOrientationZ(0), mRestitution(1), mFriction(
				0.8) {

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

void Morphogene::initialize(double branchiness) {
	mType = Gene::MorphoGene;

	Randomness randomness;
	//Choose the dimensions of the segment with a bias toward larger dimensions
	//TODO: Fix biased log
//	mX = randomness.nextBiasedLog(MorphologyConfiguration::LIMB_MIN_SIZE,
//			MorphologyConfiguration::LIMB_MAX_SIZE);
//	mY = randomness.nextBiasedLog(MorphologyConfiguration::LIMB_MIN_SIZE,
//			MorphologyConfiguration::LIMB_MAX_SIZE);
//	mZ = randomness.nextBiasedLog(MorphologyConfiguration::LIMB_MIN_SIZE,
//			MorphologyConfiguration::LIMB_MAX_SIZE);
	mX = randomness.nextDouble(MorphologyConfiguration::LIMB_MIN_SIZE,
			MorphologyConfiguration::LIMB_MAX_SIZE);
	mY = randomness.nextDouble(MorphologyConfiguration::LIMB_MIN_SIZE,
			MorphologyConfiguration::LIMB_MAX_SIZE);
	mZ = randomness.nextDouble(MorphologyConfiguration::LIMB_MIN_SIZE,
			MorphologyConfiguration::LIMB_MAX_SIZE);

	mSegmentShrinkFactor = 1.0
			+ randomness.nextDouble(MorphologyConfiguration::LIMB_SCALE_MIN,
					MorphologyConfiguration::LIMB_SCALE_MAX);

	/* Set joint anchor X, Y and Z, where the anchor lies in the center of mass
	 and the X, Y and Z form a vector, pointing to the point on the surface where
	 the joint will be attached. The vector contains three values between -1 and 1.
	 */
	do {
		mJointAnchorX = randomness.nextDouble(-1, 1);
		mJointAnchorY = randomness.nextDouble(-1, 1);
		mJointAnchorZ = randomness.nextDouble(-1, 1);
	} while (mJointAnchorX == 0 && mJointAnchorY == 0 && mJointAnchorZ == 0);

	/*
	 * The yaw, pitch and roll values representing a correction in angle of the joint anchor on the surface.
	 */
	mJointYaw = randomness.nextDouble(0,
			2 * boost::math::constants::pi<double>());
	mJointPitch = randomness.nextDouble(0,
			2 * boost::math::constants::pi<double>());
	mJointRoll = randomness.nextDouble(0,
			2 * boost::math::constants::pi<double>());

	// A random color RGB values between 0 and 1
	mColorR = randomness.nextDouble(0.0f, 1.0f);
	mColorG = randomness.nextDouble(0.0f, 1.0f);
	mColorB = randomness.nextDouble(0.0f, 1.0f);

	switch ((LimbModel::PrimitiveType) randomness.nextPosInt(1,
			LimbModel::NUM_PRIMITIVES)) {
	case LimbModel::BLOCK: {
		//Randomly choose a segment primitive
		mPrimitiveType = LimbModel::BLOCK;
		break;
	}
	case LimbModel::CAPSULE: {
		mPrimitiveType = LimbModel::CAPSULE;
		break;
	}
	}

	// The maximum repetition of this gene in a root-to-leaf path. This can change later to a higher number than the initial type repeats.
	mRepetitionLimit = randomness.nextPosInt(0,
			MorphologyConfiguration::LIMB_INITIAL_TYPE_REPEATS);

	//The follow up gene follows instead if this gene's repetition limit is reached.
	mFollowUpGene = -1;

	int branchQty = randomness.nextPosInt(0, branchiness);

	for (int i = 0; i < branchQty; i++) {
		MorphogeneBranch* branch = new MorphogeneBranch();
		branch->initialize();
		mGeneBranches.push_back(branch);
	}

	mControllerGene = new SineControllerGene();
	mControllerGene->initialize();
}

Morphogene* Morphogene::clone() {
	Morphogene* morphoGene = new Morphogene();
	morphoGene->setColorB(mColorB);
	morphoGene->setColorG(mColorG);
	morphoGene->setColorR(mColorR);

	morphoGene->setControllerGene(mControllerGene->clone());
	morphoGene->setFollowUpGene(mFollowUpGene);
	morphoGene->setType(mType);
	morphoGene->setJointAnchorX(mJointAnchorX);
	morphoGene->setJointAnchorY(mJointAnchorY);
	morphoGene->setJointAnchorZ(mJointAnchorZ);
	morphoGene->setJointPitch(mJointPitch);
	morphoGene->setJointRoll(mJointRoll);
	morphoGene->setJointYaw(mJointYaw);
	morphoGene->setOrientationW(mOrientationW);
	morphoGene->setOrientationX(mOrientationX);
	morphoGene->setOrientationY(mOrientationY);
	morphoGene->setOrientationZ(mOrientationZ);
	morphoGene->setPrimitiveType(mPrimitiveType);
	morphoGene->setRepetitionLimit(mRepetitionLimit);
	morphoGene->setSegmentShrinkFactor(mSegmentShrinkFactor);
	morphoGene->setX(mX);
	morphoGene->setY(mY);
	morphoGene->setZ(mZ);

	std::vector<MorphogeneBranch*>::iterator mgbit = mGeneBranches.begin();
	for (; mgbit != mGeneBranches.end(); mgbit++) {
		morphoGene->getGeneBranches().push_back((*mgbit)->clone());
	}

	return morphoGene;

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

	Randomness randomness;
	//TODO: Add reasonable numbers
	initialize(randomness.nextDouble(10, 30));
}

void Morphogene::grow(int branchiness) {
	Randomness randomness;

	int branchQty =
			(branchiness != 0) ? randomness.nextPosInt(0, branchiness) : 0;

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

bool Morphogene::equals(const Morphogene & morphoGene) const {

	if (mColorR != morphoGene.mColorR) {
		return false;
	}

	if (mColorG != morphoGene.mColorG) {
		return false;
	}

	if (mColorB != morphoGene.mColorB) {
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

	if (mFollowUpGene != morphoGene.mFollowUpGene) {
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

	if (mRepetitionLimit != morphoGene.mRepetitionLimit) {
		return false;
	}

	if (mSegmentShrinkFactor != morphoGene.mSegmentShrinkFactor) {
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

	return true;
}

