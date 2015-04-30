/*
 * PhenotypeGenerator.cpp
 *
 *  Created on: Mar 23, 2015
 *      Author: leviathan
 */

//# corresponding headers
#include <controller/evolution/genetics/PhenotypeGenerator.hpp>
#include <controller/evolution/population/creature/phenome/Component.hpp>
#include <model/evolution/population/creature/genome/GeneBranch.hpp>

//## view headers
//## utils headers

PhenotypeGenerator::PhenotypeGenerator() :
		mGene(0), mRoot2LeafPath(0), mParentComponent(0), mCurrentShrinkageFactor(
				1), mGeneBranch(0),mFlipped(false),mMirrored(false) {
	// TODO Auto-generated constructor stub

}

void PhenotypeGenerator::initialize(std::map<int,int>& repetitionList,
		Ogre::Vector3 position, Ogre::Quaternion orientation,
		Component* parentComponent, GeneBranch* geneBranch,
		double currentShrinkageFactor,bool flipped,bool mirrored) {
	mRepetitionList = repetitionList;
	mPosition = position;
	mOrientation = orientation;
	mParentComponent = parentComponent;
	mGeneBranch = geneBranch;
	mCurrentShrinkageFactor = currentShrinkageFactor;
	mFlipped = flipped;
	mMirrored = mirrored;
}

PhenotypeGenerator::~PhenotypeGenerator() {

}

