/*
 * Evolution.cpp
 *
 *  Created on: Apr 28, 2015
 *      Author: leviathan
 */

#include <controller/evolution/Evolution.hpp>

Evolution::Evolution():mCurrentCreature(NULL),mEnvironment(NULL) {
	// TODO Auto-generated constructor stub

}

Evolution::~Evolution() {
	// TODO Auto-generated destructor stub
}

void Evolution::initialize(Environment* environment) {
	mEnvironment = environment;
}
