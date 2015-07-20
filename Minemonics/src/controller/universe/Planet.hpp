#ifndef CONTROLLER_UNIVERSE_PLANET_HPP_
#define CONTROLLER_UNIVERSE_PLANET_HPP_

//# corresponding header
//# forward declarations
//# system headers
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
#include <model/universe/PlanetModel.hpp>

//## view headers
//## utils headers

/**
 * @brief		The planet controller holds an evolution together with a certain environment in which it is evaluated.
 * @details		Details
 * @date		2015-05-06
 * @author		Benjamin Ellenberger
 */
class Planet {
public:
	Planet(const Environment::EnvironmentType type,
			OgreBtDebugDrawer* const debugDrawer, const int evaluationTime);
	Planet(PlanetModel* const planetModel);
	virtual ~Planet();

	/**
	 * Initialize the planet.
	 * @param simulationManager The simulation manager.
	 * @param type The type of the environment.
	 * @param debugDrawer The debug drawer of this simulation.
	 */
	void initialize(const Environment::EnvironmentType type, OgreBtDebugDrawer* const debugDrawer,const int evaluationTime);

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
	 * @param timeSinceLastFrame The size of the time step.
	 */
	void stepPhysics(const double timeSinceLastFrame);

	/**
	 * Update the model of the planet.
	 */
	void update();

	/**
	 * Proceed with the evaluation. In serial mode, this just goes on to the next evaluation, in parallel mode, this schedules one more evaluation.
	 * @return If true then this means it proceeded successfully, if false this means that the generation is over and evaluated.
	 */
	bool proceedEvaluation();

	// Accessor methods
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
					boost::log::attributes::constant<std::string>(
							"Planet"));
		}
	} _initializer;

	/**
	 * The model representation of this planet.
	 */
	PlanetModel* mPlanetModel;

	/**
	 * The evolution on this planet.
	 */
	Evolution mEvolution;

	/**
	 * The environment of this planet.
	 */
	Environment* mEnvironment;
};

#endif /* CONTROLLER_UNIVERSE_PLANET_HPP_ */
