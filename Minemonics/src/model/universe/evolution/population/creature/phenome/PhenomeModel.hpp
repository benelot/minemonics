#ifndef MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_PHENOMEMODEL_HPP_
#define MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_PHENOMEMODEL_HPP_

//# corresponding headers
//# forward declarations
class SimulationManager;
class Creature;
class MixedGenome;

//# system headers
#include <vector>

//## controller headers
//## model headers
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/version.hpp>
#include <OgreVector3.h>
#include <btBulletDynamicsCommon.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
#include <model/universe/evolution/population/creature/phenome/controller/Controller.hpp>
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

	void initialize(SimulationManager* simulationManager,
			btDynamicsWorld* world);

	/**
	 * @brief Perform the generation of the creature embryo.
	 * @details Details
	 * @param creature The creature handle we want to get back from the physics engine when we pick the creature.
	 * @param genome The genome of the creature to be built.
	 * @param rootPosition The position of origin where the creature starts to be generated in the physical space.
	 */
	void performEmbryogenesis(Creature* creature, MixedGenome* genome,
			Ogre::Vector3 rootPosition);

	/**
	 * Update the phenome model.
	 * @param timeSinceLastFrame
	 */
	void update(double timeSinceLastFrame);

	/**
	 * Compare the phenome model to another phenome model.
	 * @param phenomeModel Another phenome model.
	 * @return If the phenome model is equal to the other phenome model.
	 */
	bool equals(const PhenomeModel & phenomeModel) const;

	/**
	 * Give access to boost serialization
	 */
	friend class boost::serialization::access;

	/**
	 * Serializes the phemone model to a string.
	 * @param os The ostream.
	 * @param phenomeModel The phemone model we want to serialize.
	 * @return A string containing all information about the phemone model.
	 */
	friend std::ostream & operator<<(std::ostream &os,
			const PhenomeModel &phenomeModel) {
		os
		/**if the phenome is in the world*/
		<< "PhenomeModel: isInWorld=" << phenomeModel.mInWorld;

		/**The vector of limb models.*/
		std::vector<LimbModel*>::const_iterator it;
		for (it = phenomeModel.mLimbModels.begin(); it != phenomeModel.mLimbModels.end(); it++) {
			os << (**it);
			os << "||";
		}

		/**The vector of joint models.*/
		std::vector<JointModel*>::const_iterator it2;
		for (it2 = phenomeModel.mJointModels.begin(); it2 != phenomeModel.mJointModels.end(); it2++) {
			os << (**it2);
			os << "||";
		}

		/**The vector of controllers.*/
		std::vector<Controller*>::const_iterator it3;
		for (it3 = phenomeModel.mControllers.begin(); it3 != phenomeModel.mControllers.end(); it3++) {
			os << (**it3);
			os << "||";
		}

		return os;
	}

	/**
	 * Serializes the creature to an xml file.
	 * @param ar The archive.
	 * @param The file version.
	 */
	template<class Archive>
	void serialize(Archive & ar, const unsigned int /* file_version */) {
		ar
		/**if the phenome is in the world*/
		& BOOST_SERIALIZATION_NVP(mInWorld)

		/**The vector of limb models.*/
		& BOOST_SERIALIZATION_NVP(mLimbModels)

		/**The vector of joint models.*/
		& BOOST_SERIALIZATION_NVP(mJointModels)

		/**The vector of controllers.*/
		& BOOST_SERIALIZATION_NVP(mControllers);
	}

	//Accessor methods
	/**
	 * Is the phenotype in the world?
	 * @return
	 */
	bool isInWorld() const {
		return mInWorld;
	}

	/**
	 * Set whether the phenotype is in the world or not.
	 * @param inWorld Whether the phenotype is in the world or not.
	 */
	void setInWorld(bool inWorld) {
		this->mInWorld = inWorld;
	}

	std::vector<Controller*>& getControllers() {
		return mControllers;
	}

	void setControllers(const std::vector<Controller*>& controllers) {
		mControllers = controllers;
	}

	const std::vector<ComponentModel*>& getComponentModels() const {
		return mComponentModels;
	}

private:

	/**
	 * Handle to the dynamics world.
	 */
	btDynamicsWorld* mWorld;

	/**
	 * Handle to the simulation manager
	 */
	SimulationManager* mSimulationManager;

	/**
	 * Whether the phenome is in the world or not.
	 */
	bool mInWorld;

	/**
	 * The vector of phenotype component models.
	 */
	std::vector<ComponentModel*> mComponentModels;

	/**
	 * The vector of phenotype limb models.
	 */
	std::vector<LimbModel*> mLimbModels;

	/**
	 * The vector of phenotype joint models.
	 */
	std::vector<JointModel*> mJointModels;

	//std::vector<Sensor*> mSensors;

	/**
	 * The vector of phenotype joint controller models.
	 */
	std::vector<Controller*> mControllers;
};

#endif /* MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_PHENOMEMODEL_HPP_ */
