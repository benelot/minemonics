#ifndef MODEL_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_LIMB_LIMBBT_H_
#define MODEL_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_LIMB_LIMBBT_H_

//## controller headers
//## model headers
//## view headers
//## utils headers

//# corresponding headers
#include <model/evolution/population/creature/phenome/morphology/limb/LimbPhysics.h>

//# forward declarations
struct btDefaultMotionState;
class btDynamicsWorld;

//# system headers
//## controller headers
//## model headers
#include <BulletDynamics/Dynamics/btRigidBody.h>
#include <LinearMath/btQuaternion.h>
#include <LinearMath/btScalar.h>
#include <LinearMath/btVector3.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
#include <configuration/MorphologyConfiguration.h>

//## controller headers
//## model headers
//## view headers
//## utils headers

/**
 * @brief		The physical model of the limb implemented in the Bullet Physics Engine.
 * @details		Details
 * @date		2015-03-24
 * @author		Benjamin Ellenberger
 */
class LimbBt: public LimbPhysics {
public:
	LimbBt();
	virtual ~LimbBt();

	void initialize(btDynamicsWorld* world,
			MorphologyConfiguration::PrimitiveType type, btVector3 position,
			btQuaternion orientation, btVector3 size, btScalar mass);

	/**
	 * Add the limb to the physical world.
	 */
	void addToWorld();

	/**
	 * Remove the limb from the physical world.
	 */
	void removeFromWorld();

	/**
	 * Get the intersection in the global reference frame.
	 * @param origin: The origin the intersection starts from.
	 * @param direction: The direction of the intersection testing ray.
	 * @return The intersection in the global reference frame.
	 */
	btVector3 getIntersection(btVector3 origin, btVector3 direction);

	/**
	 * Get the precise intersection in the global reference frame.
	 * @param origin The origin the intersection starts from.
	 * @param direction: The direction of the intersection testing ray.
	 * @return The intersection in the local reference frame.
	 */
	btVector3 getPreciseIntersection(btVector3 origin, btVector3 direction);

	/**
	 * Get the fake intersection with the surface in the local reference frame.
	 * @param origin The origin the intersection starts from.
	 * @param direction: The direction of the intersection testing ray.
	 * @return The fake intersection in the local reference frame.
	 */
	btVector3 getLocalFakeIntersection(btVector3 origin, btVector3 direction);

	/**
	 * Get the intersection in the local reference frame of the indicated origin.
	 * @param origin: The origin the intersection starts from and in whose reference frame the intersection is shown.
	 * @param direction: The direction of the intersection testing ray.
	 * @return The intersection in the local reference frame.
	 */
	btVector3 getLocalIntersection(btVector3 origin, btVector3 direction);

	/**
	 * Get the precise intersection in the local reference frame of the indicated origin.
	 * @param origin The origin the intersection starts from and in whose reference frame the intersection is shown.
	 * @param direction: The direction of the intersection testing ray.
	 * @return The intersection in the local reference frame.
	 */
	btVector3 getLocalPreciseIntersection(btVector3 origin,
			btVector3 direction);

	//Accessor methods

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
	btDynamicsWorld* mWorld;
	btCollisionShape* mCollisionShape;
	btDefaultMotionState* mMotionState;
	btRigidBody* mBody;
	btVector3 mSize;
};

#endif /* MODEL_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_LIMB_LIMBBT_H_ */
