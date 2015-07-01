#ifndef MODEL_UNIVERSE_UNIVERSEMODEL_HPP_
#define MODEL_UNIVERSE_UNIVERSEMODEL_HPP_

//# corresponding header
//# forward declarations
class PlanetModel;
class EvaluationModel;

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
//## view headers
//## utils headers

/**
 * @brief		The universe model holds information about the universe.
 * @details		The Answer to the Ultimate Question of Life, the Universe, and Everything: 42. But we do not know the question.
 * @date		2015-04-06
 * @author		Benjamin Ellenberger
 */
class UniverseModel {
public:
	UniverseModel();
	virtual ~UniverseModel();

	/**
	 * Initialize the universe model.
	 */
	void initialize();

	/**
	 * Add a planet model to the universe model.
	 * @param planetModel The planet model to add.
	 */
	void addPlanetModel(PlanetModel* planetModel);

	/**
	 * Proceed the evaluation.
	 */
	void proceedEvaluation();

	//Accessor methods
	std::vector<PlanetModel*>::size_type getCurrentEvaluationPlanetIndex() const {
		return mCurrentEvaluationPlanetIndex;
	}

	void setCurrentEvaluationPlanetIndex(
			std::vector<PlanetModel*>::size_type currentEvaluationPlanetIndex) {
		mCurrentEvaluationPlanetIndex = currentEvaluationPlanetIndex;
	}

	const std::vector<EvaluationModel*>& getEvaluationModels() const {
		return mEvaluationModels;
	}

	const std::vector<PlanetModel*>& getPlanetModels() const {
		return mPlanetModels;
	}

private:

	/**
	 * Vector of evaluation models
	 */
	std::vector<EvaluationModel*> mEvaluationModels;

	/**
	 * The models of the planets in this universe.
	 */
	std::vector<PlanetModel*> mPlanetModels;

	/**
	 * Planet being currently evaluated.
	 */
	std::vector<PlanetModel*>::size_type mCurrentEvaluationPlanetIndex;
};

#endif /* MODEL_UNIVERSE_UNIVERSEMODEL_HPP_ */
