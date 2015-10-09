#ifndef MODEL_UNIVERSE_ENVIRONMENTS_PLANEMODEL_HPP_
#define MODEL_UNIVERSE_ENVIRONMENTS_PLANEMODEL_HPP_

//# corresponding headers
#include <model/universe/environments/EnvironmentModel.hpp>

//# forward declarations
class PlaneBt;

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
 * @brief		The plane model holds all the information about a plane.
 * @details		Details
 * @date		2015-05-30
 * @author		Benjamin Ellenberger
 */
class PlaneModel: public EnvironmentModel {
public:
	PlaneModel();
	PlaneModel(PhysicsController::PhysicsModelType type);
	virtual ~PlaneModel();

	/**
	 * Initialize the plane model.
	 */
	virtual void initialize();

	/**
	 * Update the plane model.
	 * @param timeSinceLastTick The time that has passed since the last update.
	 */
	virtual void update(double timeSinceLastTick);

	//Accessor methods
	PlaneBt* const getPlaneBt() const {
		return (PlaneBt*) mEnvironmentPhysics;
	}

	//Serialization
	/**
	 * Give access to boost serialization
	 */
	friend class boost::serialization::access;

	/**
	 * Serializes the plane model to a string.
	 * @param os The ostream.
	 * @param planet The planet we want to serialize.
	 * @return A string containing all information about the plane.
	 */
	friend std::ostream & operator<<(std::ostream &os,
		const PlaneModel &planeModel) {
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
	 * Serializes the plane to an xml file.
	 * @param ar The archive.
	 * @param The file version.
	 */
	template<class Archive>
	void serialize(Archive & ar, const unsigned int /* file_version */) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(EnvironmentModel); /**!< Serialize the base object */
	}
};

#endif /* MODEL_UNIVERSE_ENVIRONMENTS_PLANEMODEL_HPP_ */
