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
	PhenotypeGenerator(const PhenotypeGenerator& phenotypeGenerator);

	virtual ~PhenotypeGenerator();

	void initialize(std::map<int, int>& repetitionList, const Ogre::Vector3 position,
			const Ogre::Quaternion orientation, ComponentModel* const parentComponentModel,
			GeneBranch* const geneBranch, const double currentShrinkageFactor,
			const bool flipped = false, const bool mirrored = false);

	/**
	 * Clone the phenotype generator.
	 * @return The clone of the phenotype generator.
	 */
	virtual PhenotypeGenerator* clone();

	//Accessor methods
	int getRoot2LeafPath() const {
		return mRoot2LeafPath;
	}

	void setRoot2LeafPath(const int root2LeafPath) {
		mRoot2LeafPath = root2LeafPath;
	}

	std::map<int, int>& getRepetitionList() {
		return mRepetitionList;
	}

	ComponentModel* const getParentComponentModel() const {
		return mParentComponentModel;
	}

	void setParentComponentModel(ComponentModel* const parentComponentModel) {
		mParentComponentModel = parentComponentModel;
	}

	Ogre::Vector3 getPosition() const {
		return mPosition;
	}

	void setPosition(const Ogre::Vector3 position) {
		mPosition = position;
	}

	Ogre::Quaternion getOrientation() const {
		return mOrientation;
	}

	void setOrientation(const Ogre::Quaternion orientation) {
		mOrientation = orientation;
	}

	GeneBranch* const getGeneBranch() const {
		return mGeneBranch;
	}

	void setGeneBranch(GeneBranch* const geneBranch) {
		mGeneBranch = geneBranch;
	}

	double getCurrentShrinkageFactor() const {
		return mCurrentShrinkageFactor;
	}

	void setCurrentShrinkageFactor(const double currentShrinkageFactor) {
		mCurrentShrinkageFactor = currentShrinkageFactor;
	}

	bool isFlipped() const {
		return mFlipped;
	}

	bool isMirrored() const {
		return mMirrored;
	}

private:

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
