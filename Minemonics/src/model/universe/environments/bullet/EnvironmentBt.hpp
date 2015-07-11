#ifndef MODEL_BULLET_ENVIRONMENTS_ENVIRONMENTBT_H_
#define MODEL_BULLET_ENVIRONMENTS_ENVIRONMENTBT_H_

//# corresponding headers
#include <model/universe/environments/EnvironmentPhysics.hpp>

//# forward declarations
class btCollisionShape;
struct btDefaultMotionState;
class btRigidBody;
namespace Ogre {
class SceneNode;
class Vector3;
} /* namespace Ogre */

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
//## model headers
//## view headers
//## utils headers
#include <utils/logging/Logger.hpp>

/**
 * @brief		Bullet physics model implementation of the environment.
 * @details		Details
 * @date		2015-03-17
 * @author		Benjamin Ellenberger
 */
class EnvironmentBt: public EnvironmentPhysics {
public:
	EnvironmentBt();
	virtual ~EnvironmentBt();

	virtual btRigidBody*& getBody() = 0;

	virtual void createTerrainData(Ogre::SceneNode* sceneNode, float w, float h,
			float* data, float minH, float maxH, Ogre::Vector3& pos,
			float scale, float heightScale);

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
					boost::log::attributes::constant<std::string>(
							"EnvironmentBt"));
		}
	} _initializer;

	/**
	 * The collision shape of the environment.
	 */
	btCollisionShape* mGroundShape;

	/**
	 * The rigidbody of the environment.
	 */
	btRigidBody* mGroundBody;
};

#endif /* MODEL_BULLET_ENVIRONMENTS_ENVIRONMENTBT_H_ */
