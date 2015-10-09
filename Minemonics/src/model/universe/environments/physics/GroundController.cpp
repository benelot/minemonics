//# corresponding header
#include <model/universe/environments/physics/GroundController.hpp>

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

GroundController::GroundController(){

}

GroundController::GroundController(
	PhysicsController::PhysicsModelType physicsModelType) :
	PhysicsController(physicsModelType, PhysicsController::GroundController) {
}

GroundController::~GroundController() {
}

