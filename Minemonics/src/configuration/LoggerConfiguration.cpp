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
	"AverageVelocity|CreatureModel|Debugger|SimulationManager|PhysicsController|Reaper|FSPhenomeModel|SRBPhenomeModel|PhenomeModel|Phenome"
// Reaper debugging
//	+ "|FSPhenomeModel|SRBPhenomeModel|PhenomeModel"
// Embryogenesis Debugging
//+"|FSLimbBt|SRBLimbBt|LimbO3D|Embryogenesis|FSJointBt|SRBJointBt"
;

const std::string LoggerConfiguration::TOP_FOLDER = "logs";

const bool LoggerConfiguration::LOG_SPECIAL = false;
