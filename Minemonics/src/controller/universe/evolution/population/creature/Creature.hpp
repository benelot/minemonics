#ifndef CONTROLLER_UNIVERSE_EVOLUTION_POPULATION_CREATURE_CREATURE_HPP_
#define CONTROLLER_UNIVERSE_EVOLUTION_POPULATION_CREATURE_CREATURE_HPP_

//# corresponding header
//# forward declarations
class SimulationManager;
class Population;

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
#include <model/universe/evolution/population/PopulationModel.hpp>
#include <model/universe/evolution/population/creature/CreatureModel.hpp>

//## view headers
//## utils headers

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

	// Facade accessor methods
	void setPosition(const Ogre::Vector3 position) {
		mCreatureModel->setPosition(position);
	}

	PlanetModel* getPlanet() {
		return mCreatureModel->getPopulationModel()->getPlanetModel();
	}

	void setPlanet(PlanetModel* planetModel) {
		mCreatureModel->getPopulationModel()->setPlanetModel(planetModel);
	}

	bool isDeveloped() {
		return mCreatureModel->isDeveloped();
	}

	void setDeveloped(bool developed) {
		mCreatureModel->setDeveloped(developed);
	}

	CreatureModel* getCreatureModel() {
		return mCreatureModel;
	}

	void setCulled(bool culled) {
		mCreatureModel->setCulled(culled);
	}

	bool isCulled() const {
		return mCreatureModel->isCulled();
	}

	PhysicsController::PhysicsModelType getPhysicsModelType() {
		return mCreatureModel->getPhysicsModelType();
	}

	void addJury(Jury* jury) {
		mCreatureModel->addJury(jury);
	}

	void clearJuries() {
		mCreatureModel->clearJuries();
	}

	void processJuries();

	void hasInterpenetrations() {
		mCreatureModel->hasInterpenetrations();
	}

protected:
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
				boost::log::attributes::constant < std::string > ("Creature"));
		}
	} _initializer;

	/**
	 * The model representation of the creature
	 */
	CreatureModel* mCreatureModel;

	//CHILD
	/**
	 * The phenotype of the creature.
	 */
	Phenome mPhenotype;
};

#endif /* CONTROLLER_UNIVERSE_EVOLUTION_POPULATION_CREATURE_RSBCREATURE_CREATURE_HPP_ */
