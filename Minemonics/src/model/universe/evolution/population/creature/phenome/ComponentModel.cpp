//# corresponding headers
#include <model/universe/evolution/population/creature/phenome/ComponentModel.hpp>

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

ComponentModel::ComponentModel() :
		mType(UnknownComponent) {
}

ComponentModel::~ComponentModel() {
}

void ComponentModel::initialize(ComponentType type) {
	mType = type;
}

