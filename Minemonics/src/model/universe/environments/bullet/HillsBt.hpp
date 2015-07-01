#ifndef MODEL_ENVIRONMENT_HILLSBT_H_
#define MODEL_ENVIRONMENT_HILLSBT_H_

//# corresponding header
#include <model/universe/environments/bullet/EnvironmentBt.hpp>
//# forward declarations
namespace Ogre {
class Terrain;
} /* namespace Ogre */

//# system headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers

/**
 * @brief		The bullet physics model implementation of the hills environment.
 * @details		Details
 * @date		2015-03-17
 * @author		Benjamin Ellenberger
 */
class HillsBt : public EnvironmentBt {
public:
	HillsBt();
	virtual ~HillsBt();

	void initialize(Ogre::Terrain* terrain);

	btRigidBody*& getBody() {
		return mGroundBody;
	}

private:
	btCollisionShape* mGroundShape;
	btDefaultMotionState* mGroundMotionState;
	btRigidBody* mGroundBody;
};

#endif /* MODEL_ENVIRONMENT_HILLSBT_H_ */
