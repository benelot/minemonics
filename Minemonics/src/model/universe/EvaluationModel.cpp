
//# corresponding headers
#include <model/universe/EvaluationModel.hpp>

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
//## view headers
//## utils headers

EvaluationModel::EvaluationModel():mPlanetModel(NULL) {
	// TODO Auto-generated constructor stub

}

EvaluationModel::~EvaluationModel() {
	// TODO Auto-generated destructor stub
}

void EvaluationModel::initialize(PlanetModel* planetModel) {
	mPlanetModel = planetModel;
}

void EvaluationModel::addPopulationModel(PopulationModel* populationModel) {
	mPopulationModels.push_back(populationModel);
}
