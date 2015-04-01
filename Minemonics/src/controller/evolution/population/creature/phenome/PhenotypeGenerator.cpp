/*
 * PhenotypeGenerator.cpp
 *
 *  Created on: Mar 23, 2015
 *      Author: leviathan
 */

//# corresponding header
#include "PhenotypeGenerator.h"

//# forward declarations
//# system headers
//## controller headers
//## model headers
//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
#include "controller/evolution/population/creature/phenome/Component.h"

//## model headers
#include "model/evolution/population/creature/genome/GeneBranch.h"

//## view headers
//## utils headers

PhenotypeGenerator::PhenotypeGenerator() :
		mGene(0), mRoot2LeafPath(0), mTotalQty(0), mParentComponent(0) {
	// TODO Auto-generated constructor stub

}

void PhenotypeGenerator::initialize(std::vector<int>& repetitionList,
		Ogre::Vector3 position, Ogre::Quaternion orientation, Component* parentComponent,GeneBranch* geneBranch) {
	mRepetitionList = repetitionList;
	mPosition = position;
	mOrientation = orientation;
	mParentComponent = parentComponent;
}

PhenotypeGenerator::~PhenotypeGenerator() {

}

