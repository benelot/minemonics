#ifndef MODEL_UNIVERSE_ENVIRONMENTS_PHYSICS_BULLETRAY_HPP_
#define MODEL_UNIVERSE_ENVIRONMENTS_PHYSICS_BULLETRAY_HPP_

//# corresponding headers
#include <configuration/Definitions.hpp>

//# forward declarations
class btDynamicsWorld;
class btMultiBodyPoint2Point;
class btMultiBodyDynamicsWorld;
class btRigidBody;
class btTypedConstraint;

//# system headers
//## controller headers
//## model headers
#include <LinearMath/btScalar.h>
#include <LinearMath/btVector3.h>

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
