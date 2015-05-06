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
	EvolutionModel();
	~EvolutionModel();

	void proceed();

	//accessor methods
	const Reaper& getReaper() const {
		return mReaper;
	}

	void setReaper(const Reaper& reaper) {
		mReaper = reaper;
	}

protected:
	/**
	 * The vector of populations that are evaluated.
	 */
	std::vector<PopulationModel> populationModels;
private:
	Reaper mReaper;

	// Evolution states
	enum EvolutionState
	{
		EVALUATION, GENERATION, PROCESSING
	};

	EvolutionState mState;


	/**
	 * The type evaluation
	 */
	enum EvaluationType
	{
		INDIVIDUAL_EVALUATION,N_EVALUATION,POPULATION_EVALUATION
	};

	EvaluationType mType;
};

#endif /* MODEL_UNIVERSE_EVOLUTION_EVOLUTIONMODEL_HPP_ */
