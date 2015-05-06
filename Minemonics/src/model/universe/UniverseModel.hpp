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

private:
	/**
	 * The models of the planets in this universe.
	 */
	std::vector<PlanetModel*> mPlanetModels;
};

#endif /* MODEL_UNIVERSE_UNIVERSEMODEL_HPP_ */