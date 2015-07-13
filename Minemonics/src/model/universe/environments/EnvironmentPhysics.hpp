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
 * @brief		The physics model representation of the environment model.
 * @details		Details
 * @date		2015-03-17
 * @author		Benjamin Ellenberger
 */
class EnvironmentPhysics {
public:
	EnvironmentPhysics();
	virtual ~EnvironmentPhysics();

	/**
	 * Initialize the environment physics.
	 */
	virtual void initialize() = 0;

	/**
	 * Update the environment physics.
	 */
	virtual void update() = 0;

	/**
	 * Create the terrain data.
	 * @param sceneNode
	 * @param w
	 * @param h
	 * @param data
	 * @param minH
	 * @param maxH
	 * @param pos
	 * @param scale
	 * @param heightScale
	 */
	virtual void createTerrainData(Ogre::SceneNode* const sceneNode, const float w, const float h,
			const float* const data, const float minH, const float maxH, const Ogre::Vector3& pos,
			const float scale, const float heightScale) = 0;
};

#endif /* MODEL_UNIVERSE_ENVIRONMENTS_ENVIRONMENTPHYSICS_HPP_ */
