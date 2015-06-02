#ifndef MODEL_UNIVERSE_ENVIRONMENTS_ENVIRONMENTPHYSICS_HPP_
#define MODEL_UNIVERSE_ENVIRONMENTS_ENVIRONMENTPHYSICS_HPP_

//# corresponding header
//# forward declarations
namespace Ogre {
class SceneNode;
class Vector3;
} /* namespace Ogre */

//# system headers
//## controller headers
//## model headers
//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers

/**
 * @brief		The physics part of the environment model.
 * @details		Details
 * @date		2015-03-17
 * @author		Benjamin Ellenberger
 */
class EnvironmentPhysics {
public:
	EnvironmentPhysics();
	virtual ~EnvironmentPhysics();

	virtual void initialize() = 0;

	virtual void update() = 0;

	virtual void createTerrainData(Ogre::SceneNode* sceneNode, float w,float h,float* data,float minH,float maxH,Ogre::Vector3& pos,float scale,float heightScale) = 0;
};

#endif /* MODEL_UNIVERSE_ENVIRONMENTS_ENVIRONMENTPHYSICS_HPP_ */
