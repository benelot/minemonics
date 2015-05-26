#ifndef CONTROLLER_UNIVERSE_UNIVERSE_HPP_
#define CONTROLLER_UNIVERSE_UNIVERSE_HPP_

//# corresponding header
//# forward declarations
class Planet;

//# system headers
#include <vector>

//## controller headers
//## model headers
#include <model/universe/UniverseModel.hpp>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers

/**
 * @brief		The universe is the class that contains everything: Creatures in populations under evolutionary rules and in environments on different planets.
 * @details		The Answer to the Ultimate Question of Life, the Universe, and Everything: 42. But we do not know the question.
 * @date		2015-04-06
 * @author		Benjamin Ellenberger
 */

class Universe {
public:
	Universe();
	virtual ~Universe();

	void initialize();

	void addPlanet(Planet* planet);

	void proceedEvaluation();

	void update();

	//Accessor methods

	Planet*& getCurrentEvaluationPlanet() {
		return mPlanets[mUniverseModel.getCurrentEvaluationPlanetIndex()];
	}

	void setCurrentEvaluationPlanet(const Planet*& currentEvaluationPlanet) {
		mUniverseModel.setCurrentEvaluationPlanetIndex(0);
		//mCurrentEvaluationPlanet = currentEvaluationPlanet;
	}

	const std::vector<Planet*>& getPlanets() const {
		return mPlanets;
	}

	const UniverseModel& getUniverseModel() const {
		return mUniverseModel;
	}

private:

	/**
	 * The model of the universe
	 */
	UniverseModel mUniverseModel;

	/**
	 * The planets in this universe
	 */
	std::vector<Planet*> mPlanets;
};

#endif /* CONTROLLER_UNIVERSE_UNIVERSE_HPP_ */
