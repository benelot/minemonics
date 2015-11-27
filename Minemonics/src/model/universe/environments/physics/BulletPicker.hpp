#ifndef MODEL_UNIVERSE_ENVIRONMENTS_PHYSICS_BULLETRAY_HPP_
#define MODEL_UNIVERSE_ENVIRONMENTS_PHYSICS_BULLETRAY_HPP_

//# corresponding headers
#include <configuration/Definitions.hpp>

//# forward declarations
//# system headers
//## controller headers
//## model headers
#include <LinearMath/btScalar.h>
#include <LinearMath/btVector3.h>
#include <BulletDynamics/Dynamics/btDynamicsWorld.h>
#include <BulletDynamics/Dynamics/btRigidBody.h>
#include <BulletDynamics/ConstraintSolver/btTypedConstraint.h>
#include <BulletDynamics/Featherstone/btMultiBodyDynamicsWorld.h>
#include <BulletDynamics/Featherstone/btMultiBodyPoint2Point.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers

/**
 * @brief		The object picker implemented in bullet physics.
 * @details		Details
 * @date		2015-05-20
 * @author		Benjamin Ellenberger
 */
class BulletPicker {
public:
	BulletPicker();
	virtual ~BulletPicker();
	btVector3 pickBody(btDynamicsWorld* world, const btVector3& rayFromWorld,
		const btVector3& rayToWorld);
	bool movePickedBody(const btVector3& rayFromWorld,
		const btVector3& rayToWorld);

	// Accessor methods ##########################
	bool isPicking() const {
		return mPicking;
	}

	void setPicking(bool picking);

private:
	//data for picking objects
	btRigidBody* mPickedBody;
	btTypedConstraint* mPickedConstraint;
	btMultiBodyPoint2Point* mPickingMultiBodyPoint2Point;

	btVector3 mOldPickingPos;
	btVector3 mHitPos;
	btScalar mOldPickingDist;
	bool mPrevCanSleep;
	bool mPicking;
	btMultiBodyDynamicsWorld* mMultibodyworld;
	btDynamicsWorld* mWorld;
};

#endif /* MODEL_UNIVERSE_ENVIRONMENTS_PHYSICS_BULLETRAY_HPP_ */
