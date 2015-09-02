//# corresponding header
#include <model/universe/evolution/population/creature/phenome/morphology/effector/motor/Motor.hpp>

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

Motor::Motor(const MotorType motorType) :
	mMotorType(motorType), mMaxForce(0), mPositionControlled(true), mIndex(-1), mEnabled(
		false) {
}

Motor::~Motor() {
}
