#ifndef CONFIGURATION_EVALUATIONCONFIGURATION_H_
#define CONFIGURATION_EVALUATIONCONFIGURATION_H_

//# corresponding headers
//# forward declarations
//# system headers
//## controller headers
//## model headers
#include <OgreVector3.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers

/**
 * @brief		The configuration for the evaluation of the creatures.
 * @details		Details
 * @date		2015-06-10
 * @author		Benjamin Ellenberger
 */
class EvaluationConfiguration {
public:
	static const unsigned DEFAULT_PARALLEL_EVALUATION; /**!< Number of parallel evaluations */
	static const double DEFAULT_EVALUATION_TIME; /**!< The default evaluation time */
	static const Ogre::Vector3 ROOT_POSITION; /**!< The position where creatures are dropped */
};

#endif /* CONFIGURATION_EVALUATIONCONFIGURATION_H_ */
