//# corresponding headers
//# forward declarations
//# system headers
//## controller headers
#include <controller/universe/evolution/population/creature/phenome/Component.hpp>

//## model headers
#include <model/universe/evolution/population/creature/phenome/ComponentModel.hpp>

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
}

void Component::initialize(ComponentModel* const componentModel) {

	mComponentModel = componentModel;
}

