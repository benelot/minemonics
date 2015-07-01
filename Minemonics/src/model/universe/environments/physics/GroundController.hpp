#ifndef GROUNDCONTROLLER_H_
#define GROUNDCONTROLLER_H_

//# forward declarations
#include <model/universe/environments/physics/MotionController.hpp>

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
class GroundController: public MotionController {
public:
	GroundController();
	virtual ~GroundController();
};

#endif /* GROUNDCONTROLLER_H_ */
