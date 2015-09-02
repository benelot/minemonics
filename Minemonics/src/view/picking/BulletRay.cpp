//# corresponding headers
#include <view/picking/BulletRay.hpp>

//# forward declarations
//# system headers
//## controller headers
//## model headers
#include <LinearMath/btVector3.h>
#include <BulletCollision/CollisionDispatch/btCollisionWorld.h>
#include <BulletCollision/NarrowPhaseCollision/btRaycastCallback.h>
#include <BulletDynamics/Dynamics/btDynamicsWorld.h>

//## view headers
//# custom headers
//## base headers
#include <SimulationManager.hpp>

//## configuration headers
#include <configuration/PhysicsConfiguration.hpp>

//## controller headers
//## model headers
//## view headers
#include <view/visualization/bulletphysics/OgreBtDebugDrawer.hpp>

//## utils headers

btVector3 BulletRay::castRay(btDynamicsWorld* world, btVector3 origin,
	btVector3 direction) {
	// the ray caster currently only finds the intersection
	// when hitting the forward face of a triangle therefore,
	//the ray has to come from the outside of the shape
	btVector3 rayStart = origin;
	btVector3 rayEnd = origin + direction.normalized() * 1000.0f;

	SimulationManager::getSingleton()->getDebugDrawer().drawLine(rayStart,
		rayEnd, btVector3(1, 1, 0));

	btVector3 hitPosition = origin;

	btCollisionWorld::ClosestRayResultCallback rayCallback(rayStart, rayEnd);

	//kF_UseGjkConvexRaytest flag is now enabled by default, use the faster but more approximate algorithm
	rayCallback.m_flags |= btTriangleRaycastCallback::kF_KeepUnflippedNormal;
	rayCallback.m_flags &= !btTriangleRaycastCallback::kF_FilterBackfaces;
	rayCallback.m_collisionFilterGroup =
		PhysicsConfiguration::COL_CREATURE_TESTRAY;
	rayCallback.m_collisionFilterMask =
		PhysicsConfiguration::CREATURE_TESTRAY_COLLIDES_WITH;

	world->rayTest(rayStart, rayEnd, rayCallback);

	if (rayCallback.hasHit()) {
		btVector3 p = rayStart.lerp(rayEnd, rayCallback.m_closestHitFraction);
		SimulationManager::getSingleton()->getDebugDrawer().drawSphere(p, 1,
			btVector3(1, 0, 0));
		SimulationManager::getSingleton()->getDebugDrawer().drawLine(p,
			p + rayCallback.m_hitNormalWorld, btVector3(1, 0, 0));
		hitPosition = p;

	} else {
		SimulationManager::getSingleton()->getDebugDrawer().drawSphere(rayStart,
			1, btVector3(1, 0, 0));
		//no hit
	}
	return hitPosition;
}
