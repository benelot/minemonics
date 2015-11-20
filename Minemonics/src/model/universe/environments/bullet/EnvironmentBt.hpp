#ifndef MODEL_BULLET_ENVIRONMENTS_ENVIRONMENTBT_H_
#define MODEL_BULLET_ENVIRONMENTS_ENVIRONMENTBT_H_

//# corresponding headers
#include <configuration/Definitions.hpp>
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
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/version.hpp>
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

	/**
	 * Create the terrain.
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
	virtual void createTerrainData(Ogre::SceneNode* const sceneNode,
		const float w, const float h, const float* const data, const float minH,
		const float maxH, const Ogre::Vector3& pos, const float scale,
		const float heightScale);

	// Accessor methods ##########################
	/**
	 * Get the rigid body of the environment.
	 * @return The rigid body of the environment.
	 */
	virtual btRigidBody*& getBody() = 0;

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
		const EnvironmentBt &environmentBt) {
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
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(EnvironmentPhysics); /**!< Serialize the base object */
	}

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
				boost::log::attributes::constant < std::string
					> ("EnvironmentBt"));
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
BOOST_CLASS_VERSION(EnvironmentBt, 1)
BOOST_SERIALIZATION_ASSUME_ABSTRACT(EnvironmentBt)
#endif /* MODEL_BULLET_ENVIRONMENTS_ENVIRONMENTBT_H_ */
