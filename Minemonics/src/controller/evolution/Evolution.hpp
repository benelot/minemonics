#ifndef CONTROLLER_EVOLUTION_EVOLUTION_HPP_
#define CONTROLLER_EVOLUTION_EVOLUTION_HPP_

//# forward declarations
//# system headers
//## controller headers
//## model headers
//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
#include <controller/environments/Environment.hpp>
#include <controller/evolution/population/creature/Creature.hpp>
#include <model/evolution/EvolutionModel.hpp>
#include <utils/TimerManager.hpp>

/**
 * @brief		Brief
 * @details		 A particular experimental setup is referred to as an "evolution".
 *      Evolutions consist of one or more independent GA runs, where each
 *      run is identical in terms of settings like population size,
 *      tournament size, mutation rates, and so on.
 *
 *      All creatures in the first generation of any run are produced from randomly-initialized genomes.
 *      Creatures in generations other than the first are produced either by mutation or
 *      crossover of parents selected by tournament from the previous generation. The sole
 *      exception is the first creature in such generations, which is always a copy of the best (or
 *      elite) creature from the previous generation. (Graham Lee Thesis)
 * @date		2015-04-28
 * @author		Benjamin Ellenberger
 */
class Evolution {
public:
	Evolution();
	virtual ~Evolution();

	/**
	 * Initialize the evolution.
	 */
	void initialize(Environment* environment);

	/**
	 * Proceed with the next creature of the currently tested population or
	 * proceed with reaping and sowing. This method is called by the
	 * EvaluationTimer after the predefined evaluation interval.
	 */
	void proceedEvaluation();


	//Accessor methods

	Environment* getEnvironment() {
		return mEnvironment;
	}

	void setEnvironment(Environment*& environment) {
		mEnvironment = environment;
	}

private:

	/**
	 * The model of the evolution
	 */
	EvolutionModel mEvolutionModel;

	/**
	 * The creature that is currently evaluated.
	 */
	Creature* mCurrentCreature;

	/**
	 * The environment the evolution is running in.
	 */
	Environment* mEnvironment;

	TimerManager<Evolution> mEvaluationManager;
};

#endif /* CONTROLLER_EVOLUTION_EVOLUTION_HPP_ */
