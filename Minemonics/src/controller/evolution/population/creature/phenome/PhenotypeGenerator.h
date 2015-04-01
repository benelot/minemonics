/*
 * PhenotypeGenerator.h
 *
 *  Created on: Mar 23, 2015
 *      Author: leviathan
 */

#ifndef CONTROLLER_EVOLUTION_POPULATION_CREATURE_PHENOME_PHENOTYPEGENERATOR_H_
#define CONTROLLER_EVOLUTION_POPULATION_CREATURE_PHENOME_PHENOTYPEGENERATOR_H_

//# corresponding header
//# forward declarations
class GeneBranch;
class Component;

//# system headers
#include <vector>

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

	void initialize(std::vector<int>& repetitionList, Ogre::Vector3 position,
			Ogre::Quaternion orientation,Component* parentComponent,GeneBranch* geneBranch);

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

	int getTotalQty() const {
		return mTotalQty;
	}

	void setTotalQty(int totalQty) {
		mTotalQty = totalQty;
	}

	std::vector<int>& getRepetitionList() {
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

	void setPosition(Ogre::Vector3& position) {
		mPosition = position;
	}

	Ogre::Quaternion& getOrientation() {
		return mOrientation;
	}

	void setOrientation(Ogre::Quaternion& orientation) {
		mOrientation = orientation;
	}

private:
	Gene* mGene;
	int mRoot2LeafPath;
	int mTotalQty;
	std::vector<int> mRepetitionList;
	Component* mParentComponent;

	Ogre::Vector3 mPosition;
	Ogre::Quaternion mOrientation;

	/**
	 * If a gene asks for a reference component, it gets the first out of the vector to connect to.
	 * Components are processed in a fifo type of list.
	 */
	std::list<Component*> mReferenceComponents;
};

#endif /* CONTROLLER_EVOLUTION_POPULATION_CREATURE_PHENOME_PHENOTYPEGENERATOR_H_ */
