//# corresponding headers
#include <configuration/LoggerConfiguration.hpp>

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

const std::string LoggerConfiguration::loggedClasses =
	"AverageVelocity|CreatureModel|Debugger|SimulationManager|ViewController|PhysicsController|Reaper|FSPhenomeModel|SRBPhenomeModel|PhenomeModel|Phenome|Evaluation|ChaoticController|Planet|Population";

const std::string LoggerConfiguration::TOP_FOLDER = "logs";

const int LoggerConfiguration::LOG_DATA_QTY = 20;

bool LoggerConfiguration::LOG_SPECIAL = false;
