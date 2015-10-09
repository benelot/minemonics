#ifndef MODEL_UNIVERSE_ENVIRONMENTS_ENVIRONMENTMODEL_HPP_
#define MODEL_UNIVERSE_ENVIRONMENTS_ENVIRONMENTMODEL_HPP_

//# corresponding headers
#include <model/Serializable.hpp>

//# forward declarations
//# system headers
//## controller headers
//## model headers
#include <boost/serialization/vector.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/version.hpp>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
#include <model/universe/environments/physics/GroundController.hpp>
#include <model/universe/environments/EnvironmentPhysics.hpp>
#include <model/universe/environments/bullet/EnvironmentBt.hpp>
#include <model/universe/environments/bullet/PlaneBt.hpp>
#include <model/universe/environments/physics/PhysicsController.hpp>

//## view headers
//## utils headers

/**
 * @brief		The Environment model holds all general information about an environment.
 * @details		Details
 * @date		2015-05-06
 * @author		Benjamin Ellenberger
 */
class EnvironmentModel: public Serializable {
public:
	EnvironmentModel();
	virtual ~EnvironmentModel();

	/**
	 * Update the environment model.
	 */
	virtual void update(double timeSinceLastTick) = 0;

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

	void createTerrainData(Ogre::SceneNode* const sceneNode, const float w,
		const float h, const float* const data, const float minH,
		const float maxH, const Ogre::Vector3& pos, const float scale,
		const float heightScale) {
		mEnvironmentPhysics->createTerrainData(sceneNode, w, h, data, minH,
			maxH, pos, scale, heightScale);
	}

	PhysicsController* getPhysicsController() {
		return mPhysicsController;
	}

	void setPhysicsController(PhysicsController* physicsController) {
		mPhysicsController = physicsController;
	}

	//Serialization
	virtual void save();

	virtual void load();

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
		const EnvironmentModel &environmentModel) {
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
		ar.register_type(static_cast<GroundController*>(NULL));
		ar.register_type(static_cast<PhysicsController*>(NULL));

		ar.register_type(static_cast<PlaneBt*>(NULL));
//		ar.register_type(static_cast<EnvironmentBt*>(NULL));
//		ar.register_type(static_cast<EnvironmentPhysics*>(NULL));

		ar
		/**The physics controller of the environment*/
		& BOOST_SERIALIZATION_NVP(mPhysicsController)

		/**!< The environment physics of the environment */
		& BOOST_SERIALIZATION_NVP(mEnvironmentPhysics);
	}

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
BOOST_CLASS_VERSION(EnvironmentModel, 1)
#endif /* MODEL_UNIVERSE_ENVIRONMENTS_ENVIRONMENTMODEL_HPP_ */
