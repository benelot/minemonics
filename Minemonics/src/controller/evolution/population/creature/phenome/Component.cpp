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
}

Component::~Component() {
}

void Component::initialize(ComponentType componentType) {
	mComponentType = componentType;
}

