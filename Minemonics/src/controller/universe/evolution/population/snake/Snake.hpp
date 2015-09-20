#ifndef CONTROLLER_SNAKE_SNAKE_HPP_
#define CONTROLLER_SNAKE_SNAKE_HPP_

//# corresponding header
#include <configuration/Definitions.hpp>

//# forward declarations
class Limb;
class Joint;

//# system headers
#include <vector>

//## controller headers
#include <controller/universe/evolution/population/creature/Creature.hpp>

//## model headers
#include <btBulletDynamicsCommon.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers

/**
 * @brief		A dummy creature to test things with a simple, well defined creature.
 * @details		Details
 * @date		2015-03-24
 * @author		Benjamin Ellenberger
 */
class Snake: public Creature {

public:
	Snake(Population* const population, double size,
		const btVector3& positionOffset);

	virtual ~Snake();

	virtual void update(double timeSinceLastTick);

	virtual int addToWorld();

	virtual int addToPhysicsWorld();

	virtual void removeFromWorld();

	btMultiBody* createFeatherstoneMultiBody(int numLinks,
		const btVector3 &basePosition, const btVector3 &baseHalfExtents,
		const btVector3 &linkHalfExtents, bool spherical, bool floating);

	void addColliders(btMultiBody *pMultiBody, const btVector3 &baseHalfExtents,
		const btVector3 &linkHalfExtents);

private:
	double rotate;
	double sign;
	btVector3 integrativeError;
};

#endif /* CONTROLLER_SNAKE_SNAKE_HPP_ */
