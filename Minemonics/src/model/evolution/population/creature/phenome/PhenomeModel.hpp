#ifndef MODEL_EVOLUTION_POPULATION_CREATURE_PHENOME_PHENOMEMODEL_HPP_
#define MODEL_EVOLUTION_POPULATION_CREATURE_PHENOME_PHENOMEMODEL_HPP_

#include <model/evolution/population/creature/phenome/controller/Controller.hpp>
#include <model/evolution/population/creature/phenome/morphology/effector/motor/Motor.hpp>
#include <vector>

/**
 * @brief		The phenome model holds all the state information of the phenome independent of other models.
 * @details		Details
 * @date		2015-04-29
 * @author		Benjamin Ellenberger
 */
class PhenomeModel {
public:
	PhenomeModel();
	virtual ~PhenomeModel();

	//Accessor methods
	/**
	 * Is the phenotype in the world?
	 * @return
	 */
	bool isInWorld() const {
		return inWorld;
	}

	/**
	 * Set whether the phenotype is in the world or not.
	 * @param inWorld Whether the phenotype is in the world or not.
	 */
	void setInWorld(bool inWorld) {
		this->inWorld = inWorld;
	}
private:
	/**
	 * Whether the phenome is in the world or not.
	 */
	bool inWorld;

	//std::vector<Sensor*> mSensors;

	std::vector<Controller*> mControllers;
};

#endif /* MODEL_EVOLUTION_POPULATION_CREATURE_PHENOME_PHENOMEMODEL_HPP_ */
