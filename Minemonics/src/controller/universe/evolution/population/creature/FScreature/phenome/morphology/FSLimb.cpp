//# corresponding headers
#include <boost/lexical_cast.hpp>

//### bullet headers
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
#include <controller/universe/evolution/population/creature/SRBcreature/phenome/morphology/Limb.hpp>
#include <controller/universe/evolution/population/creature/SRBcreature/SRBCreature.hpp>
#include <model/universe/environments/physics/PhysicsController.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/limb/LimbModel.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/limb/LimbBt.hpp>
#include <model/universe/environments/EnvironmentModel.hpp>

//## view headers
#include <view/universe/evolution/population/creature/phenome/morphology/limb/LimbO3D.hpp>

//## utils headers
#include <utils/ogre3D/OgreBulletUtils.hpp>

BoostLogger FSLimb::mBoostLogger; /*<! initialize the boost logger*/
FSLimb::_Init FSLimb::_initializer;
FSLimb::FSLimb() :
	mLimbGraphics(NULL), mCreature(NULL), mLimbModel(NULL) {
	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::debug) << "Limb created.";
	mLimbModel = new FSLimbModel();
}

FSLimb::FSLimb(const FSLimb& limb) :
	mLimbModel(limb.mLimbModel) {
	mCreature = limb.mCreature;
	mLimbGraphics = limb.mLimbGraphics->clone();
}

FSLimb::FSLimb(Creature* const creature, FSLimbModel* const limbModel) {
	mLimbModel = limbModel;
	mCreature = creature;

	// Define the new component as a limb
	FSComponent::initialize(limbModel);

	// initialize the graphics part of the limb
	mLimbGraphics = new LimbO3D(mLimbModel);

//	// Update the state of the limb.
	update(0);
}

FSLimb::~FSLimb() {
	delete mLimbGraphics;
	mLimbGraphics = NULL;

	delete mLimbModel;
	mLimbModel = NULL;

	mCreature = NULL;
}

void FSLimb::initialize(Creature* const creature,
	const FSLimbPhysics::PrimitiveType type, const Ogre::Vector3 position,
	const Ogre::Quaternion orientation,
	const Ogre::Vector3 initialRelativePosition,
	const Ogre::Quaternion initialOrientation, const Ogre::Vector3 dimensions,
	const double mass, const double restitution, const double friction,
	const Ogre::ColourValue color, bool isIntraBodyColliding,
	const int ownIndex) {

	//initialize the model of the limb
	mLimbModel = new FSLimbModel();
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
void FSLimb::update(double timeSinceLastTick) {
	//update the limb graphics
	mLimbModel->update(timeSinceLastTick);
	mLimbGraphics->update(timeSinceLastTick);
}

void FSLimb::reset(const Ogre::Vector3 position) {
	mLimbModel->reset(position);
}

void FSLimb::reposition(const Ogre::Vector3 position) {
	mLimbModel->reposition(position);
}

FSLimb* FSLimb::clone() {
	return new FSLimb(*this);
}

/**
 * Add the limb to the physics world.
 */
void FSLimb::addToPhysicsWorld() {

	if (!getLimbPhysics()->isInWorld()) {
		getLimbPhysics()->addToWorld();
	}
}

/**
 * Add the limb to the world.
 */
void FSLimb::addToWorld() {
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
void FSLimb::removeFromWorld() {
	if (mLimbGraphics->isInWorld()) {
		mLimbGraphics->removeFromWorld();
	}

	if (getLimbPhysics()->isInWorld()) {
		getLimbPhysics()->removeFromWorld();
	}
}

void FSLimb::generateLink(btMultiBody* multiBody, btVector3 origin,
	btQuaternion rotation, int index) {
	mLimbModel->generateLink(multiBody, origin, rotation, index);
}

/**
 * Get intersection point with the limb graphics given a straight line defined by origin and direction.
 */
Ogre::Vector3 FSLimb::getIntersection(const Ogre::Vector3 origin,
	const Ogre::Vector3 direction) {
	return mLimbGraphics->getIntersection(origin, direction);
}
