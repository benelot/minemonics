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
#include <model/universe/environments/EnvironmentModel.hpp>
#include <model/universe/evolution/EvolutionModel.hpp>

//## view headers
//## utils headers

PlanetModel::PlanetModel() :
		mEnvironmentModel(NULL), mEvolutionModel(NULL) {
	// TODO Auto-generated constructor stub

}

PlanetModel::~PlanetModel() {
	// TODO Auto-generated destructor stub
}

void PlanetModel::initialize() {
}

bool PlanetModel::proceedEvaluation() {
	if (!mEnvironmentModel->isInWorld()) {
		mEnvironmentModel->addToWorld();
	}

	if(!mEvolutionModel->proceedEvaluation())
	{
		mEnvironmentModel->removeFromWorld();
		return false;
	}
	return true;

}
