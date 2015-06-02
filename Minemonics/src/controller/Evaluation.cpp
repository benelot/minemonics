/*
 * Evaluation.cpp
 *
 *  Created on: Jun 1, 2015
 *      Author: leviathan
 */

#include <controller/Evaluation.hpp>
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
//## model headers
//## view headers
//## utils headers


Evaluation::Evaluation():mPlanet(NULL) {
	// TODO Auto-generated constructor stub

}

Evaluation::~Evaluation() {
	// TODO Auto-generated destructor stub
}

void Evaluation::initialize(Planet* planet) {
	mPlanet = planet;
}

void Evaluation::addPopulation(Population* population) {
	mPopulations.push_back(population);
	mEvaluationModel.addPopulationModel(population->getPopulationModel());
}
