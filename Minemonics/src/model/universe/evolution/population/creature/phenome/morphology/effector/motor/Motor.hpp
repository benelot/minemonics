#ifndef MODEL_EVOLUTION_POPULATION_CREATURE_GENOME_EFFECTOR_MOTOR_H_
#define MODEL_EVOLUTION_POPULATION_CREATURE_GENOME_EFFECTOR_MOTOR_H_

//# corresponding header
#include <model/universe/evolution/population/creature/phenome/controller/ControlInput.hpp>

//# forward declarations
class btMultiBody;
namespace boost {
namespace serialization {
class access;
} /* namespace serialization */
} /* namespace boost */

//# system headers
#include <iostream>

//## controller headers
//## model headers
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/version.hpp>

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

	Motor(const MotorType motorType);
	~Motor();

	/**
	 * Initialize the motor.
	 */
	void initialize();

	/**
	 * Clone the motor.
	 * @return The clone of the motor.
	 */
	virtual Motor* clone() = 0;

	/**
	 * Apply the motor's effect.
	 */
	virtual void apply(double timeSinceLastTick) = 0;

	//Accessor methods

	double getMaxForce() const {
		return mMaxForce;
	}

	void setMaxForce(const double maxForce) {
		mMaxForce = maxForce;
	}

	bool isPositionControlled() const {
		return mPositionControlled;
	}

	void setPositionControlled(const bool positionControlled) {
		mPositionControlled = positionControlled;
	}

	int getIndex() const {
		return mIndex;
	}

	void setIndex(const int index) {
		mIndex = index;
	}

	bool isEnabled() const {
		return mEnabled;
	}

	void setEnabled(const bool enabled) {
		mEnabled = enabled;
	}

	// Serialization
	friend class boost::serialization::access; /**!< Give access to boost serialization */

	/**
	 * Serializes the motor to a string.
	 * @param os The ostream.
	 * @param motor The motor we want to serialize.
	 * @return A string containing all information about the motor.
	 */
	friend std::ostream & operator<<(std::ostream &os, const Motor &motor) {
		return os;
	}

	/**
	 * Serializes the motor to an xml file.
	 * @param ar The archive.
	 * @param The file version.
	 */
	template<class Archive>
	void serialize(Archive & ar, const unsigned int /* file_version */) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(ControlInput) /**!< Serialize the base object */
		& BOOST_SERIALIZATION_NVP(mMotorType) /**!< The type of motor */
		& BOOST_SERIALIZATION_NVP(mEnabled) /**!< Whether the motor is enabled */
		& BOOST_SERIALIZATION_NVP(mPositionControlled) /**!< Direction or position? */
		& BOOST_SERIALIZATION_NVP(mMaxForce) /**!< The maximum force of the motor.*/
		& BOOST_SERIALIZATION_NVP(mIndex); /**!< The index of the motor. */
	}

protected:

	MotorType mMotorType; /**!< The type of motor */

	bool mEnabled; /**!< Whether the motor is enabled */

	bool mPositionControlled; /**!< Direction or position? */

	double mMaxForce; /**!< The maximum force of the motor.*/

	int mIndex; /**!< The index of the motor. */
};
BOOST_CLASS_VERSION(Motor, 1)
BOOST_SERIALIZATION_ASSUME_ABSTRACT(Motor)
#endif /* MODEL_EVOLUTION_POPULATION_CREATURE_GENOME_EFFECTOR_MOTOR_H_ */
