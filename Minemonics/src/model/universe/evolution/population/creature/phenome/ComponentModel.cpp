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
		mComponentType(UnknownComponent), mOwnIndex(-1) {
}

ComponentModel::~ComponentModel() {
}

void ComponentModel::initialize(const ComponentType type, const int ownIndex) {
	mComponentType = type;
	mOwnIndex = ownIndex;
}

