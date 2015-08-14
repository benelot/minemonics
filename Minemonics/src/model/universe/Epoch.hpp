#ifndef MODEL_UNIVERSE_EPOCH_HPP_
#define MODEL_UNIVERSE_EPOCH_HPP_

//# corresponding header
//# forward declarations
//# system headers
#include <vector>

//## controller headers
//## model headers
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

	bool isEndOfEpoch();
	//Accessor methods

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
		return mLastingGenerations;
	}

	void setLastingGenerations(int lastingGenerations) {
		mLastingGenerations = lastingGenerations;
	}

	void addJuryType(Jury::JuryType type, double weight, bool higherIsBetter) {
		mJuryTypes.push_back(type);
		mWeights.push_back(weight);
		mSortOrders.push_back(higherIsBetter);
	}

	int getLastingGenerationsLimit() const {
		return mLastingGenerationsLimit;
	}

	void setLastingGenerationsLimit(int lastingGenerationsLimit) {
		mLastingGenerationsLimit = lastingGenerationsLimit;
	}

	bool isLastingGenerationsReached(){
		return mLastingGenerationsLimit <= mLastingGenerations;
	}

	bool isFitnessReached(){
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

private:
	std::vector<Jury::JuryType> mJuryTypes;

	std::vector<double> mWeights;

	std::vector<bool> mSortOrders;

	//Epoch criteria

	//Number of generations
	bool mGenerationsEnabled;
	int mLastingGenerations;
	int mLastingGenerationsLimit;

	//Reached fitness
	bool mFitnessEnabled;
	double mCurrentFitness;
	double mEndingAtFitness;
};

#endif /* MODEL_UNIVERSE_EPOCH_HPP_ */
