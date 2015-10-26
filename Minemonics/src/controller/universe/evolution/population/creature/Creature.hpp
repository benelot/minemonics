#ifndef CONTROLLER_UNIVERSE_EVOLUTION_POPULATION_CREATURE_CREATURE_HPP_
#define CONTROLLER_UNIVERSE_EVOLUTION_POPULATION_CREATURE_CREATURE_HPP_

//# corresponding header
//# forward declarations
class SimulationManager;
class Population;
class PlanetModel;
class PopulationModel;
class CreatureModel;
class Jury;

//# system headers
//## controller headers
//## model headers
//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
#include <controller/universe/evolution/population/creature/phenome/Phenome.hpp>

//## model headers
#include <model/universe/environments/physics/PhysicsController.hpp>

//## view headers
//## utils headers
#include <utils/logging/Logger.hpp>

/**
 * @brief		The creature controller synchronizes the model with the view.
 * @details		Details
 * @date		2015-04-07
 * @author		Benjamin Ellenberger
 */
class Creature {
public:

	Creature(Population* const population,
		const PhysicsController::PhysicsModelType physicsModelType,
		const Ogre::Vector3 position, const double branchiness);
	Creature(CreatureModel* const creatureModel);
	virtual ~Creature();

	/**
	 * Perform embryogenesis on the creature to build his phenotype from the genotype.
	 */
	int performEmbryogenesis();

	/**
	 * Reset the creature to the way it was born.
	 */
	void reset(const Ogre::Vector3 position);

	/**
	 * Reset the creature to its former position.
	 */
	void reset();

	/**
	 * Reposition the creature without resetting it.
	 */
	void reposition(const Ogre::Vector3 position);

	/**
	 * Update the creature as it moves.
	 */
	virtual void update(double timeSinceLastTick);

	/**
	 * Add the creature to the physics world.
	 */
	int addToPhysicsWorld();

	/**
	 * Add the creature to the world.
	 */
	virtual int addToWorld();

	/**
	 * Remove the creature from the world.
	 */
	virtual void removeFromWorld();

	void calm();

	void save(std::string folderPath);

	// Facade accessor methods
	CreatureModel* getCreatureModel() {
		return mCreatureModel;
	}

	void processJuries();

	void setPosition(const Ogre::Vector3 position);

	PlanetModel* getPlanet();

	void setPlanet(PlanetModel* planetModel);

	bool isDeveloped();

	void setDeveloped(bool developed);

	void setCulled(bool culled);

	bool isCulled() const;

	PhysicsController::PhysicsModelType getPhysicsModelType() ;

	void addJury(Jury* jury);

	void clearJuries();

	void hasInterpenetrations();

protected:
	static BoostLogger mBoostLogger; /**!< The boost logger. */

	/**
	 * Initializer of the boost logger to include the class name into the logging messages.
	 */
	static class _Init {
	public:
		_Init() {
			mBoostLogger.add_attribute("ClassName",
				boost::log::attributes::constant<std::string>("Creature"));
		}
	} _initializer;

	CreatureModel* mCreatureModel; /**!< The model representation of the creature */

	//CHILD
	Phenome mPhenotype; /**!< The phenotype of the creature. */
};

#endif /* CONTROLLER_UNIVERSE_EVOLUTION_POPULATION_CREATURE_RSBCREATURE_CREATURE_HPP_ */
