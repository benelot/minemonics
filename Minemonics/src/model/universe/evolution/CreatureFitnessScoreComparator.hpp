#ifndef MODEL_UNIVERSE_EVOLUTION_CREATUREFITNESSSCORECOMPARATOR_HPP_
#define MODEL_UNIVERSE_EVOLUTION_CREATUREFITNESSSCORECOMPARATOR_HPP_

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
 * @brief		The creature fitness score comparator compares two creature fitness scores values and returns, which one is higher/lower.
 * @details
 * @date		2015-08-12
 * @author		Benjamin Ellenberger
 */
class CreatureFitnessScoreComparator {
public:
	CreatureFitnessScoreComparator(bool higherIsBetter = true);
	virtual ~CreatureFitnessScoreComparator();

	/**
	 * Comparator for the creature sort function
	 * @param creature1 First creature.
	 * @param creature2 Second creature.
	 */
	static bool compareCreatureFitnessScore(CreatureModel* const creature1,
			CreatureModel* const creature2) {
		return (mHigherIsBetter) ?
				compareCreatureFitnessScoreAsc(creature1, creature2) :
				compareCreatureFitnessScoreDsc(creature1, creature2);
	}

	/**
	 * Comparator for the creature sort function
	 * @param creature1 First creature.
	 * @param creature2 Second creature.
	 */
	static bool compareCreatureFitnessScoreAsc(CreatureModel* const creature1,
			CreatureModel* const creature2) {
		// lesser means ascending/ greater means descending
		return (creature1->getFitnessScore() < creature2->getFitnessScore());
	}

	/**
	 * Comparator for the creature sort function
	 * @param creature1 First creature.
	 * @param creature2 Second creature.
	 */
	static bool compareCreatureFitnessScoreDsc(CreatureModel* const creature1,
			CreatureModel* const creature2) {
		// lesser means ascending/ greater means descending
		return !compareCreatureFitnessScoreAsc(creature1, creature2);
	}

private:
	static bool mHigherIsBetter;
};

#endif /* MODEL_UNIVERSE_EVOLUTION_CREATUREFITNESSSCORECOMPARATOR_HPP_ */
