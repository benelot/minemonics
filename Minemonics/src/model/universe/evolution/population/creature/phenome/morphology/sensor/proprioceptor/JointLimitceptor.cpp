//# corresponding header
#include <model/universe/evolution/population/creature/phenome/morphology/sensor/proprioceptor/JointLimitceptor.hpp>
#include <model/universe/evolution/population/creature/phenome/PhenomeModel.hpp>

//## view headers
//## utils headers

JointLimitceptor::JointLimitceptor() :
	mLimitError(0), mLimit(JointLimitceptor::BOTH_LIMITS) {
}

JointLimitceptor::JointLimitceptor(JointModel* jointModel,
	JointPhysics::RotationalDegreeOfFreedom rotationalDOF, Limit limit) :
	JointProprioceptor(jointModel, rotationalDOF), mLimitError(0), mLimit(
		limit) {

}

JointLimitceptor::~JointLimitceptor() {

}

void JointLimitceptor::initialize() {
	JointProprioceptor::initialize();
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
