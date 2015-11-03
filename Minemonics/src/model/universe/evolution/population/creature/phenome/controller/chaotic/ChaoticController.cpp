//# corresponding headers
#include <model/universe/evolution/population/creature/phenome/controller/chaotic/ChaoticController.hpp>

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
#include <utils/NumericUtils.hpp>

BoostLogger ChaoticController::mBoostLogger; /*<! initialize the boost logger*/
ChaoticController::_Init ChaoticController::_initializer;
ChaoticController::ChaoticController() :
	Controller(CHAOTIC_CONTROLLER), mTime(0) {
	// Nothing to do for now

}

ChaoticController::ChaoticController(const ChaoticController& chaoticController) :
	Controller(CHAOTIC_CONTROLLER) {
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
}

ChaoticController::~ChaoticController() {
	// Nothing to do for now
}

void ChaoticController::initialize() {
	// Nothing to do for now
	u[0] = -1.5f;
	u[1] = 0;
	u[2] = 0;
}

ChaoticController* ChaoticController::clone() {
	return new ChaoticController();
}

void ChaoticController::perform(const double timeSinceLastTick) {

	if (mControlInputs.size() >= 2) {
		// set the inputs to the chaotic controller
		u[0] = mControlInputs[0]->getOutputValue();
		u[1] = mControlInputs[1]->getOutputValue();
	}

//time might not be the same as real-time, but it is close. On the other hand it is a very accurate simulation.
	mTime += timeSinceLastTick;

	calcChuaCircuit(); // calculate the circuit change

	double output = u[2]; //output the new value to the motor

	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info) << this << "(ChaoticController)::" << timeSinceLastTick << "/Output:" << output;

	setOutputValue(output);

	// distribute the output to the adjacent controllers or endpoints
	distributeOutput(output);
}

double* chuaCircuit(double t, int dimensions, double u[]) {
	/*
	 m0: slope in outer region
	 m1: slope in inner region
	 b: Breakpoints
	 */
	double c1 = 13.7;
	double c2 = 1;
	double c3 = 29;
	double m0 = -0.714;
	double m1 = -1.143;
	double b = 1;
	double limval = -0.5;
	double k = 7;
	double g = m0 * u[0] + (m1 - m0) / 2.0f * (abs(u[0] + b) - abs(u[0] - b));

	double* uout = new double[dimensions];
	uout[0] = c1 * (u[1] - u[0] - g);

	uout[1] = c2 * (u[0] - u[1] + u[2]);
	uout[2] = -c3 * u[1];

	return uout;
}

void ChaoticController::calcChuaCircuit() {
	/*
	 dx/dt=c1*(y-x-f (x))
	 dy/dt=c2*(x-y+z)
	 dz/dt=-c3*y
	 f(x)=m1*x+(m0-m1)/2*(|x+1|-|x-1|)
	 */
	std::cout << u[0] << "\t" << u[1] << "\t" << u[2] << std::endl;

	NumericUtils::calcRK4(0, 3, u, 0.001f, &chuaCircuit);
}

void ChaoticController::collectInputs() {
//Keep the inputs as they are
}
