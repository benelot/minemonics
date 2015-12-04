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
#include <model/universe/evolution/population/creature/CreatureModel.hpp>
#include <model/universe/evolution/population/creature/phenome/ComponentModel.hpp>

//## view headers
//## utils headers

BoostLogger PhenomeModel::mBoostLogger; /*<! initialize the boost logger*/
PhenomeModel::_Init PhenomeModel::_initializer;

PhenomeModel::PhenomeModel() :
	mCreatureModel(NULL), mInWorld(false), mDeveloped(false), mHasInterpenetrations(
		false), mBodyGenerated(false) {
}

PhenomeModel::PhenomeModel(CreatureModel* const creatureModel) :
	mCreatureModel(creatureModel), mInWorld(false), mDeveloped(false), mHasInterpenetrations(
		false), mBodyGenerated(false) {
}

PhenomeModel::PhenomeModel(const PhenomeModel& phenomeModel) {
	mInWorld = phenomeModel.mInWorld;
	mCreatureModel = phenomeModel.mCreatureModel;
	mDeveloped = phenomeModel.mDeveloped;
	mHasInterpenetrations = phenomeModel.mHasInterpenetrations;

	for (std::vector<Controller*>::const_iterator cit =
		phenomeModel.mControllers.begin();
		cit != phenomeModel.mControllers.end(); cit++) {
		mControllers.push_back((*cit)->clone());
	}

	for (std::vector<ComponentModel*>::const_iterator coit =
		phenomeModel.mComponentModels.begin();
		coit != phenomeModel.mComponentModels.end(); coit++) {
		ComponentModel* componentModel = (*coit)->clone();
		mComponentModels.push_back(componentModel);
		switch (componentModel->getComponentType()) {
		case ComponentModel::LimbComponent:
			mLimbModels.push_back((LimbModel*) componentModel);
			break;
		case ComponentModel::JointComponent:
			mJointModels.push_back((JointModel*) componentModel);
			break;

		}
	}
	mBodyGenerated = phenomeModel.mBodyGenerated;
}

PhenomeModel::~PhenomeModel() {

	for (std::vector<ComponentModel*>::const_iterator cit =
		mComponentModels.begin(); cit != mComponentModels.end(); cit++) {
		delete (*cit);
	}

	mComponentModels.clear();
	mLimbModels.clear();
	mJointModels.clear();

	for (std::vector<Controller*>::const_iterator cit = mControllers.begin();
		cit != mControllers.end(); cit++) {
		delete (*cit);
	}

	mControllers.clear();
}

void PhenomeModel::calm() {
	for (std::vector<LimbModel*>::iterator lit = mLimbModels.begin();
		lit != mLimbModels.end(); lit++) {
		(*lit)->calm();
	}
}

void PhenomeModel::collectControlInputs() {
	for (std::vector<LimbModel*>::iterator lit = mLimbModels.begin();
		lit != mLimbModels.end(); lit++) {
		std::vector<ControlInput*> mLimbControlInputs = (*lit)->getControlInputs();
		mControlInputs.insert(mControlInputs.end(),mLimbControlInputs.begin(),mLimbControlInputs.end());
	}

	for (std::vector<Controller*>::iterator cit = mControllers.begin();
		cit != mControllers.end(); cit++) {
		mControlInputs.push_back(*cit);
	}

	for (std::vector<JointModel*>::const_iterator jit = mJointModels.begin();
		jit != mJointModels.end(); jit++) {
		std::vector<ControlInput*> mJointControlInputs = (*jit)->getControlInputs();
		mControlInputs.insert(mControlInputs.end(),mJointControlInputs.begin(),mJointControlInputs.end());
	}
}

