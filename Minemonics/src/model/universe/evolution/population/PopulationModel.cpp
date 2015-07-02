//# corresponding headers
//# forward declarations
//# system headers
#include <stddef.h>

//## controller headers
//## model headers
//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
#include <model/universe/evolution/population/PopulationModel.hpp>

//## view headers
//## utils headers

PopulationModel::PopulationModel() :
		mCreatureQty(0), mCurrentCreatureIndex(0), mPlanetModel(NULL) {

}

PopulationModel::~PopulationModel() {
	while (!mCreatureModels.empty()) {
		CreatureModel* f = mCreatureModels.back();
		mCreatureModels.pop_back();
		delete f;
	}
}

/**
 * Initializes the population and adds creatures up to the creatureQty. Each creature gets a bushiness value around an predefined mean with a predefined variance.
 * @param creatureQty The number of creatures that the population will consist of in every generation.
 */
void PopulationModel::initialize(PlanetModel* planetModel, int creatureQty) {
	mPlanetModel = planetModel;
	mCreatureQty = creatureQty;
}

/**
 * Adds a new creature to the population with the bushiness as a input.
 * @param bushiness The bushiness determines the number of gene branches a gene has in this creature's genome.
 */
void PopulationModel::addMember(CreatureModel* creatureModel) {
	mCreatureModels.push_back(creatureModel);
	mCreatureQty++;

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

	std::vector<CreatureModel*>::const_iterator it = mCreatureModels.begin();
	std::vector<CreatureModel*>::const_iterator it2 =
			population.getCreatureModels().begin();
	for (;
			it != mCreatureModels.end(), it2
					!= population.getCreatureModels().end(); it++, it2++) {
		if (!(*it)->equals(**it2)) {
			return false;
		}
	}

	return true;

}

