#ifndef CONTROLLER_EVALUATION_HPP_
#define CONTROLLER_EVALUATION_HPP_

//# corresponding headers
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
#include <controller/universe/evolution/population/Population.hpp>

//## model headers
#include <model/universe/EvaluationModel.hpp>

//## view headers
//## utils headers

/**
 * @brief		An evaluation holds the creatures and the planet that is evaluated by the simulator, possibly in parallel with other planets.
 * @details		 Details
 * @date		2015-06-01
 * @author		Benjamin Ellenberger
 */
class Evaluation {
public:
	Evaluation();
	virtual ~Evaluation();

	void initialize(Planet* planet);

	void addPopulation(Population* population);

private:
	EvaluationModel mEvaluationModel;

	Planet* mPlanet;

	std::vector<Population*> mPopulations;
};

#endif /* CONTROLLER_EVALUATION_HPP_ */
