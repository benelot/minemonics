//# corresponding headers
#include <model/universe/evolution/population/creature/phenome/controller/chaotic/ChaoticController.hpp>

//# forward declarations
//# system headers
#include <cstdlib>
#include <vector>
#include <string>

//## controller headers
//## model headers
#include <boost/lexical_cast.hpp>
#include <boost/log/attributes/scoped_attribute.hpp>

//## view headers
//# custom headers
//## base headers
//## configuration headers
#include <configuration/LoggerConfiguration.hpp>

//## controller headers
//## model headers
#include <model/universe/evolution/population/creature/phenome/controller/ControlOutput.hpp>

//## view headers
//## utils headers
#include <utils/NumericUtils.hpp>

BoostLogger ChaoticController::mBoostLogger; /*<! initialize the boost logger*/
ChaoticController::_Init ChaoticController::_initializer;

ChaoticController::ChaoticController() :
	Controller(CHAOTIC_CONTROLLER), mLoggerName(
		"ChaosLogger" + boost::lexical_cast<std::string>(this)), mTime(0), mSystemType(
		ChaoticControllerGene::CHUA_CIRCUIT), mFirstTime(true), mInitialX(0), mInitialY(
		0), mInitialZ(0), mSpeed(1) {
}

ChaoticController::ChaoticController(
	ChaoticControllerGene::ChaoticSystemType systemType, double initialX,
	double initialY, double initialZ, double speed) :
	Controller(CHAOTIC_CONTROLLER), mLoggerName(
		"ChaosLogger" + boost::lexical_cast<std::string>(this)), mTime(0), mSystemType(
		systemType), mFirstTime(true), mInitialX(initialX), mInitialY(initialY), mInitialZ(
		initialZ), mSpeed(speed) {
}

ChaoticController::ChaoticController(
	ChaoticControllerGene::ChaoticSystemType systemType) :
	Controller(CHAOTIC_CONTROLLER), mTime(0), mSystemType(systemType), mFirstTime(
		0) {
	mLoggerName = "ChaosLogger" + boost::lexical_cast<std::string>(this);
}

ChaoticController::ChaoticController(const ChaoticController& chaoticController) :
	Controller(CHAOTIC_CONTROLLER) {
	mLoggerName = "ChaosLogger" + boost::lexical_cast<std::string>(this);

	mTime = chaoticController.mTime;
	mType = chaoticController.mType;

	for (std::vector<ControlInput*>::const_iterator cit =
		chaoticController.mControlOutputs.begin();
		cit != chaoticController.mControlOutputs.end(); cit++) {
		mControlOutputs.push_back(*cit);
	}

	for (std::vector<ControlOutput*>::const_iterator cit =
		chaoticController.mControlInputs.begin();
		cit != chaoticController.mControlInputs.end(); cit++) {
		mControlInputs.push_back(*cit);
	}

	mSystemType = chaoticController.mSystemType;

	mFirstTime = chaoticController.mFirstTime;

}

ChaoticController::~ChaoticController() {
	// Nothing to do for now
}

void ChaoticController::initialize() {
	mDataSink.initialize(mLoggerName, 3, 20);

	u[0] = mInitialX;
	u[1] = mInitialY;
	u[2] = mInitialZ;
}

ChaoticController* ChaoticController::clone() {
	return new ChaoticController(*this);
}

void ChaoticController::perform(const double timeSinceLastTick) {

	if (mControlInputs.size() >= 2 && !mFirstTime) {
		// LIMIT x
		// set the inputs to the chaotic controller
//		u[0] = mControlInputs[0]->getOutputValue();
//		u[0] = mControlInputs[1]->getOutputValue();

//		u[1] = mControlInputs[0]->getOutputValue();
//		u[1] = mControlInputs[1]->getOutputValue();

//		u[2] = mControlInputs[0]->getOutputValue();
//		u[2] = mControlInputs[1]->getOutputValue();
	}

	mFirstTime = false;

	mTime += timeSinceLastTick; // time might not be the same as real-time, but it is close. On the other hand it is a very accurate simulation.

	calcChuaCircuit(); // calculate the circuit change

//	double output = u[0]; //output the new value to the motor
//	double output = u[1]; //output the new value to the motor
	double output = u[2]; //output the new value to the motor

//	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< this << "(ChaoticController)::" << timeSinceLastTick << "/Output:" << output;

	// create 1 dimensional data set out of 3 dimensional data
	double dataX[1];
	dataX[0] = u[0];
	double dataY[1];
	dataY[0] = u[1];
	double dataZ[1];
	dataZ[0] = u[2];

	mDataSink.addData(dataX, dataY, dataZ, 3, 1); // Send data point to the data sink

	setOutputValue(output); // set output value to be used by outputs

	distributeOutput(output); // distribute the output to the adjacent controllers or endpoints
}

