#ifndef MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_GENOME_GENETICS_EMBRYOGENESIS_PHENOTYPEGENERATOR_HPP_
#define MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_GENOME_GENETICS_EMBRYOGENESIS_PHENOTYPEGENERATOR_HPP_

//# corresponding header
#include <model/universe/evolution/population/creature/genome/genetics/embryogenesis/BaseGenerator.hpp>

//# forward declarations
class GeneBranch;
class ComponentModel;

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
#include <model/universe/evolution/population/creature/genome/Gene.hpp>

//## view headers
//## utils headers

/**
 * @brief		The phenotype generator helps to generate limbs.
 * @details		Details
 * @date		2015-03-23
 * @author		Benjamin Ellenberger
 */
class PhenotypeGenerator: public BaseGenerator {
public:
	PhenotypeGenerator();
	virtual ~PhenotypeGenerator();

	void initialize(std::map<int, int>& repetitionList, Ogre::Vector3 position,
			Ogre::Quaternion orientation, ComponentModel* parentComponentModel,
			GeneBranch* geneBranch, double currentShrinkageFactor,
			bool flipped = false, bool mirrored = false);

	//Accessor methods
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

	std::map<int, int>& getRepetitionList() {
		return mRepetitionList;
	}

	ComponentModel*& getParentComponentModel() {
		return mParentComponentModel;
	}

	void setParentComponentModel(ComponentModel*& parentComponentModel) {
		mParentComponentModel = parentComponentModel;
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

	bool isFlipped() const {
		return mFlipped;
	}

	bool isMirrored() const {
		return mMirrored;
	}

private:
	Gene* mGene;

	int mRoot2LeafPath;

	std::map<int, int> mRepetitionList;

	ComponentModel* mParentComponentModel;

	GeneBranch* mGeneBranch;

	Ogre::Vector3 mPosition;

	Ogre::Quaternion mOrientation;

	double mCurrentShrinkageFactor;

	bool mFlipped, mMirrored;

	/**
	 * If a gene asks for a reference component, it gets the first out of the vector to connect to.
	 * Components are processed in a fifo type of list.
	 */
	std::list<ComponentModel*> mReferenceComponents;
};

#endif /* MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_GENOME_GENETICS_EMBRYOGENESIS_PHENOTYPEGENERATOR_HPP_ */
