#ifndef CONTROLLER_UNIVERSE_PLANET_HPP_
#define CONTROLLER_UNIVERSE_PLANET_HPP_

//# corresponding header
#include <configuration/Definitions.hpp>

//# forward declarations
//# system headers
#include <string>

//## controller headers
//## model headers
#include <boost/log/attributes/constant.hpp>
#include <boost/log/sources/basic_logger.hpp>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
#include <controller/universe/evolution/Evolution.hpp>
#include <controller/universe/environments/Environment.hpp>

//## model headers
#include <model/universe/environments/EnvironmentModel.hpp>
#include <model/universe/environments/physics/PhysicsController.hpp>
#include <model/universe/evolution/EvolutionModel.hpp>
#include <model/universe/PlanetModel.hpp>

//## view headers
//## utils headers
#include <utils/logging/Logger.hpp>

/**
 * @brief		The planet controller holds an evolution together with a certain environment in which it is evaluated.
 * @details		Details
 * @date		2015-05-06
 * @author		Benjamin Ellenberger
 */
class Planet {
public:

	/**
	 * Constructor to load a planet afterwards.
	 */
	Planet();

	/**
	 * Constructor to create a new planet.
	 * @param physicsModelType The physics model type.
	 * @param environmentType The environment type.
	 * @param evaluationTime The evalution time.
	 * @param evaluationType The evaluation type.
	 * @param tournamentSize The tournament size.
	 */
	Planet(const PhysicsController::PhysicsModelType physicsModelType,
		const EnvironmentModel::EnvironmentType environmentType,
		const int evaluationTime, EvolutionModel::EvaluationType evaluationType,
		int tournamentSize);

	/**
	 * Copy constructor.
	 * @param planetModel
	 */
	Planet(PlanetModel* const planetModel);
	virtual ~Planet();

	/**
	 * Called to initialize the planet to be a complete entity.
	 */
	void initialize();

	/**
	 * Perform embryogenesis on all creatures that are not yet developed.
	 */
	void performEmbryogenesis();

	/**
	 * Add a population to the planet.
	 * @param population The population to be added to the planet.
	 */
	void addPopulation(Population* const population);

	/**
	 * Draw the debug world if debug drawing is enabled.
	 */
	void drawDebugWorld();

	/**
	 * Step the universe physics forward.
	 * @param timeStep The size of the time step.
	 */
	void stepPhysics(const double timeStep);

	/**
	 * Update the model of the planet.
	 */
	void update(double timeSinceLastTick);

	/**
	 * Proceed with the evaluation. In serial mode, this just goes on to the next evaluation, in parallel mode, this schedules one more evaluation.
	 * @return If true then this means it proceeded successfully, if false this means that the generation is over and evaluated.
	 */
	bool proceedEvaluation();

	void save();

	void load();

	// Accessor methods ##########################
	/**
	 * Get the environment of the planet.
	 * @return The environment of the planet.
	 */
	Environment* getEnvironment() {
		return mEnvironment;
	}

	/**
	 * Set the environment of the planet.
	 * @param environment The environment of the planet.
	 */
	void setEnvironment(Environment* const environment) {
		mEnvironment = environment;
	}

	Evolution& getEvolution() {
		return mEvolution;
	}

	void setEvolution(const Evolution& evolution) {
		mEvolution = evolution;
	}

	PlanetModel* getPlanetModel() {
		return mPlanetModel;
	}

	PhysicsController::PhysicsModelType getPhysicsModelType();

	int getTotalCreatureQty();

	void addEpoch(Epoch* epoch);

	void setSerializationPath(std::string serializationPath);

	std::string getSerializationPath();

private:

	static BoostLogger mBoostLogger; /**!< The boost logger. */

	/**
	 * Initializer of the boost logger to include the class name into the logging messages.
	 */
	static class _Init {
	public:
		_Init() {
			mBoostLogger.add_attribute("ClassName",
				boost::log::attributes::constant<std::string>("Planet"));
		}
	} _initializer;

	PlanetModel* mPlanetModel; /**!< The model representation of this planet. */

	Evolution mEvolution; /**!< The evolution on this planet. */

	Environment* mEnvironment; /**!< The environment of this planet. */
};

#endif /* CONTROLLER_UNIVERSE_PLANET_HPP_ */
