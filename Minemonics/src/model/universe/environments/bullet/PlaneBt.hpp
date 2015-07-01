#ifndef MODEL_ENVIRONMENT_PLANEBT_H_
#define MODEL_ENVIRONMENT_PLANEBT_H_

//# corresponding header
#include <model/universe/environments/bullet/EnvironmentBt.hpp>

//# forward declarations

//# system headers
//## controller headers
//## model headers
#include <btBulletDynamicsCommon.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers

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
};

#endif /* MODEL_ENVIRONMENT_PLANEBT_H_ */
