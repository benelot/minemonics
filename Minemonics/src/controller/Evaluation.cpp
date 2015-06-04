//# corresponding headers
//# forward declarations
//# system headers
//## controller headers
//## model headers
//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
#include <controller/Evaluation.hpp>
#include <controller/universe/Planet.hpp>

//## model headers
//## view headers
//## utils headers

Evaluation::Evaluation() :
		mPlanet(NULL) {
	// TODO Auto-generated constructor stub

}

Evaluation::~Evaluation() {
	// TODO Auto-generated destructor stub
}

void Evaluation::initialize(Planet* planet, double evaluationTime) {
	mPlanet = planet;
	mEvaluationModel.initialize(&planet->getPlanetModel(), evaluationTime);
}

void Evaluation::addPopulation(Population* population) {
	mPopulations.push_back(population);
	mEvaluationModel.addPopulationModel(population->getPopulationModel());
}

void Evaluation::runEvaluation() {
	//TODO: Implement runEvaluation.
}
