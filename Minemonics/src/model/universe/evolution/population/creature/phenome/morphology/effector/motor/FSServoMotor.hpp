#ifndef MODEL_EVOLUTION_POPULATION_CREATURE_GENOME_EFFECTOR_FSSERVOMOTOR_H_
#define MODEL_EVOLUTION_POPULATION_CREATURE_GENOME_EFFECTOR_FSSERVOMOTOR_H_

//# corresponding header
#include <configuration/Definitions.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/effector/motor/ServoMotor.hpp>

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
#include <model/universe/evolution/population/creature/phenome/morphology/joint/JointPhysics.hpp>

//## view headers
//## utils headers

/**
 * @brief		The servo motor acts directly on the DoF of a joint and thereby moves the creature.
 * @details		Details
 * @date		2015-03-09
 * @author		Benjamin Ellenberger
 */
class FSServoMotor: public ServoMotor {
public:
	FSServoMotor();
	FSServoMotor(const JointPhysics::RotationalDegreeOfFreedom jointMotorIndex,
		const double maxForce, double lowerLimit, double upperLimit,
		bool positionControlled);
	FSServoMotor(const FSServoMotor& servoMotor);

	virtual ~FSServoMotor();

	/**
	 * Initialize the servo motor with its bullet physics engine rotational motor.
	 * @param jointMotorIndex The index of the motor in the 6DoF joint.
	 * @param motorBt
	 */
	virtual void initialize();

	void instantiate(JointPhysics* jointPhysics, const int jointIndex);
	/**
	 * Clone the servomotor.
	 * @return The clone of the servo motor.
	 */
	FSServoMotor* clone();

	//TODO: Add equals method

	/**
	 * Apply the movement of the servomotor on the joint it controls.
	 * @param timeSinceLastTick
	 */
	void apply(double timeSinceLastTick);

	// Accessor methods ##########################

// Serialization
	friend class boost::serialization::access; /**!< Give access to boost serialization */

	/**
	 * Serializes the servo motor to a string.
	 * @param os The ostream.
	 * @param servoMotor The servo motor we want to serialize.
	 * @return A string containing all information about the servo motor.
	 */
	friend std::ostream & operator<<(std::ostream &os,
		const FSServoMotor &servoMotor) {
		return os;
	}

	/**
	 * Serializes the servo motor to an xml file.
	 * @param ar The archive.
	 * @param The file version.
	 */
	template<class Archive>
	void serialize(Archive & ar, const unsigned int /* file_version */) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(ServoMotor); /**!< Serialize the base object */
	}
};

#endif /* MODEL_EVOLUTION_POPULATION_CREATURE_GENOME_EFFECTOR_FSSERVOMOTOR_H_ */
