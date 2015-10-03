//# corresponding headers
#include <model/universe/UniverseModel.hpp>

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
#include <model/universe/EvaluationModel.hpp>
#include <model/universe/PlanetModel.hpp>

//## view headers
//## utils headers

UniverseModel::UniverseModel() :
	mCurrentEvaluationPlanetIndex(0) {
}

UniverseModel::~UniverseModel() {
//	mCurrentEvaluationPlanetIndex

	for (std::vector<EvaluationModel*>::iterator eit =
		mEvaluationModels.begin(); eit != mEvaluationModels.end(); eit++) {
		delete (*eit);
	}
	mEvaluationModels.clear();

	for (std::vector<PlanetModel*>::iterator eit = mPlanetModels.begin();
		eit != mPlanetModels.end(); eit++) {
		delete (*eit);
	}
	mPlanetModels.clear();
}

void UniverseModel::initialize() {
}

void UniverseModel::addPlanetModel(PlanetModel* const planetModel) {
	mPlanetModels.push_back(planetModel);
}

void UniverseModel::proceedEvaluation() {

}
