//# corresponding headers
#include <model/universe/evolution/population/creature/genome/genetics/embryogenesis/PhenotypeGenerator.hpp>
#include <model/universe/evolution/population/creature/genome/GeneBranch.hpp>
#include <model/universe/evolution/population/creature/phenome/ComponentModel.hpp>

//## view headers
//## utils headers

PhenotypeGenerator::PhenotypeGenerator() :
		mGene(NULL), mRoot2LeafPath(0), mParentComponentModel(NULL), mCurrentShrinkageFactor(
				1), mGeneBranch(NULL),mFlipped(false),mMirrored(false) {
}


PhenotypeGenerator::~PhenotypeGenerator() {
	mGene = NULL;
	mGeneBranch = NULL;
	mParentComponentModel = NULL;
	mReferenceComponents.clear();
	mRepetitionList.clear();
}

void PhenotypeGenerator::initialize(std::map<int,int>& repetitionList,
		Ogre::Vector3 position, Ogre::Quaternion orientation,
		ComponentModel* parentComponentModel, GeneBranch* geneBranch,
		double currentShrinkageFactor,bool flipped,bool mirrored) {
	mRepetitionList = repetitionList;
	mPosition = position;
	mOrientation = orientation;
	mParentComponentModel = parentComponentModel;
	mGeneBranch = geneBranch;
	mCurrentShrinkageFactor = currentShrinkageFactor;
	mFlipped = flipped;
	mMirrored = mirrored;
}

PhenotypeGenerator::PhenotypeGenerator(
		const PhenotypeGenerator& phenotypeGenerator) {
	mCurrentShrinkageFactor = phenotypeGenerator.mCurrentShrinkageFactor;
	mFlipped = phenotypeGenerator.mFlipped;
	mGene = phenotypeGenerator.mGene;
	mGeneBranch = phenotypeGenerator.mGeneBranch;
	mMirrored = phenotypeGenerator.mMirrored;
	mOrientation = phenotypeGenerator.mOrientation;
	mParentComponentModel = phenotypeGenerator.mParentComponentModel;
	mPosition = phenotypeGenerator.mPosition;
	mReferenceComponents = phenotypeGenerator.mReferenceComponents;
	mRepetitionList = phenotypeGenerator.mRepetitionList;
	mRoot2LeafPath = phenotypeGenerator.mRoot2LeafPath;
}

PhenotypeGenerator* PhenotypeGenerator::clone() {
	return new PhenotypeGenerator(*this);
}
