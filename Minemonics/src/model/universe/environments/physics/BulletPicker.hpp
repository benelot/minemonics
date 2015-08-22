#ifndef VIEW_PICKING_BULLETRAY_HPP_
#define VIEW_PICKING_BULLETRAY_HPP_

//# corresponding headers
//# forward declarations
class btDynamicsWorld;
class btMultiBodyPoint2Point;
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
	btVector3 pickBody(btDynamicsWorld* world, const btVector3& rayFromWorld,
			const btVector3& rayToWorld);
	bool movePickedBody(const btVector3& rayFromWorld,
			const btVector3& rayToWorld);
private:
	//data for picking objects
	btRigidBody* mPickedBody;
	btTypedConstraint* mPickedConstraint;
	btMultiBodyPoint2Point* mPickingMultiBodyPoint2Point;

	btVector3 mOldPickingPos;
	btVector3 mHitPos;
	btScalar mOldPickingDist;
	bool mPrevCanSleep;
};

#endif /* VIEW_PICKING_BULLETRAY_HPP_ */
