#ifndef MODEL_UNIVERSE_EVOLUTION_EVOLUTIONMODEL_HPP_
#define MODEL_UNIVERSE_EVOLUTION_EVOLUTIONMODEL_HPP_

//# corresponding header
//# forward declarations
class Creature;
class Environment;

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

	// Evolution states
		enum EvolutionState {
			EVALUATION, GENERATION, PROCESSING
		};

		/**
		 * The type evaluation
		 */
		enum EvaluationType {
			INDIVIDUAL_EVALUATION /**< Every individual gets separately evaluated.*/,
			N_TOURNAMENT_EVALUATION /**< Individual get evaluated in groups of n (Individuals Tournament).*/,
			POPULATION_EVALUATION /**< Each population gets evaluated as a whole.*/,
			N_POPULATION_EVALUATION /**< A group of n individuals from each population get evaluated.*/,
			N_POPULATIONS_EVALUATION /**< N populations are evaluated together (Populations Tournament).*/,
			POPULATIONS_EVALUATION/**< All populations are evaluated together.*/
		};

	EvolutionModel();
	~EvolutionModel();

	void initialize(double evaluationTime);

	bool evaluate();

	bool selectAndReap();

	bool evolve();

	//accessor methods
	const Reaper& getReaper() const {
		return mReaper;
	}

	EvolutionState getState() const {
		return mState;
	}

	EvaluationType getType() const {
		return mType;
	}

	const std::vector<PopulationModel>& getPopulationModels() const {
		return populationModels;
	}

	double getEvaluationTime() const {
		return mEvaluationTime;
	}

private:
	/**
	 * The vector of populations that are evaluated.
	 */
	std::vector<PopulationModel> populationModels;

	/**
	 * The reaper of this evolution model.
	 */
	Reaper mReaper;

	/**
	 * The state this evolution is in.
	 */
	EvolutionState mState;

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
