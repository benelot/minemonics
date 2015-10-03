//# corresponding headers
#include <model/universe/evolution/population/creature/phenome/PhenomeModel.hpp>
#include <configuration/Definitions.hpp>
//# forward declarations
//# system headers
#include <list>
#include <map>

//## controller headers
//## model headers
#include <BulletCollision/NarrowPhaseCollision/btRaycastCallback.h>
#include <OgreQuaternion.h>

//## view headers
//# custom headers
//## base headers
#include <SimulationManager.hpp>

//## configuration headers
//## controller headers
//## model headers
#include <model/universe/PlanetModel.hpp>
#include <model/universe/environments/EnvironmentModel.hpp>
#include <model/universe/environments/physics/PhysicsController.hpp>
#include <model/universe/evolution/population/PopulationModel.hpp>
#include <model/universe/evolution/population/creature/CreatureModel.hpp>
#include <model/universe/evolution/population/creature/genome/genetics/embryogenesis/BaseGenerator.hpp>
#include <model/universe/evolution/population/creature/genome/genetics/embryogenesis/PhenotypeGenerator.hpp>
#include <model/universe/evolution/population/creature/genome/Gene.hpp>
#include <model/universe/evolution/population/creature/genome/Genome.hpp>
#include <model/universe/evolution/population/creature/phenome/ComponentModel.hpp>

//## view headers
//## utils headers

BoostLogger PhenomeModel::mBoostLogger; /*<! initialize the boost logger*/
PhenomeModel::_Init PhenomeModel::_initializer;
PhenomeModel::PhenomeModel() :
	mCreatureModel(NULL), mInWorld(false), mDeveloped(false), mHasInterpenetrations(
		true) {
	mControllers.clear();
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
}

PhenomeModel::~PhenomeModel() {
	for (std::vector<ComponentModel*>::const_iterator coit =
		mComponentModels.begin(); coit != mComponentModels.end(); coit++) {
		switch ((*coit)->getComponentType()) {
		case ComponentModel::LimbComponent:
			delete ((LimbModel*) *coit);
			break;
		case ComponentModel::JointComponent:
			delete ((JointModel*) *coit);
			break;

		}
	}

	mComponentModels.clear();

	for (std::vector<Controller*>::const_iterator cit = mControllers.begin();
		cit != mControllers.end(); cit++) {
		delete (*cit);
	}

	mControllers.clear();
}

void PhenomeModel::initialize(CreatureModel* const creatureModel) {
	mCreatureModel = creatureModel;
}

void PhenomeModel::update(const double timeSinceLastTick) {
	//update all controllers
	//TODO: Hacks to make it run, make nicer
	// let the controller perform
	for (std::vector<Controller*>::iterator cit = mControllers.begin();
		cit != mControllers.end(); cit++) {
		(*cit)->perform(timeSinceLastTick);
	}

//	std::vector<JointModel*>::iterator jit = mJointModels.begin();
//	for (; jit != mJointModels.end(); jit++) {
//		(*jit)->update(timeSinceLastTick);
//	}

//	// test for strains
	//TODO: Remove if not used
//	std::vector<JointModel*>::iterator jit = mJointModels.begin();
//	for (; jit != mJointModels.end(); jit++) {
//		(*jit)->isStrained();
//	}

	// Update all limb models
	mHasInterpenetrations = false;
	for (std::vector<LimbModel*>::iterator lit = mLimbModels.begin();
		lit != mLimbModels.end(); lit++) {

		//detect interpenetrations
		if ((*lit)->getInterpenetrationDepth() < 0 && !mHasInterpenetrations) {

//			std::cout << "Limb interpenetration depth: "
//					<< (*lit)->getInterpenetrationDepth()
//					<< std::endl;
			mHasInterpenetrations = true;
			break;
		}
		(*lit)->setInterpenetrationDepth(0);
	}

}

void PhenomeModel::calm() {
	for (std::vector<LimbModel*>::iterator lit = mLimbModels.begin();
		lit != mLimbModels.end(); lit++) {
		(*lit)->calm();
	}
}

void PhenomeModel::reset(const Ogre::Vector3 position) {
	/**The vector of limb models.*/
	for (std::vector<LimbModel*>::const_iterator it = mLimbModels.begin();
		it != mLimbModels.end(); it++) {
		(*it)->reset(position);
	}
}

void PhenomeModel::cleanup() {
	for (std::vector<ComponentModel*>::iterator cit = mComponentModels.begin();
		cit != mComponentModels.end();) {
		delete *cit;
		cit = mComponentModels.erase(cit);
	}
	mLimbModels.clear();
	mJointModels.clear();
}

void PhenomeModel::reposition(const Ogre::Vector3 position) {
	/**The vector of limb models.*/
	for (std::vector<LimbModel*>::const_iterator it = mLimbModels.begin();
		it != mLimbModels.end(); it++) {
		(*it)->reposition(position);

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

void PhenomeModel::addToWorld() {
}

void PhenomeModel::removeFromWorld() {
}
