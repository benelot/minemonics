//# corresponding header
#include <model/universe/evolution/population/creature/phenome/morphology/joint/JointModel.hpp>

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
#include <model/universe/evolution/population/creature/phenome/morphology/sensor/Sensor.hpp>

//## view headers
//## utils headers

BoostLogger JointModel::mBoostLogger; /*<! initialize the boost logger*/
JointModel::_Init JointModel::_initializer;
JointModel::JointModel() :
	mJointPhysics(NULL), mParentIndex(-1), mChildIndex(-1), mOwnIndex(-1) {

}

JointModel::JointModel(const JointModel& jointModel) :
	mParentIndex(jointModel.mParentIndex), mChildIndex(jointModel.mChildIndex), mOwnIndex(
		jointModel.mOwnIndex) {
	mJointPhysics = jointModel.mJointPhysics->clone();
}

JointModel::~JointModel() {
	delete mJointPhysics;
	mJointPhysics = NULL;

	while(!mSensors.empty()){
		delete mSensors.back();
		mSensors.pop_back();
	}

	mAngleceptors.clear();
	mForceceptors.clear();
	mLimitceptors.clear();
}

void JointModel::addSensors(){
	JointAngleceptor* angleceptor = new JointAngleceptor(this,
			JointPhysics::RDOF_PITCH);
		mSensors.push_back(angleceptor);
		mAngleceptors.push_back(angleceptor);

		angleceptor = new JointAngleceptor(this, JointPhysics::RDOF_YAW);
		mSensors.push_back(angleceptor);
		mAngleceptors.push_back(angleceptor);

		angleceptor = new JointAngleceptor(this, JointPhysics::RDOF_ROLL);
		mSensors.push_back(angleceptor);
		mAngleceptors.push_back(angleceptor);

		JointVelocityceptor* velocityceptor = new JointVelocityceptor(this,
			JointPhysics::RDOF_PITCH);
		mSensors.push_back(velocityceptor);
		mVelocityceptors.push_back(velocityceptor);

		velocityceptor = new JointVelocityceptor(this, JointPhysics::RDOF_YAW);
		mSensors.push_back(velocityceptor);
		mVelocityceptors.push_back(velocityceptor);

		velocityceptor = new JointVelocityceptor(this, JointPhysics::RDOF_ROLL);
		mSensors.push_back(velocityceptor);
		mVelocityceptors.push_back(velocityceptor);

		JointForceceptor* forceceptor = new JointForceceptor(this,
			JointPhysics::RDOF_PITCH);
		mSensors.push_back(forceceptor);
		mForceceptors.push_back(forceceptor);

		forceceptor = new JointForceceptor(this, JointPhysics::RDOF_YAW);
		mSensors.push_back(forceceptor);
		mForceceptors.push_back(forceceptor);

		forceceptor = new JointForceceptor(this, JointPhysics::RDOF_ROLL);
		mSensors.push_back(forceceptor);
		mForceceptors.push_back(forceceptor);

		JointLimitceptor* limitceptor = new JointLimitceptor(this,
			JointPhysics::RDOF_PITCH, JointLimitceptor::BOTH_LIMITS);
		mSensors.push_back(limitceptor);
		mLimitceptors.push_back(limitceptor);

		limitceptor = new JointLimitceptor(this, JointPhysics::RDOF_YAW,
			JointLimitceptor::BOTH_LIMITS);
		mSensors.push_back(limitceptor);
		mLimitceptors.push_back(limitceptor);

		limitceptor = new JointLimitceptor(this, JointPhysics::RDOF_ROLL,
			JointLimitceptor::BOTH_LIMITS);
		mSensors.push_back(limitceptor);
		mLimitceptors.push_back(limitceptor);
}

void JointModel::update(double timeSinceLastTick) {
	mJointPhysics->update(timeSinceLastTick);

	for (std::vector<Sensor*>::iterator sit = mSensors.begin();
		sit != mSensors.end(); sit++) {
		(*sit)->update(timeSinceLastTick);
	}

//	std::cout << std::endl << "AngleSensors:";
//	for (std::vector<JointAngleProprioceptor*>::iterator tit = mAngleceptors.begin();
//			tit != mAngleceptors.end(); tit++) {
//		std::cout << (*tit)->getAngle() << "|";
//	}
//	std::cout << std::endl;
//
//	std::cout << std::endl << "ForceSensors:";
//	for (std::vector<JointForceProprioceptor*>::iterator tit = mForceceptors.begin();
//			tit != mForceceptors.end(); tit++) {
//		std::cout << (*tit)->getForce() << "|";
//	}
//	std::cout << std::endl;
//
//	std::cout << std::endl << "LimitSensors:";
//	for (std::vector<JointLimitProprioceptor*>::iterator tit = mLimitceptors.begin();
//			tit != mLimitceptors.end(); tit++) {
//		std::cout << (*tit)->getLimitError() << "|";
//	}
//	std::cout << std::endl;
}

std::vector<ControlInput*> JointModel::getControlInputs() {
	std::vector<ControlInput*> mControlInputs;

	mControlInputs.insert(mControlInputs.end(),mJointPhysics->getMotors().begin(),mJointPhysics->getMotors().end());
	return mControlInputs;
}

std::vector<ControlOutput*> JointModel::getControlOutputs() {
	std::vector<ControlOutput*> mControlOutputs;

	mControlOutputs.insert(mControlOutputs.end(),mSensors.begin(),mSensors.end());

	return mControlOutputs;
}

bool JointModel::equals(const JointModel& jointModel) const {
	if (!ComponentModel::equals(jointModel)) {
		return false;
	}

	if (!mJointPhysics->equals(*jointModel.mJointPhysics)) {
		return false;
	}

	if (mParentIndex != jointModel.mParentIndex) {
		return false;
	}

	if (mChildIndex != jointModel.mChildIndex) {
		return false;
	}

	if (mOwnIndex != jointModel.mOwnIndex) {
		return false;
	}

	if (mComponentType != jointModel.mComponentType) {
		return false;
	}

	return true;
}

void JointModel::reset(const Ogre::Vector3 position) {
	mJointPhysics->reset(position);
}

void JointModel::reposition(const Ogre::Vector3 position) {
	mJointPhysics->reposition(position);
}

double JointModel::getJointPos(int jointAxisIndex) {
	return mJointPhysics->getJointPos(jointAxisIndex);
}

double JointModel::getJointVel(int jointAxisIndex,double timeSinceLastTick, double lastJointPosition) {
	return mJointPhysics->getJointVel(jointAxisIndex,timeSinceLastTick,lastJointPosition);
}

