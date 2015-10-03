//# corresponding headers
#include <model/universe/environments/PlaneModel.hpp>

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
#include <model/universe/environments/bullet/PlaneBt.hpp>

//## view headers
//## utils headers

PlaneModel::PlaneModel() {
}

PlaneModel::~PlaneModel() {
	delete mEnvironmentPhysics;
	mEnvironmentPhysics = NULL;
}

void PlaneModel::initialize() {
	mEnvironmentPhysics = new PlaneBt();
	getPlaneBt()->initialize();
}

void PlaneModel::update(double timeSinceLastTick) {
	mEnvironmentPhysics->update(timeSinceLastTick);
}
