#ifndef CONTROLLER_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_JOINT_HPP_
#define CONTROLLER_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_JOINT_HPP_

//# corresponding header
#include <controller/evolution/population/creature/phenome/Component.hpp>

//# forward declarations
class SimulationManager;
class Limb;

//# system headers
//## controller headers
//## model headers
#include <bullet/LinearMath/btTransform.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
#include <model/evolution/population/creature/phenome/morphology/joint/JointPhysics.hpp>

//## view headers
#include <view/evolution/population/creature/phenome/morphology/joint/JointGraphics.hpp>

//## utils headers

/**
 * @brief		The joint controller synchronizes the joint graphical representation with the joint model.
 * @details		Details
 * @date		2014-11-17
 * @author		Benjamin Ellenberger
 */
class Joint: public Component {
public:
	Joint();
	virtual ~Joint();

	void initialize(SimulationManager* simulationManager, Limb* limbA,
			Limb* limbB, btTransform localA, btTransform localB);

	void update();

	void addToWorld();

	void removeFromWorld();

	void setAngularLimits(Ogre::Vector3 angularLowerLimit,
			Ogre::Vector3 angularUpperLimit);

	void setAngularStiffness(double jointPitchStiffness,double jointYawStiffness,double jointRollStiffness);

	void setAngularDamping(double springPitchDampingCoefficient,double springYawDampingCoefficient,double springRollDampingCoefficient);

	JointGraphics*& getJointGraphics() {
		return mJointGraphics;
	}

	JointPhysics*& getJointPhysics() {
		return mJointPhysics;
	}

private:
	JointPhysics* mJointPhysics;
	JointGraphics* mJointGraphics;
};

#endif /* CONTROLLER_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_JOINT_HPP_ */
