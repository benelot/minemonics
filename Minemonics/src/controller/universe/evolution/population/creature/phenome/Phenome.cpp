//# corresponding header
//# forward declarations
//# system headers
#include <vector>
#include <map>

//## controller headers
//## model headers
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

//## view headers
//# custom headers
//## base headers
#include <SimulationManager.hpp>

//## configuration headers
#include <configuration/MorphologyConfiguration.hpp>
#include <configuration/PhysicsConfiguration.hpp>

//## model headers
#include <model/universe/evolution/population/creature/genome/morphology/Morphogene.hpp>
#include <model/universe/evolution/population/creature/genome/morphology/MorphogeneBranch.hpp>
#include <model/universe/evolution/population/creature/phenome/controller/sine/SineController.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/joint/JointBt.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/limb/LimbBt.hpp>
#include <model/universe/evolution/population/creature/genome/Gene.hpp>
#include <model/universe/evolution/population/creature/genome/genetics/embryogenesis/PhenotypeGenerator.hpp>
#include <model/universe/environments/EnvironmentModel.hpp>
//## controller headers
#include <controller/universe/evolution/population/creature/phenome/morphology/Joint.hpp>
#include <controller/universe/evolution/population/creature/phenome/morphology/Limb.hpp>
#include <controller/universe/evolution/population/creature/phenome/Phenome.hpp>

//## view headers
#include <view/picking/OgreMeshRay.hpp>
#include <view/universe/evolution/population/creature/phenome/morphology/limb/LimbO3D.hpp>

//## utils headers
#include <utils/ogre3D/Euler.hpp>
#include <utils/ogre3D/OgreBulletUtils.hpp>

Phenome::Phenome() :
		mSimulationManager(NULL), mCreature(NULL) {

}

Phenome::Phenome(const Phenome& phenome) :
		mPhenomeModel(phenome.mPhenomeModel) {

	mCreature = phenome.mCreature;

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

	mSimulationManager = phenome.mSimulationManager;
}

Phenome::~Phenome() {
	mSimulationManager = NULL;
}

void Phenome::initialize(SimulationManager* simulationManager,
		Creature* creature) {
	mSimulationManager = simulationManager;
	mCreature = creature;
	mPhenomeModel.initialize(mSimulationManager,
			creature->getPlanet()->getEnvironmentModel()->getPhysicsController()->getDynamicsWorld());
}

/**
 * Performs the embryogenesis of a genome. We follow each part of the tree with the phenotype generators.
 * @param creature the handle to the creature will want to get back from the physics engine when we pick a creature.
 * @param genome The genome we perform embryogenesis with.
 * @param rootPosition The position the creature should be generated at.
 */
void Phenome::performEmbryogenesis(Creature* creature, MixedGenome* genome,
		Ogre::Vector3 rootPosition) {
	//perform the embryogenesis in the model
	mPhenomeModel.performEmbryogenesis(creature, genome, rootPosition);

	// iterate over all the component models
	std::vector<ComponentModel*>::const_iterator cmit =
			mPhenomeModel.getComponentModels().begin();

	for (; cmit != mPhenomeModel.getComponentModels().end(); cmit++) {

		switch ((*cmit)->getComponentType()) {
		case ComponentModel::LimbComponent: {
			Limb* limb = new Limb();
			limb->buildFrom(mSimulationManager, mCreature, (LimbModel*) *cmit);
			mLimbs.push_back(limb);
			mComponents.push_back(limb);
			break;
		}
		case ComponentModel::JointComponent: {
			Joint* joint = new Joint();
			//TODO:: Fix with indices
			joint->buildFrom((JointModel*) *cmit);
			mJoints.push_back(joint);
			mComponents.push_back(joint);
			break;
		}
		case ComponentModel::UnknownComponent:
		default:
			std::cout << "######################################\n";
			std::cout << "Unknown component found.\n";
			std::cout << "######################################\n";
			exit(-1);
		}
	}
}

void Phenome::update() {
	//update all controllers
	//TODO: Hacks to make it run, make nicer
	boost::posix_time::ptime time_t_epoch(boost::gregorian::date(1970, 1, 1));
	boost::posix_time::ptime now =
			boost::posix_time::microsec_clock::local_time();
	boost::posix_time::time_duration diff = now - time_t_epoch;

	mPhenomeModel.update(diff.total_milliseconds());

	// Update all limbs
	std::vector<Limb*>::iterator lit = mLimbs.begin();
	for (; lit != mLimbs.end(); lit++) {
		(*lit)->update();
	}

	// Update all constraints
	std::vector<Joint*>::iterator jit = mJoints.begin();
	for (; jit != mJoints.end(); jit++) {
		(*jit)->update();
	}
}

void Phenome::addToWorld() {
	if (!isInWorld()) {
		// Add all limbs
		std::vector<Limb*>::iterator lit = mLimbs.begin();
		for (; lit != mLimbs.end(); lit++) {
			(*lit)->addToWorld();
		}

		// Add all constraints
		std::vector<Joint*>::iterator jit = mJoints.begin();
		for (; jit != mJoints.end(); jit++) {
			(*jit)->addToWorld();
		}
		setInWorld(true);
	}
}

void Phenome::removeFromWorld() {
	if (isInWorld()) {
		// Remove all constraints
		std::vector<Joint*>::iterator jit = mJoints.begin();
		for (; jit != mJoints.end(); jit++) {
			(*jit)->removeFromWorld();
		}

		// Remove all limbs
		std::vector<Limb*>::iterator lit = mLimbs.begin();
		for (; lit != mLimbs.end(); lit++) {
			(*lit)->removeFromWorld();
		}
		setInWorld(false);
	}
}

void Phenome::reset(Ogre::Vector3 position) {
	mPhenomeModel.reset(position);

	// reset all constraints
	std::vector<Joint*>::iterator jit = mJoints.begin();
	for (; jit != mJoints.end(); jit++) {
		(*jit)->reset(position);
	}

	// reset all limbs
	std::vector<Limb*>::iterator lit = mLimbs.begin();
	for (; lit != mLimbs.end(); lit++) {
		(*lit)->reset(position);
	}
}

void Phenome::reposition(Ogre::Vector3 position) {
	mPhenomeModel.reposition(position);

	// reset all constraints
	std::vector<Joint*>::iterator jit = mJoints.begin();
	for (; jit != mJoints.end(); jit++) {
		(*jit)->reposition(position);
	}

	// reset all limbs
	std::vector<Limb*>::iterator lit = mLimbs.begin();
	for (; lit != mLimbs.end(); lit++) {
		(*lit)->reposition(position);
	}
}

Phenome* Phenome::clone() {
	return new Phenome(*this);
}
