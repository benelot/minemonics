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

	virtual void update() = 0;

	bool isInWorld();
	void addToWorld();
	void removeFromWorld();

	//Accessor methods

	EnvironmentPhysics*& getEnvironmentPhysics() {
		return mEnvironmentPhysics;
	}

	void setEnvironmentPhysics(EnvironmentPhysics* environmentPhysics) {
		mEnvironmentPhysics = environmentPhysics;
	}

	void createTerrainData(Ogre::SceneNode* sceneNode, float w, float h,
			float* data, float minH, float maxH, Ogre::Vector3& pos,
			float scale, float heightScale){
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
