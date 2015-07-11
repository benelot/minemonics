#ifndef CONTROLLER_UNIVERSE_ENVIRONMENTS_PLANE_HPP_
#define CONTROLLER_UNIVERSE_ENVIRONMENTS_PLANE_HPP_

//# corresponding headers
//# forward declarations
class EnvironmentModel;
class OgreBtDebugDrawer;
class PlaneO3D;
class PlaneModel;
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

	/**
	 * Initialize the plane environment.
	 * @param simulationMgr A handle to the simulation manager.
	 * @param l The general light source.
	 * @param debugDrawer The debug drawer of the simulation.
	 */
	void initialize(SimulationManager* simulationMgr, Ogre::Light* l,OgreBtDebugDrawer* debugDrawer);

	virtual void update();

	PlaneO3D* getPlaneView() {
		return (PlaneO3D*) mEnvironmentGraphics;
	}

	PlaneModel* getPlaneModel() {
		return (PlaneModel*)mEnvironmentModel;
	}
};

#endif /* CONTROLLER_UNIVERSE_ENVIRONMENTS_PLANE_HPP_ */
