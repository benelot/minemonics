#ifndef MODEL_UNIVERSE_EVOLUTION_CREATUREFITNESSCOMPARATOR_HPP_
#define MODEL_UNIVERSE_EVOLUTION_CREATUREFITNESSCOMPARATOR_HPP_

//# corresponding header
//# forward declarations
//# system headers
//## controller headers
//## model headers
//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
#include <model/universe/evolution/population/creature/CreatureModel.hpp>

//## view headers
//## utils headers

/**
 * @brief		The creature fitness comparator compares two creature fitness values and returns, which one is higher/lower.
 * @details
 * @date		2015-08-12
 * @author		Benjamin Ellenberger
 */
class CreatureFitnessComparator {
public:
	CreatureFitnessComparator(int criterium);
	virtual ~CreatureFitnessComparator();

	/**
	 * Comparator for the creature sort function
	 * @param creature1 First creature.
	 * @param creature2 Second creature.
	 */
	static bool compareCreatureFitness(CreatureModel* const creature1,
		CreatureModel* const creature2) {
		return
			(creature1->getJuries()[mCriterium]->isHigherBetter()) ?
				compareCreatureFitnessAsc(creature1, creature2) :
				compareCreatureFitnessDsc(creature1, creature2);
	}

	/**
	 * Comparator for the creature sort function
	 * @param creature1 First creature.
	 * @param creature2 Second creature.
	 */
	static bool compareCreatureFitnessAsc(CreatureModel* const creature1,
		CreatureModel* const creature2) {
		// lesser means descending/ greater means ascending
		return (creature1->getJuries()[mCriterium]->getFitness()
			> creature2->getJuries()[mCriterium]->getFitness());
	}

	/**
	 * Comparator for the creature sort function
	 * @param creature1 First creature.
	 * @param creature2 Second creature.
	 */
	static bool compareCreatureFitnessDsc(CreatureModel* const creature1,
		CreatureModel* const creature2) {
		// lesser means descending/ greater means ascending
		return (creature1->getJuries()[mCriterium]->getFitness()
			< creature2->getJuries()[mCriterium]->getFitness());
	}

	int getCriterium() const {
		return mCriterium;
	}

	void setCriterium(int criterium) {
		mCriterium = criterium;
	}

private:
	static int mCriterium; /**!< The criterium index */
};

#endif /* MODEL_UNIVERSE_EVOLUTION_CREATUREFITNESSCOMPARATOR_HPP_ */
