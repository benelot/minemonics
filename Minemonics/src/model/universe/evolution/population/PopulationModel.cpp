//# corresponding headers
#include <model/universe/evolution/population/PopulationModel.hpp>

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
#include <model/universe/PlanetModel.hpp>

//## view headers
//## utils headers
#include <utils/Randomness.hpp>

PopulationModel::PopulationModel() :
	mCreatureQty(0), mCurrentCreatureIndex(0), mPlanetModel(
	NULL), mOutOfSync(false), mCurrentGeneration(0) {

}

PopulationModel::PopulationModel(PlanetModel* const planetModel,
	const int creatureQty) :
	mCreatureQty(creatureQty), mCurrentCreatureIndex(0), mPlanetModel(
		planetModel), mOutOfSync(false), mCurrentGeneration(0) {
}

PopulationModel::PopulationModel(PlanetModel* const planetModel,
	const int creatureQty, const Ogre::Vector3 initialPosition) :
	mCreatureQty(0), mCurrentCreatureIndex(0), mPlanetModel(
		planetModel), mOutOfSync(false), mCurrentGeneration(0) {
	// add creatures up to the creature quantity.
	double branchiness = 0;
	for (int i = 0; i < creatureQty; i++) {
		branchiness = Randomness::getSingleton()->nextNormalDouble(
			MorphologyConfiguration::BODY_BRANCH_INITIAL_MEAN,
			MorphologyConfiguration::BODY_BRANCH_INITIAL_VAR);
		addNewMember(branchiness, initialPosition);
	}
}

PopulationModel::PopulationModel(const PopulationModel& populationModel) :
	mOutOfSync(false) {
	mPlanetModel = populationModel.mPlanetModel;
	mCreatureQty = populationModel.mCreatureQty;
	mCurrentCreatureIndex = populationModel.mCurrentCreatureIndex;
	mCurrentGeneration = populationModel.mCurrentGeneration;

	for (std::vector<CreatureModel*>::const_iterator cit =
		populationModel.getCreatureModels().begin();
		cit != populationModel.getCreatureModels().end(); cit++) {
		mCreatureModels.push_back((*cit)->clone());
	}
}

PopulationModel::~PopulationModel() {
	// models only delete their own things
	mCreatureModels.clear();

	mPlanetModel = NULL;
}

/**
 * Initializes the population and adds creatures up to the creatureQty. Each creature gets a bushiness value around an predefined mean with a predefined variance.
 */
void PopulationModel::initialize() {
	for (std::vector<CreatureModel*>::const_iterator cit =
		mCreatureModels.begin(); cit != mCreatureModels.end(); cit++) {
		(*cit)->initialize();
	}
}

/**
 * Adds a new creature to the population with the bushiness as a input.
 * @param bushiness The bushiness determines the number of gene branches a gene has in this creature's genome.
 */
void PopulationModel::addNewMember(const double branchiness,
	const Ogre::Vector3 rootPosition) {
	//add new creature
//	Creature* creature = new Snake(this,15,OgreBulletUtils::convert(rootPosition));
//	Creature* creature = new RagDoll(this,10,OgreBulletUtils::convert(rootPosition));
	CreatureModel* creatureModel = new CreatureModel(this,
		mPlanetModel->getPhysicsModelType(), rootPosition, branchiness);
	creatureModel->setNew(true);
	addMember(creatureModel);
}

/**
 * Adds a new creature to the population with the bushiness as a input.
 * @param bushiness The bushiness determines the number of gene branches a gene has in this creature's genome.
 */
void PopulationModel::addMember(CreatureModel* const creatureModel) {
	mCreatureModels.push_back(creatureModel);
	mCreatureQty++;
}

/**
 * Tests if a population is equal to another population.
 * @param population The population to test for equality.
 * @return If this population and the other are equal.
 */
bool PopulationModel::equals(const PopulationModel& population) const {
	if (mCreatureQty != population.mCreatureQty) {
		return false;
	}

	//This is usually loaded separately
//	/**Comparison of creature models*/
//	if (mCreatureModels.size() != population.mCreatureModels.size()) {
//		return false;
//	}
//	std::vector<CreatureModel*>::const_iterator it = mCreatureModels.begin();
//	std::vector<CreatureModel*>::const_iterator it2 =
//		population.getCreatureModels().begin();
//	for (;
//		it != mCreatureModels.end(), it2 != population.getCreatureModels().end();
//		it++, it2++) {
//		if (!(*it)->equals(**it2)) {
//			return false;
//		}
//	}

	return true;

}

PopulationModel* PopulationModel::clone() {
	return new PopulationModel(*this);
}

bool PopulationModel::hasInterpenetrations() {
	bool hasInterpenetrations = false;
	for (std::vector<CreatureModel*>::const_iterator cit =
		mCreatureModels.begin(); cit != mCreatureModels.end(); cit++) {
		if ((*cit)->hasInterpenetrations()) {
			hasInterpenetrations = true;
			break;
		}
	}
	return hasInterpenetrations;
}

void PopulationModel::save() {
	SaveController<PopulationModel> populationSaveController;
	populationSaveController.save(*this, std::string(mSerializationPath + "/population.po").c_str());
//	if (SerializationConfiguration::POPULATION_EXPANDED) {
//		saveCreatures();
//	}
}

void PopulationModel::load() {
	SaveController<PopulationModel> populationSaveController;
	populationSaveController.restore(*this, std::string(mSerializationPath + "/population.po").c_str());
	if (SerializationConfiguration::POPULATION_EXPANDED) {
		loadCreatures();
	}
}

void PopulationModel::saveCreatures() {
	for (std::vector<CreatureModel*>::const_iterator it =
		mCreatureModels.begin(); it != mCreatureModels.end(); it++) {
		(*it)->save();
	}
}

void PopulationModel::loadCreatures() {
	mCreatureModels.clear();

	//create folder for the generation
	std::string generationPath = getSerializationPath()
		+ std::string("/Generation-")
		+ boost::lexical_cast<std::string>(getCurrentGeneration());

	std::vector<std::string> files =
		FilesystemManipulator::getFileNamesByExtension(generationPath, ".cr");
	for (int i = 0; i < files.size(); i++) {
		CreatureModel* creature = new CreatureModel();

		std::string creaturePath = generationPath + std::string("/") + files[i];

		creature->setSerializationPath(creaturePath);
		creature->load();
		creature->setNew(true);
		creature->setPopulationModel(this);
		mCreatureModels.push_back(creature);
	}
}

