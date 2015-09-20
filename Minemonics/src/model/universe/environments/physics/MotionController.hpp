#ifndef MODEL_UNIVERSE_ENVIRONMENTS_PHYSICS_MOTIONCONTROLLER_H_
#define MODEL_UNIVERSE_ENVIRONMENTS_PHYSICS_MOTIONCONTROLLER_H_

//# corresponding header
#include <model/universe/environments/physics/PhysicsController.hpp>
#include <configuration/Definitions.hpp>

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

/**
 * @brief		The motion controller is the base class to all controller for special environments.
 * @details		Details
 * @date		2015-03-03
 * @author		Benjamin Ellenberger
 */
class MotionController: public PhysicsController {
public:
	MotionController();
	virtual ~MotionController();
};

#endif /* MODEL_UNIVERSE_ENVIRONMENTS_PHYSICS_MOTIONCONTROLLER_H_ */
