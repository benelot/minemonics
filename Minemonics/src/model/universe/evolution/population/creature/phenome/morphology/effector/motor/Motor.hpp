#ifndef MODEL_EVOLUTION_POPULATION_CREATURE_GENOME_EFFECTOR_MOTOR_H_
#define MODEL_EVOLUTION_POPULATION_CREATURE_GENOME_EFFECTOR_MOTOR_H_

//# corresponding header
#include <model/universe/evolution/population/creature/phenome/controller/ControlInput.hpp>

//# forward declarations
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
 * @brief		The motor base class stores attributes that are important for motors in general.
 * @details		Details
 * @date		2015-03-09
 * @author		Benjamin Ellenberger
 */
class Motor: public ControlInput {
public:

	enum MotorType {
		MUSCLE, SERVO_MOTOR
	};

	Motor(MotorType motorType);
	~Motor();

	void initialize();

	virtual Motor* clone() = 0;

	virtual void apply() = 0;

	//Accessor methods

	double getMaxForce() const {
		return mMaxForce;
	}

	void setMaxForce(double maxForce) {
		mMaxForce = maxForce;
	}

	double getMaxSpeed() const {
		return mMaxSpeed;
	}

	void setMaxSpeed(double maxSpeed) {
		mMaxSpeed = maxSpeed;
	}

	bool isPositionControlled() const {
		return mPositionControlled;
	}

	void setPositionControlled(bool positionControlled) {
		mPositionControlled = positionControlled;
	}

	int getIndex() const {
		return mIndex;
	}

	void setIndex(int index) {
		mIndex = index;
	}

	bool isEnabled() const {
		return mEnabled;
	}

	void setEnabled(bool enabled) {
		mEnabled = enabled;
	}

protected:

	/**
	 * The type of motor
	 */
	MotorType mMotorType;

	/**
	 * Direction or position?
	 */
	bool mPositionControlled;

	/**
	 * The maximum force of the motor.
	 */
	double mMaxForce;

	/**
	 * The maximum speed of the motor.
	 */
	double mMaxSpeed;

	/**
	 * The index of the motor.
	 */
	int mIndex;

	/**
	 * Whether the motor is enabled
	 */
	bool mEnabled;
};

#endif /* MODEL_EVOLUTION_POPULATION_CREATURE_GENOME_EFFECTOR_MOTOR_H_ */
