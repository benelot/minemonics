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
#include <boost/log/attributes/constant.hpp>
#include <boost/log/sources/basic_logger.hpp>

//## view headers
#include <controller/universe/environments/Environment.hpp>

//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers
#include <utils/logging/Logger.hpp>

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
	 * @param l The general light source.
	 * @param debugDrawer The debug drawer of the simulation.
	 */
	void initialize(const Ogre::Light* const l, OgreBtDebugDrawer* const debugDrawer);

	/**
	 * Update the plane environment.
	 */
	virtual void update();

	// Accessor methods
	PlaneO3D* getPlaneView() const {
		return (PlaneO3D*) mEnvironmentGraphics;
	}

	PlaneModel* getPlaneModel() const {
		return (PlaneModel*) mEnvironmentModel;
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
					boost::log::attributes::constant<std::string>("Plane"));
		}
	} _initializer;
};

#endif /* CONTROLLER_UNIVERSE_ENVIRONMENTS_PLANE_HPP_ */
