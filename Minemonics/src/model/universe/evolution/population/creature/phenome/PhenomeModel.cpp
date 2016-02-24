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

void PhenomeModel::perturbControllers(){
	// store the control indices of the controllers
	for (std::vector<Controller*>::iterator cit = mControllers.begin();
		cit != mControllers.end(); cit++) {
		(*cit)->perturb();
	}
}

void PhenomeModel::calm() {
	for (std::vector<LimbModel*>::iterator lit = mLimbModels.begin();
		lit != mLimbModels.end(); lit++) {
		(*lit)->calm();
	}
}

void PhenomeModel::collectControlInputs() {
	mControlInputs.clear();

	// collect control inputs from the limbs
	for (std::vector<LimbModel*>::iterator lit = mLimbModels.begin();
		lit != mLimbModels.end(); lit++) {
		std::vector<ControlInput*> mLimbControlInputs =
			(*lit)->getControlInputs();
		mControlInputs.insert(mControlInputs.end(), mLimbControlInputs.begin(),
			mLimbControlInputs.end());
	}

	// collect the control inputs from the controllers
	for (std::vector<Controller*>::iterator cit = mControllers.begin();
		cit != mControllers.end(); cit++) {
		mControlInputs.push_back(*cit);
	}

	// collect the control inputs from the joints
	for (std::vector<JointModel*>::const_iterator jit = mJointModels.begin();
		jit != mJointModels.end(); jit++) {
		std::vector<ControlInput*> mJointControlInputs =
			(*jit)->getControlInputs();
		mControlInputs.insert(mControlInputs.end(), mJointControlInputs.begin(),
			mJointControlInputs.end());
	}

	// set the vector index to be the control input
	for (int i = 0; i < mControlInputs.size(); i++) {
		mControlInputs[i]->setOwnControlInputIndex(i);
	}
}

void PhenomeModel::collectControlOutputs() {
	mControlOutputs.clear();

	// collect the control outputs from the limbs
	for (std::vector<LimbModel*>::iterator lit = mLimbModels.begin();
		lit != mLimbModels.end(); lit++) {
		std::vector<ControlOutput*> mLimbControlOutputs =
			(*lit)->getControlOutputs();
		mControlOutputs.insert(mControlOutputs.end(),
			mLimbControlOutputs.begin(), mLimbControlOutputs.end());

	}

	// collect the control outputs from the controllers
	for (std::vector<Controller*>::iterator cit = mControllers.begin();
		cit != mControllers.end(); cit++) {
		mControlOutputs.push_back(*cit);
	}

	// collect the control outputs from the joints
	for (std::vector<JointModel*>::const_iterator jit = mJointModels.begin();
		jit != mJointModels.end(); jit++) {
		std::vector<ControlOutput*> mJointControlOutputs =
			(*jit)->getControlOutputs();
		mControlOutputs.insert(mControlOutputs.end(),
			mJointControlOutputs.begin(), mJointControlOutputs.end());
	}

	for (int i = 0; i < mControlOutputs.size(); i++) {
		mControlOutputs[i]->setOwnControlOutputIndex(i);
	}
}

void PhenomeModel::wireController() {

	// wire the limbs
	for (std::vector<LimbModel*>::iterator lit = mLimbModels.begin();
		lit != mLimbModels.end(); lit++) {
		(*lit)->setControlInputs(mControlOutputs);
		(*lit)->setControlOutputs(mControlInputs);
	}

	// wire the controllers
	for (std::vector<Controller*>::iterator cit = mControllers.begin();
		cit != mControllers.end(); cit++) {
		(*cit)->setControlInputs(mControlOutputs);
		(*cit)->setControlOutputs(mControlInputs);
	}

	// wire the joints
	for (std::vector<JointModel*>::const_iterator jit = mJointModels.begin();
		jit != mJointModels.end(); jit++) {
		(*jit)->setControlInputs(mControlOutputs);
		(*jit)->setControlOutputs(mControlInputs);
	}
}

void PhenomeModel::storeControlIndices() {

	// store the control indices of the limbs
	for (std::vector<LimbModel*>::iterator lit = mLimbModels.begin();
		lit != mLimbModels.end(); lit++) {
		(*lit)->storeControlIndices();
	}

	// store the control indices of the controllers
	for (std::vector<Controller*>::iterator cit = mControllers.begin();
		cit != mControllers.end(); cit++) {
		(*cit)->storeControlIndices();
	}

	// store the control indices of the joints
	for (std::vector<JointModel*>::const_iterator jit = mJointModels.begin();
		jit != mJointModels.end(); jit++) {
		(*jit)->storeControlIndices();
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

Ogre::Vector3 PhenomeModel::getLowestRelativePoint() {
	Ogre::Vector3 lowestPoint =
		(*mLimbModels.begin())->getInitialRelativePosition();
	for (std::vector<LimbModel*>::iterator lit = mLimbModels.begin();
		lit != mLimbModels.end(); lit++) {
		// find lowest relative position (COM) and approximate the lowest point by subtracting half dimension length
		if (lowestPoint.y
			> (*lit)->getInitialRelativePosition().y
				- 0.5f * (*lit)->getDimensions().length()) {
			lowestPoint = (*lit)->getInitialRelativePosition();
			lowestPoint.y -= 0.5f * (*lit)->getDimensions().length();
		}
	}
	return lowestPoint;
}

std::vector<const DataSink*> PhenomeModel::getControllerDataSinks() {
	std::vector<const DataSink*> datasinks;
	for (std::vector<Controller*>::iterator cit = mControllers.begin();
		cit != mControllers.end(); cit++) {
		datasinks.push_back((*cit)->getDataSink());
	}

	std::cout << "Number of controllers: " << mControllers.size() << std::endl;

	return datasinks;
}

std::vector<const DataSink*> PhenomeModel::getJointDataSinks() {
	std::vector<const DataSink*> datasinks;

	for (std::vector<JointModel*>::iterator jit = mJointModels.begin();
		jit != mJointModels.end(); jit++) {
		datasinks.push_back((*jit)->getDataSinkPitch());
		datasinks.push_back((*jit)->getDataSinkYaw());
		datasinks.push_back((*jit)->getDataSinkRoll());
	}

	std::cout << "Number of sensors: " << mJointModels.size() * 3 << std::endl;
	return datasinks;
}

std::vector<const DataSink*> PhenomeModel::getDataSinks() {
	std::vector<const DataSink*> datasinks;
	std::vector<const DataSink*> controllerDatasinks = getControllerDataSinks();
	datasinks.insert(datasinks.begin(), controllerDatasinks.begin(),
		controllerDatasinks.end());

	std::vector<const DataSink*> jointDatasinks = getJointDataSinks();
	datasinks.insert(datasinks.begin(), jointDatasinks.begin(),
		jointDatasinks.end());

	return datasinks;
}

double PhenomeModel::getMaxJointVelocity() {
	double maxJointVelocity = 0;
	for (std::vector<JointModel*>::iterator jit = mJointModels.begin();
		jit != mJointModels.end(); jit++) {
		//TODO: time 0 only works for FS model
		double jointVelocity = (*jit)->getJointVel((*jit)->getIndex(), 0, 0);
		if (jointVelocity > maxJointVelocity) {
			maxJointVelocity = jointVelocity;
		}
	}
	return maxJointVelocity;
}
