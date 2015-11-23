#ifndef MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_FSPHENOMEMODEL_HPP_
#define MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_FSPHENOMEMODEL_HPP_

//# corresponding headers
#include <configuration/Definitions.hpp>
#include <model/universe/evolution/population/creature/phenome/PhenomeModel.hpp>

//# forward declarations
class btMultiBody;
class btMultiBodyDynamicsWorld;
class CreatureModel;
class PhenotypeGenerator;
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
#include <BulletDynamics/Featherstone/btMultiBodyConstraint.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
#include <model/universe/evolution/population/creature/phenome/controller/sine/SineController.hpp>
#include <model/universe/evolution/population/creature/phenome/PhenomeModel.hpp>

//## view headers
//## utils headers
#include <utils/logging/Logger.hpp>

/**
 * @brief		The phenome model holds all the state information of the phenome independent of other models.
 * @details		Details
 * @date		2015-04-29
 * @author		Benjamin Ellenberger
 */
class FSPhenomeModel: public PhenomeModel {
public:
	FSPhenomeModel();
	FSPhenomeModel(CreatureModel* const creatureModel);
	FSPhenomeModel(const FSPhenomeModel& phenomeModel);
	virtual ~FSPhenomeModel();

	virtual void initialize();

	/**
	 * @brief Perform the generation of the creature embryo.
	 * @details Details
	 */
	virtual int performEmbryogenesis();

	virtual void calculateChildPositionRelativeToParent(
		PhenotypeGenerator* generator, btTransform& parentHitTransform,
		btTransform& childHitTransform, Morphogene* childMorphogene,
		Ogre::Vector3& jointPivotInW);

	virtual LimbModel* createLimb(PhenotypeGenerator* generator,
		Morphogene* childMorphogene);

	virtual void appendToParentLimb(LimbModel* childLimb,
		PhenotypeGenerator* generator,
		Ogre::Vector3& jointPivotInW,
		btTransform& parentHitTransform, btTransform& childHitTransform);

	virtual btTransform getParentIntersectionInW(LimbPhysics* parentLimb,
		MorphogeneBranch* parentMorphogeneBranch, Ogre::Vector3 parentLimbCOM,
		Ogre::Vector3 localParentAnchorDirInRefParent);

	virtual btTransform getOwnIntersection(Morphogene* childMorphogene,
		PhenotypeGenerator* generator,
		Ogre::Vector3 localChildAnchorDirInRefChild);

	void generateBody();

	void addJointConstraints();

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
	bool equals(const FSPhenomeModel& phenomeModel) const;

	/**
	 * Clone the phenome model.
	 */
	virtual PhenomeModel* clone();

	virtual void calm();

	/**
	 * Add the phenotype to the physical and graphical world.
	 */
	void addToWorld();

	/**
	 * Remove the phenotype from the physical and graphical world.
	 */
	void removeFromWorld();

	// Accessor methods ##########################

	btMultiBody* getMultiBody() {
		return mMultiBody;
	}

	void setMultiBody(btMultiBody* multiBody) {
		mMultiBody = multiBody;
	}

	friend class boost::serialization::access; /**!< Give access to boost serialization */

	/**
	 * Serializes the phenome model to a string.
	 * @param os The ostream.
	 * @param phenomeModel The phenome model we want to serialize.
	 * @return A string containing all information about the phenome model.
	 */
	friend std::ostream & operator<<(std::ostream& os,
		const FSPhenomeModel& phenomeModel) {
		os
		/**if the phenome is in the world*/
		<< "/PhenomeModel: isInWorld=" << phenomeModel.mInWorld

		<< "/Limbs=[";

		/**The vector of limb models.*/
//TODO
//		for (std::vector<FSLimbModel*>::const_iterator it =
//			phenomeModel.mLimbModels.begin();
//			it != phenomeModel.mLimbModels.end(); it++) {
//			os << (**it);
//			os << "||";
//		}
//
//		os << "]/Joints=[";
//
//		/**The vector of joint models.*/
//		for (std::vector<FSJointModel*>::const_iterator it =
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
	 * Serializes the FS phenome model to an xml file.
	 * @param ar The archive.
	 * @param The file version.
	 */
	template<class Archive>
	void serialize(Archive & ar, const unsigned int /* file_version */) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(PhenomeModel); /**!< Serialize the base object */
	}
private:

	btMultiBodyDynamicsWorld* getWorld();

	static BoostLogger mBoostLogger; /**!< The boost logger. */

	/**
	 * Initializer of the boost logger to include the class name into the logging messages.
	 */
	static class _Init {
	public:
		_Init() {
			mBoostLogger.add_attribute("ClassName",
				boost::log::attributes::constant<std::string>("PhenomeModel"));
		}
	} _initializer;

	btMultiBody* mMultiBody; /**!< The multibody of this phenotype */

	btMultiBodyDynamicsWorld* mWorld; /**!< The multibody world of this phenotype */

	std::vector<btMultiBodyConstraint*> mLimitConstraints; /**!< The limit constraints of this phenotype */
};

#endif /* MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_FSPHENOMEMODEL_HPP_ */
