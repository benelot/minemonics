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

	/**
	 *  Evolution phase
	 */
	enum EvolutionPhase {
		VARIATION_PHASE, //!< Phase in which the genomes are varied
		EVALUATION_PHASE, //!< Phase in which the phenotypes are evaluated
		PROCESSING_PHASE, //!< Phase in which the phenotype's scores are processed
		CULLING_PHASE, //!< Phase in which the bad phenotypes are culled
		NUM_EVOLUTION_PHASES //!< NUM_EVOLUTION_PHASES
	};

	/**
	 * The type evaluation
	 */
	enum EvaluationType {
		INDIVIDUAL_EVALUATION, //!< Every individual gets separately evaluated.
		N_INDIVIDUALS_TOURNAMENT_EVALUATION, //!< Individual get evaluated in groups of n (Individuals Tournament).
		POPULATION_EVALUATION, //!< Each population gets evaluated as a whole.
		N_POPULATION_EVALUATION, //!< A group of n individuals from each population get evaluated.
		N_POPULATIONS_TOURNAMENT_EVALUATION, //!< N populations are evaluated together (Populations Tournament).
		POPULATIONS_EVALUATION, //!< All populations are evaluated together.
		NUM_EVALUATION_TYPES
	};

	EvolutionModel();
	~EvolutionModel();

	/**
	 * Initialize the evolution model.
	 * @param type The evaluation type.
	 * @param evaluationTime The evaluation time in this evolution model
	 * @param tournamentSize The size of the tournament for simultaneous evaluation
	 */
	void initialize(const EvaluationType type = INDIVIDUAL_EVALUATION,
			const double evaluationTime = 10, const int tournamentSize = 1);

	/**
	 * Perform embryogenesis on all creatures that are not developed.
	 */
	void performEmbryogenesis();

	/**
	 * Add a new population to the evolution model.
	 * @param populationModel The population to be added.
	 */
	void addNewPopulation(PopulationModel* const populationModel);

	/**
	 * Proceed the evaluation.
	 * @return If the evaluation could be proceeded.
	 */
	bool proceedEvaluation();

	/**
	 * Evaluate the evolution.
	 * @return If the evolution could be evaluated.
	 */
	bool evaluate();

	/**
	 * Process the evaluated individuals.
	 * @return If the individuals could be processed.
	 */
	bool process();

	/**
	 * Cull the bad individuals.
	 * @return If the individuals could be culled.
	 */
	bool cull();

	/**
	 * Variate the individuals.
	 * @return If the individuals could be variated.
	 */
	bool variate();

	//Accessor methods
	Reaper& getReaper() {
		return mReaper;
	}

	const EvolutionPhase getPhase() const {
		return mPhase;
	}

	const EvaluationType getType() const {
		return mType;
	}

	std::vector<PopulationModel*>& getPopulationModels() {
		return mPopulationModels;
	}

	const double getEvaluationTime() const {
		return mEvaluationTime;
	}

	const std::vector<CreatureModel*>::size_type getCurrentCreatureIndex() const {
		return mCurrentCreatureIndex;
	}

	bool setCurrentCreatureIndex(
			const std::vector<CreatureModel*>::size_type currentCreatureIndex) {
		if (currentCreatureIndex
				< mPopulationModels[mCurrentPopulationIndex]->getCreatureModels().size()) {
			mCurrentCreatureIndex = currentCreatureIndex;
			return true;
		} else {
			return false;
		}
	}

	const std::vector<PopulationModel*>::size_type getCurrentPopulationIndex() const {
		return mCurrentPopulationIndex;
	}

	void setCurrentPopulationIndex(
			const std::vector<PopulationModel*>::size_type currentPopulationIndex) {
		mCurrentPopulationIndex = currentPopulationIndex;
	}

	const unsigned long getTournamentSize() const {
		return mTournamentSize;
	}

private:
	/**
	 * The vector of populations that are evaluated.
	 */
	std::vector<PopulationModel*> mPopulationModels;

	/**
	 * The currently evaluated population.
	 */
	std::vector<PopulationModel*>::size_type mCurrentPopulationIndex;

	/**
	 * The currently evaluated creature.
	 */
	std::vector<CreatureModel*>::size_type mCurrentCreatureIndex;

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

	/**
	 * Tournament size
	 */
	unsigned long mTournamentSize;
};

#endif /* MODEL_UNIVERSE_EVOLUTION_EVOLUTIONMODEL_HPP_ */
