#ifndef MODEL_UNIVERSE_EVOLUTION_EVOLUTIONMODEL_HPP_
#define MODEL_UNIVERSE_EVOLUTION_EVOLUTIONMODEL_HPP_

//# corresponding header
//# forward declarations

//# system headers
#include <vector>

//## controller headers
//## model headers
#include <model/universe/evolution/Reaper.hpp>
#include <model/universe/evolution/population/PopulationModel.hpp>

//## view headers
//## utils headers

/**
 * @brief		The model of the evolution holds information about the evolution.
 * @details		Details
 * @date		2015-03-08
 * @author		Benjamin Ellenberger
 */
class EvolutionModel {
public:

	// Evolution phase
	enum EvolutionPhase {
		VARIATION_PHASE, EVALUATION_PHASE, PROCESSING_PHASE, CULLING_PHASE
	};

	/**
	 * The type evaluation
	 */
	enum EvaluationType {
		INDIVIDUAL_EVALUATION /**< Every individual gets separately evaluated.*/,
		N_INDIVIDUALS_TOURNAMENT_EVALUATION /**< Individual get evaluated in groups of n (Individuals Tournament).*/,
		POPULATION_EVALUATION /**< Each population gets evaluated as a whole.*/,
//		N_POPULATION_EVALUATION /**< A group of n individuals from each population get evaluated.*/,
		N_POPULATIONS_TOURNAMENT_EVALUATION /**< N populations are evaluated together (Populations Tournament).*/,
		POPULATIONS_EVALUATION/**< All populations are evaluated together.*/
	};

	EvolutionModel();
	~EvolutionModel();

	void initialize(EvaluationType type, double evaluationTime);

	void update();

	void addNewPopulation(PopulationModel* populationModel);

	bool proceedEvaluation();

	bool evaluate();

	bool process();

	bool cull();

	bool variate();

	//accessor methods
	const Reaper& getReaper() const {
		return mReaper;
	}

	EvolutionPhase getPhase() const {
		return mPhase;
	}

	EvaluationType getType() const {
		return mType;
	}

	std::vector<PopulationModel*>& getPopulationModels() {
		return mPopulationModels;
	}

	double getEvaluationTime() const {
		return mEvaluationTime;
	}

	int getCurrentCreatureIndex() const {
		return mCurrentCreatureIndex;
	}

	void setCurrentCreatureIndex(int currentCreatureIndex) {
		mCurrentCreatureIndex = currentCreatureIndex;
	}

	int getCurrentPopulationIndex() const {
		return mCurrentPopulationIndex;
	}

	void setCurrentPopulationIndex(int currentPopulationIndex) {
		mCurrentPopulationIndex = currentPopulationIndex;
	}

private:
	/**
	 * The vector of populations that are evaluated.
	 */
	std::vector<PopulationModel*> mPopulationModels;

	/**
	 * The currently evaluated population.
	 */
	int mCurrentPopulationIndex;

	/**
	 * The currently evaluated creature.
	 */
	int mCurrentCreatureIndex;

	/**
	 * The reaper of this evolution model.
	 */
	Reaper mReaper;

	/**
	 * The phase this evolution is in.
	 */
	EvolutionPhase mPhase;

	/**
	 * The type of evolution model.
	 */
	EvaluationType mType;

	/**
	 * Evaluation time
	 */
	double mEvaluationTime;
};

#endif /* MODEL_UNIVERSE_EVOLUTION_EVOLUTIONMODEL_HPP_ */
