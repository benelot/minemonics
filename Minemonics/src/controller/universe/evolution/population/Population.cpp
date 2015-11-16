//# corresponding headers
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
#include <configuration/MorphologyConfiguration.hpp>

//## controller headers
#include <controller/universe/Planet.hpp>
#include <controller/universe/evolution/population/creature/Creature.hpp>
//#include <controller/universe/evolution/population/ragdoll/RagDoll.hpp>
//#include <controller/universe/evolution/population/snake/Snake.hpp>

//## model headers
#include <model/universe/evolution/population/PopulationModel.hpp>

//## view headers
//## utils headers
#include <utils/Randomness.hpp>

BoostLogger Population::mBoostLogger; /*<! initialize the boost logger*/
Population::_Init Population::_initializer;
Population::Population() :
	mPlanet(NULL) {
	mPopulationModel = new PopulationModel();

}
Population::Population(Planet* const planet, const int creatureQty) :
	mPlanet(planet) {
	mPopulationModel = new PopulationModel(planet->getPlanetModel(),
		creatureQty);

	initialize();
}

Population::Population(Planet* const planet, const int creatureQty,
	const Ogre::Vector3 initialPosition) :
	mPlanet(planet) {
	mPopulationModel = new PopulationModel(planet->getPlanetModel(),
		creatureQty, initialPosition);

	initialize();
}

Population::Population(PopulationModel* const populationModel) :
	mPlanet(NULL), mPopulationModel(populationModel) {
}

Population::~Population() {
	for (std::vector<Creature*>::iterator cit = mCreatures.begin();
		cit != mCreatures.end(); cit++) {
		delete (*cit);
	}
	mCreatures.clear();

	delete mPopulationModel;
	mPopulationModel = NULL;

	mPlanet = NULL;
}

void Population::initialize() {
	//initialize the population model with zero creatures.
	mPopulationModel->initialize();
	resyncWithModel();
}

/**
 * Adds a new creature to the population with the bushiness as a input.
 * @param branchiness The branchiness determines the number of gene branches a gene has in this creature's genome.
 */
void Population::addNewMember(const double branchiness,
	const Ogre::Vector3 rootPosition) {
	//add new creature
//	Creature* creature = new Snake(this,15,OgreBulletUtils::convert(rootPosition));
//	Creature* creature = new RagDoll(this,10,OgreBulletUtils::convert(rootPosition));
	Creature* creature = new Creature(this, mPlanet->getPhysicsModelType(),
		rootPosition, branchiness);
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
			BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info) << "Creature culled.";
			Creature* creature = *cit;
			delete creature->getCreatureModel();
			delete creature;
			cit = mCreatures.erase(cit);
		} else {
			cit++;
		}
	}

	//add new creatures that were newly born.
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
		cit != mCreatures.end(); cit++) {
		(*cit)->setCulled(true);
	}
}

void Population::calm() {
	for (std::vector<Creature*>::iterator cit = mCreatures.begin();
		cit != mCreatures.end(); cit++) {
		(*cit)->calm();
	}
}

bool Population::isOutOfSync() const {
	return mPopulationModel->isOutOfSync();
}

void Population::setOutOfSync(const bool outOfSync) {
	mPopulationModel->setOutOfSync(outOfSync);
}

void Population::setSerializationPath(std::string path) {
	mPopulationModel->setSerializationPath(path);
}

const std::string Population::getSerializationPath() const {
	return mPopulationModel->getSerializationPath();
}

const int Population::getCurrentGeneration() const {
	return mPopulationModel->getCurrentGeneration();
}

void Population::save() {
	mPopulationModel->save();
}

void Population::load() {
	mPopulationModel->load();
	initialize();
}

const std::string Population::getGenerationSerializationPath() {
	return mPopulationModel->getGenerationSerializationPath();
}

void Population::clearJuries() {
	mPopulationModel->clearJuries();
}
