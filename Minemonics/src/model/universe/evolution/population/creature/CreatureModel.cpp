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
#include <model/universe/evolution/population/PopulationModel.hpp>

//## view headers
//## utils headers
#include <utils/NameGenerator.hpp>
#include <utils/Randomness.hpp>

CreatureModel::CreatureModel() :
		mPopulationModel(NULL), mPhenotypeModel(NULL), mFitness(0) {
	mJuries.clear();
}

CreatureModel::CreatureModel(const CreatureModel& creatureModel) :
		mGenotype(creatureModel.mGenotype), mFitness(0) {
	mJuries.clear();

	mFirstName = creatureModel.mFirstName;

	mPopulationModel = creatureModel.mPopulationModel;
	if (creatureModel.mPhenotypeModel != NULL) {
		mPhenotypeModel = creatureModel.mPhenotypeModel->clone();
	}
	mInitialPosition = creatureModel.mInitialPosition;
	mPosition = creatureModel.mPosition;

	for (std::vector<Jury*>::const_iterator jit = creatureModel.mJuries.begin();
			jit != creatureModel.mJuries.end(); jit++) {
		mJuries.push_back((*jit)->clone());
	}
}

void CreatureModel::initialize(PopulationModel* const populationModel,
		PhenomeModel* const phenomeModel, const Ogre::Vector3 position,
		const double branchiness) {
	mPopulationModel = populationModel;
	mPhenotypeModel = phenomeModel;
	mInitialPosition = position;
	mPosition = position;
	Randomness randomness;
	NameGenerator nameGenerator;
	mFirstName = nameGenerator.generateFirstName();
	mGenotype.createRandomGenome(branchiness);
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

//	for (std::vector<Jury*>::const_iterator jit = mJuries.begin();
//			jit != mJuries.end(); jit++) {
//		fitness += (*jit)->getFitness() * (*jit)->getWeight();
//		weight += (*jit)->getWeight();
//	}

	if (mFitness == 0) {
		Randomness randomness;
		mFitness = randomness.nextUnifDouble(0, 100);
	}
	fitness = mFitness;

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

	std::vector<Jury*>::const_iterator it = mJuries.begin();
	std::vector<Jury*>::const_iterator it2 = creature.mJuries.begin();
	for (; it != mJuries.end(), it2 != creature.mJuries.end(); it++, it2++) {
		if (!(*it)->equals(**(it2))) {
			return false;
		}
	}

	if (mPhenotypeModel->equals(*creature.mPhenotypeModel)) {
		return false;
	}

	if (mPopulationModel != mPopulationModel) {
		return false;
	}

	return true;
}

void CreatureModel::performEmbryogenesis() {
	mPhenotypeModel->performEmbryogenesis(this);
}

CreatureModel* CreatureModel::clone() {
	return new CreatureModel(*this);
}
