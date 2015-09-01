#ifndef MODEL_UNIVERSE_ENVIRONMENTS_PHYSICS_GROUNDCONTROLLER_H_
#define MODEL_UNIVERSE_ENVIRONMENTS_PHYSICS_GROUNDCONTROLLER_H_

//# forward declarations
#include <model/universe/environments/physics/PhysicsController.hpp>

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

/**
 * @brief		The ground controller simulates physical motion similar to motion on ground.
 * @details		Details
 * @date		2014-11-17
 * @author		Benjamin Ellenberger
 */
class GroundController: public PhysicsController {
public:
	GroundController(PhysicsController::SolverType solverType);
	virtual ~GroundController();
};

#endif /* MODEL_UNIVERSE_ENVIRONMENTS_PHYSICS_GROUNDCONTROLLER_H_ */
