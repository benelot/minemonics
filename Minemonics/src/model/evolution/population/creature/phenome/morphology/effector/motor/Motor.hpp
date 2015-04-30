#ifndef MODEL_EVOLUTION_POPULATION_CREATURE_GENOME_EFFECTOR_MOTOR_H_
#define MODEL_EVOLUTION_POPULATION_CREATURE_GENOME_EFFECTOR_MOTOR_H_

//# corresponding header
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
class Motor: public ControlOutput {
public:

	Motor();
	~Motor();

	void initialize();

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

private:

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
};

#endif /* MODEL_EVOLUTION_POPULATION_CREATURE_GENOME_EFFECTOR_MOTOR_H_ */