double* ChaoticController::chuaCircuit(double t, int dimensions, double u[]) {
	double c1 = 15.6;
	double c2 = 1;
	double c3 = 28;
	double m0 = -0.714; /**!< slope in outer region */
	double m1 = -1.143; /**!< slope in inner region */
	double b = 1; /**!< Breakpoints */

	double g = m0 * u[0] + (m1 - m0) / 2.0f * (abs(u[0] + b) - abs(u[0] - b)); // a 3-segment piecewise-linear equation (Chua diode)

	double* uout = new double[dimensions];
	uout[0] = c1 * (u[1] - u[0] - g);

	uout[1] = c2 * (u[0] - u[1] + u[2]);
	uout[2] = -c3 * u[1];

	// LIMIT dx/dt
	//prepare limiter
//	double limiter = mControlInputs[0]->getOutputValue();
//	double limiter = mControlInputs[1]->getOutputValue();

	//Sample simple limiter
	//double limitValue = 2;//(* 1.9/Period 1 limit cycle // 2.23/Period 4 limit \cycle // >2.4/Not limited *)
	//double softness = 7; //(* Softness *)
	//double limiter = (1.0f/2.0f)*(std::tanh(softness* (limitValue - u[0])) + 1.0f);

	// where do we limit?
//	uout[0] *= limiter;
//	uout[1] *= limiter;
//	uout[2] *= limiter; //	(limiter >= 1.0f) ? 1.0f : limiter;

	return uout;
}

static double* unlimitedChuaCircuit(double t, int dimensions, double u[]) {
	double c1 = 15.6;
	double c2 = 1;
	double c3 = 28;
	double m0 = -0.714; /**!< slope in outer region */
	double m1 = -1.143; /**!< slope in inner region */
	double b = 1; /**!< Breakpoints */

	double g = m0 * u[0] + (m1 - m0) / 2.0f * (abs(u[0] + b) - abs(u[0] - b)); // a 3-segment piecewise-linear equation (Chua diode)

	double* uout = new double[dimensions];
	uout[0] = c1 * (u[1] - u[0] - g);

	uout[1] = c2 * (u[0] - u[1] + u[2]);
	uout[2] = -c3 * u[1];

	return uout;
}

double* ChaoticController::runChuaCircuit(double t, int dimensions, double u[],
	ChaoticController* controller) {
	return controller->chuaCircuit(t, dimensions, u);
}

void ChaoticController::calcChuaCircuit() {
	/*
	 dx/dt=c1*(y-x-f (x))
	 dy/dt=c2*(x-y+z)
	 dz/dt=-c3*y
	 f(x)=m1*x+(m0-m1)/2*(|x+1|-|x-1|)
	 */
	if (LoggerConfiguration::LOG_SPECIAL) {
		BOOST_LOG_SCOPED_THREAD_TAG("LoggerName", mLoggerName);
		BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::debug)<< u[0] << "\t" << u[1] << "\t" << u[2];
	}

	double h = 0.001f;
	double i = mSpeed;
	for(; i >= 1;i--) {
		NumericUtils::calcRK6(0, 3, u, h, unlimitedChuaCircuit);
	}

	h *= i;
	NumericUtils::calcRK6(0, 3, u, h, unlimitedChuaCircuit);
}

void ChaoticController::collectInputs() {
//Keep the inputs as they are
}
