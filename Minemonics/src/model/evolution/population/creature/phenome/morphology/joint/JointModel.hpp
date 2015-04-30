#ifndef MODEL_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_JOINT_JOINTMODEL_HPP_
#define MODEL_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_JOINT_JOINTMODEL_HPP_

//# corresponding headers
//# forward declarations
class JointPhysics;

//# system headers
#include <vector>

//## controller headers
//## model headers
#include <model/evolution/population/creature/phenome/morphology/effector/motor/Motor.hpp>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers
/**
 * @brief		The joint model holds all the state information of the joint.
 * @details		Details
 * @date		2015-04-29
 * @author		Benjamin Ellenberger
 */
class JointModel {
public:
	JointModel();
	virtual ~JointModel();


	//Accessor methods

	const JointPhysics*& getJointPhysics() const {
		return mJointPhysics;
	}

	void setJointPhysics(const JointPhysics*& jointPhysics) {
		mJointPhysics = jointPhysics;
	}

	const std::vector<Motor*>& getMotors() const {
		return mMotors;
	}

	void setMotors(const std::vector<Motor*>& motors) {
		mMotors = motors;
	}

private:
	JointPhysics* mJointPhysics;

	/**
	 * The motors of the joints. Be it servo motors acting directly on the DoF or be it muscles acting on attachment points on the limb.
	 */
	std::vector<Motor*> mMotors;
};

#endif /* MODEL_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_JOINT_JOINTMODEL_HPP_ */
