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
