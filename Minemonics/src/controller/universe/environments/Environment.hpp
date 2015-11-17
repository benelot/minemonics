#ifndef CONTROLLER_UNIVERSE_ENVIRONEMTNS_ENVIRONMENT_H_
#define CONTROLLER_UNIVERSE_ENVIRONEMTNS_ENVIRONMENT_H_

//# corresponding header
//# forward declarations
class SimulationManager;
class EnvironmentGraphics;
class EnvironmentPhysics;
class PhysicsController;
class EnvironmentO3D;

//# system headers
//## controller headers
//## model headers
//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
#include <model/universe/environments/EnvironmentModel.hpp>

//## view headers
//## utils headers

/**
 * @brief		The environment controller is the base class for all environments.
 * @details		Details
 * @date		2014-11-17
 * @author		Benjamin Ellenberger
 */
class Environment {
public:
	Environment();
	virtual ~Environment();

	/**
	 * Initialize the environment.
	 */
	void initialize();

	/**
	 * Update the environment.
	 */
	virtual void update(double timeSinceLastTick) = 0;

	/**
	 * Is the environment in the world?
	 * @return If the environment is in the world.
	 */
	bool isInWorld() const;

	/**
	 * Add the environment to the world.
	 */
	void addToWorld();

	/**
	 * Add the environment to the physics world only.
	 */
	void addToPhysicsWorld();

	/**
	 * Remove the environment from the world.
	 */
	void removeFromWorld();

	// Accessor methods ##########################

	EnvironmentO3D* getEnvironmentO3D() const {
		return (EnvironmentO3D*) mEnvironmentGraphics;
	}

	EnvironmentModel* getEnvironmentModel() {
		return mEnvironmentModel;
	}

protected:
	/**
	 * The graphical representation of the environment.
	 */
	EnvironmentGraphics* mEnvironmentGraphics;

	/**
	 * The model representation of the environment.
	 */
	EnvironmentModel* mEnvironmentModel;

};

#endif /* CONTROLLER_UNIVERSE_ENVIRONEMTNS_ENVIRONMENT_H_ */
