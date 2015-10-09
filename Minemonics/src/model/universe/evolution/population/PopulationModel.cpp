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

PopulationModel::PopulationModel() :
	mCreatureQty(0), mCurrentCreatureIndex(0), mPlanetModel(NULL), mOutOfSync(
		false), mCurrentGeneration(0) {

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
 * @param creatureQty The number of creatures that the population will consist of in every generation.
 */
void PopulationModel::initialize(PlanetModel* const planetModel,
	const int creatureQty) {
	mPlanetModel = planetModel;
	mCreatureQty = creatureQty;
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

	/**Comparison of creature models*/
	if (mCreatureModels.size() != population.mCreatureModels.size()) {
		return false;
	}
	std::vector<CreatureModel*>::const_iterator it = mCreatureModels.begin();
	std::vector<CreatureModel*>::const_iterator it2 =
		population.getCreatureModels().begin();
	for (;
		it != mCreatureModels.end(), it2 != population.getCreatureModels().end();
		it++, it2++) {
		if (!(*it)->equals(**it2)) {
			return false;
		}
	}

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
	populationSaveController.save(*this, mSerializationPath.c_str());
	if (SerializationConfiguration::POPULATION_EXPANDED) {
		saveCreatures();
	}
}

void PopulationModel::load() {
	SaveController<PopulationModel> populationSaveController;
	populationSaveController.restore(*this, mSerializationPath.c_str());
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

	//get parent directory name
	std::string dirname =
		boost::filesystem::path(mSerializationPath).parent_path().string();

	std::vector<std::string> files =
		FilesystemManipulator::getFileNamesByExtension(dirname, ".cr");
	for (int i = 0; i < files.size(); i++) {
		CreatureModel* creature = new CreatureModel();

		creature->setSerializationPath(files[i]);
		creature->load();
		mCreatureModels.push_back(creature);
	}
}

