#ifndef MODEL_ENVIRONMENT_PLANEBT_H_
#define MODEL_ENVIRONMENT_PLANEBT_H_

//# corresponding header
#include <model/universe/environments/bullet/EnvironmentBt.hpp>

//# forward declarations

//# system headers
//## controller headers
//## model headers
#include <boost/log/attributes/constant.hpp>
#include <boost/log/sources/basic_logger.hpp>
#include <btBulletDynamicsCommon.h>

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
 * @brief		The bullet physics model implementation of the plane environment.
 * @details		Details
 * @date		2015-03-17
 * @author		Benjamin Ellenberger
 */
class PlaneBt: public EnvironmentBt {
public:
	PlaneBt();
	virtual ~PlaneBt();

	void initialize();

	virtual void update();

	//Accessor methods
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
					boost::log::attributes::constant<std::string>(
							"PlaneBt"));
		}
	} _initializer;
};

#endif /* MODEL_ENVIRONMENT_PLANEBT_H_ */
