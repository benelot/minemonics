#ifndef MODEL_ENVIRONMENT_HILLSBT_H_
#define MODEL_ENVIRONMENT_HILLSBT_H_

//# corresponding header
#include <configuration/Definitions.hpp>
#include <model/universe/environments/bullet/EnvironmentBt.hpp>

//# forward declarations
//# system headers
//## controller headers
//## model headers
#include <OgreTerrain.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers
#include <utils/logging/Logger.hpp>

/**
 * @brief		The bullet physics model implementation of the hills environment.
 * @details		Details
 * @date		2015-03-17
 * @author		Benjamin Ellenberger
 */
class HillsBt: public EnvironmentBt {
public:
	HillsBt();
	virtual ~HillsBt();

	void initialize(Ogre::Terrain* terrain);

	btRigidBody*& getBody() {
		return mGroundBody;
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
				boost::log::attributes::constant < std::string > ("HillsBt"));
		}
	} _initializer;
};

#endif /* MODEL_ENVIRONMENT_HILLSBT_H_ */
