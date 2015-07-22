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

EvaluationModel::EvaluationModel() :
		mPlanetModel(NULL), mEvaluationTime(0), mTimePassed(0), mEvaluating(
				false), mTornDown(false), mSimulationSpeed(1) {
	// TODO Auto-generated constructor stub

}

EvaluationModel::~EvaluationModel() {
	// TODO Auto-generated destructor stub
}

void EvaluationModel::initialize(PlanetModel* const planetModel,
		const double evaluationTime) {
	mPlanetModel = planetModel;
	mEvaluationTime = evaluationTime;
}

void EvaluationModel::addPopulationModel(
		PopulationModel* const populationModel) {
	mPopulationModels.push_back(populationModel);
}
