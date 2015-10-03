//# corresponding headers
#include <configuration/Definitions.hpp>
#include <boost/lexical_cast.hpp>
//## model headers
#include <BulletDynamics/Dynamics/btRigidBody.h>
#include <configuration/MorphologyConfiguration.hpp>
#include <LinearMath/btQuadWord.h>
#include <LinearMath/btQuaternion.h>
#include <LinearMath/btScalar.h>
#include <LinearMath/btVector3.h>

//## view headers
//# custom headers
//## base headers
#include <SimulationManager.hpp>

//## configuration headers
#include <configuration/PhysicsConfiguration.hpp>

#include <controller/universe/evolution/population/creature/Creature.hpp>
#include <controller/universe/evolution/population/creature/phenome/morphology/Limb.hpp>
#include <model/universe/environments/physics/PhysicsController.hpp>
#include <model/universe/environments/EnvironmentModel.hpp>
#include <model/universe/evolution/population/creature/FScreature/phenome/morphology/limb/FSLimbBt.hpp>
#include <model/universe/evolution/population/creature/FScreature/phenome/morphology/limb/FSLimbModel.hpp>
#include <model/universe/evolution/population/creature/SRBcreature/phenome/morphology/limb/SRBLimbBt.hpp>
#include <model/universe/evolution/population/creature/SRBcreature/phenome/morphology/limb/SRBLimbModel.hpp>

//## view headers
#include <view/universe/evolution/population/creature/phenome/morphology/limb/LimbO3D.hpp>

//## utils headers
#include <utils/ogre3D/OgreBulletUtils.hpp>

BoostLogger Limb::mBoostLogger; /*<! initialize the boost logger*/
Limb::_Init Limb::_initializer;
Limb::Limb() :
	mLimbGraphics(NULL), mCreature(NULL), mLimbModel(NULL) {
	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::debug) << "Limb created.";
	mLimbModel = new SRBLimbModel();
}

Limb::Limb(const Limb& limb) :
	mLimbModel(limb.mLimbModel) {
	mCreature = limb.mCreature;
	mLimbGraphics = limb.mLimbGraphics->clone();
}

Limb::Limb(Creature* const creature, LimbModel* const limbModel) {
	mLimbModel = limbModel;
	mCreature = creature;

	// Define the new component as a limb
	Component::initialize(limbModel);

	// initialize the graphics part of the limb
	mLimbGraphics = new LimbO3D(mLimbModel);

//	// Update the state of the limb.
	update(0);
}

Limb::~Limb() {
	delete mLimbGraphics;
	mLimbGraphics = NULL;

	delete mLimbModel;
	mLimbModel = NULL;

	mCreature = NULL;
}

void Limb::initialize(Creature* const creature,
	const LimbPhysics::PrimitiveType type, const Ogre::Vector3 position,
	const Ogre::Quaternion orientation,
	const Ogre::Vector3 initialRelativePosition,
	const Ogre::Quaternion initialOrientation, const Ogre::Vector3 dimensions,
	const double mass, const double restitution, const double friction,
	const Ogre::ColourValue color, bool isIntraBodyColliding,
	const int ownIndex) {

	//initialize the model of the limb
	switch (creature->getPhysicsModelType()) {
	case PhysicsController::RigidbodyModel:
		mLimbModel = new SRBLimbModel();
		break;
	case PhysicsController::FeatherstoneModel:
		mLimbModel = new FSLimbModel();
		break;
	default:
		break;
	}

	mLimbModel->initialize(
		creature->getPlanet()->getEnvironmentModel()->getPhysicsController()->getDynamicsWorld(),
		creature->getCreatureModel(), type, position, orientation,
		initialRelativePosition, initialOrientation, dimensions, mass,
		restitution, friction, color, isIntraBodyColliding, ownIndex);

	mCreature = creature;

	// Define the new component as a limb
	Component::initialize (mLimbModel);

	// initialize the graphics part of the limb
	mLimbGraphics = new LimbO3D(mLimbModel);

	// Update the state of the limb.
	update(0);
}

/**
 * Update the state of the limb.
 */
void Limb::update(double timeSinceLastTick) {
	//update the limb graphics
	mLimbModel->update(timeSinceLastTick);
	mLimbGraphics->update(timeSinceLastTick);
}

void Limb::reset(const Ogre::Vector3 position) {
	mLimbModel->reset(position);
}

void Limb::reposition(const Ogre::Vector3 position) {
	mLimbModel->reposition(position);
}

Limb* Limb::clone() {
	return new Limb(*this);
}

/**
 * Add the limb to the physics world.
 */
void Limb::addToPhysicsWorld() {

	if (!getLimbPhysics()->isInWorld()) {
		getLimbPhysics()->addToWorld();
	}
}

/**
 * Add the limb to the world.
 */
void Limb::addToWorld() {
	if (!mLimbGraphics->isInWorld()) {
		mLimbGraphics->addToWorld();
	}

	if (!getLimbPhysics()->isInWorld()) {
		getLimbPhysics()->addToWorld();
	}
}

/**
 * Remove the limb from the world.
 */
void Limb::removeFromWorld() {
	if (mLimbGraphics->isInWorld()) {
		mLimbGraphics->removeFromWorld();
	}

	if (getLimbPhysics()->isInWorld()) {
		getLimbPhysics()->removeFromWorld();
	}
}
