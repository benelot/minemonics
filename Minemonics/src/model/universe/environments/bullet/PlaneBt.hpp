#ifndef MODEL_ENVIRONMENT_PLANEBT_H_
#define MODEL_ENVIRONMENT_PLANEBT_H_

//# corresponding header
#include <configuration/Definitions.hpp>
#include <model/universe/environments/bullet/EnvironmentBt.hpp>

//# forward declarations
namespace boost {
namespace serialization {
class access;
} /* namespace serialization */
} /* namespace boost */

//# system headers
#include <iostream>

//## controller headers
//## model headers
#include <boost/serialization/base_object.hpp>
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
 * @brief		The bullet physics model implementation of the plane environment.
 * @details		Details
 * @date		2015-03-17
 * @author		Benjamin Ellenberger
 */
class PlaneBt: public EnvironmentBt {
public:
	PlaneBt();
	virtual ~PlaneBt();

	/**
	 * Initialize the plane bullet physics.
	 */
	void initialize();

	/**
	 * Update tehe plane bullet physics.
	 */
	virtual void update(double timeSinceLastTick);

	// Accessor methods ##########################
	btRigidBody*& getBody() {
		return mGroundBody;
	}

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
		const PlaneBt &planetBt) {
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
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(EnvironmentBt); /**!< Serialize the base object */
	}
private:
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
				boost::log::attributes::constant < std::string > ("PlaneBt"));
		}
	} _initializer;
};
BOOST_CLASS_VERSION(PlaneBt, 1)
#endif /* MODEL_ENVIRONMENT_PLANEBT_H_ */
