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
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/version.hpp>

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
	virtual void update(double timeSinceLastTick) = 0;

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

	// Serialization ##########################
	/**
	 * Give access to boost serialization
	 */
	friend class boost::serialization::access;

	/**
	 * Serializes the planet model to a string.
	 * @param os The ostream.
	 * @param planet The planet we want to serialize.
	 * @return A string containing all information about the planet.
	 */
	friend std::ostream & operator<<(std::ostream &os,
		const EnvironmentPhysics &environmentPhysics) {
//		os
//
//		<< "/PlanetModel: Name=" << planet.mName /**!< The name of the creature */
//
//		/**The evolutionmodel of the planet*/
//		<< "\n/EvolutionModel=" << planet.mEvolutionModel
//
//		/**!< The environment of the planet */
//		<< "\n/EnvironmentModel=" << planet.mEnvironmentModel;
//
//		/**The epochs of the planet*/
//		for (std::vector<Epoch*>::const_iterator eit = planet.mEpochs.begin();
//			eit != planet.mEpochs.end(); eit++) {
//			os << (**eit) << "||";
//		}
//
//		/** The current epoch of the planet*/
//		os << "\n/Current Epoch=" << planet.mCurrentEpoch;
		return os;
	}

	/**
	 * Serializes the environment to an xml file.
	 * @param ar The archive.
	 * @param The file version.
	 */
	template<class Archive>
	void serialize(Archive & ar, const unsigned int /* file_version */) {
	}
};
BOOST_CLASS_VERSION(EnvironmentPhysics, 1)
BOOST_SERIALIZATION_ASSUME_ABSTRACT(EnvironmentPhysics)
#endif /* MODEL_UNIVERSE_ENVIRONMENTS_ENVIRONMENTPHYSICS_HPP_ */
