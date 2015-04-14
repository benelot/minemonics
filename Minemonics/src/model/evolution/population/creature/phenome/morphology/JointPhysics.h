/*
 * JointPhysics.h
 *
 *  Created on: Apr 14, 2015
 *      Author: leviathan
 */

#ifndef MODEL_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_JOINTPHYSICS_H_
#define MODEL_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_JOINTPHYSICS_H_

//# corresponding header
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

class JointPhysics {
public:
	JointPhysics();
	virtual ~JointPhysics();

	virtual void addToWorld() = 0;

	virtual void removeFromWorld() = 0;

	virtual void setAngularLimits(Ogre::Vector3 angularLowerLimit,
			Ogre::Vector3 angularUpperLimit) = 0;
};

#endif /* MODEL_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_JOINTPHYSICS_H_ */
