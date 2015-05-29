#ifndef ENVIRONMENT_H_
#define ENVIRONMENT_H_

//# corresponding header
//# forward declarations
class SimulationManager;
class EnvironmentGraphics;
class EnvironmentPhysics;
class EnvironmentModel;
class PhysicsController;

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
 * @brief		The environment controller is the base class for all environments.
 * @details		Details
 * @date		2014-11-17
 * @author		Benjamin Ellenberger
 */
class Environment {
public:
	enum EnvironmentType {
		UNKNOWN_ENVIRONMENT_TYPE = 0, HILLS = 1, PLANE = 2, OPENSEA = 3
	};

	EnvironmentType mEnvironmentType;

	Environment();
	virtual ~Environment();
	void initialize(EnvironmentType environmentType);

	virtual EnvironmentModel* getEnvironmentModel() = 0;

	btRigidBody*& getBody();

	void update();

protected:
	EnvironmentGraphics* mEnvironmentGraphics;
	EnvironmentModel* mEnvironmentModel;

};

#endif /* ENVIRONMENT_H_ */
