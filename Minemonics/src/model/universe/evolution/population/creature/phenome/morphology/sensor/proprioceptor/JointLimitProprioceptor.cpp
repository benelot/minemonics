//# corresponding header
#include <model/universe/evolution/population/creature/phenome/morphology/sensor/proprioceptor/JointLimitProprioceptor.hpp>

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
#include <model/universe/evolution/population/creature/phenome/morphology/effector/motor/ServoMotor.hpp>

//## view headers
//## utils headers

JointLimitProprioceptor::JointLimitProprioceptor(
		std::vector<CONSTRAINT_TYPE*>::size_type jointIndex,
		JointPhysics::RotationalDegreeOfFreedom rotationalDOF, Limit limit) :
		JointProprioceptor(jointIndex, rotationalDOF), mLimitError(0), mLimit(
				limit) {

}

JointLimitProprioceptor::~JointLimitProprioceptor() {

}

void JointLimitProprioceptor::update(double timeSinceLastTick) {
//	MOTOR_TYPE* motor = mG6DofJoint->getRotationalLimitMotor(mMotorIndex);
//	switch (mLimit) {
//	case LOWER_LIMIT:
//		if (motor->m_currentPosition >= motor->m_hiLimit) {
//			setLimitError(motor->m_currentLimitError);
//		} else {
//			setLimitError(0);
//		}
//		break;
//	case UPPER_LIMIT:
//		if (motor->m_currentPosition <= motor->m_loLimit) {
//			setLimitError(motor->m_currentLimitError);
//		} else {
//			setLimitError(0);
//		}
//		break;
//	case BOTH_LIMITS:
//		setLimitError(motor->m_currentLimitError);
//		break;
//	}

}
