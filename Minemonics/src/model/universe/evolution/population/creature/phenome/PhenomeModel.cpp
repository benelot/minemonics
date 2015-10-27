//# corresponding headers
#include <model/universe/evolution/population/creature/phenome/PhenomeModel.hpp>

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
#include <model/universe/evolution/population/creature/genome/genetics/BaseGenerator.hpp>
#include <model/universe/evolution/population/creature/genome/genetics/PhenotypeGenerator.hpp>
#include <model/universe/evolution/population/creature/genome/Gene.hpp>
#include <model/universe/evolution/population/creature/genome/Genome.hpp>
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
		false),mBodyGenerated(false) {
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

	for (std::vector<ComponentModel*>::const_iterator cit = mComponentModels.begin();
		cit != mComponentModels.end(); cit++) {
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
