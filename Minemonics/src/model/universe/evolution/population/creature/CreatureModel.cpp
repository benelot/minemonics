//# corresponding headers
#include <model/universe/evolution/population/creature/CreatureModel.hpp>

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
#include <model/universe/evolution/juries/Jury.hpp>
#include <model/universe/evolution/population/PopulationModel.hpp>
#include <model/universe/environments/EnvironmentModel.hpp>
#include <model/universe/environments/physics/PhysicsController.hpp>
#include <model/universe/evolution/juries/IntegralAverageVelocity.hpp>
#include <model/universe/evolution/population/creature/phenome/FSPhenomeModel.hpp>
#include <model/universe/evolution/population/creature/phenome/SRBPhenomeModel.hpp>
#include <model/universe/PlanetModel.hpp>
#include <utils/NameGenerator.hpp>
#include <utils/Randomness.hpp>

BoostLogger CreatureModel::mBoostLogger; /*<! initialize the boost logger*/
CreatureModel::_Init CreatureModel::_initializer;
CreatureModel::CreatureModel() :
	mPopulationModel(NULL), mCulled(false), mNew(false), mFitnessScore(-1), mWorld(
	NULL), mPhenotypeModel(NULL), mFitnessScoreCalculated(false), mPhysicsModelType(
		PhysicsController::RigidbodyModel),mDynasty(0) {
}

CreatureModel::CreatureModel(PopulationModel* const populationModel,
	const PhysicsController::PhysicsModelType physicsModelType,
	const Ogre::Vector3 position, const double branchiness) :
	mPopulationModel(populationModel), mCulled(false), mNew(false), mFitnessScore(
		-1), mPhenotypeModel(NULL), mPhysicsModelType(physicsModelType), mInitialPosition(
		position), mFitnessScoreCalculated(false), mPosition(position),mDynasty(0) {
#ifndef EXCLUDE_FROM_TEST
	mWorld =
		populationModel->getPlanetModel()->getEnvironmentModel()->getPhysicsController()->getDynamicsWorld();
#endif
	NameGenerator nameGenerator; //set first name of creature
	mFirstName = nameGenerator.generateFirstName();

	mGenotype.createRandomGenome(branchiness); //generate random genome for the creature

	switch (mPhysicsModelType) { // add the phenome model depending on physics model type
	case PhysicsController::FeatherstoneModel:
		mPhenotypeModel = new FSPhenomeModel(this);
		break;
	case PhysicsController::RigidbodyModel:
		mPhenotypeModel = new SRBPhenomeModel(this);
		break;
	default:
		break;
	}
}

CreatureModel::CreatureModel(const CreatureModel& creatureModel) :
	mGenotype(&creatureModel.mGenotype) {

	mFirstName = creatureModel.mFirstName;
	mCulled = creatureModel.mCulled;
	mNew = creatureModel.mNew;
	mPopulationModel = creatureModel.mPopulationModel;
	mInitialPosition = creatureModel.mInitialPosition;
	mPosition = creatureModel.mPosition;
	mFitnessScore = creatureModel.mFitnessScore;
	mWorld = creatureModel.mWorld;
	mPhysicsModelType = creatureModel.mPhysicsModelType;
	mDynasty = creatureModel.mDynasty;

	switch (mPhysicsModelType) { // add the phenome model depending on physics model type
	case PhysicsController::FeatherstoneModel:
		mPhenotypeModel = new FSPhenomeModel(this);
		break;
	case PhysicsController::RigidbodyModel:
		mPhenotypeModel = new SRBPhenomeModel(this);
		break;
	default:
		break;
	}

	mFitnessScoreCalculated = creatureModel.mFitnessScoreCalculated;

	mJuries.clear();
	for (std::vector<Jury*>::const_iterator jit = creatureModel.mJuries.begin();
		jit != creatureModel.mJuries.end(); jit++) {
		mJuries.push_back((*jit)->clone());
	}
}

void CreatureModel::initialize() {

	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info) << "Initialize " << mFirstName;
	mPhenotypeModel->initialize(); 	//initialize the phenome model
}

CreatureModel::~CreatureModel() {
	mWorld = NULL;
	mPopulationModel = NULL;
	while (!mJuries.empty()) {
		Jury* f = mJuries.back();
		mJuries.pop_back();
		delete f;
	}
	delete mPhenotypeModel;
	mPhenotypeModel = NULL;
}

void CreatureModel::reset(const Ogre::Vector3 position) {
	mInitialPosition = position;
	mPosition = position;
}

void CreatureModel::reposition(const Ogre::Vector3 position) {
	mInitialPosition = position;
	mPosition = position;
}

double CreatureModel::getFitnessScore() {

	if (mFitnessScoreCalculated) {
		return mFitnessScore;
	}

	double fitness = 0;
	double weight = 0;

	for (std::vector<Jury*>::const_iterator jit = mJuries.begin();
		jit != mJuries.end(); jit++) {
		fitness += (*jit)->getScore() * (*jit)->getWeight();
		weight += (*jit)->getWeight();
	}

	if (weight != 0) {
		mFitnessScore = fitness / weight;
	} else {
		mFitnessScore = 0;
	}
	mFitnessScoreCalculated = true;
	return mFitnessScore;
}

bool CreatureModel::equals(const CreatureModel& creature) const {
	if (mFirstName != creature.mFirstName) {
		return false;
	}

	if (!mGenotype.equals(creature.mGenotype)) {
		return false;
	}

	if (!mPhenotypeModel->equals(*creature.mPhenotypeModel)) {
		return false;
	}

	/**Comparison of juries*/
	if (mJuries.size() != creature.mJuries.size()) {
		return false;
	}
	std::vector<Jury*>::const_iterator it = mJuries.begin();
	std::vector<Jury*>::const_iterator it2 = creature.mJuries.begin();
	for (; it != mJuries.end(), it2 != creature.mJuries.end(); it++, it2++) {
		if (!(*it)->equals(**(it2))) {
			return false;
		}
	}

	if (mPosition != creature.mPosition) {
		return false;
	}

	if (mInitialPosition != creature.mInitialPosition) {
		return false;
	}

	if (mCulled != creature.mCulled) {
		return false;
	}

	if (mNew != creature.mNew) {
		return false;
	}

	if (mPopulationModel != creature.mPopulationModel) {
		return false;
	}

	return true;
}

void CreatureModel::performEmbryogenesis() {
	mPhenotypeModel->performEmbryogenesis();
}

void CreatureModel::giveRebirth() {
	NameGenerator nameGenerator;
	mFirstName = nameGenerator.generateFirstName();
}

CreatureModel* CreatureModel::clone() {
	return new CreatureModel(*this);
}

void CreatureModel::update(double timeSinceLastTick) {
	for (std::vector<Jury*>::iterator jit = mJuries.begin();
		jit != mJuries.end(); jit++) {
		switch ((*jit)->getJuryType()) {
		default: {
			(*jit)->calculateFitness(this, timeSinceLastTick);
			break;
		}
		}
	}
}

void CreatureModel::processJuries() {
	for (std::vector<Jury*>::iterator jit = mJuries.begin();
		jit != mJuries.end(); jit++) {
		(*jit)->evaluateFitness();
	}
}

void CreatureModel::calm() {
	mPhenotypeModel->calm();
}

btDynamicsWorld*& CreatureModel::getWorld() {
	if (!mWorld) {
		mWorld =
			mPopulationModel->getPlanetModel()->getEnvironmentModel()->getPhysicsController()->getDynamicsWorld();
	}
	return mWorld;

}
