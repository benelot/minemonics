#ifndef CONTROLLER_UNIVERSE_ENVIRONMENTS_PLANE_HPP_
#define CONTROLLER_UNIVERSE_ENVIRONMENTS_PLANE_HPP_

//# corresponding headers
//# forward declarations
class EnvironmentModel;
class OgreBtDebugDrawer;
namespace Ogre {
class Light;
} /* namespace Ogre */

//# system headers
//## controller headers
//## model headers
//## view headers
#include <controller/universe/environments/Environment.hpp>

//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers

/**
 * @brief		The plane environment simulates an environment that is a geometric plane.
 * @details		Details
 * @date		2015-03-24
 * @author		Benjamin Ellenberger
 */
class Plane: public Environment {
public:
	Plane();
	virtual ~Plane();

	void initialize(SimulationManager* simulationMgr, Ogre::Light* l,OgreBtDebugDrawer* debugDrawer);

	EnvironmentModel* getEnvironmentModel();
};

#endif /* CONTROLLER_UNIVERSE_ENVIRONMENTS_PLANE_HPP_ */
