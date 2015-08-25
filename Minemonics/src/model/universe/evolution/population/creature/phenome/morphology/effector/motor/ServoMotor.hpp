#ifndef MODEL_EVOLUTION_POPULATION_CREATURE_GENOME_EFFECTOR_SERVOMOTOR_H_
#define MODEL_EVOLUTION_POPULATION_CREATURE_GENOME_EFFECTOR_SERVOMOTOR_H_

//# corresponding header
#include <model/universe/evolution/population/creature/phenome/morphology/effector/motor/Motor.hpp>

//# forward declarations
class btMultiBodyJointMotor;

//# system headers
//## controller headers
//## model headers
//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
#include <model/universe/evolution/population/creature/phenome/morphology/joint/JointPhysics.hpp>

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
	ServoMotor();
	ServoMotor(const ServoMotor& servoMotor);

	virtual ~ServoMotor();

	/**
	 * Initialize the servo motor with its bullet physics engine rotational motor.
	 * @param jointMotorIndex The index of the motor in the 6DoF joint.
	 * @param motorBt
	 */
	void initialize(const JointPhysics::RotationalDegreeOfFreedom jointMotorIndex,
			const double maxForce, const double maxSpeed,double lowerLimit, double upperLimit);
	/**
	 * Clone the servomotor.
	 * @return The clone of the servo motor.
	 */
	ServoMotor* clone();

	/**
	 * Apply the movement of the servomotor on the joint it controls.
	 * @param timeSinceLastTick
	 */
	void apply(double timeSinceLastTick);

	//Accessor methods

	int getJointMotorIndex() const {
		return mJointMotorIndex;
	}

	const btMultiBodyJointMotor* getJointMotor() const {
		return mJointMotor;
	}

	void setJointMotor(btMultiBodyJointMotor* jointMotor) {
		mJointMotor = jointMotor;
	}

private:
	JointPhysics::RotationalDegreeOfFreedom mJointMotorIndex;
	btMultiBodyJointMotor* mJointMotor;

	double mLowerLimit;
	double mUpperLimit;
};

#endif /* MODEL_EVOLUTION_POPULATION_CREATURE_GENOME_EFFECTOR_SERVOMOTOR_H_ */
