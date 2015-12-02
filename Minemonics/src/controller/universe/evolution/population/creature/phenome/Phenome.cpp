//# corresponding header
#include <controller/universe/evolution/population/creature/phenome/Phenome.hpp>

//# forward declarations
//# system headers
#include <cstdlib>

//## controller headers
//## model headers
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <configuration/MorphologyConfiguration.hpp>

//## view headers
//## custom headers
//# base headers
#include <SimulationManager.hpp>

//## configuration headers
#include <configuration/PhysicsConfiguration.hpp>

//## controller headers
#include <controller/universe/evolution/population/creature/Creature.hpp>
#include <controller/universe/evolution/population/creature/phenome/Phenome.hpp>

//## model headers
#include <model/universe/evolution/population/creature/phenome/morphology/joint/JointModel.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/limb/LimbModel.hpp>

//## view headers
#include <view/universe/evolution/population/creature/phenome/morphology/limb/LimbO3D.hpp>

//## utils headers

BoostLogger Phenome::mBoostLogger; /*<! initialize the boost logger*/
Phenome::_Init Phenome::_initializer;
Phenome::Phenome() :
	mCreature(NULL), mPhenotypeModel(NULL) {

}

Phenome::Phenome(const Phenome& phenome) {

	mCreature = phenome.mCreature;
	mPhenotypeModel = phenome.mPhenotypeModel;

	std::vector<Component*>::const_iterator coit = phenome.mComponents.begin();
	for (; coit != phenome.mComponents.end(); coit++) {
		Component* component = (*coit)->clone();
		mComponents.push_back(component);
		switch (component->getComponentType()) {
		case ComponentModel::LimbComponent:
			mLimbs.push_back((Limb*) component);
			break;
		case ComponentModel::JointComponent:
			mJoints.push_back((Joint*) component);
			break;
		}
	}
}

Phenome::~Phenome() {
	for (std::vector<Component*>::iterator cit = mComponents.begin();
		cit != mComponents.end();cit++) {
		delete (*cit);
	}
	mComponents.clear();
	mLimbs.clear();
	mJoints.clear();

	mPhenotypeModel = NULL;

	mCreature = NULL;
}

void Phenome::initialize(Creature* const creature) {
	mCreature = creature;
	performEmbryogenesis();
}

/**
 * Performs the embryogenesis of a genome. We follow each part of the tree with the phenotype generators.
 * @param creatureModel the handle to the creatureModel we want to get back from the physics engine when we pick a creature.
 */
int Phenome::performEmbryogenesis() {
	cleanup();
	//perform the embryogenesis in the model
	mPhenotypeModel->initialize();
	int limbQty = mPhenotypeModel->getLimbModels().size();

	if (limbQty == 0) {
		return limbQty;
	}

	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info) << "--Synchronize the creature from the model to the controller";
	// iterate over all the component models
	for (std::vector<ComponentModel*>::const_iterator cmit =
		mPhenotypeModel->getComponentModels().begin();
		cmit != mPhenotypeModel->getComponentModels().end(); cmit++) {

		switch ((*cmit)->getComponentType()) {
		case ComponentModel::LimbComponent: {
			Limb* limb = new Limb(mCreature, (LimbModel*) *cmit);
			mLimbs.push_back(limb);
			mComponents.push_back(limb);
			break;
		}
		case ComponentModel::JointComponent: {
			Joint* joint = new Joint(((JointModel*) *cmit));
			mJoints.push_back(joint);
			mComponents.push_back(joint);
			break;
		}
		case ComponentModel::UnknownComponent:
		default:
			BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::fatal) << "Unknown component found";
			exit(-1);
		}
	}
	return limbQty;
}

void Phenome::update(double timeSinceLastTick) {

	// Update all limbs
	for (std::vector<Limb*>::iterator lit = mLimbs.begin(); lit != mLimbs.end();
		lit++) {
		(*lit)->update(timeSinceLastTick);
	}

	// Update all constraints
	for (std::vector<Joint*>::iterator jit = mJoints.begin();
		jit != mJoints.end(); jit++) {
		(*jit)->update(timeSinceLastTick);
	}

	mPhenotypeModel->update(timeSinceLastTick);
}

int Phenome::addToPhysicsWorld() {
	int limbQty = 0;
	mPhenotypeModel->addToWorld();
	if (!isInWorld()) {
		// Add all limbs
		for (std::vector<Limb*>::iterator lit = mLimbs.begin();
			lit != mLimbs.end(); lit++) {
			(*lit)->addToPhysicsWorld();
			limbQty++;
		}

		// Add all constraints
		for (std::vector<Joint*>::iterator jit = mJoints.begin();
			jit != mJoints.end(); jit++) {
			(*jit)->addToPhysicsWorld();
		}
		setInWorld(true);
	}
	return limbQty;
}

int Phenome::addToWorld() {
	int limbQty = 0;
	mPhenotypeModel->addToWorld();
	if (!isInWorld()) {
		// Add all limbs
		for (std::vector<Limb*>::iterator lit = mLimbs.begin();
			lit != mLimbs.end(); lit++) {
			(*lit)->addToWorld();
			limbQty++;
		}

		// Add all constraints
		for (std::vector<Joint*>::iterator jit = mJoints.begin();
			jit != mJoints.end(); jit++) {
			(*jit)->addToWorld();
		}
		setInWorld(true);
	}
	return limbQty;
}

void Phenome::removeFromWorld() {
	mPhenotypeModel->removeFromWorld();
	if (isInWorld()) {
		// Remove all constraints
		for (std::vector<Joint*>::iterator jit = mJoints.begin();
			jit != mJoints.end(); jit++) {
			(*jit)->removeFromWorld();
		}

		// Remove all limbs
		for (std::vector<Limb*>::iterator lit = mLimbs.begin();
			lit != mLimbs.end(); lit++) {
			(*lit)->removeFromWorld();
		}
		setInWorld(false);
	}
}

void Phenome::cleanup() {
	for (std::vector<Component*>::iterator cit = mComponents.begin();
		cit != mComponents.end();) {
		delete *cit;
		cit = mComponents.erase(cit);
	}
	mLimbs.clear();
	mJoints.clear();

}

void Phenome::reset(const Ogre::Vector3 position) {
	mPhenotypeModel->reset(position);
}

void Phenome::reposition(const Ogre::Vector3 position) {
	mPhenotypeModel->reposition(position);

	// reset all constraints
	for (std::vector<Joint*>::iterator jit = mJoints.begin();
		jit != mJoints.end(); jit++) {
		(*jit)->reposition(position);
	}

	// reset all limbs
	for (std::vector<Limb*>::iterator lit = mLimbs.begin(); lit != mLimbs.end();
		lit++) {
		(*lit)->reposition(position);
	}
}

Phenome* Phenome::clone() {
	return new Phenome(*this);
}

/**
	 * Is the phenotype in the world?
	 * @return
	 */
	bool Phenome::isInWorld() const {
		return mPhenotypeModel->isInWorld();
	}

	/**
	 * Set whether the phenotype is in the world or not.
	 * @param inWorld Whether the phenotype is in the world or not.
	 */
	void Phenome::setInWorld(bool inWorld) {
		mPhenotypeModel->setInWorld(inWorld);
	}

	bool Phenome::isDeveloped() const {
		return mPhenotypeModel->isDeveloped();
	}

	void Phenome::setDeveloped(bool developed) {
		mPhenotypeModel->setDeveloped(developed);
	}
