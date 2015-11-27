#ifndef MODEL_EVOLUTION_POPULATION_CREATURE_GENOME_EFFECTOR_SERVOMOTOR_H_
#define MODEL_EVOLUTION_POPULATION_CREATURE_GENOME_EFFECTOR_SERVOMOTOR_H_

//# corresponding header
#include <configuration/Definitions.hpp>
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
#include <utils/logging/Logger.hpp>

//comment this out to compare with original spring constraint
#define HINGECONSTRAINT 0
#define GENERIC6DOFCONSTRAINT 1
#define CONETWISTCONSTRAINT 2
#define POINT2POINTCONSTRAINT 3
#define GENERIC6DOFSPRINGCONSTRAINT 4
#define GENERIC6DOFSPRING2CONSTRAINT 5
/** bullet physics hinge constraint - A 1Dof angular joint with with limits */
#define CONSTRAINT_INDEX HINGECONSTRAINT
#define CONSTRAINT_TYPE btHingeConstraint

/** bullet physics cone twist constraint - A 3Dof angular joint with symmetric limits */
//#define CONSTRAINT_INDEX CONETWISTCONSTRAINT
//#define CONSTRAINT_TYPE btConeTwistConstraint

/** bullet physics point 2 point constraint - A 3Dof angular joint without limits*/
//#define CONSTRAINT_INDEX POINT2POINTCONSTRAINT
//#define CONSTRAINT_TYPE btPoint2PointConstraint

/** bullet physics 6 degrees of freedom constraint - A 6 Dof joint with generic limits*/
//#define CONSTRAINT_INDEX GENERIC6DOFCONSTRAINT
//#define CONSTRAINT_TYPE btGeneric6DofConstraint

/** bullet physics 6 degrees of freedom with spring constraint (more stable impl)*/
//#define CONSTRAINT_INDEX GENERIC6DOFSPRING2CONSTRAINT
//#define CONSTRAINT_TYPE btGeneric6DofSpring2Constraint

/** bullet physics 6 degrees of freedom with spring constraint (first impl)*/
//#define CONSTRAINT_INDEX GENERIC6DOFSPRINGCONSTRAINT
//#define CONSTRAINT_TYPE btGeneric6DofSpringConstraint

#define MOTOR_TYPE btRotationalLimitMotor

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
	JointPhysics::RotationalDegreeOfFreedom mJointMotorIndex;

	MOTOR_TYPE* mMotorBt;
	double mLowerLimit; /**!< The lower limit of the DoF the servo is driving */
	double mUpperLimit; /**!< The upper limit of the DoF the servo is driving */

	int mJointIndex; /**!< The index of the joint in the whole creature. */
	JointPhysics* mJoint;

	bool mPositionControlled;
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
