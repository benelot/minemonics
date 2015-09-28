#ifndef MODEL_UNIVERSE_EVOLUTION_POPULATION_POPULATIONMODEL_HPP_
#define MODEL_UNIVERSE_EVOLUTION_POPULATION_POPULATIONMODEL_HPP_

//# corresponding headers
//# forward declarations
namespace boost {
namespace serialization {
class access;
} /* namespace serialization */
} /* namespace boost */

//# system headers
#include <iostream>
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
#include <model/universe/evolution/population/creature/CreatureModel.hpp>

//## view headers
//## utils headers

#include <model/universe/evolution/population/creature/CreatureModel.hpp>

/**
 * @brief		The population model holds the information about a population of creatures.
 * @details		Details
 * @date		2015-03-09
 * @author		Benjamin Ellenberger
 */
class PopulationModel {
public:
	PopulationModel();
	PopulationModel(const PopulationModel& populationModel);

	virtual ~PopulationModel();

	/**
	 * Initialize the population model
	 * @param planetModel The planet the population lives on.
	 * @param creatureQty The number of creatures living in the population.
	 */
	void initialize(PlanetModel* const planetModel, const int creatureQty);

	/**
	 * Adds a new creature to the population.
	 */
	void addMember(CreatureModel* const creatureModel);

	/**
	 * Tests if a population is equal to another population.
	 * @param population The population to test for equality.
	 * @return If this population and the other are equal.
	 */
	bool equals(const PopulationModel& population) const;

	/**
	 * Clone the population.
	 */
	PopulationModel* clone();

	bool hasInterpenetrations();

	//Accessor methods

	int getCreatureQty() const {
		return mCreatureQty;
	}

	void setCreatureQty(const int creatureQty) {
		mCreatureQty = creatureQty;
	}

	std::vector<CreatureModel*>& getCreatureModels() {
		return mCreatureModels;
	}

	const std::vector<CreatureModel*>& getCreatureModels() const {
		return mCreatureModels;
	}

	PlanetModel* getPlanetModel() const {
		return mPlanetModel;
	}

	void setPlanetModel(PlanetModel* const planetModel) {
		mPlanetModel = planetModel;
	}

	int getCurrentCreatureIndex() const {
		return mCurrentCreatureIndex;
	}

	bool isOutOfSync() const {
		return mOutOfSync;
	}

	void setOutOfSync(bool outOfSync) {
		mOutOfSync = outOfSync;
	}

	// Serialization
	/**
	 * Give access to boost serialization
	 */
	friend class boost::serialization::access;

	/**
	 * Serializes the population to a string.
	 * @param os The ostream.
	 * @param creature The population we want to serialize.
	 * @return A string containing all information about the population.
	 */
	friend std::ostream & operator<<(std::ostream &os,
		const PopulationModel &population) {
		os << population.mCreatureQty;
		for (std::vector<CreatureModel*>::const_iterator it =
			population.mCreatureModels.begin();
			it != population.mCreatureModels.end(); it++) {
			os << (**it);
		}
		return os;

	}

	/**
	 * Serializes the creature to an xml file.
	 * @param ar The archive.
	 * @param The file version.
	 */
	template<class Archive>
	void serialize(Archive & ar, const unsigned int /* file_version */) {
		ar & BOOST_SERIALIZATION_NVP(mCreatureQty)
			& BOOST_SERIALIZATION_NVP(mCreatureModels);
	}

private:

	/**
	 * If the population model is out of sync with the controller.
	 */
	bool mOutOfSync;

	/**
	 * The creatures living in this population. All creatures in one population can mate together.
	 */
	std::vector<CreatureModel*> mCreatureModels;

	/**
	 * The index of the creature that is currently evaluated.
	 */
	int mCurrentCreatureIndex;

	/**
	 * The number of creatures that the population will consist of in every generation.
	 */
	int mCreatureQty;

	/**
	 * The planet the population lives on.
	 */
	PlanetModel* mPlanetModel;

	/**
	 * The epochs of the population.
	 */
	std::vector<Epoch*> mEpochs;
};
BOOST_CLASS_VERSION(PopulationModel, 1)
#endif /* MODEL_UNIVERSE_EVOLUTION_POPULATION_POPULATIONMODEL_HPP_ */
