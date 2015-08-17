#ifndef CONTROLLER_EVALUATION_HPP_
#define CONTROLLER_EVALUATION_HPP_

//# corresponding headers
//# forward declarations
//# system headers
#include <string>
#include <vector>

//## controller headers
//## model headers
#include <boost/log/attributes/constant.hpp>
#include <boost/log/sources/basic_logger.hpp>

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
#include <utils/logging/Logger.hpp>

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

	/**
	 * Initialize the evaluation.
	 * @param planet The planet on which the evaluation takes place.
	 * @param evaluationTime The evaluation time in this evaluation
	 */
	void initialize(Planet* const planet, const double evaluationTime);

	/**
	 * Add a population to the evaluation
	 * @param population The population to be added to the evaluation.
	 */
	void addPopulation(Population* const population);

	/**
	 * Setup the evaluation.
	 */
	void setup();

	/**
	 * Process the evaluated individuals.
	 */
	void process();

	/**
	 * Tear the evaluation down.
	 */
	void teardown();

	/**
	 * Update the evaluation.
	 * @param timeSinceLastFrame The time since the last graphics frame.
	 */
	void update(const double timeSinceLastFrame);

	// Facade accessor methods
	bool isEvaluating() const {
		return mEvaluationModel.isEvaluating();
	}

	bool isTornDown() const {
		return mEvaluationModel.isTornDown();
	}

	const std::vector<Population*>& getPopulations() const {
		return mPopulations;
	}

private:
	/**
	 * The boost logger.
	 */
	static BoostLogger mBoostLogger;

	/**
	 * Initializer of the boost logger to include the class name into the logging messages.
	 */
	static class _Init {
	public:
		_Init() {
			mBoostLogger.add_attribute("ClassName",
					boost::log::attributes::constant<std::string>(
							"Evaluation"));
		}
	} _initializer;

	/**
	 * The model representation of the evaluation.
	 */
	EvaluationModel mEvaluationModel;

	/**
	 * The planet the evaluation takes place on.
	 */
	Planet* mPlanet;

	/**
	 * The populations taking part in the evaluation.
	 */
	std::vector<Population*> mPopulations;

	unsigned long int mStart;

	bool mHasDiscardingTestRun;

	bool mHasFailed;
};

#endif /* CONTROLLER_EVALUATION_HPP_ */
