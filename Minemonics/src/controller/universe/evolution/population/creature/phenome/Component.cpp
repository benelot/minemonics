//# corresponding headers
#include <controller/universe/evolution/population/creature/phenome/Component.hpp>

//# forward declarations
//# system headers
//## controller headers
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
	delete mComponentModel;
	mComponentModel = NULL;
}

void Component::initialize(ComponentModel* const componentModel) {

	mComponentModel = componentModel;
}

