//# corresponding headers
#include <model/universe/evolution/population/PopulationModel.hpp>

//# forward declarations
//# system headers
#include <OgreVector3.h>

//## controller headers
//## model headers
//## view headers
//# custom headers
//## base headers
//## configuration headers
#include <configuration/ControlConfiguration.hpp>
#include <configuration/GeneticsConfiguration.hpp>

//## controller headers
//## model headers
#include <model/universe/evolution/population/creature/genome/MixedGenome.hpp>
#include <model/universe/evolution/population/creature/modelOrganism/modelLeg/ModelLegBuilder.hpp>
#include <model/universe/evolution/population/creature/modelOrganism/snake/SnakeBuilder.hpp>
#include <model/universe/evolution/population/creature/modelOrganism/ragdoll/RagDollBuilder.hpp>
#include <model/universe/evolution/population/creature/modelOrganism/pod/PodBuilder.hpp>
#include <model/universe/evolution/population/PopulationModel.hpp>
#include <model/universe/PlanetModel.hpp>

//## view headers
//## utils headers
#include <utils/Randomness.hpp>
#include <utils/serialization/FilesystemManipulator.hpp>

PopulationModel::PopulationModel() :
	mCreatureQty(0), mCurrentCreatureIndex(0), mPlanetModel(
	NULL), mOutOfSync(false), mCurrentGeneration(0), mDynastyQty(0) {

}

PopulationModel::PopulationModel(PlanetModel* const planetModel,
	const int creatureQty) :
	mCreatureQty(creatureQty), mCurrentCreatureIndex(0), mPlanetModel(
		planetModel), mOutOfSync(false), mCurrentGeneration(0), mDynastyQty(0) {
}

PopulationModel::PopulationModel(PlanetModel* const planetModel,
	const int creatureQty, const Ogre::Vector3 initialPosition) :
	mCreatureQty(creatureQty), mCurrentCreatureIndex(0), mPlanetModel(
		planetModel), mOutOfSync(false), mCurrentGeneration(0) {
	// add creatures up to the creature quantity.
	double branchiness = 0;
	for (int i = 0; i < creatureQty; i++) {
		branchiness = Randomness::getSingleton()->nextNormalDouble(
			GeneticsConfiguration::GENE_BRANCH_INITIAL_MEAN,
			GeneticsConfiguration::GENE_BRANCH_INITIAL_VAR);

		//add new creature
		CreatureModel* creatureModel = new CreatureModel(this,
			mPlanetModel->getPhysicsModelType(), initialPosition);

//		ModelLegBuilder::build(&creatureModel->getGenotype(),ControlConfiguration::CONTROLLER_TYPE); // start with model legs
		// OR
//		RagDollBuilder::build(&creatureModel->getGenotype(),ControlConfiguration::CONTROLLER_TYPE); // start with ragdolls
		// OR
//		SnakeBuilder::build(&creatureModel->getGenotype(),ControlConfiguration::CONTROLLER_TYPE); // start with snakes
		// OR
//		PodBuilder::build(&creatureModel->getGenotype(), ControlConfiguration::CONTROLLER_TYPE); // start with pods (hexapod etc.)

		// interesting effects can also be achieved when starting with one of the above and the create a random genome over it

		creatureModel->createRandomGenome(branchiness);
		creatureModel->setNew(true);
		creatureModel->setDynasty(mDynastyQty);
		addMember(creatureModel);
		mDynastyQty++;
	}
}

PopulationModel::PopulationModel(const PopulationModel& populationModel) :
	mOutOfSync(false) {
	mPlanetModel = populationModel.mPlanetModel;
	mCreatureQty = populationModel.mCreatureQty;
	mCurrentCreatureIndex = populationModel.mCurrentCreatureIndex;
	mCurrentGeneration = populationModel.mCurrentGeneration;
	mDynastyQty = populationModel.mDynastyQty;

	for (std::vector<CreatureModel*>::const_iterator cit =
		populationModel.getCreatureModels().begin();
		cit != populationModel.getCreatureModels().end(); cit++) {
		mCreatureModels.push_back((*cit)->clone());
	}
}

PopulationModel::~PopulationModel() {
	mCreatureModels.clear(); 	// models only delete their own things

	mPlanetModel = NULL;
}

void PopulationModel::perturbCreatureControllers(){
	for (std::vector<CreatureModel*>::const_iterator cit =
		mCreatureModels.begin(); cit != mCreatureModels.end(); cit++) {
		(*cit)->perturbControllers();
	}
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
	CreatureModel* creatureModel = new CreatureModel(this,
		mPlanetModel->getPhysicsModelType(), rootPosition);

	creatureModel->createRandomGenome(branchiness);
	creatureModel->setNew(true);
	creatureModel->setDynasty(mDynastyQty);
	mDynastyQty++;
	addMember(creatureModel);
}

/**
 * Adds a new creature to the population with the bushiness as a input.
 * @param bushiness The bushiness determines the number of gene branches a gene has in this creature's genome.
 */
void PopulationModel::addMember(CreatureModel* const creatureModel) {
	mCreatureModels.push_back(creatureModel);
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

double PopulationModel::getMaxJointVelocity() {
	double maxJointVelocity = 0;
	for (std::vector<CreatureModel*>::const_iterator cit =
		mCreatureModels.begin(); cit != mCreatureModels.end(); cit++) {
		double newMaxJointVelocity = (*cit)->getMaxJointVelocity();
		if (newMaxJointVelocity > maxJointVelocity) {
			maxJointVelocity = newMaxJointVelocity;
			break;
		}
	}
	return maxJointVelocity;
}

void PopulationModel::save() {
	SaveController<PopulationModel> populationSaveController;
	populationSaveController.save(*this,
		std::string(mSerializationPath + "/population.po").c_str());
//	if (SerializationConfiguration::POPULATION_EXPANDED) {
//		saveCreatures();
//	}
}

void PopulationModel::load() {
	SaveController<PopulationModel> populationSaveController;
	populationSaveController.restore(*this,
		std::string(mSerializationPath + "/population.po").c_str());
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
		creature->getGenotype().repairGenes();
		creature->setNew(true);
		creature->setPopulationModel(this);
		mCreatureModels.push_back(creature);
	}
}

void PopulationModel::clearJuries() {
	for (std::vector<CreatureModel*>::iterator it = mCreatureModels.begin();
		it != mCreatureModels.end(); it++) {
		(*it)->clearJuries();
	}
}
