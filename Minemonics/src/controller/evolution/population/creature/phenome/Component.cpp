/*
 * Component.cpp
 *
 *  Created on: Mar 23, 2015
 *      Author: leviathan
 */

#include "Component.h"

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

