/*
 * Component.cpp
 *
 *  Created on: Mar 23, 2015
 *      Author: leviathan
 */

//# corresponding header
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
#include <model/universe/evolution/population/creature/phenome/morphology/limb/LimbModel.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/joint/JointModel.hpp>

//## view headers
//## utils headers

Component::Component() :
		mComponentModel(NULL) {
}

Component::~Component() {
}

void Component::initialize(ComponentModel::ComponentType componentType) {
	switch (componentType) {
	case ComponentModel::LimbComponent: {
		mComponentModel = new LimbModel();
		break;
	}
	case ComponentModel::JointComponent: {
		mComponentModel = new JointModel();
		break;
	}
	default:
		break;
	}
	mComponentModel->initialize(componentType);
}

