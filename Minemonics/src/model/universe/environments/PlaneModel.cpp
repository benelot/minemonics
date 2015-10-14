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

PlaneModel::PlaneModel(PhysicsController::PhysicsModelType type){
	mType = EnvironmentModel::PLANE;

	mEnvironmentPhysics = new PlaneBt();
	// set up the physics controller
	mPhysicsController = new GroundController(type);
}

PlaneModel::~PlaneModel() {
}

void PlaneModel::initialize() {
	getPlaneBt()->initialize();
}

void PlaneModel::update(double timeSinceLastTick) {
	mEnvironmentPhysics->update(timeSinceLastTick);
}
