#ifndef MODEL_EVOLUTION_POPULATION_CREATURE_GENOME_EFFECTOR_SERVOMOTOR_H_
#define MODEL_EVOLUTION_POPULATION_CREATURE_GENOME_EFFECTOR_SERVOMOTOR_H_

//# corresponding header
#include <configuration/Definitions.hpp>
#include <configuration/SRBJointDefinitions.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/effector/motor/Motor.hpp>

//# forward declarations
namespace boost {
namespace serialization {
class access;
} /* namespace serialization */
} /* namespace boost */

//# system headers
#include <iostream>

//## controller headers
//## model headers
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/nvp.hpp>
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
class ServoMotor: public Motor {
public:
	ServoMotor();
	ServoMotor(const JointPhysics::RotationalDegreeOfFreedom jointMotorIndex, const double maxForce, double lowerLimit,
		double upperLimit);
	ServoMotor(const ServoMotor& servoMotor);

	virtual ~ServoMotor();

	/**
	 * Initialize the servo motor with its bullet physics engine rotational motor.
	 * @param jointMotorIndex The index of the motor in the 6DoF joint.
	 * @param motorBt
	 */
	void initialize();

	virtual void instantiate(JointPhysics* jointPhysics,
		const int jointIndex) = 0;

	/**
	 * Apply the movement of the servomotor on the joint it controls.
	 * @param timeSinceLastTick
	 */
	virtual void apply(double timeSinceLastTick) = 0;

	// Accessor methods ##########################

	int getJointMotorIndex() const {
		return mJointMotorIndex;
	}

	// Serialization
	friend class boost::serialization::access; /**!< Give access to boost serialization */

	/**
	 * Serializes the servo motor to a string.
	 * @param os The ostream.
	 * @param servoMotor The servo motor we want to serialize.
	 * @return A string containing all information about the servo motor.
	 */
	friend std::ostream & operator<<(std::ostream &os,
		const ServoMotor &servoMotor) {
		return os;
	}

	/**
	 * Serializes the servo motor to an xml file.
	 * @param ar The archive.
	 * @param The file version.
	 */
	template<class Archive>
	void serialize(Archive & ar, const unsigned int /* file_version */) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Motor) /**!< Serialize the base object */
		& BOOST_SERIALIZATION_NVP(mJointMotorIndex) /**!< The joint motor index */
		& BOOST_SERIALIZATION_NVP(mJointIndex) /**!< The index of the joint in the whole creature. */
		& BOOST_SERIALIZATION_NVP(mLowerLimit) /**!< The lower limit of the DoF the servo is driving */
		& BOOST_SERIALIZATION_NVP(mUpperLimit) /**!< The upper limit of the DoF the servo is driving */
		& BOOST_SERIALIZATION_NVP(mPositionControlled);
	}

protected:
	JointPhysics::RotationalDegreeOfFreedom mJointMotorIndex; /**!< The motor index of the joint that is controlled*/

	//TODO: Check if still not used at the moment
	MOTOR_TYPE* mMotorBt; /**!< The motor to control the joint*/
	double mLowerLimit; /**!< The lower limit of the DoF the servo is driving */
	double mUpperLimit; /**!< The upper limit of the DoF the servo is driving */

	int mJointIndex; /**!< The index of the joint in the whole creature. */
	JointPhysics* mJoint; /**!< The joint the servomotor is controlling */

	bool mPositionControlled; /**!< Is the servomotor position controlled via PID?*/
private:
	static BoostLogger mBoostLogger; /**!< The boost logger. */

	/**
	 * Initializer of the boost logger to include the class name into the logging messages.
	 */
	static class _Init {
	public:
		_Init() {
			mBoostLogger.add_attribute("ClassName",
				boost::log::attributes::constant<std::string>("ServoMotor"));
		}
	} _initializer;
};

#endif /* MODEL_EVOLUTION_POPULATION_CREATURE_GENOME_EFFECTOR_SERVOMOTOR_H_ */
