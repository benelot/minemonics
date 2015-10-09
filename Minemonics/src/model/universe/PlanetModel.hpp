#ifndef MODEL_UNIVERSE_PLANETMODEL_HPP_
#define MODEL_UNIVERSE_PLANETMODEL_HPP_

//# corresponding header
#include <model/Serializable.hpp>

//# forward declarations
class EnvironmentModel;
class EvolutionModel;

//# system headers
#include <vector>

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
#include <model/universe/Epoch.hpp>
#include <model/universe/environments/physics/PhysicsController.hpp>
#include <model/universe/environments/PlaneModel.hpp>

//## view headers
//## utils headers

/**
 * @brief		The planet model holds information about the planet.
 * @details		Details
 * @date		2015-04-06
 * @author		Benjamin Ellenberger
 */
class PlanetModel: public Serializable {
public:
	PlanetModel();
	virtual ~PlanetModel();

	/**
	 * Initialize the planet model.
	 * @param evolutionModel Its evolution model.
	 * @param environmentModel Its environment model.
	 */
	void initialize(EvolutionModel* const evolutionModel,
		EnvironmentModel* const environmentModel);

	/**
	 * Perform embryogenesis on all creatures that are not yet developed.
	 */
	void performEmbryogenesis();

	/**
	 * Proceed with the evaluation.
	 * @return If the evaluation could proceed.
	 */
	bool proceedEvaluation();

	/**
	 * Update the planet.
	 */
	void update(double timeSinceLastTick);

	//Accessor methods

	EnvironmentModel* const getEnvironmentModel() const {
		return mEnvironmentModel;
	}

	void setEnvironmentModel(EnvironmentModel* const environmentModel) {
		mEnvironmentModel = environmentModel;
	}

	EvolutionModel* const getEvolutionModel() const {
		return mEvolutionModel;
	}

	void setEvolutionModel(EvolutionModel* const evolutionModel) {
		mEvolutionModel = evolutionModel;
	}

	void addEpoch(Epoch* epoch) {
		mEpochs.push_back(epoch);
	}

	Epoch* getCurrentEpoch() {
		return mEpochs[mCurrentEpoch];
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
		const PlanetModel &planet) {
		os

		<< "/PlanetModel: Name=" << planet.mName /**!< The name of the creature */

		/**The evolutionmodel of the planet*/
		<< "\n/EvolutionModel=" << planet.mEvolutionModel

		/**!< The environment of the planet */
		<< "\n/EnvironmentModel=" << planet.mEnvironmentModel;

		/**The epochs of the planet*/
		for (std::vector<Epoch*>::const_iterator eit = planet.mEpochs.begin();
			eit != planet.mEpochs.end(); eit++) {
			os << (**eit) << "||";
		}

		/** The current epoch of the planet*/
		os << "\n/Current Epoch=" << planet.mCurrentEpoch;
		return os;
	}

	/**
	 * Serializes the planet to an xml file.
	 * @param ar The archive.
	 * @param The file version.
	 */
	template<class Archive>
	void serialize(Archive & ar, const unsigned int /* file_version */) {
		ar.register_type(static_cast<PlaneModel*>(NULL));

		ar
		/**!< The name of the planet */
		& BOOST_SERIALIZATION_NVP(mName)

		/**The evolutionmodel of the planet*/
		& BOOST_SERIALIZATION_NVP(mEvolutionModel)

		/**!< The environment of the planet */
		& BOOST_SERIALIZATION_NVP(mEnvironmentModel)

		/**The epochs of the planet*/
		& BOOST_SERIALIZATION_NVP(mEpochs)

		/** The current epoch of the planet*/
		& BOOST_SERIALIZATION_NVP(mCurrentEpoch);
	}

private:

	std::string mName; /**!< The name of the planet */

	EvolutionModel* mEvolutionModel; /**!< The evolution model of this planet.*/

	EnvironmentModel* mEnvironmentModel; /**!< The environment model of this planet.*/

	std::vector<Epoch*> mEpochs; /**!< The epochs of the planet. */

	int mCurrentEpoch; /**!< The current epoch of the planet */
};
BOOST_CLASS_VERSION(PlanetModel, 1)
#endif /* MODEL_UNIVERSE_PLANETMODEL_HPP_ */
