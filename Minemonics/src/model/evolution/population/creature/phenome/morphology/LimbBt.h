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
//## controller headers
#include "controller/evolution/population/creature/phenome/morphology/Limb.h"

//## model headers
#include "model/evolution/population/creature/phenome/morphology/LimbPhysics.h"

//## view headers
//## utils headers

class LimbBt: public LimbPhysics {
public:
	LimbBt();
	virtual ~LimbBt();

	void initialize(Limb::PrimitiveType type, btVector3 position, btQuaternion orientation,
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

private:
	btCollisionShape* mCollisionShape;
	btDefaultMotionState* mMotionState;
	btRigidBody* mBody;
};

#endif /* MODEL_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_LIMBBT_H_ */
