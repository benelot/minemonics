#ifndef MODEL_UNIVERSE_EPOCH_HPP_
#define MODEL_UNIVERSE_EPOCH_HPP_

//# corresponding header
//# forward declarations
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
#include <model/universe/evolution/juries/Jury.hpp>

//## view headers
//## utils headers

/**
 * @brief		An epoch is a time in which the evolution scheme does not change. It holds for a certain number of generations or a certain fitness value etc.
 * @details		Details
 * @date		2015-05-16
 * @author		Benjamin Ellenberger
 */
class Epoch {
public:
	Epoch();
	virtual ~Epoch();

	// Accessor methods ##########################

	bool isEndOfEpoch();

	double getEndingAtFitness() const {
		return mEndingAtFitness;
	}

	void setEndingAtFitness(double endingAtFitness) {
		mEndingAtFitness = endingAtFitness;
	}

	bool isFitnessEnabled() const {
		return mFitnessEnabled;
	}

	void setFitnessEnabled(bool fitnessEnabled) {
		mFitnessEnabled = fitnessEnabled;
	}

	bool isGenerationsEnabled() const {
		return mGenerationsEnabled;
	}

	void setGenerationsEnabled(bool generationsEnabled) {
		mGenerationsEnabled = generationsEnabled;
	}

	int getLastingGenerations() const {
		return mCurrentGeneration;
	}

	void setLastingGenerations(int lastingGenerations) {
		mCurrentGeneration = lastingGenerations;
	}

	void addJuryType(Jury::JuryType type, double weight, bool higherIsBetter) {
		mJuryTypes.push_back(type);
		mWeights.push_back(weight);
		mSortOrders.push_back(higherIsBetter);
	}

	int getEndingAtGeneration() const {
		return mEndingAtGeneration;
	}

	void setEndingAtGeneration(int endingAtGeneration) {
		mEndingAtGeneration = endingAtGeneration;
	}

	bool isEndingGenerationReached() {
		return mEndingAtGeneration <= mCurrentGeneration;
	}

	bool isFitnessReached() {
		return mCurrentFitness >= mEndingAtFitness;
	}

	double getCurrentFitness() const {
		return mCurrentFitness;
	}

	void setCurrentFitness(double currentFitness) {
		mCurrentFitness = currentFitness;
	}

	const std::vector<Jury::JuryType>& getJuryTypes() const {
		return mJuryTypes;
	}

	const std::vector<double>& getWeights() const {
		return mWeights;
	}

	const std::vector<bool>& getSortOrders() const {
		return mSortOrders;
	}

	//Serialization

	/**
	 * Give access to boost serialization
	 */
	friend class boost::serialization::access;

	/**
	 * Serializes the epoch model to a string.
	 * @param os The ostream.
	 * @param planet The epoch we want to serialize.
	 * @return A string containing all information about the epoch.
	 */
	friend std::ostream & operator<<(std::ostream &os, const Epoch &epoch) {
		os

		<< "/Epoch: Fitness enabled=" << epoch.mFitnessEnabled /**!< If the epoch is related to fitness */

		<< "/Epoch: Current fitness=" << epoch.mCurrentFitness /**!< The current fitness */

		<< "/Epoch: Maximum fitness=" << epoch.mEndingAtFitness /**!< The maximum fitness */

		<< "/Epoch: Generations enabled=" << epoch.mGenerationsEnabled /**!< If the epoch is related to number of generations */

		<< "/Epoch: Current Generation=" << epoch.mCurrentGeneration /**!< The current generation */

		<< "/Epoch: Maximum Generation=" << epoch.mEndingAtGeneration; /**!< The maximum generation */

		/**The juries of the epoch*/
		for (int i = 0; i < epoch.mJuryTypes.size(); i++) {
			os << epoch.mJuryTypes[i] << "," << epoch.mSortOrders[i]
				<< epoch.mWeights[i] << "||";
		}

		return os;
	}

	/**
	 * Serializes the epoch to an xml file.
	 * @param ar The archive.
	 * @param The file version.
	 */
	template<class Archive>
	void serialize(Archive & ar, const unsigned int /* file_version */) {
		ar
		/**!< If the epoch is related to fitness */
		& BOOST_SERIALIZATION_NVP(mFitnessEnabled)

		/**!< The jury types of the epoch */
		& BOOST_SERIALIZATION_NVP(mJuryTypes)

		/**!< The weighting of the juries */
		& BOOST_SERIALIZATION_NVP(mWeights)

		/**!< If way the jury fitness is sorted */
		& BOOST_SERIALIZATION_NVP(mSortOrders)

		/**!< The current fitness */
		& BOOST_SERIALIZATION_NVP(mCurrentFitness)

		/**!< The maximum fitness */
		& BOOST_SERIALIZATION_NVP(mEndingAtFitness)

		/**!< If the epoch is related to generations */
		& BOOST_SERIALIZATION_NVP(mGenerationsEnabled)

		/**!< The current generation */
		& BOOST_SERIALIZATION_NVP(mCurrentGeneration)

		/**!< The maximum generation */
		& BOOST_SERIALIZATION_NVP(mEndingAtGeneration);
	}

private:
	//Epoch criteria
	std::vector<Jury::JuryType> mJuryTypes;
	std::vector<double> mWeights;
	std::vector<bool> mSortOrders;

	//Number of generations
	bool mGenerationsEnabled;
	int mCurrentGeneration;
	int mEndingAtGeneration;

	//Reached fitness
	bool mFitnessEnabled;
	double mCurrentFitness;
	double mEndingAtFitness;
};
BOOST_CLASS_VERSION(Epoch, 1)
#endif /* MODEL_UNIVERSE_EPOCH_HPP_ */
