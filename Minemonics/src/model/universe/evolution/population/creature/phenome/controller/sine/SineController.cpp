//# corresponding headers
#include <model/universe/evolution/population/creature/phenome/controller/sine/SineController.hpp>

//# forward declarations
//# system headers
#include <cmath>
#include <iostream>
#include <vector>

//## controller headers
//## model headers
#include <boost/lexical_cast.hpp>
#include <boost/log/attributes/scoped_attribute.hpp>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers

BoostLogger SineController::mBoostLogger; /*<! initialize the boost logger*/
SineController::_Init SineController::_initializer;
SineController::SineController(const double amplitude, const double frequency,
	const double xShift, const double yShift) :
	Controller(SINE_CONTROLLER), mAmplitude(amplitude), mFrequency(frequency), mXShift(
		xShift), mYShift(yShift), mTime(0) {
	mLoggerName = boost::lexical_cast<std::string>(this) + "SineLogger";
}

SineController::SineController() :
	Controller(SINE_CONTROLLER), mAmplitude(1), mFrequency(1), mXShift(0), mYShift(
		1), mTime(0) {
	mLoggerName = boost::lexical_cast<std::string>(this) + "SineLogger";
}

SineController::SineController(const SineController& sineController) :
	Controller(SINE_CONTROLLER) {

	mLoggerName = boost::lexical_cast<std::string>(this) + "SineLogger";

	mAmplitude = sineController.mAmplitude;
	mFrequency = sineController.mFrequency;
	mTime = sineController.mTime;
	mType = sineController.mType;
	mXShift = sineController.mXShift;
	mYShift = sineController.mYShift;

	for (std::vector<ControlInput*>::const_iterator cit =
		sineController.mControlOutputs.begin();
		cit != sineController.mControlOutputs.end(); cit++) {
		mControlOutputs.push_back(*cit);
	}

	for (std::vector<ControlOutput*>::const_iterator cit =
		sineController.mControlInputs.begin();
		cit != sineController.mControlInputs.end(); cit++) {
		mControlInputs.push_back(*cit);
	}
}

SineController::~SineController() {
}

void SineController::initialize() {
	mLoggerName = "[" + boost::lexical_cast<std::string>(mOwnIndex) + "]" + mLoggingID + "SineLogger";
	mDataSink.initialize(mLoggerName, 3, 20);
}

void SineController::perturb(){
	//Sine controllers can not be perturbed
}

void SineController::perform(const double timeSinceLastTick) {
	double input = 0;
	if (mControlInputs.size() != 0) {
		BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::fatal)<< "Why is there sine control input?";
	}
	//time might not be the same as real-time, but it is close. On the other hand it is a very accurate simulation.
	mTime += timeSinceLastTick;

	double output = mAmplitude
		* sin(mFrequency * mTime * 2.0f * M_PIl + mXShift) + mYShift;

//	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info) << this << "::" << timeSinceLastTick << "/Output:" << output << std::endl;

	double dataX[1];
	dataX[0] = mTime;
	double dataY[1];
	dataY[0] = output;
	double dataZ[1];
	dataZ[0] = 0;

	mDataSink.addData(dataX, dataY, dataZ, 3, 1); // Send data point to the data sink

	setOutputValue(output);

	// distribute the output to the adjacent controllers or endpoints
	distributeOutput(output);
}

SineController* SineController::clone() {
	return new SineController(*this);
}

void SineController::collectInputs() {
	//Keep the inputs as they are
}
