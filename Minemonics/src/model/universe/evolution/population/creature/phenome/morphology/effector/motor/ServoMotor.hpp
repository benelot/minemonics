#ifndef MODEL_EVOLUTION_POPULATION_CREATURE_GENOME_EFFECTOR_SERVOMOTOR_H_
#define MODEL_EVOLUTION_POPULATION_CREATURE_GENOME_EFFECTOR_SERVOMOTOR_H_

//# corresponding header
#include <model/universe/evolution/population/creature/phenome/morphology/effector/motor/Motor.hpp>

//# forward declarations
class btRotationalLimitMotor;

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
 * @brief		The servo motor acts directly on the DoF of a joint and thereby moves the creature.
 * @details		Details
 * @date		2015-03-09
 * @author		Benjamin Ellenberger
 */
class ServoMotor: public Motor {
public:
	virtual ~ServoMotor();
	ServoMotor();

	/**
	 * Initialize the servo motor with its bullet physics engine rotational motor.
	 * @param jointMotorIndex The index of the motor in the 6DoF joint.
	 * @param motorBt
	 */
	void initialize(int jointMotorIndex, btRotationalLimitMotor* motorBt,
			double maxForce, double maxSpeed);

	void apply();

	//Accessor methods

	int getJointMotorIndex() const {
		return mJointMotorIndex;
	}

	btRotationalLimitMotor* getMotorBt() {
		return mMotorBt;
	}

private:
	int mJointMotorIndex;
	btRotationalLimitMotor* mMotorBt;
};

#endif /* MODEL_EVOLUTION_POPULATION_CREATURE_GENOME_EFFECTOR_SERVOMOTOR_H_ */
