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
	// TODO Auto-generated constructor stub

}

PlaneModel::~PlaneModel() {
	// TODO Auto-generated destructor stub
}

void PlaneModel::initialize() {
	mEnvironmentPhysics = new PlaneBt();
	((PlaneBt*) mEnvironmentPhysics)->initialize();
}
