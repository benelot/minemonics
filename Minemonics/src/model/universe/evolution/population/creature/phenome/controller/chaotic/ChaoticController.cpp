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

BoostLogger ChaoticController::mBoostLogger; /*<! initialize the boost logger*/
ChaoticController::_Init ChaoticController::_initializer;
ChaoticController::ChaoticController() :Controller(CHAOTIC_CONTROLLER),
	mTime(0) {
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
}

ChaoticController* ChaoticController::clone() {
	return new ChaoticController();
}

void ChaoticController::perform(const double timeSinceLastTick) {
	if (mControlInputs.size() != 0) {
		BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::fatal)<< "Why is there sine control input?";
	}

	//time might not be the same as real-time, but it is close. On the other hand it is a very accurate simulation.
	mTime += timeSinceLastTick;

	double output = mTime;

//	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info) << this << "::" << timeSinceLastTick << "/Output:" << output << std::endl;

	setOutputValue(output);

	// distribute the output to the adjacent controllers or endpoints
	distributeOutput(output);
}

void ChaoticController::collectInputs() {
	//Keep the inputs as they are
}
