#ifndef MODEL_UNIVERSE_ENVIRONMENTS_PHYSICS_GROUNDCONTROLLER_H_
#define MODEL_UNIVERSE_ENVIRONMENTS_PHYSICS_GROUNDCONTROLLER_H_

//# forward declarations
#include <model/universe/environments/physics/PhysicsController.hpp>
#include <configuration/Definitions.hpp>

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
//## view headers
//## utils headers

/**
 * @brief		The ground controller simulates physical motion similar to motion on ground.
 * @details		Details
 * @date		2014-11-17
 * @author		Benjamin Ellenberger
 */
class GroundController: public PhysicsController {
public:
	GroundController();
	GroundController(PhysicsController::PhysicsModelType solverType);
	virtual ~GroundController();

	// Serialization ##########################
	friend class boost::serialization::access; /**!< Give access to boost serialization */

	/**
	 * Serializes the planet model to a string.
	 * @param os The ostream.
	 * @param planet The planet we want to serialize.
	 * @return A string containing all information about the planet.
	 */
	friend std::ostream & operator<<(std::ostream &os,
		const GroundController &groundController) {
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
	 * Serializes the ground controller to an xml file.
	 * @param ar The archive.
	 * @param The file version.
	 */
	template<class Archive>
	void serialize(Archive & ar, const unsigned int /* file_version */) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(PhysicsController); /**!< Serialize the base object */
	}
};
BOOST_CLASS_VERSION(GroundController, 1)
#endif /* MODEL_UNIVERSE_ENVIRONMENTS_PHYSICS_GROUNDCONTROLLER_H_ */
