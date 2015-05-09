#ifndef MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_PHENOMEMODEL_HPP_
#define MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_PHENOMEMODEL_HPP_

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
#include <model/universe/evolution/population/creature/phenome/controller/Controller.hpp>
#include <model/universe/evolution/population/creature/phenome/ComponentModel.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/joint/JointModel.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/limb/LimbModel.hpp>

//## view headers
//## utils headers


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

	void update(double totalMilliseconds);

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

	std::vector<Controller*>& getControllers() {
		return mControllers;
	}

	void setControllers(const std::vector<Controller*>& controllers) {
		mControllers = controllers;
	}

private:
	/**
	 * Whether the phenome is in the world or not.
	 */
	bool inWorld;

	std::vector<ComponentModel*> mComponentModels;

	std::vector<LimbModel*> mLimbModels;

	std::vector<JointModel*> mJointModels;

	//std::vector<Sensor*> mSensors;

	std::vector<Controller*> mControllers;
};

#endif /* MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_PHENOMEMODEL_HPP_ */
