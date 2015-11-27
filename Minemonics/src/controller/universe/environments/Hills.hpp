#ifndef CONTROLLER_UNIVERSE_ENVIRONMENTS_HILLS_HPP_
#define CONTROLLER_UNIVERSE_ENVIRONMENTS_HILLS_HPP_

//# corresponding header
#include <controller/universe/environments/Environment.hpp>

//# forward declarations
//# system headers
//## controller headers
//## model headers
//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers

/**
 * @brief		The hills environment is a bumpy environment that generates a terrain that extends as creatures walk into it.
 * It is filled with hills of a defined height.
 * @details		Details
 * @date		2015-03-24
 * @author		Benjamin Ellenberger
 */
class Hills: public Environment {
public:
	Hills();
	virtual ~Hills();

	/**
	 * Initialize the hills environment.
	 * @param simulationMgr A handle of the simulation manager.
	 * @param l The light source.
	 */
	void initialize(SimulationManager* simulationMgr, Ogre::Light* l);

	// Accessor methods ##########################

//	EnvironmentModel* getEnvironmentModel();
};

#endif /* CONTROLLER_UNIVERSE_ENVIRONMENTS_HILLS_HPP_ */
