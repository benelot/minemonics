//# corresponding headers
#include <model/universe/evolution/population/creature/SRBcreature/phenome/SRBPhenomeModel.hpp>

//# forward declarations
//# system headers
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
#include <model/universe/evolution/population/creature/CreatureModel.hpp>
#include <model/universe/evolution/population/creature/genome/genetics/embryogenesis/BaseGenerator.hpp>
#include <model/universe/evolution/population/creature/genome/genetics/embryogenesis/PhenotypeGenerator.hpp>
#include <model/universe/evolution/population/creature/genome/Gene.hpp>
#include <model/universe/evolution/population/creature/genome/Genome.hpp>
#include <model/universe/evolution/population/creature/phenome/ComponentModel.hpp>
#include <model/universe/evolution/population/creature/SRBcreature/genome/genetics/embryogenesis/SRBEmbryogenesis.hpp>

//## view headers
//## utils headers

BoostLogger SRBPhenomeModel::mBoostLogger; /*<! initialize the boost logger*/
SRBPhenomeModel::_Init SRBPhenomeModel::_initializer;
SRBPhenomeModel::SRBPhenomeModel() {
	mControllers.clear();
}

SRBPhenomeModel::SRBPhenomeModel(const SRBPhenomeModel& SRBPhenomeModel) {
	mInWorld = SRBPhenomeModel.mInWorld;
	mCreatureModel = SRBPhenomeModel.mCreatureModel;
	mDeveloped = SRBPhenomeModel.mDeveloped;
	mHasInterpenetrations = SRBPhenomeModel.mHasInterpenetrations;

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
}

void SRBPhenomeModel::update(const double timeSinceLastTick) {
	//update all controllers
	for (std::vector<Controller*>::iterator cit = mControllers.begin();
		cit != mControllers.end(); cit++) {
		(*cit)->perform(timeSinceLastTick);
	}

//	std::vector<JointModel*>::iterator jit = mJointModels.begin();
//	for (; jit != mJointModels.end(); jit++) {
//		(*jit)->update(timeSinceLastTick);
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

void SRBPhenomeModel::calm() {
	for (std::vector<LimbModel*>::iterator lit = mLimbModels.begin();
		lit != mLimbModels.end(); lit++) {
		(*lit)->calm();
	}
}

int SRBPhenomeModel::performEmbryogenesis(CreatureModel* const creatureModel) {
	int totalSegmentCounter = 0;
	if (!mDeveloped) {
		cleanup();
		std::list<PhenotypeGenerator*> generatorList;

		mCreatureModel = creatureModel;

		// get the first gene from the genome
		Gene* gene = mCreatureModel->getGenotype().getGenes()[mCreatureModel->getGenotype().getRootIndex()];

		//create a phenotype generator and initialize it with the starting point of the creation of the creature
		PhenotypeGenerator* rootGenerator = new PhenotypeGenerator();
		std::map<int, int> repList;
		rootGenerator->initialize(repList, creatureModel->getInitialPosition(),
			Ogre::Quaternion().IDENTITY, NULL, NULL, 1);
		rootGenerator->setGene(gene);
		rootGenerator->setRoot2LeafPath(0);
		generatorList.push_back(rootGenerator);

		// this loop creates the creature up to the point at which we reach the correct root-to-leaf path length
		while (!generatorList.empty()) {

			BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)
				<< "Phenome generator qty:" << generatorList.size();

			PhenotypeGenerator* generator = generatorList.front();
			generatorList.pop_front();

			SRBEmbryogenesis::transcribeGene(generatorList, totalSegmentCounter,
				this, generator);

			// delete the generator of this gene
			delete generator;
		}

		mDeveloped = true;
	}
	return totalSegmentCounter;
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

SRBPhenomeModel* SRBPhenomeModel::clone() {
	return new SRBPhenomeModel(*this);
}
