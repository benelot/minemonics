/*
 * LimbBt.h
 *
 *  Created on: Mar 24, 2015
 *      Author: leviathan
 */

#ifndef MODEL_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_LIMBBT_H_
#define MODEL_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_LIMBBT_H_

//# corresponding header
//# forward declarations
//# system headers
//## controller headers
//## model headers
#include <btBulletDynamicsCommon.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
#include "configuration/MorphologyConfiguration.h"

//## controller headers
//## model headers
#include "model/evolution/population/creature/phenome/morphology/LimbPhysics.h"

//## view headers
//## utils headers

class LimbBt: public LimbPhysics {
public:
	LimbBt();
	virtual ~LimbBt();

	void initialize(btDynamicsWorld* world, MorphologyConfiguration::PrimitiveType type, btVector3 position, btQuaternion orientation,
			btVector3 size, btScalar mass);

	btVector3 getPosition() {
		return mBody->getCenterOfMassPosition();
	}

	btQuaternion getOrientation() {
		return mBody->getOrientation();
	}

	btRigidBody* getRigidBody() {
		return mBody;
	}

	void addToWorld();

	void removeFromWorld();

private:
	btDynamicsWorld* mWorld;
	btCollisionShape* mCollisionShape;
	btDefaultMotionState* mMotionState;
	btRigidBody* mBody;
};

#endif /* MODEL_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_LIMBBT_H_ */