void PhenomeModel::collectControlOutputs() {
	for (std::vector<LimbModel*>::iterator lit = mLimbModels.begin();
		lit != mLimbModels.end(); lit++) {
		std::vector<ControlOutput*> mLimbControlOutputs = (*lit)->getControlOutputs();
		mControlOutputs.insert(mControlOutputs.end(),mLimbControlOutputs.begin(),mLimbControlOutputs.end());

	}

	for (std::vector<Controller*>::iterator cit = mControllers.begin();
		cit != mControllers.end(); cit++) {
		mControlOutputs.push_back(*cit);
	}

	for (std::vector<JointModel*>::const_iterator jit = mJointModels.begin();
		jit != mJointModels.end(); jit++) {
		std::vector<ControlOutput*> mJointControlOutputs = (*jit)->getControlOutputs();
		mControlOutputs.insert(mControlOutputs.end(),mJointControlOutputs.begin(),mJointControlOutputs.end());
	}
}

void PhenomeModel::wireController(){
	for (std::vector<LimbModel*>::iterator lit = mLimbModels.begin();
		lit != mLimbModels.end(); lit++) {
		for(std::vector<int>::const_iterator iit = (*lit)->getControlInputIndices().begin();iit !=(*lit)->getControlInputIndices().end();iit++){
			//TODO: Add control inputs when the limb needs them
		}

		for(std::vector<int>::const_iterator iit = (*lit)->getControlOutputIndices().begin();iit !=(*lit)->getControlOutputIndices().end();iit++){
			//TODO:: Add control outputs when the limb needs them
		}
	}

	for (std::vector<Controller*>::iterator cit = mControllers.begin();
		cit != mControllers.end(); cit++) {
		for(std::vector<int>::const_iterator iit = (*cit)->getControlInputIndices().begin();iit !=(*cit)->getControlInputIndices().end();iit++){
			(*cit)->addControlInput(mControlOutputs[*iit]);
		}

		for(std::vector<int>::const_iterator iit = (*cit)->getControlOutputIndices().begin();iit !=(*cit)->getControlOutputIndices().end();iit++){
			(*cit)->addControlOutput(mControlInputs[*iit]);
		}
	}

	for (std::vector<JointModel*>::const_iterator jit = mJointModels.begin();
		jit != mJointModels.end(); jit++) {
		for(std::vector<int>::const_iterator iit = (*jit)->getControlInputIndices().begin();iit !=(*jit)->getControlInputIndices().end();iit++){
			//TODO: Add control inputs when the joint needs them
		}

		for(std::vector<int>::const_iterator iit = (*jit)->getControlOutputIndices().begin();iit !=(*jit)->getControlOutputIndices().end();iit++){
			//TODO:: Add control outputs when the joint needs them
		}
	}
}

bool PhenomeModel::equals(const PhenomeModel& phenomeModel) const {
	if (mInWorld != phenomeModel.mInWorld) {
		return false;
	}

	if (mDeveloped != phenomeModel.mDeveloped) {
		return false;
	}

	/**The vector of limb models.*/
	if (mLimbModels.size() != phenomeModel.mLimbModels.size()) {
		return false;
	}
	std::vector<LimbModel*>::const_iterator it = mLimbModels.begin();
	std::vector<LimbModel*>::const_iterator it2 =
		phenomeModel.mLimbModels.begin();
	for (; it != mLimbModels.end(), it2 != phenomeModel.mLimbModels.end();
		it++, it2++) {
		if (!(*it)->equals(**(it2))) {
			return false;
		}
	}

	/**The vector of joint models.*/
	if (mJointModels.size() != phenomeModel.mJointModels.size()) {
		return false;
	}
	std::vector<JointModel*>::const_iterator it3 = mJointModels.begin();
	std::vector<JointModel*>::const_iterator it4 =
		phenomeModel.mJointModels.begin();
	for (; it3 != mJointModels.end(), it4 != phenomeModel.mJointModels.end();
		it3++, it4++) {
		if (!(*it3)->equals(**(it4))) {
			return false;
		}
	}

	/**The vector of controllers.*/
	if (mControllers.size() != phenomeModel.mControllers.size()) {
		return false;
	}
	std::vector<Controller*>::const_iterator it5 = mControllers.begin();
	std::vector<Controller*>::const_iterator it6 =
		phenomeModel.mControllers.begin();
	for (; it5 != mControllers.end(), it6 != phenomeModel.mControllers.end();
		it5++, it6++) {
		if (!(*it5)->equals(**(it6))) {
			return false;
		}
	}
	return true;
}
