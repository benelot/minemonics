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

