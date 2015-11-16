//# corresponding headers
#include <model/universe/evolution/population/creature/genome/controller/ControllerGene.hpp>

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

ControllerGene::ControllerGene() :
	mControllerType(GenericControllerGene) {

}

ControllerGene::ControllerGene(ControllerType type) :
	mControllerType(type) {

}

ControllerGene::~ControllerGene() {
}

bool ControllerGene::equals(const ControllerGene& controllerGene) const {

	if (mControllerType != controllerGene.mControllerType) {
		return false;
	}

	return true;
}

