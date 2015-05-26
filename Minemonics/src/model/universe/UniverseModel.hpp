#ifndef MODEL_UNIVERSE_UNIVERSEMODEL_HPP_
#define MODEL_UNIVERSE_UNIVERSEMODEL_HPP_

//# corresponding header
//# forward declarations
class PlanetModel;

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

	void initialize();

	void addPlanetModel(PlanetModel* planetModel);

	void proceedEvaluation();

	//Accessor methods

	int getCurrentEvaluationPlanetIndex() const {
		return mCurrentEvaluationPlanetIndex;
	}

	void setCurrentEvaluationPlanetIndex(int currentEvaluationPlanetIndex) {
		mCurrentEvaluationPlanetIndex = currentEvaluationPlanetIndex;
	}

	const std::vector<PlanetModel*>& getPlanetModels() const {
		return mPlanetModels;
	}

private:
	/**
	 * The models of the planets in this universe.
	 */
	std::vector<PlanetModel*> mPlanetModels;

	/**
	 * Planet being currently evaluated.
	 */
	int mCurrentEvaluationPlanetIndex;
};

#endif /* MODEL_UNIVERSE_UNIVERSEMODEL_HPP_ */
