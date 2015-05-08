#ifndef MODEL_UNIVERSE_PLANETMODEL_HPP_
#define MODEL_UNIVERSE_PLANETMODEL_HPP_

//# corresponding header
//# forward declarations
class EnvironmentModel;
class EvolutionModel;

//# system headers
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
 * @brief		The planet model holds information about the planet.
 * @details		Details
 * @date		2015-04-06
 * @author		Benjamin Ellenberger
 */
class PlanetModel {
public:
	PlanetModel();
	virtual ~PlanetModel();

	void initialize();

	void proceedEvaluation();

	//Accesssor methods

	EnvironmentModel*& getEnvironmentModel() {
		return mEnvironmentModel;
	}

	void setEnvironmentModel(EnvironmentModel*& environmentModel) {
		mEnvironmentModel = environmentModel;
	}

	EvolutionModel*& getEvolutionModel() {
		return mEvolutionModel;
	}

	void setEvolutionModel(EvolutionModel*& evolutionModel) {
		mEvolutionModel = evolutionModel;
	}

private:
	/**
	 * The evolution model of this planet.
	 */
	EvolutionModel* mEvolutionModel;

	/**
	 * The environment model of this planet.
	 */
	EnvironmentModel* mEnvironmentModel;

	/**
	 *
	 */
};

#endif /* MODEL_UNIVERSE_PLANETMODEL_HPP_ */
