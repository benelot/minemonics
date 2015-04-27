/*
 * LimbBt.h
 *
 *  Created on: Mar 24, 2015
 *      Author: leviathan
 */

#ifndef MODEL_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_LIMBBT_H_
#define MODEL_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_LIMBBT_H_

//# corresponding headers
#include "model/evolution/population/creature/phenome/morphology/LimbPhysics.h"

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
//## view headers
//## utils headers

/**
 * @brief		Brief
 * @details		Details
 * @date		2015-04-27
 * @author		Benjamin Ellenberger
 */
class LimbBt: public LimbPhysics {
public:
	LimbBt();
	virtual ~LimbBt();

	void initialize(btDynamicsWorld* world,
			MorphologyConfiguration::PrimitiveType type, btVector3 position,
			btQuaternion orientation, btVector3 size, btScalar mass);

	btVector3 getPosition() {
		return mBody->getCenterOfMassPosition();
	}

	btQuaternion getOrientation() {
		return mBody->getOrientation();
	}

	btRigidBody* getRigidBody() {
		return mBody;
	}

	/**
	 * Get the intersection in the global reference frame.
	 * @param origin: The origin the intersection starts from.
	 * @param direction: The direction of the intersection testing ray.
	 */
	btVector3 getIntersection(btVector3 origin, btVector3 direction);

	/**
	 * Get the precise intersection in the global reference frame.
	 * @param origin The origin the intersection starts from.
	 * @param direction: The direction of the intersection testing ray.
	 */
	btVector3 getPreciseIntersection(btVector3 origin, btVector3 direction);


	btVector3 getLocalFakeIntersection(btVector3 origin, btVector3 direction);

	/**
	 * Get the intersection in the local reference frame of the indicated origin.
	 * @param origin: The origin the intersection starts from and in whose reference frame the intersection is shown.
	 * @param direction: The direction of the intersection testing ray.
	 */
	btVector3 getLocalIntersection(btVector3 origin, btVector3 direction);

	/**
	 * Get the precise intersection in the local reference frame of the indicated origin.
	 * @param origin The origin the intersection starts from and in whose reference frame the intersection is shown.
	 * @param direction: The direction of the intersection testing ray.
	 */
	btVector3 getLocalPreciseIntersection(btVector3 origin,
			btVector3 direction);

	void addToWorld();

	void removeFromWorld();

private:
	btDynamicsWorld* mWorld;
	btCollisionShape* mCollisionShape;
	btDefaultMotionState* mMotionState;
	btRigidBody* mBody;
	btVector3 mSize;
};

#endif /* MODEL_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_LIMBBT_H_ */
