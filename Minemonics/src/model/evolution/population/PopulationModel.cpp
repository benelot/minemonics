/*
 * Population.cpp
 *
 *  Created on: Mar 9, 2015
 *      Author: leviathan
 */

//# corresponding header
#include <configuration/MorphologyConfiguration.hpp>
#include <model/evolution/population/PopulationModel.hpp>
#include <utils/Randomness.hpp>

PopulationModel::PopulationModel() :
		mCreatureQty(0) {

}

PopulationModel::~PopulationModel() {
	while (!mCreatures.empty()) {
		CreatureModel* f = mCreatures.back();
		mCreatures.pop_back();
		delete f;
	}
}

/**
 * Initializes the population and adds creatures up to the creatureQty. Each creature gets a bushiness value around an predefined mean with a predefined variance.
 * @param creatureQty The number of creatures that the population will consist of in every generation.
 */
void PopulationModel::initialize(int creatureQty) {
	mCreatureQty = creatureQty;
	Randomness randomness;
	double bushiness = 0;
	for (int i = 0; i < mCreatureQty; i++) {
		bushiness = randomness.nextNormalDouble(
				MorphologyConfiguration::BODY_BRANCH_INITIAL_MEAN,
				MorphologyConfiguration::BODY_BRANCH_INITIAL_VAR);
		CreatureModel* creature = new CreatureModel();
		//creature->initialize(bushiness);
		mCreatures.push_back(creature);
	}
}



/**
 * Adds a new creature to the population with the bushiness as a input.
 * @param bushiness The bushiness determines the number of gene branches a gene has in this creature's genome.
 */
void PopulationModel::addNewMember(double bushiness) {
	CreatureModel* creature = new CreatureModel();
	//creature->initialize(bushiness);
	mCreatures.push_back(creature);

}

/**
 * Tests if a population is equal to another population.
 * @param population The population to test for equality.
 * @return If this population and the other are equal.
 */
bool PopulationModel::equals(const PopulationModel & population) const {
	if (mCreatureQty != population.mCreatureQty) {
		return false;
	}

	std::vector<CreatureModel*>::const_iterator it = mCreatures.begin();
	std::vector<CreatureModel*>::const_iterator it2 = population.mCreatures.begin();
	for (; it != mCreatures.end(), it2 != population.mCreatures.end();
			it++, it2++) {
		if (!(*it)->equals(**it2)) {
			return false;
		}
	}

	return true;

}

