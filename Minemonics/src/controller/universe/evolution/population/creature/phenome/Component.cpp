//# corresponding headers
#include <controller/universe/evolution/population/creature/phenome/Component.hpp>

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
	mComponentModel(NULL) {
}

Component::~Component() {
	//The componentmodel is killed in the specific component
	mComponentModel = NULL;
}

void Component::initialize(ComponentModel* const componentModel) {

	mComponentModel = componentModel;
}

const ComponentModel::ComponentType Component::getComponentType() {
		return mComponentModel->getComponentType();
	}
