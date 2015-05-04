//# corresponding header
#include <model/evolution/population/creature/phenome/morphology/effector/motor/Motor.hpp>

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

Motor::Motor(MotorType motorType) :
		mMotorType(motorType), mMaxForce(0), mMaxSpeed(0), mPositionControlled(
				true), mIndex(-1), mEnabled(false) {
}

Motor::~Motor() {
}
