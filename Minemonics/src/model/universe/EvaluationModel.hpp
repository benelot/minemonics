#ifndef MODEL_UNIVERSE_EVALUATIONMODEL_HPP_
#define MODEL_UNIVERSE_EVALUATIONMODEL_HPP_

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
//## model headers
#include <model/universe/evolution/population/PopulationModel.hpp>

//## view headers
//## utils headers

/**
 * @brief		The evaluation model holds the information about the evaluation.
 * @details		 Details
 * @date		2015-06-01
 * @author		Benjamin Ellenberger
 */
class EvaluationModel {
public:
	EvaluationModel();
	virtual ~EvaluationModel();

	void initialize(PlanetModel* planetModel,double evaluationTime);

	PlanetModel* getPlanetModel() {
		return mPlanetModel;
	}

	void setPlanetModel(PlanetModel* planetModel) {
		mPlanetModel = planetModel;
	}

	void addPopulationModel(PopulationModel* populationModel);

private:
	PlanetModel* mPlanetModel;
	std::vector<PopulationModel*> mPopulationModels;

	double mEvaluationTime;
};

#endif /* MODEL_UNIVERSE_EVALUATIONMODEL_HPP_ */
