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
#include <model/universe/evolution/juries/AverageVelocity.hpp>
#include <model/universe/evolution/population/PopulationModel.hpp>
#include <model/universe/environments/EnvironmentModel.hpp>

//## view headers
//## utils headers
#include <utils/NameGenerator.hpp>
#include <utils/Randomness.hpp>

CreatureModel::CreatureModel() :
		mPopulationModel(NULL), mCulled(false), mNew(false) {
	mJuries.clear();
}

CreatureModel::CreatureModel(const CreatureModel& creatureModel) :
		mGenotype(creatureModel.mGenotype), mPhenotypeModel(
				creatureModel.mPhenotypeModel) {

	mFirstName = creatureModel.mFirstName;
	mCulled = creatureModel.mCulled;
	mNew = creatureModel.mNew;
	mPopulationModel = creatureModel.mPopulationModel;
	mInitialPosition = creatureModel.mInitialPosition;
	mPosition = creatureModel.mPosition;

	mJuries.clear();
	for (std::vector<Jury*>::const_iterator jit = creatureModel.mJuries.begin();
			jit != creatureModel.mJuries.end(); jit++) {
		mJuries.push_back((*jit)->clone());
	}
}

void CreatureModel::initialize(PopulationModel* const populationModel,
		const Ogre::Vector3 position, const double branchiness) {
	mPopulationModel = populationModel;
	mInitialPosition = position;
	mPosition = position;
	NameGenerator nameGenerator;
	mFirstName = nameGenerator.generateFirstName();
	mGenotype.createRandomGenome(branchiness);
	mPhenotypeModel.initialize(this);
}

CreatureModel::~CreatureModel() {
	while (!mJuries.empty()) {
		Jury* f = mJuries.back();
		mJuries.pop_back();
		delete f;
	}
}

void CreatureModel::reset(const Ogre::Vector3 position) {
	mInitialPosition = position;
	mPosition = position;
}

void CreatureModel::reposition(const Ogre::Vector3 position) {
	mInitialPosition = position;
	mPosition = position;
}

double CreatureModel::getFitness() {
	double fitness = 0;
	double weight = 1;

	for (std::vector<Jury*>::const_iterator jit = mJuries.begin();
			jit != mJuries.end(); jit++) {
		fitness += (*jit)->getFitness() * (*jit)->getWeight();
		weight += (*jit)->getWeight();
	}

	if (weight != 0) {
		return fitness / weight;
	}
	return 0;
}

bool CreatureModel::equals(const CreatureModel& creature) const {
	if (mFirstName != creature.mFirstName) {
		return false;
	}

	if (!mGenotype.equals(creature.mGenotype)) {
		return false;
	}

	if (!mPhenotypeModel.equals(creature.mPhenotypeModel)) {
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
	mPhenotypeModel.performEmbryogenesis(this);
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
		case Jury::AVG_VELOCITY: {
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
