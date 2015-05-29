/*
 * GroundController.h
 *
 *  Created on: Nov 17, 2014
 *      Author: leviathan
 */

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
 * @brief		Brief
 * @details		Details
 * @date		2015-04-27
 * @author		Benjamin Ellenberger
 */
class GroundController: public MotionController {
public:
	GroundController();
	virtual ~GroundController();
};

#endif /* GROUNDCONTROLLER_H_ */
