#ifndef MODEL_UNIVERSE_PLANETMODEL_HPP_
#define MODEL_UNIVERSE_PLANETMODEL_HPP_

//# corresponding header
//# forward declarations
class EnvironmentModel;
class EvolutionModel;
class Epoch;

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
#include <model/universe/environments/physics/PhysicsController.hpp>

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

	/**
	 * Initialize the planet model.
	 * @param evolutionModel Its evolution model.
	 * @param environmentModel Its environment model.
	 */
	void initialize(EvolutionModel* evolutionModel, EnvironmentModel* environmentModel);

	/**
	 * Perform embryogenesis on all creatures that are not yet developed.
	 */
	void performEmbryogenesis();

	/**
	 * Proceed with the evaluation.
	 * @return If the evaluation could proceed.
	 */
	bool proceedEvaluation();

	/**
	 * Update the planet.
	 */
	void update();

	//Accessor methods

	EnvironmentModel*& getEnvironmentModel() {
		return mEnvironmentModel;
	}

	void setEnvironmentModel(EnvironmentModel* environmentModel) {
		mEnvironmentModel = environmentModel;
	}

	EvolutionModel*& getEvolutionModel() {
		return mEvolutionModel;
	}

	void setEvolutionModel(EvolutionModel* evolutionModel) {
		mEvolutionModel = evolutionModel;
	}

	//Serialization
	//TODO: Add serialization to the planet model.

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
	 * The epochs of the planet.
	 */
	std::vector<Epoch*> mEpochs;
};

#endif /* MODEL_UNIVERSE_PLANETMODEL_HPP_ */
