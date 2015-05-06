//# corresponding headers
#include <model/universe/evolution/population/creature/phenome/PhenomeModel.hpp>

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

PhenomeModel::PhenomeModel() :
		inWorld(false) {
	mControllers.clear();
}

PhenomeModel::~PhenomeModel() {
	mControllers.clear();
}

void PhenomeModel::update(double totalMilliseconds) {
	std::vector<Controller*>::iterator cit = mControllers.begin();
	for (; cit != mControllers.end(); cit++) {
		(*cit)->perform(totalMilliseconds);
	}
}
