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
}

Evaluation::~Evaluation() {
	mPlanet = NULL;
	mPopulations.clear();
}

void Evaluation::initialize(Planet* planet, double evaluationTime) {
	mPlanet = planet;
	mEvaluationModel.initialize(&planet->getPlanetModel(), evaluationTime);
}

void Evaluation::addPopulation(Population* population) {
	mPopulations.push_back(population);
	mEvaluationModel.addPopulationModel(population->getPopulationModel());
}

void Evaluation::setup() {
	//add environment to the world
	//TODO: Must be a separate copy for parallel evaluations(you can not use the same reference for multiple worlds), but must update (possibly in parallel)
	// the main environment to stay the same for all evaluations
	mPlanet->getEnvironment()->addToWorld();

	//add competing populations to the world
	std::vector<Population*>::iterator pit = mPopulations.begin();
	for (; pit != mPopulations.end(); pit++) {
		(*pit)->addToWorld();
	}

	mEvaluationModel.setEvaluating(true);
}

void Evaluation::process() {
	//TODO: Process populations and add scores from juries.
}

void Evaluation::teardown() {

	//remove the environment from the world
	mPlanet->getEnvironment()->removeFromWorld();

	// remove competing populations from the world
	std::vector<Population*>::iterator pit = mPopulations.begin();
	for (; pit != mPopulations.end(); pit++) {
		(*pit)->removeFromWorld();
	}

	mEvaluationModel.setEvaluating(false);
	mEvaluationModel.setTornDown(true);
}

void Evaluation::update(double timeSinceLastFrame) {

	//update the planet's environment
	mPlanet->getEnvironment()->update();


	//update the competing populations
	std::vector<Population*>::iterator pit = mPopulations.begin();
	for (; pit != mPopulations.end(); pit++) {
		(*pit)->update();
	}

	//update the time passed
	mEvaluationModel.addTimePassed(timeSinceLastFrame);

	//terminate if the time passed is higher than the evaluation time
	if (mEvaluationModel.getTimePassed()
			> mEvaluationModel.getEvaluationTime()) {
		process();

		teardown();
	}
}
