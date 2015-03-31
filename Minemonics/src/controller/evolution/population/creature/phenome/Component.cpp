/*
 * Component.cpp
 *
 *  Created on: Mar 23, 2015
 *      Author: leviathan
 */

//# corresponding header
#include "Component.h"

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

Component::Component() :
		mComponentType(UnknownComponent) {
	// TODO Auto-generated constructor stub

}

Component::~Component() {
	// TODO Auto-generated destructor stub
}

void Component::initialize(ComponentType componentType) {
	mComponentType = componentType;
}

