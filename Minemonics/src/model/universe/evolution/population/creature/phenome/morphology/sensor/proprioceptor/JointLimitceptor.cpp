//# corresponding header
#include <model/universe/evolution/population/creature/phenome/morphology/effector/motor/ServoMotor.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/sensor/proprioceptor/JointLimitceptor.hpp>

//## view headers
//## utils headers

JointLimitceptor::JointLimitceptor() :
mLimit(BOTH_LIMITS), mLimitError(0) {
}

JointLimitceptor::JointLimitceptor(std::vector<int*>::size_type jointIndex,
JointPhysics::RotationalDegreeOfFreedom rotationalDOF, Limit limit) :
JointProprioceptor(jointIndex, rotationalDOF), mLimitError(0), mLimit(limit) {

}

JointLimitceptor::~JointLimitceptor() {

}

void JointLimitceptor::update(double timeSinceLastTick) {
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
