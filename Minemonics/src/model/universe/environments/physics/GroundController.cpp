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

GroundController::GroundController(PhysicsController::SolverType solverType) :
	PhysicsController(solverType, PhysicsController::GroundController) {
}

GroundController::~GroundController() {

}

