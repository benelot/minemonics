#ifndef MODEL_UNIVERSE_UNIVERSEMODEL_HPP_
#define MODEL_UNIVERSE_UNIVERSEMODEL_HPP_

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
#include <model/universe/PlanetModel.hpp>
#include <model/universe/EvaluationModel.hpp>

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
	void addPlanetModel(PlanetModel* const planetModel);

	/**
	 * Proceed the evaluation.
	 */
	void proceedEvaluation();

	// Accessor methods ##########################

	const std::vector<PlanetModel*>::size_type getEvaluatingPlanetIndex() const {
		return mEvaluatingPlanetIndex;
	}

	void setEvaluatingPlanetIndex(
			const std::vector<PlanetModel*>::size_type evaluatingPlanetIndex) {
		mEvaluatingPlanetIndex = evaluatingPlanetIndex;
	}

	const std::vector<EvaluationModel*>& getEvaluationModels() const {
		return mEvaluationModels;
	}

	const std::vector<PlanetModel*>& getPlanetModels() const {
		return mPlanetModels;
	}

private:

	std::vector<EvaluationModel*> mEvaluationModels; /**!< The evaluations currently running */

	std::vector<PlanetModel*> mPlanetModels; /**!< The models of the planets in this universe. */

	std::vector<PlanetModel*>::size_type mEvaluatingPlanetIndex; /**!< Planet being currently evaluated. */
};

#endif /* MODEL_UNIVERSE_UNIVERSEMODEL_HPP_ */
