//# corresponding headers
#include <controller/universe/evolution/population/creature/phenome/morphology/Limb.hpp>

//# forward declarations
//# system headers
//## controller headers
//## model headers
//### boost headers
#include <boost/lexical_cast.hpp>

//### bullet headers
#include <BulletDynamics/Dynamics/btRigidBody.h>
#include <LinearMath/btQuadWord.h>
#include <LinearMath/btQuaternion.h>
#include <LinearMath/btScalar.h>
#include <LinearMath/btVector3.h>

//## view headers
//# custom headers
//## base headers
#include <SimulationManager.hpp>

//## configuration headers
#include <configuration/MorphologyConfiguration.hpp>
#include <configuration/PhysicsConfiguration.hpp>

//## controller headers
#include <controller/universe/evolution/population/creature/Creature.hpp>

//## model headers
#include <model/universe/environments/physics/PhysicsController.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/limb/LimbModel.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/limb/LimbBt.hpp>
#include <model/universe/environments/EnvironmentModel.hpp>

//## view headers
#include <view/universe/evolution/population/creature/phenome/morphology/limb/LimbO3D.hpp>

//## utils headers
#include <utils/ogre3D/OgreBulletUtils.hpp>

BoostLogger Limb::mBoostLogger; /*<! initialize the boost logger*/
Limb::_Init Limb::_initializer;
Limb::Limb() :
		mLimbGraphics(NULL), mCreature(NULL), mLimbModel(NULL) {
	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::debug)<< "Limb created.";
}

Limb::Limb(const Limb& limb) :
		mLimbModel(limb.mLimbModel) {
	mCreature = limb.mCreature;
	mLimbGraphics = limb.mLimbGraphics->clone();
}

Limb::Limb(SimulationManager* const simulationManager, Creature* const creature,
		LimbModel* const limbModel) {
	mLimbModel = limbModel;
	mCreature = creature;

	// Define the new component as a limb
	Component::initialize(limbModel);

	// initialize the graphics part of the limb
	mLimbGraphics = new LimbO3D();
	getLimbGraphics()->initialize(simulationManager,
			limbModel->getPrimitiveType(), limbModel->getDimensions(),
			limbModel->getColor());

//	// Update the state of the limb.
	update();
}

Limb::~Limb() {
	delete mLimbGraphics;
	mLimbGraphics = NULL;

	delete mLimbModel;
	mLimbModel = NULL;

	mCreature = NULL;
}

void Limb::initialize(SimulationManager* const simulationManager,
		Creature* const creature, const LimbModel::PrimitiveType type,
		const Ogre::Vector3 position, const Ogre::Quaternion orientation,
		const Ogre::Vector3 initialRelativePosition,
		const Ogre::Quaternion initialOrientation,
		const Ogre::Vector3 dimensions, const double mass,
		const double restitution, const double friction,
		const Ogre::ColourValue color, const int ownIndex) {

	//initialize the model of the limb
	mLimbModel = new LimbModel();
	mLimbModel->initialize(
			creature->getPlanet()->getEnvironmentModel()->getPhysicsController()->getDynamicsWorld(),
			&creature->getCreatureModel(), type, position, orientation,
			initialRelativePosition, initialOrientation, dimensions, mass,
			restitution, friction, color, ownIndex);

	mCreature = creature;

	// Define the new component as a limb
	Component::initialize(mLimbModel);

	// initialize the graphics part of the limb
	mLimbGraphics = new LimbO3D();
	getLimbGraphics()->initialize(simulationManager,
			mLimbModel->getPrimitiveType(), mLimbModel->getDimensions(),
			mLimbModel->getColor());

	// Update the state of the limb.
	update();
}

/**
 * Update the state of the limb.
 */
void Limb::update() {
	// get the rigid body of the limb
	btRigidBody* body = getLimbPhysics()->getRigidBody();

	// if the limb's rigid body is existing
	if (body) {

		// update the position of the limb graphics
		btVector3 point = body->getCenterOfMassPosition();
		mLimbGraphics->setPosition(
				Ogre::Vector3(point.x(), point.y(), point.z()));

		// Get the Orientation of the rigid body as a bullet Quaternion
		// Convert it to an Ogre quaternion
		btQuaternion btq = body->getOrientation();
		Ogre::Quaternion quart = Ogre::Quaternion(btq.w(), btq.x(), btq.y(),
				btq.z());

		// update the orientation of the limb graphics
		mLimbGraphics->setOrientation(quart);
	}

	mLimbGraphics->update();
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

std::string Limb::getInfo() {
	std::string text;
	text.append("Box coordinate: ");
	text.append(
			boost::lexical_cast<std::string>(mLimbGraphics->getPosition().x));
	text.append(",");
	text.append(
			boost::lexical_cast<std::string>(mLimbGraphics->getPosition().y));
	text.append(",");
	text.append(
			boost::lexical_cast<std::string>(mLimbGraphics->getPosition().z));
	text.append(",\n");
	text.append("---------");
	return text;
}

/**
 * Add the limb to the world.
 */
void Limb::addToWorld() {
	mLimbGraphics->addToWorld();
	mLimbModel->getLimbPhysics()->addToWorld();
}

/**
 * Remove the limb from the world.
 */
void Limb::removeFromWorld() {
	mLimbGraphics->removeFromWorld();
	mLimbModel->getLimbPhysics()->removeFromWorld();
}

/**
 * Get intersection point with the limb graphics given a straight line defined by origin and direction.
 */
Ogre::Vector3 Limb::getIntersection(const Ogre::Vector3 origin,
		const Ogre::Vector3 direction) {
	return mLimbGraphics->getIntersection(origin, direction);
}
