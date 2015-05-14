//# corresponding header
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
#include <controller/universe/Planet.hpp>

//## model headers
//## view headers
//## utils headers

Planet::Planet() :
		mEnvironment(NULL), mEvolution(NULL),mPhysicsController(NULL) {
}

Planet::~Planet() {
	mEnvironment = NULL;
	mEvolution = NULL;
}

void Planet::initialize(Evolution* evolution, Environment* environment,PhysicsController::PhysicsControllerType type) {
	PhysicsController* physicsController;

	switch (type) {
		case PhysicsController::GroundController:

			break;
		case PhysicsController::DeepSeaController:

			break;
		default:
			break;
	}
	initialize(evolution,environment,physicsController);
}

void Planet::initialize(Evolution* evolution, Environment* environment,PhysicsController* physicsController) {
	mEvolution = evolution;
	mEnvironment = environment;
	mPhysicsController = physicsController;
}
