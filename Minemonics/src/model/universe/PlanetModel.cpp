//# corresponding header
#include <model/universe/PlanetModel.hpp>

//# forward declarations
//# system headers
//## controller headers
//## model headers
//## view headers
//# custom headers
//## base headers
#include <SimulationManager.hpp>

//## configuration headers
//## controller headers
#include <controller/SaveController.hpp>

//## model headers
//## view headers
//## utils headers
#include <utils/serialization/FilesystemManipulator.hpp>

PlanetModel::PlanetModel() :
	mEnvironmentModel(NULL), mCurrentEpoch(0) {
}

PlanetModel::PlanetModel(const EvolutionModel::EvaluationType type,
	const double evaluationTime, const int tournamentSize,
	const PhysicsController::PhysicsModelType physicsModelType,
	const EnvironmentModel::EnvironmentType environmentType) :
	mEvolutionModel(type, evaluationTime, tournamentSize), mCurrentEpoch(0) {
	// set up environment
	switch (environmentType) {
	case EnvironmentModel::HILLS: {
		//		mEnvironment = new Hills();
		//		((Hills*) mEnvironment)->initialize(physicsModelType, light);
		break;
	}
	case EnvironmentModel::PLANE: {
		//create the terrain
		mEnvironmentModel = new PlaneModel(physicsModelType);
		break;
	}
	}
}

PlanetModel::~PlanetModel() {
//	~EvolutionModel();
	mEnvironmentModel = NULL; // environment model is deleted in the environment controller

	for (std::vector<Epoch*>::iterator eit = mEpochs.begin();
		eit != mEpochs.end(); eit++) {
		delete (*eit);
	}
	mEpochs.clear();
}

void PlanetModel::initialize() {
	mEnvironmentModel->getPhysicsController()->initialize();
#ifndef EXCLUDE_FROM_TEST
	mEnvironmentModel->getPhysicsController()->setDebugDrawer(
		&(SimulationManager::getSingleton()->getDebugDrawer()));
#endif
	mEvolutionModel.initialize();
}

bool PlanetModel::proceedEvaluation() {
	if (mEpochs.size() > mCurrentEpoch) {
		if (mEpochs[mCurrentEpoch]->isEndOfEpoch()) {
			mCurrentEpoch++;
		}
		return true;
	}
	return false;
}

void PlanetModel::performEmbryogenesis() {
	mEvolutionModel.performEmbryogenesis();
}

void PlanetModel::perturbPopulations(){
	mEvolutionModel.perturbPopulations();
}

void PlanetModel::update(double timeSinceLastTick) {
	mEnvironmentModel->update(timeSinceLastTick);
}

void PlanetModel::save() {
	SaveController<PlanetModel> planetModelSaver;
	planetModelSaver.save(*this, mSerializationPath.c_str());

	for (std::vector<PopulationModel*>::iterator pit =
		mEvolutionModel.getPopulationModels().begin();
		pit != mEvolutionModel.getPopulationModels().end(); pit++) {
		(*pit)->save();
	}
}

void PlanetModel::load() {
	SaveController<PlanetModel> planetModelSaver;
	planetModelSaver.restore(*this, mSerializationPath.c_str());

	mEvolutionModel.getPopulationModels().clear();

	//get parent directory name
	std::string dirname =
		boost::filesystem::path(mSerializationPath).parent_path().string();

	std::vector<std::string> files =
		FilesystemManipulator::getFileNamesByExtension(dirname, ".population");
	for (int i = 0; i < files.size(); i++) {
		PopulationModel* population = new PopulationModel();

		population->setSerializationPath(files[i]);
		population->load();
		mEvolutionModel.getPopulationModels().push_back(population);
	}
}

PhysicsController::PhysicsModelType PlanetModel::getPhysicsModelType() {
	return mEnvironmentModel->getPhysicsController()->getPhysicsModelType();
}
