//# corresponding headers
#include <model/universe/evolution/population/creature/phenome/SRBPhenomeModel.hpp>

#include <list>
#include <map>

//## controller headers
//## model headers
#include <OgreQuaternion.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
#include <model/universe/environments/EnvironmentModel.hpp>
#include <model/universe/environments/physics/PhysicsController.hpp>
#include <model/universe/evolution/population/creature/CreatureModel.hpp>
#include <model/universe/evolution/population/creature/genome/genetics/BaseGenerator.hpp>
#include <model/universe/evolution/population/creature/genome/genetics/PhenotypeGenerator.hpp>
#include <model/universe/evolution/population/creature/genome/genetics/SRBEmbryogenesis.hpp>
#include <model/universe/evolution/population/creature/genome/Gene.hpp>
#include <model/universe/evolution/population/creature/genome/Genome.hpp>
#include <model/universe/evolution/population/creature/phenome/ComponentModel.hpp>
#include <model/universe/evolution/population/PopulationModel.hpp>
#include <model/universe/PlanetModel.hpp>

//## view headers
//## utils headers

BoostLogger SRBPhenomeModel::mBoostLogger; /*<! initialize the boost logger*/
SRBPhenomeModel::_Init SRBPhenomeModel::_initializer;
SRBPhenomeModel::SRBPhenomeModel() :
	mWorld(NULL) {
}

SRBPhenomeModel::SRBPhenomeModel(CreatureModel* const creatureModel) {
	mCreatureModel = creatureModel;
	mWorld = creatureModel->getWorld();
}

