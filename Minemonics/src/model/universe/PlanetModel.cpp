//# corresponding header
#include <model/universe/PlanetModel.hpp>

//# forward declarations
#ifndef NULL
#define NULL 0
#endif /*NULL*/

//# system headers
//## controller headers
//## model headers
//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
#include <model/universe/Epoch.hpp>
#include <model/universe/environments/EnvironmentModel.hpp>
#include <model/universe/evolution/EvolutionModel.hpp>

//## view headers
//## utils headers
#include <utils/serialization/FilesystemManipulator.hpp>

PlanetModel::PlanetModel() :
	mEnvironmentModel(NULL), mEvolutionModel(NULL), mCurrentEpoch(0) {
}

PlanetModel::~PlanetModel() {
	if (mEnvironmentModel) {
		delete mEnvironmentModel;
	}

	mEpochs.clear();

	if (mEvolutionModel) {
		delete mEvolutionModel;
	}
}

void PlanetModel::initialize(EvolutionModel* const evolutionModel,
	EnvironmentModel* const environmentModel) {
	mEvolutionModel = evolutionModel;
	mEnvironmentModel = environmentModel;
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
	mEvolutionModel->performEmbryogenesis();
}

void PlanetModel::update(double timeSinceLastTick) {
	mEnvironmentModel->update(timeSinceLastTick);
}

void PlanetModel::save() {
	SaveController < PlanetModel > planetModelSaver;
	planetModelSaver.save(*this, mSerializationPath.c_str());

	for (std::vector<PopulationModel*>::iterator pit =
		mEvolutionModel->getPopulationModels().begin();
		pit != mEvolutionModel->getPopulationModels().end(); pit++) {
		(*pit)->save();
	}
}

void PlanetModel::load() {
	SaveController < PlanetModel > planetModelSaver;
	planetModelSaver.restore(*this, mSerializationPath.c_str());

	mEvolutionModel->getPopulationModels().clear();

	//get parent directory name
	std::string dirname =
		boost::filesystem::path(mSerializationPath).parent_path().string();

	std::vector < std::string > files =
		FilesystemManipulator::getFileNamesByExtension(dirname, ".population");
	for (int i = 0; i < files.size(); i++) {
		PopulationModel* population = new PopulationModel();

		population->setSerializationPath(files[i]);
		population->load();
		mEvolutionModel->getPopulationModels().push_back(population);
	}
}
