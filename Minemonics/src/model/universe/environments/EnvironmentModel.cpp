//# corresponding headers
#include <model/universe/environments/EnvironmentModel.hpp>

//# forward declarations
#ifndef NULL
#define NULL 0
#endif

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

EnvironmentModel::EnvironmentModel() :
		mEnvironmentPhysics(NULL), mPhysicsController(NULL) {

}

EnvironmentModel::~EnvironmentModel() {
	// TODO Auto-generated destructor stub
}

bool EnvironmentModel::isInWorld() {
	return false;
}

void EnvironmentModel::addToWorld() {
}

void EnvironmentModel::removeFromWorld() {
}
