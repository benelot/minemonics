//# corresponding headers
#include <configuration/MorphologyConfiguration.hpp>
#include <controller/universe/evolution/population/Population.hpp>

//# forward declarations
//# system headers
#include <stddef.h>
#include <iterator>
#include <vector>

//## controller headers
//## model headers
//## view headers
#include <OgreVector3.h>

//# custom headers
//## base headers
//## configuration headers
#include <controller/universe/Planet.hpp>
#include <controller/universe/evolution/population/creature/Creature.hpp>
#include <controller/universe/evolution/population/ragdoll/RagDoll.hpp>
#include <controller/universe/evolution/population/snake/Snake.hpp>

//## model headers
//## view headers
//## utils headers
#include <utils/Randomness.hpp>

BoostLogger Population::mBoostLogger; /*<! initialize the boost logger*/
Population::_Init Population::_initializer;
Population::Population() :
		mPlanet(NULL) {
	mPopulationModel = new PopulationModel();
}

Population::Population(PopulationModel* const populationModel) :
		mPlanet(NULL), mPopulationModel(populationModel) {
}

Population::~Population() {
	for (std::vector<Creature*>::iterator cit = mCreatures.begin();
			cit != mCreatures.end();) {
		Creature* creature = *cit;
		cit = mCreatures.erase(cit);
		delete creature;
	}
	mPlanet = NULL;
}

/**
 * Initializes the population and adds creatures up to the creatureQty. Each creature gets a bushiness value around an predefined mean with a predefined variance.
 * @param simulationManager The simulation manager handle
 * @param creatureQty The number of creatures that the population will consist of in every generation.
 */
void Population::initialize(Planet* const planet, const int creatureQty,
		const Ogre::Vector3 initialPosition) {
	mPlanet = planet;

	//initialize the population model with zero creatures.
	mPopulationModel->initialize(planet->getPlanetModel(), 0);

	// add creatures up to the creature quantity.
	double branchiness = 0;
	for (int i = 0; i < creatureQty; i++) {
		branchiness = Randomness::getSingleton()->nextNormalDouble(
				MorphologyConfiguration::BODY_BRANCH_INITIAL_MEAN,
				MorphologyConfiguration::BODY_BRANCH_INITIAL_VAR);
		addNewMember(branchiness, initialPosition);
	}
}

void Population::initialize(Planet* const planet, const int creatureQty) {
	mPlanet = planet;

	//initialize the population model with n creatures.
	mPopulationModel->initialize(planet->getPlanetModel(), creatureQty);
}

/**
 * Adds a new creature to the population with the bushiness as a input.
 * @param branchiness The branchiness determines the number of gene branches a gene has in this creature's genome.
 */
void Population::addNewMember(const double branchiness,
		const Ogre::Vector3 rootPosition) {
	//add new creature
	Creature* creature = new Snake(this,15,OgreBulletUtils::convert(rootPosition));
//	Creature* creature = new RagDoll(this,10,OgreBulletUtils::convert(rootPosition));
//	Creature* creature = new Creature(this, rootPosition, branchiness);
	addMember(creature);
}

void Population::addMember(Creature* const creature) {
	mCreatures.push_back(creature);

	//hand model down to the population model
	mPopulationModel->addMember(creature->getCreatureModel());
}

void Population::update(double timeSinceLastTick) {
	for (std::vector<Creature*>::iterator cit = mCreatures.begin();
			cit != mCreatures.end(); cit++) {
		(*cit)->update(timeSinceLastTick);
	}
}

void Population::reset() {
	for (std::vector<Creature*>::iterator cit = mCreatures.begin();
			cit != mCreatures.end(); cit++) {
		(*cit)->reset();
	}
}

int Population::addToPhysicsWorld() {
	int limbQty = 0;
	for (std::vector<Creature*>::iterator cit = mCreatures.begin();
			cit != mCreatures.end(); cit++) {
		limbQty = (*cit)->addToPhysicsWorld();
	}
	return limbQty;
}

int Population::addToWorld() {
	int limbQty = 0;
	for (std::vector<Creature*>::iterator cit = mCreatures.begin();
			cit != mCreatures.end(); cit++) {
		limbQty += (*cit)->addToWorld();
	}
	return limbQty;
}

void Population::removeFromWorld() {
	for (std::vector<Creature*>::iterator cit = mCreatures.begin();
			cit != mCreatures.end(); cit++) {
		(*cit)->removeFromWorld();
	}
}

void Population::resyncWithModel() {
	//remove the creatures that were culled
	for (std::vector<Creature*>::iterator cit = mCreatures.begin();
			cit != mCreatures.end();) {
		if ((*cit)->isCulled()) {
			BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Creature culled.";
			Creature* creature = *cit;
			delete creature;
			cit = mCreatures.erase(cit);
		} else {
			cit++;
		}
	}

	for (std::vector<CreatureModel*>::const_iterator cit =
			mPopulationModel->getCreatureModels().begin();
			cit != mPopulationModel->getCreatureModels().end(); cit++) {
		if ((*cit)->isNew()) {
			BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info) << "Creature added.";
			Creature* creature = new Creature(*cit);
			mCreatures.push_back(creature);
			(*cit)->setNew(false);
		}
	}

	mPopulationModel->setOutOfSync(false);
}

void Population::process() {
	for (std::vector<Creature*>::iterator cit = mCreatures.begin();
			cit != mCreatures.end(); cit++) {
		(*cit)->processJuries();
	}
}

bool Population::hasInterpenetrations() {
	return mPopulationModel->hasInterpenetrations();
}

void Population::markCull() {
	for (std::vector<Creature*>::iterator cit = mCreatures.begin();
			cit != mCreatures.end();cit++) {
		(*cit)->setCulled(true);
	}
}

void Population::calm() {
	for (std::vector<Creature*>::iterator cit = mCreatures.begin();
			cit != mCreatures.end();cit++) {
		(*cit)->calm();
	}
}
