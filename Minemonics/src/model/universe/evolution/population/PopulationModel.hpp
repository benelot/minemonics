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
#include <iterator>
#include <vector>

//## controller headers
//## model headers
#include <boost/serialization/nvp.hpp>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
#include <model/universe/PlanetModel.hpp>
#include <model/universe/evolution/population/creature/CreatureModel.hpp>

//## view headers
//## utils headers

/**
 * @brief		The population model holds the information about a population of creatures.
 * @details		Details
 * @date		2015-03-09
 * @author		Benjamin Ellenberger
 */
class PopulationModel {
public:
	PopulationModel();
	virtual ~PopulationModel();

	/**
	 * Initialize the population model
	 * @param planetModel The planet the population lives on.
	 * @param creatureQty The number of creatures living in the population.
	 */
	void initialize(PlanetModel* planetModel,int creatureQty);

	/**
	 * Adds a new creature to the population.
	 */
	void addMember(CreatureModel* creatureModel);

	/**
	 * Proceed with the evaluation.
	 * @return If the evaluation could be proceeded.
	 */
	bool proceedEvaluation();

	/**
	 * Tests if a population is equal to another population.
	 * @param population The population to test for equality.
	 * @return If this population and the other are equal.
	 */
	bool equals(const PopulationModel & population) const;

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
		std::vector<CreatureModel*>::const_iterator it;
		for (it = population.mCreatureModels.begin();
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
		ar & BOOST_SERIALIZATION_NVP(mCreatureQty) & BOOST_SERIALIZATION_NVP(
				mCreatureModels);
	}

	//Accessor methods

	int getCreatureQty() const {
		return mCreatureQty;
	}

	void setCreatureQty(int creatureQty) {
		mCreatureQty = creatureQty;
	}

	const std::vector<CreatureModel*>& getCreatureModels() const {
		return mCreatureModels;
	}

	PlanetModel* getPlanetModel() {
		return mPlanetModel;
	}

	void setPlanetModel(PlanetModel* planetModel) {
		mPlanetModel = planetModel;
	}

private:
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
};

#endif /* MODEL_UNIVERSE_EVOLUTION_POPULATION_POPULATIONMODEL_HPP_ */
