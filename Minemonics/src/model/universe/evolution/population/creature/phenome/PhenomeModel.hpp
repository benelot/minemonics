#ifndef MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_PHENOMEMODEL_HPP_
#define MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_PHENOMEMODEL_HPP_

//# corresponding headers
#include <configuration/Definitions.hpp>

//# forward declarations
class CreatureModel;
namespace boost {
namespace serialization {
class access;
} /* namespace serialization */
} /* namespace boost */

//# system headers
#include <iostream>
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
#include <model/universe/evolution/population/creature/phenome/controller/sine/SineController.hpp>
#include <model/universe/evolution/population/creature/SRBcreature/phenome/morphology/joint/SRBJointModel.hpp>
#include <model/universe/evolution/population/creature/SRBcreature/phenome/morphology/limb/SRBLimbModel.hpp>

//## view headers
//## utils headers
#include <utils/logging/Logger.hpp>

/**
 * @brief		The phenome model holds all the state information of the phenome independent of other models.
 * @details		Details
 * @date		2015-04-29
 * @author		Benjamin Ellenberger
 */
class PhenomeModel {
public:
	PhenomeModel();
	PhenomeModel(const PhenomeModel& phenomeModel);
	virtual ~PhenomeModel();

	virtual void initialize(CreatureModel* const creatureModel);

	/**
	 * @brief Perform the generation of the creature embryo.
	 * @details Details
	 * @param creatureModel The creatureModel handle we want to get back from the physics engine when we pick the creature.
	 */
	virtual int performEmbryogenesis(CreatureModel* const creatureModel) = 0;

	/**
	 * Reset the creature to the way it was born.
	 */
	virtual void reset(const Ogre::Vector3 position);

	/**
	 * Cleanup phenome model for a new embryogenesis.
	 */
	virtual void cleanup();

	/**
	 * Reposition the creature without resetting it.
	 */
	virtual void reposition(const Ogre::Vector3 position);

	/**
	 * Update the phenome model.
	 * @param timeSinceLastTick
	 */
	virtual void update(const double timeSinceLastTick);

	/**
	 * Compare the phenome model to another phenome model.
	 * @param phenomeModel Another phenome model.
	 * @return If the phenome model is equal to the other phenome model.
	 */
	bool equals(const PhenomeModel& phenomeModel) const;

	virtual void addToWorld();

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
	void setInWorld(const bool inWorld) {
		this->mInWorld = inWorld;
	}

	std::vector<Controller*>& getControllers() {
		return mControllers;
	}

	const std::vector<Controller*>& getControllers() const {
		return mControllers;
	}

	std::vector<ComponentModel*>& getComponentModels() {
		return mComponentModels;
	}

	const std::vector<ComponentModel*>& getComponentModels() const {
		return mComponentModels;
	}

	bool isDeveloped() const {
		return mDeveloped;
	}

	void setDeveloped(const bool developed) {
		mDeveloped = developed;
	}

	std::vector<JointModel*>& getJointModels() {
		return mJointModels;
	}

	const std::vector<JointModel*>& getJointModels() const {
		return mJointModels;
	}

	std::vector<LimbModel*>& getLimbModels() {
		return mLimbModels;
	}

	const std::vector<LimbModel*>& getLimbModels() const {
		return mLimbModels;
	}

	CreatureModel* const getCreatureModel() const {
		return mCreatureModel;
	}

	bool hasInterpenetrations() const {
		return mHasInterpenetrations;
	}

	void calm();

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
	friend std::ostream & operator<<(std::ostream& os,
		const PhenomeModel& phenomeModel) {
		os
		/**if the phenome is in the world*/
		<< "/PhenomeModel: isInWorld=" << phenomeModel.mInWorld

		<< "/Limbs=[";

		/**The vector of limb models.*/

		for (std::vector<LimbModel*>::const_iterator it =
			phenomeModel.mLimbModels.begin();
			it != phenomeModel.mLimbModels.end(); it++) {
			os << (**it);
			os << "||";
		}

		os << "]/Joints=[";

		/**The vector of joint models.*/
		//TODO
//		for (std::vector<JointModel*>::const_iterator it =
//			phenomeModel.mJointModels.begin();
//			it != phenomeModel.mJointModels.end(); it++) {
//			os << (**it);
//			os << "||";
//		}
		os << "]/Controllers=[";

		/**The vector of controllers.*/
		for (std::vector<Controller*>::const_iterator it =
			phenomeModel.mControllers.begin();
			it != phenomeModel.mControllers.end(); it++) {
			os << (**it);
			os << "||";
		}

		os << "]";

		return os;
	}

	/**
	 * Serializes the creature to an xml file.
	 * @param ar The archive.
	 * @param The file version.
	 */
	template<class Archive>
	void serialize(Archive & ar, const unsigned int /* file_version */) {
		ar.register_type(static_cast<SineController*>(NULL));
		ar & BOOST_SERIALIZATION_NVP(mDeveloped) /**!< If the phenome is developed*/

		& BOOST_SERIALIZATION_NVP(mInWorld) /**!< if the phenome is in the world*/

		& BOOST_SERIALIZATION_NVP(mLimbModels) /**!< The vector of limb models.*/

		& BOOST_SERIALIZATION_NVP(mJointModels) /**!< The vector of joint models.*/

		& BOOST_SERIALIZATION_NVP(mControllers); /**!< The vector of controllers.*/
	}
private:
	/**
	 * The boost logger.
	 */
	static BoostLogger mBoostLogger;

	/**
	 * Initializer of the boost logger to include the class name into the logging messages.
	 */
	static class _Init {
	public:
		_Init() {
			mBoostLogger.add_attribute("ClassName",
				boost::log::attributes::constant < std::string
					> ("PhenomeModel"));
		}
	} _initializer;

protected:
	/**
	 * Is the phenotype developed?
	 */
	bool mDeveloped;

	CreatureModel* mCreatureModel;

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

	bool mHasInterpenetrations;
};

#endif /* MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_PHENOMEMODEL_HPP_ */
