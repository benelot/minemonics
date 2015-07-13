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
#include <model/universe/PlanetModel.hpp>

//## view headers
//## utils headers

UniverseModel::UniverseModel() :
		mCurrentEvaluationPlanetIndex(0) {
}

UniverseModel::~UniverseModel() {
//	mCurrentEvaluationPlanetIndex
	mEvaluationModels.clear();
	mPlanetModels.clear();
}

void UniverseModel::initialize() {
}

void UniverseModel::addPlanetModel(PlanetModel* const planetModel) {
	mPlanetModels.push_back(planetModel);
}

void UniverseModel::proceedEvaluation() {

}
