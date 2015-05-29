#ifndef MODEL_UNIVERSE_ENVIRONMENTS_ENVIRONMENTMODEL_HPP_
#define MODEL_UNIVERSE_ENVIRONMENTS_ENVIRONMENTMODEL_HPP_

//# corresponding headers
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
#include <model/universe/environments/EnvironmentPhysics.hpp>
#include <model/universe/environments/physics/PhysicsController.hpp>

//## view headers
//## utils headers

/**
 * @brief		The Environment model holds all general information about an environment.
 * @details		Details
 * @date		2015-05-06
 * @author		Benjamin Ellenberger
 */
class EnvironmentModel {
public:
	EnvironmentModel();
	virtual ~EnvironmentModel();

	bool isInWorld();
	void addToWorld();
	void removeFromWorld();

	//TODO: Add serialization to EnvironmentModel

	EnvironmentPhysics*& getEnvironmentPhysics() {
		return mEnvironmentPhysics;
	}

	void setEnvironmentPhysics(EnvironmentPhysics* environmentPhysics) {
		mEnvironmentPhysics = environmentPhysics;
	}

	PhysicsController* getPhysicsController() {
		return mPhysicsController;
	}

	void setPhysicsController(PhysicsController* physicsController){
		mPhysicsController = physicsController;
	}

protected:

	PhysicsController* mPhysicsController;
	EnvironmentPhysics* mEnvironmentPhysics;
};

#endif /* MODEL_UNIVERSE_ENVIRONMENTS_ENVIRONMENTMODEL_HPP_ */
