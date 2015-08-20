#ifndef MODEL_EVOLUTION_POPULATION_CREATURE_GENOME_EFFECTOR_SERVOMOTOR_H_
#define MODEL_EVOLUTION_POPULATION_CREATURE_GENOME_EFFECTOR_SERVOMOTOR_H_

//# corresponding header
#include <model/universe/evolution/population/creature/phenome/morphology/effector/motor/Motor.hpp>

//# forward declarations
class btGeneric6DofSpring2Constraint;
class btGeneric6DofSpringConstraint;
class btGeneric6DofConstraint;
class btRotationalLimitMotor2;
class btRotationalLimitMotor;
class btPoint2PointConstraint;
class btConeTwistConstraint;
class JointBt;

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

//comment this out to compare with original spring constraint
#define CONSTRAINT_TYPE btConeTwistConstraint
#define EXTRAPARAMS
#define MOTOR_TYPE btRotationalLimitMotor
//#define CONSTRAINT_TYPE btPoint2PointConstraint
//#define EXTRAPARAMS
//#define MOTOR_TYPE btRotationalLimitMotor
//#define CONSTRAINT_TYPE btGeneric6DofConstraint
//#define EXTRAPARAMS ,true
//#define MOTOR_TYPE btRotationalLimitMotor
//#define CONSTRAINT_TYPE btGeneric6DofSpring2Constraint
//#define EXTRAPARAMS
//#define MOTOR_TYPE btRotationalLimitMotor2
//#define CONSTRAINT_TYPE btGeneric6DofSpringConstraint
//#define EXTRAPARAMS ,true
//#define MOTOR_TYPE btRotationalLimitMotor

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
	void initialize(const JointPhysics::RotationalDegreeOfFreedom jointMotorIndex, JointBt* jointBt,
			const double maxForce, const double maxSpeed);
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

private:
	JointPhysics::RotationalDegreeOfFreedom mJointMotorIndex;
	JointBt* mJointBt;
};

#endif /* MODEL_EVOLUTION_POPULATION_CREATURE_GENOME_EFFECTOR_SERVOMOTOR_H_ */
