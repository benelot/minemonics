#ifndef CONTROLLER_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_LIMB_HPP_
#define CONTROLLER_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_LIMB_HPP_

//# corresponding headers
#include <configuration/Definitions.hpp>
#include <controller/universe/evolution/population/creature/phenome/Component.hpp>

//# forward declarations
class SimulationManager;
class Creature;

//# system headers
#include <string>

//## controller headers
//## model headers
#include <OgreVector3.h>
#include <OgreQuaternion.h>
#include <boost/log/attributes/constant.hpp>
#include <boost/log/sources/basic_logger.hpp>

//## view headers
#include <OgreColourValue.h>

//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
#include <model/universe/evolution/population/creature/phenome/morphology/limb/LimbModel.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/limb/LimbPhysics.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/limb/LimbBt.hpp>

//## view headers
#include <view/universe/evolution/population/creature/phenome/morphology/limb/LimbGraphics.hpp>
#include <view/universe/evolution/population/creature/phenome/morphology/limb/LimbO3D.hpp>

//## utils headers
#include <utils/logging/Logger.hpp>

/**
 * @brief		The limb controller synchronizes the limb graphical representation with the limb model.
 * @details		Details
 * @date		2014-12-19
 * @author		Benjamin Ellenberger
 */
class FSLimb: public FSComponent {
public:
	FSLimb();
	FSLimb(const FSLimb& limb);
	FSLimb(FSCreature* const creature, FSLimbModel* const limbModel);
	virtual ~FSLimb();

	/**
	 * Initialize the limb.
	 * @param creature A handle to the creature the limb belongs to.
	 * @param type The primitive type of the limb.
	 * @param position The position of the limb.
	 * @param orientation The orientation of the limb.
	 * @param size The size of the limb.
	 * @param mass The mass of the limb.
	 * @param restitution The restitution of the limb.
	 * @param friction The friction of the limb.
	 * @param color The color of the limb.
	 * @param ownIndex The limb's own index in the array of limbs.
	 */
	void initialize(Creature* const creature,
		const FSLimbPhysics::PrimitiveType type, const Ogre::Vector3 position,
		const Ogre::Quaternion orientation,
		const Ogre::Vector3 initialRelativePosition,
		const Ogre::Quaternion initialOrientation, const Ogre::Vector3 size,
		const double mass, const double restitution = 1.0,
		const double friction = 0.8, const Ogre::ColourValue color =
			Ogre::ColourValue(1, 1, 1), bool isIntraBodyColliding = true,
		const int ownIndex = 0);

	/**
	 * Build a limb from the limb model.
	 * @param simulationManager The handle of the simulationManager.
	 * @param creature The handle of the creature.
	 * @param limbModel The model of the limb.
	 */
	void buildFrom(SimulationManager* const simulationManager,
		Creature* const creature, FSLimbModel* const limbModel);

	/**
	 * Clone the limb.
	 * @return The clone of the limb.
	 */
	FSLimb* clone();

	/**
	 * Reset the creature to the way it was born.
	 */
	void reset(const Ogre::Vector3 position);

	/**
	 * Reposition the creature without resetting it.
	 */
	void reposition(const Ogre::Vector3 position);

	/**
	 * Update the graphical representation of the limb with the physical representation.
	 */
	void update(double timeSinceLastTick);

	/**
	 * Add the limb to the physics world.
	 */
	void addToPhysicsWorld();

	/**
	 * Add the limb to the graphical and the physical world.
	 */
	void addToWorld();

	/**
	 * Remove the limb from the graphical and the physical world.
	 */
	void removeFromWorld();

	void generateLink(btMultiBody* multiBody, btVector3 origin,
		btQuaternion rotation, int index);

	/**
	 * Get the intersection of a ray with origin and direction and the limb surface in the global reference frame.
	 * @param origin The origin of the ray in the global reference frame.
	 * @param direction The direction of the ray.
	 * @return The intersection of a ray with origin and direction and the limb surface in the global reference frame.
	 */
	Ogre::Vector3 getIntersection(const Ogre::Vector3 origin,
		const Ogre::Vector3 direction);

	// Accessor methods
	const Ogre::Vector3 getPosition() const {
		return mLimbModel->getPosition();
	}

	const Ogre::Quaternion getOrientation() const {
		return mLimbModel->getOrientation();
	}

	/**
	 * Get the Graphics part of the limb.
	 */
	LimbGraphics* const getLimbGraphics() const {
		return mLimbGraphics;
	}

	/**
	 * Get the Physics part of the limb.
	 */
	FSLimbPhysics* const getLimbPhysics() const {
		return mLimbModel->getLimbPhysics();
	}

	FSLimbModel* getLimbModel() {
		return mLimbModel;
	}

	const FSLimbModel* getLimbModel() const {
		return mLimbModel;
	}

	btMultiBodyLinkCollider* getLink() {
		return mLimbModel->getLink();
	}

private:

	/**
	 * The boost logger.
	 */
	static BoostLogger mBoostLogger;

	/**
	 * Initializer of the boost logger to include the class name into the logging messages.
	 */
	static class _Init {
	public:
		_Init() {
			mBoostLogger.add_attribute("ClassName",
				boost::log::attributes::constant < std::string > ("Limb"));
		}
	} _initializer;

	/**
	 * Graphical representation of the limb.
	 */
	LimbGraphics* mLimbGraphics;

	/**
	 * The model representation of the limb.
	 */
	FSLimbModel* mLimbModel;

	/**
	 * The creature the limb belongs to.
	 */
	Creature* mCreature;
};

#endif /* CONTROLLER_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_LIMB_HPP_ */
