//# corresponding headers
#include <model/universe/UniverseModel.hpp>

//# forward declarations
//# system headers
//## controller headers
//## model headers
//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
#include <model/universe/PlanetModel.hpp>

//## view headers
//## utils headers



UniverseModel::UniverseModel() :
		mCurrentEvaluationPlanetIndex(0) {
	// TODO Auto-generated constructor stub

}

UniverseModel::~UniverseModel() {
	// TODO Auto-generated destructor stub
}

void UniverseModel::initialize() {
}

void UniverseModel::addPlanetModel(PlanetModel* planetModel) {
	mPlanetModels.push_back(planetModel);
}

void UniverseModel::proceedEvaluation() {
	if (mPlanetModels.size() != 0) {
		if (mCurrentEvaluationPlanetIndex < mPlanetModels.size()) {
			if (!mPlanetModels[mCurrentEvaluationPlanetIndex]->proceedEvaluation()) {
				mCurrentEvaluationPlanetIndex =
						(mCurrentEvaluationPlanetIndex < mPlanetModels.size()) ?
								mCurrentEvaluationPlanetIndex + 1 : 0;
			}
		}
	}
}
