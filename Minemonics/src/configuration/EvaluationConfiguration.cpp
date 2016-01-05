//# corresponding headers
#include <configuration/EvaluationConfiguration.hpp>

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

const unsigned EvaluationConfiguration::DEFAULT_PARALLEL_EVALUATION = 1; /**!< Number of parallel evaluations */
const double EvaluationConfiguration::DEFAULT_EVALUATION_TIME = 100; /**!< The default evaluation time */

const Ogre::Vector3 EvaluationConfiguration::ROOT_POSITION = Ogre::Vector3(0, 10,
	0); /**!< The position where creatures are dropped */
