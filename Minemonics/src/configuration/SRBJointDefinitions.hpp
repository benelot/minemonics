#ifndef CONFIGURATION_SRBJOINTDEFINITIONS_HPP_
#define CONFIGURATION_SRBJOINTDEFINITIONS_HPP_

/**
 * @brief		The definitions for the used SRB joint.
 * @details		Details
 * @date		2015-11-27
 * @author		Benjamin Ellenberger
 */

//comment this out to compare with original spring constraint
#define HINGECONSTRAINT 1
#define GENERIC6DOFCONSTRAINT 2
#define CONETWISTCONSTRAINT 3
#define POINT2POINTCONSTRAINT 4
#define GENERIC6DOFSPRINGCONSTRAINT 5
#define GENERIC6DOFSPRING2CONSTRAINT 6
/** bullet physics hinge constraint - A 1Dof angular joint with with limits */
//#define CONSTRAINT_INDEX HINGECONSTRAINT
/** bullet physics cone twist constraint - A 3Dof angular joint with symmetric limits */
//#define CONSTRAINT_INDEX CONETWISTCONSTRAINT
/** bullet physics point 2 point constraint - A 3Dof angular joint without limits*/
//#define CONSTRAINT_INDEX POINT2POINTCONSTRAINT
/** bullet physics 6 degrees of freedom constraint - A 6 Dof joint with generic limits*/
#define CONSTRAINT_INDEX GENERIC6DOFCONSTRAINT
/** bullet physics 6 degrees of freedom with spring constraint (more stable impl)*/
//#define CONSTRAINT_INDEX GENERIC6DOFSPRING2CONSTRAINT
/** bullet physics 6 degrees of freedom with spring constraint (first impl)*/
//#define CONSTRAINT_INDEX GENERIC6DOFSPRINGCONSTRAINT

#define MOTOR_TYPE btRotationalLimitMotor

#if CONSTRAINT_INDEX == HINGECONSTRAINT
#define CONSTRAINT_TYPE btHingeConstraint
#elif CONSTRAINT_INDEX == GENERIC6DOFCONSTRAINT
#define CONSTRAINT_TYPE btGeneric6DofConstraint
#elif CONSTRAINT_INDEX == GENERIC6DOFSPRING2CONSTRAINT
#define CONSTRAINT_TYPE btGeneric6DofSpring2Constraint
#elif CONSTRAINT_INDEX == GENERIC6DOFSPRINGCONSTRAINT
#define CONSTRAINT_TYPE btGeneric6DofSpringConstraint
#elif CONSTRAINT_INDEX == POINT2POINTCONSTRAINT
#define CONSTRAINT_TYPE btPoint2PointConstraint
#elif CONSTRAINT_INDEX == CONETWISTCONSTRAINT
#define CONSTRAINT_TYPE btConeTwistConstraint
#else
#define CONSTRAINT_TYPE btHingeConstraint
#endif

#endif /* CONFIGURATION_SRBJOINTDEFINITIONS_HPP_ */
