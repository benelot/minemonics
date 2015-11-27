#ifndef MODEL_EVOLUTION_POPULATION_CREATURE_GENOME_EFFECTOR_SRBServoMotor_H_
#define MODEL_EVOLUTION_POPULATION_CREATURE_GENOME_EFFECTOR_SRBServoMotor_H_

//# corresponding header
#include <configuration/Definitions.hpp>
#include <configuration/SRBJointDefinitions.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/effector/motor/ServoMotor.hpp>

//# forward declarations
//# system headers
//## controller headers
//## model headers
#include <BulletDynamics/ConstraintSolver/btGeneric6DofConstraint.h>
#include <BulletDynamics/ConstraintSolver/btGeneric6DofSpringConstraint.h>
#include <BulletDynamics/ConstraintSolver/btGeneric6DofSpring2Constraint.h>
#include <BulletDynamics/ConstraintSolver/btPoint2PointConstraint.h>
#include <BulletDynamics/ConstraintSolver/btConeTwistConstraint.h>
#include <BulletDynamics/ConstraintSolver/btHingeConstraint.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
#include <model/universe/evolution/population/creature/phenome/morphology/joint/JointPhysics.hpp>

//## view headers
//## utils headers
#include <utils/logging/Logger.hpp>

/**
 * @brief		The servo motor acts directly on the DoF of a joint and thereby moves the creature.
 * @details		Details
 * @date		2015-03-09
 * @author		Benjamin Ellenberger
 */
class SRBServoMotor: public ServoMotor {
public:
	SRBServoMotor();
	SRBServoMotor(const JointPhysics::RotationalDegreeOfFreedom jointMotorIndex,
		const double maxForce, double lowerLimit, double upperLimit,bool positionControlled);
	SRBServoMotor(const SRBServoMotor& SRBServoMotor);

	virtual ~SRBServoMotor();

	/**
	 * Initialize the servo motor with its bullet physics engine rotational motor.
	 * @param jointMotorIndex The index of the motor in the 6DoF joint.
	 * @param motorBt
	 */
	void initialize(MOTOR_TYPE* const motorBt);

	void instantiate(JointPhysics* jointPhysics, const int jointIndex);

	/**
	 * Clone the SRBServoMotor.
	 * @return The clone of the servo motor.
	 */
	SRBServoMotor* clone();

	/**
	 * Apply the movement of the SRBServoMotor on the joint it controls.
	 * @param timeSinceLastTick
	 */
	void apply(double timeSinceLastTick);

	// Accessor methods ##########################

	int getJointMotorIndex() const {
		return mJointMotorIndex;
	}

	// Serialization
	friend class boost::serialization::access; /**!< Give access to boost serialization */

	/**
	 * Serializes the servo motor to a string.
	 * @param os The ostream.
	 * @param SRBServoMotor The servo motor we want to serialize.
	 * @return A string containing all information about the servo motor.
	 */
	friend std::ostream & operator<<(std::ostream &os,
		const SRBServoMotor &SRBServoMotor) {
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

private:
	static BoostLogger mBoostLogger; /**!< The boost logger. */

	/**
	 * Initializer of the boost logger to include the class name into the logging messages.
	 */
	static class _Init {
	public:
		_Init() {
			mBoostLogger.add_attribute("ClassName",
				boost::log::attributes::constant<std::string>("SRBServoMotor"));
		}
	} _initializer;

	double mLastPosition;
};

#endif /* MODEL_EVOLUTION_POPULATION_CREATURE_GENOME_EFFECTOR_SRBSERVOMOTOR_H_ */