SRBPhenomeModel::SRBPhenomeModel(const SRBPhenomeModel& SRBPhenomeModel) {
	mInWorld = SRBPhenomeModel.mInWorld;
	mCreatureModel = SRBPhenomeModel.mCreatureModel;
	mDeveloped = SRBPhenomeModel.mDeveloped;
	mHasInterpenetrations = SRBPhenomeModel.mHasInterpenetrations;

	mWorld = SRBPhenomeModel.mWorld;

	for (std::vector<Controller*>::const_iterator cit =
		SRBPhenomeModel.mControllers.begin();
		cit != SRBPhenomeModel.mControllers.end(); cit++) {
		mControllers.push_back((*cit)->clone());
	}

	for (std::vector<ComponentModel*>::const_iterator coit =
		SRBPhenomeModel.mComponentModels.begin();
		coit != SRBPhenomeModel.mComponentModels.end(); coit++) {
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

SRBPhenomeModel::~SRBPhenomeModel() {
	mWorld = NULL;
}

void SRBPhenomeModel::initialize() {

	performEmbryogenesis();

	//initialize the limb models if it did not already happen in embryogenesis
	for (std::vector<LimbModel*>::iterator lit = mLimbModels.begin();
		lit != mLimbModels.end(); lit++) {
		((SRBLimbModel*) (*lit))->setWorld(getWorld());
		(*lit)->initialize();
	}

	generateBody();
}

void SRBPhenomeModel::update(const double timeSinceLastTick) {
	//update all controllers
	for (std::vector<Controller*>::iterator cit = mControllers.begin();
		cit != mControllers.end(); cit++) {
		(*cit)->perform(timeSinceLastTick);
	}

// Update all limb models
	mHasInterpenetrations = false;
	for (std::vector<LimbModel*>::iterator lit = mLimbModels.begin();
		lit != mLimbModels.end(); lit++) {

		//detect interpenetrations
		if ((*lit)->getInterpenetrationDepth() < 0 && !mHasInterpenetrations) {

			mHasInterpenetrations = true;
			break;
		}
		(*lit)->setInterpenetrationDepth(0);
	}

}

void SRBPhenomeModel::calm() {
	for (std::vector<LimbModel*>::iterator lit = mLimbModels.begin();
		lit != mLimbModels.end(); lit++) {
		(*lit)->calm();
	}
}

int SRBPhenomeModel::performEmbryogenesis() {
	int totalSegmentCounter = 0;
	if (!mDeveloped) {
		cleanup();
		std::list<PhenotypeGenerator*> generatorList;

		// get the first gene from the genome
		Gene* gene =
			mCreatureModel->getGenotype().getGenes()[mCreatureModel->getGenotype().getRootIndex()];

		//create a phenotype generator and initialize it with the starting point of the creation of the creature
		PhenotypeGenerator* rootGenerator = new PhenotypeGenerator();
		std::map<int, int> repList;
		rootGenerator->initialize(repList, mCreatureModel->getInitialPosition(),
			Ogre::Quaternion().IDENTITY, NULL, NULL, 1);
		rootGenerator->setGene(gene);
		rootGenerator->setRoot2LeafPath(0);
		generatorList.push_back(rootGenerator);

		// this loop creates the creature up to the point at which we reach the correct root-to-leaf path length
		while (!generatorList.empty()) {

			BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info) << "Phenome generator qty:" << generatorList.size();

			PhenotypeGenerator* generator = generatorList.front();
			generatorList.pop_front();

			SRBEmbryogenesis::transcribeGene(generatorList, totalSegmentCounter,
				this, generator);

			// delete the generator of this gene
			delete generator;
		}

		mDeveloped = true;
	} else {
		mComponentModels.clear();
		for (std::vector<LimbModel*>::const_iterator it = mLimbModels.begin();
			it != mLimbModels.end(); it++) {
			mComponentModels.push_back((*it));
		}

		for (std::vector<JointModel*>::const_iterator it = mJointModels.begin();
			it != mJointModels.end(); it++) {
			mComponentModels.push_back((*it));
		}
	}
	return totalSegmentCounter;
}

void SRBPhenomeModel::generateBody() {
	bool isFixedBase = false;
	bool isMultiDof = true;
	bool setDamping = true;
	bool gyro = true;
	bool canSleep = true;

	if (mBodyGenerated) {
		return;
	}

	if (mJointModels.size() != 0) {

		for (int i = 0; i < mJointModels.size(); i++) {

			((SRBJointModel*) mJointModels[i])->setBodyA(
				((SRBLimbModel*) mLimbModels[((long) mJointModels[i]->getParentIndex())])->getRigidBody());

			((SRBJointModel*) mJointModels[i])->setFrameInA(
				mJointModels[i]->getParentComToPivot());

			((SRBJointModel*) mJointModels[i])->setBodyB(
				((SRBLimbModel*) mLimbModels[((long) mJointModels[i]->getChildIndex())])->getRigidBody());

			((SRBJointModel*) mJointModels[i])->setFrameInB(
				mJointModels[i]->getPivotToChildCom());

			BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Joint: Parent: " << mJointModels[i]->getParentIndex() << " /Child: "
			<< mJointModels[i]->getChildIndex();

			((SRBJointModel*) mJointModels[i])->setWorld(getWorld());

			mJointModels[i]->initialize();

//			for (std::vector<Motor*>::iterator mit =
//				mJointModels[i]->getMotors().begin();
//				mit != mJointModels[i]->getMotors().end(); mit++) {
//				((FSServoMotor*) (*mit))->instantiate(mMultiBody,
//					mJointModels[i]->getIndex());
//			}
		}
	}
}

void SRBPhenomeModel::reset(const Ogre::Vector3 position) {
	/**The vector of limb models.*/
	for (std::vector<LimbModel*>::const_iterator it = mLimbModels.begin();
		it != mLimbModels.end(); it++) {
		(*it)->reset(position);
	}
}

void SRBPhenomeModel::cleanup() {
	for (std::vector<ComponentModel*>::iterator cit = mComponentModels.begin();
		cit != mComponentModels.end();) {
		delete *cit;
		cit = mComponentModels.erase(cit);
	}
	mLimbModels.clear();
	mJointModels.clear();
}

void SRBPhenomeModel::reposition(const Ogre::Vector3 position) {
	/**The vector of limb models.*/
	for (std::vector<LimbModel*>::const_iterator it = mLimbModels.begin();
		it != mLimbModels.end(); it++) {
		(*it)->reposition(position);

	}
}

bool SRBPhenomeModel::equals(const SRBPhenomeModel& SRBPhenomeModel) const {
	if (mInWorld != SRBPhenomeModel.mInWorld) {
		return false;
	}

	if (mDeveloped != SRBPhenomeModel.mDeveloped) {
		return false;
	}

	/**The vector of limb models.*/
	if (mLimbModels.size() != SRBPhenomeModel.mLimbModels.size()) {
		return false;
	}
	std::vector<LimbModel*>::const_iterator it = mLimbModels.begin();
	std::vector<LimbModel*>::const_iterator it2 =
		SRBPhenomeModel.mLimbModels.begin();
	for (; it != mLimbModels.end(), it2 != SRBPhenomeModel.mLimbModels.end();
		it++, it2++) {
		if (!(*it)->equals(**(it2))) {
			return false;
		}
	}

	/**The vector of joint models.*/
	if (mJointModels.size() != SRBPhenomeModel.mJointModels.size()) {
		return false;
	}
	std::vector<JointModel*>::const_iterator it3 = mJointModels.begin();
	std::vector<JointModel*>::const_iterator it4 =
		SRBPhenomeModel.mJointModels.begin();
	for (; it3 != mJointModels.end(), it4 != SRBPhenomeModel.mJointModels.end();
		it3++, it4++) {
		if (!(*it3)->equals(**(it4))) {
			return false;
		}
	}

	/**The vector of controllers.*/
	if (mControllers.size() != SRBPhenomeModel.mControllers.size()) {
		return false;
	}
	std::vector<Controller*>::const_iterator it5 = mControllers.begin();
	std::vector<Controller*>::const_iterator it6 =
		SRBPhenomeModel.mControllers.begin();
	for (; it5 != mControllers.end(), it6 != SRBPhenomeModel.mControllers.end();
		it5++, it6++) {
		if (!(*it5)->equals(**(it6))) {
			return false;
		}
	}
	return true;
}

void SRBPhenomeModel::addToWorld() {
	if (!isInWorld()) {

	}
}

void SRBPhenomeModel::removeFromWorld() {
	if (isInWorld()) {

	}
}

PhenomeModel* SRBPhenomeModel::clone() {
	return new SRBPhenomeModel(*this);
}

btDynamicsWorld* SRBPhenomeModel::getWorld() {
	if (!mWorld) {
#ifndef EXCLUDE_FROM_TEST
		mWorld = (btDynamicsWorld*) mCreatureModel->getWorld();
#endif
	}
	return mWorld;

}
