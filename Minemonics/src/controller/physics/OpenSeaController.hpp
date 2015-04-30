/*
 * OpenSeaController.h
 *
 *  Created on: Nov 17, 2014
 *      Author: leviathan
 */

#ifndef OPENSEACONTROLLER_H_
#define OPENSEACONTROLLER_H_

//# corresponding header
#include <controller/physics/MotionController.hpp>

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
class OpenSeaController: public MotionController {
public:
	OpenSeaController();
	virtual ~OpenSeaController();
};

#endif /* OPENSEACONTROLLER_H_ */
