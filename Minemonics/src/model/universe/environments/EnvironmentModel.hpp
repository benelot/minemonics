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

	/**
	 * Update the environment model.
	 */
	virtual void update() = 0;

	/**
	 * Is the environment in the world?
	 * @return If the environment is in the world.
	 */
	bool isInWorld() const;

	/**
	 * Add the environment to the world.
	 */
	void addToWorld();

	/**
	 * Remove the environment from the world.
	 */
	void removeFromWorld();

	//Accessor methods

	EnvironmentPhysics* getEnvironmentPhysics() {
		return mEnvironmentPhysics;
	}

	void setEnvironmentPhysics(EnvironmentPhysics* const environmentPhysics) {
		mEnvironmentPhysics = environmentPhysics;
	}

	void createTerrainData(Ogre::SceneNode* const sceneNode, const float w, const float h,
			const float* const data, const float minH, const float maxH, const Ogre::Vector3& pos,
			const float scale, const float heightScale){
		mEnvironmentPhysics->createTerrainData(sceneNode,w,h,data,minH,maxH,pos,scale,heightScale);
	}

	PhysicsController* getPhysicsController() {
		return mPhysicsController;
	}

	void setPhysicsController(PhysicsController* physicsController) {
		mPhysicsController = physicsController;
	}

	//Serialization
	//TODO: Add serialization to EnvironmentModel

protected:

	/**
	 * Is the environment in the world?
	 */
	bool mInWorld;

	/**
	 * The physics controller of the environment.
	 */
	PhysicsController* mPhysicsController;

	/**
	 * The physical model representation of the environment.
	 */
	EnvironmentPhysics* mEnvironmentPhysics;
};

#endif /* MODEL_UNIVERSE_ENVIRONMENTS_ENVIRONMENTMODEL_HPP_ */
