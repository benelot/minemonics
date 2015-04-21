/*
 * PhenotypeGenerator.h
 *
 *  Created on: Mar 23, 2015
 *      Author: leviathan
 */

#ifndef CONTROLLER_EVOLUTION_GENETICS_PHENOTYPEGENERATOR_H_
#define CONTROLLER_EVOLUTION_GENETICS_PHENOTYPEGENERATOR_H_

//# corresponding header
//#include "controller/evolution/genetics/BaseGenerator.h"

//# forward declarations
class GeneBranch;
class Component;

//# system headers
#include <map>

//## controller headers
//## model headers
#include <OgreVector3.h>
#include <OgreQuaternion.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
#include "model/evolution/population/creature/genome/Gene.h"

//## view headers
//## utils headers

class PhenotypeGenerator {
public:
	PhenotypeGenerator();
	virtual ~PhenotypeGenerator();

	void initialize(std::map<int,int>& repetitionList, Ogre::Vector3 position,
			Ogre::Quaternion orientation, Component* parentComponent,
			GeneBranch* geneBranch, double currentShrinkageFactor);

	Gene* getGene() {
		return mGene;
	}

	void setGene(Gene* gene) {
		this->mGene = gene;
	}

	int getRoot2LeafPath() const {
		return mRoot2LeafPath;
	}

	void setRoot2LeafPath(int root2LeafPath) {
		mRoot2LeafPath = root2LeafPath;
	}

	std::map<int,int>& getRepetitionList() {
		return mRepetitionList;
	}

	Component*& getParentComponent() {
		return mParentComponent;
	}

	void setParentComponent(Component*& parentComponent) {
		mParentComponent = parentComponent;
	}

	Ogre::Vector3& getPosition() {
		return mPosition;
	}

	void setPosition(Ogre::Vector3 position) {
		mPosition = position;
	}

	Ogre::Quaternion& getOrientation() {
		return mOrientation;
	}

	void setOrientation(Ogre::Quaternion orientation) {
		mOrientation = orientation;
	}

	GeneBranch*& getGeneBranch() {
		return mGeneBranch;
	}

	void setGeneBranch(GeneBranch*& geneBranch) {
		mGeneBranch = geneBranch;
	}

	double getCurrentShrinkageFactor() const {
		return mCurrentShrinkageFactor;
	}

	void setCurrentShrinkageFactor(double currentShrinkageFactor) {
		mCurrentShrinkageFactor = currentShrinkageFactor;
	}

private:
	Gene* mGene;
	int mRoot2LeafPath;
	std::map<int,int> mRepetitionList;
	Component* mParentComponent;
	GeneBranch* mGeneBranch;

	Ogre::Vector3 mPosition;
	Ogre::Quaternion mOrientation;

	double mCurrentShrinkageFactor;

	/**
	 * If a gene asks for a reference component, it gets the first out of the vector to connect to.
	 * Components are processed in a fifo type of list.
	 */
	std::list<Component*> mReferenceComponents;
};

#endif /* CONTROLLER_EVOLUTION_GENETICS_PHENOTYPEGENERATOR_H_ */
