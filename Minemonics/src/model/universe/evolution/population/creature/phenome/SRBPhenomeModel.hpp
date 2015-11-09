#ifndef MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_SRBPHENOMEMODEL_HPP_
#define MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_SRBPHENOMEMODEL_HPP_
//# corresponding headers
#include <configuration/Definitions.hpp>

//# forward declarations
class CreatureModel;
class PhenotypeGenerator;
namespace boost {
namespace serialization {
class access;
} /* namespace serialization */
} /* namespace boost */

//# system headers
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

//## controller headers
//## model headers
#include <boost/log/attributes/constant.hpp>
#include <boost/log/sources/basic_logger.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/nvp.hpp>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
#include <model/universe/evolution/population/creature/phenome/controller/Controller.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/joint/JointModel.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/limb/LimbModel.hpp>
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
class SRBPhenomeModel: public PhenomeModel {
public:
	SRBPhenomeModel();
	SRBPhenomeModel(CreatureModel* const creatureModel);
	SRBPhenomeModel(const SRBPhenomeModel& phenomeModel);
	virtual ~SRBPhenomeModel();

	virtual void initialize();

	/**
	 * @brief Perform the generation of the creature embryo.
	 * @details Details
	 * @param creatureModel The creatureModel handle we want to get back from the physics engine when we pick the creature.
	 */
	virtual int performEmbryogenesis();

	virtual void calculateChildPositionRelativeToParent(
		PhenotypeGenerator* generator, btTransform& parentHitTransform,
		btTransform& childHitTransform, Morphogene* childMorphogene,
		Ogre::Vector3& localParentJointInRefParent,
		Ogre::Vector3& localChildJointInRefChild);

	virtual LimbModel* createLimb(PhenotypeGenerator* generator,
		Morphogene* childMorphogene);

	virtual void appendToParentLimb(LimbModel* childLimb,
		PhenotypeGenerator* generator,
		Ogre::Vector3& localParentJointInRefParent,
		Ogre::Vector3& localChildJointInRefChild,
		btTransform& parentHitTransform, btTransform& childHitTransform);

	virtual btTransform getParentIntersection(LimbPhysics* parentLimb,
		MorphogeneBranch* parentMorphogeneBranch, Ogre::Vector3 parentLimbCOM,
		Ogre::Vector3 localParentAnchorDirInRefParent);

	virtual btTransform getOwnIntersection(Morphogene* childMorphogene,
		PhenotypeGenerator* generator,
		Ogre::Vector3 localChildAnchorDirInRefChild);

	void generateBody();

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
	virtual bool equals(const SRBPhenomeModel& phenomeModel) const;

	/**
	 * Add the phenotype to the physical and graphical world.
	 */
	virtual void addToWorld();

	/**
	 * Remove the phenotype from the physical and graphical world.
	 */
	virtual void removeFromWorld();

	/**
	 * Clone the phenome model.
	 */
	virtual PhenomeModel* clone();

	virtual void calm();

	btDynamicsWorld* getWorld();

	//Accessor methods

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
		const SRBPhenomeModel& phenomeModel) {
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
		for (std::vector<JointModel*>::const_iterator it =
			phenomeModel.mJointModels.begin();
			it != phenomeModel.mJointModels.end(); it++) {
			os << (**it);
			os << "||";
		}

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
	 * Serializes the srbphenomemodel to an xml file.
	 * @param ar The archive.
	 * @param The file version.
	 */
	template<class Archive>
	void serialize(Archive & ar, const unsigned int /* file_version */) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(PhenomeModel); /**!< Serialize the base object */
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
				boost::log::attributes::constant<std::string>("PhenomeModel"));
		}
	} _initializer;

	btDynamicsWorld* mWorld;
};

#endif /* MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_SRBPHENOMEMODEL_HPP_ */
