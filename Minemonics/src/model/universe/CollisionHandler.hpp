//#ifndef MODEL_UNIVERSE_COLLISIONHANDLER_HPP_
//#define MODEL_UNIVERSE_COLLISIONHANDLER_HPP_

//# corresponding header
//# forward declarations
//# system headers
#include <stddef.h>

//## controller headers
//## model headers
#include <BulletCollision/CollisionDispatch/btCollisionObject.h>
#include <BulletCollision/NarrowPhaseCollision/btManifoldPoint.h>
//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
#include <model/universe/evolution/population/creature/phenome/morphology/limb/LimbModel.hpp>

//## view headers
//## utils headers

/**
 * @brief		The Collision handler processes collisions and distributes them to the relevant elements in the world.
 * @details		Details
 * @date		2015-08-14
 * @author		Benjamin Ellenberger
 */
bool processContactCallback(btManifoldPoint& cp, void* body0, void* body1) {
	LimbModel* limbModel1;
	LimbModel* limbModel2;
	btCollisionObject* o1 = static_cast<btCollisionObject*>(body0);
	btCollisionObject* o2 = static_cast<btCollisionObject*>(body1);
	int groundID = 9;
	if (o1->getUserPointer() != NULL) {
		limbModel1 = static_cast<LimbModel*>(o1->getUserPointer());
		limbModel1->activateTactioceptors();
	}

	if (o2->getUserPointer() != NULL) {
		limbModel2 = static_cast<LimbModel*>(o2->getUserPointer());
		limbModel2->activateTactioceptors();
	}

	double threshold = -1e7;
	if (limbModel1 != NULL && limbModel2 != NULL) {
		if (cp.getDistance() < threshold) {
			//TODO: Penetration testing
		}
	}

	//ignore according to the documentation.
	return false;
}

//#endif /* MODEL_UNIVERSE_COLLISIONHANDLER_HPP_ */
