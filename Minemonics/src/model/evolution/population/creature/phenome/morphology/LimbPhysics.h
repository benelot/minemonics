/*
 * LimbPhysics.h
 *
 *  Created on: Mar 24, 2015
 *      Author: leviathan
 */

#ifndef MODEL_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_LIMBPHYSICS_H_
#define MODEL_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_LIMBPHYSICS_H_

//# corresponding header
//# forward declarations
//# system headers
//## controller headers
//## model headers
#include <bullet/LinearMath/btVector3.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers

class LimbPhysics {
public:
	LimbPhysics();
	virtual ~LimbPhysics();

	virtual void addToWorld() = 0;

	virtual void removeFromWorld() = 0;

	virtual btVector3 getIntersection(btVector3 origin,
			btVector3 direction) = 0;
	virtual btVector3 getLocalIntersection(btVector3 origin,
			btVector3 direction) = 0;
	virtual btVector3 getLocalPreciseIntersection(btVector3 origin,
			btVector3 direction) = 0;
};

#endif /* MODEL_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_LIMBPHYSICS_H_ */
