/*
 * MotionController.h
 *
 *  Created on: Mar 3, 2015
 *      Author: leviathan
 */

#ifndef MOTIONCONTROLLER_H_
#define MOTIONCONTROLLER_H_

//# corresponding header
#include <controller/physics/PhysicsController.hpp>

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
 * @brief		Brief
 * @details		Details
 * @date		2015-04-27
 * @author		Benjamin Ellenberger
 */
class MotionController: public PhysicsController {
public:
	MotionController();
	virtual ~MotionController();
};

#endif /* MOTIONCONTROLLER_H_ */
