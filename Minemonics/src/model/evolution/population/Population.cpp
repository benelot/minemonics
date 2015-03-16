/*
 * Population.cpp
 *
 *  Created on: Mar 9, 2015
 *      Author: leviathan
 */


//# corresponding header
#include "Population.h"

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

//## view headers

//## utils headers
#include "utils/Randomness.h"
#include "configuration/MorphologyConfiguration.h"

Population::Population() :
		mCreatureQty(0) {

}

void Population::initialize(int creatureQty) {
	mCreatureQty = creatureQty;
	Randomness randomness;
	double bushiness = 0;
	for (int i = 0; i < mCreatureQty; i++) {
		bushiness = randomness.nextNormalDouble(
				MorphologyConfiguration::BODY_BRANCH_INITIAL_MEAN,
				MorphologyConfiguration::BODY_BRANCH_INITIAL_VAR);
		Creature creature;
		creature.initialize(bushiness);
		mCreatures.push_back(creature);
	}
}

Population::~Population() {
	// TODO Auto-generated destructor stub
}

void Population::addNewCreature(double bushiness) {
	Creature creature;
	creature.initialize(bushiness);
	mCreatures.push_back(creature);

}

bool Population::equals(const Population & population) const
{
	if(mCreatureQty != population.mCreatureQty)
	{
		return false;
	}

	std::vector<Creature>::const_iterator it = mCreatures.begin();
	std::vector<Creature>::const_iterator it2 =
			population.mCreatures.begin();
	for (; it != mCreatures.end(), it2 != population.mCreatures.end();
			it++, it2++) {
		if (!it->equals(*(it2))) {
			return false;
		}
	}

	return true;


}

