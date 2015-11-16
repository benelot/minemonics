#ifndef CONTROLLER_RAGDOLL_RAGDOLL_HPP_
#define CONTROLLER_RAGDOLL_RAGDOLL_HPP_

//# corresponding header
#include <configuration/Definitions.hpp>

//# forward declarations
//# system headers
#include <vector>

//## controller headers
//## model headers
#include <btBulletDynamicsCommon.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
#include <controller/universe/evolution/population/creature/Creature.hpp>

//## model headers
//## view headers
//## utils headers

/**
 * @brief		A dummy creature to test things with a simple, well defined creature.
 * @details		Details
 * @date		2015-03-24
 * @author		Benjamin Ellenberger
 */
class RagDoll: public CreatureModel {
	enum {
		BODYPART_ABDOMENPELVIS = 0, BODYPART_THORAX, BODYPART_HEAD,

		BODYPART_LEFT_THIGH, BODYPART_LEFT_LEG,

		BODYPART_RIGHT_THIGH, BODYPART_RIGHT_LEG,

		BODYPART_LEFT_UPPER_ARM, BODYPART_LEFT_FOREARM,

		BODYPART_RIGHT_UPPER_ARM, BODYPART_RIGHT_FOREARM,

		BODYPART_COUNT
	};

	enum {
		JOINT_PELVIS_THORAX = 0, JOINT_THORAX_HEAD,

		JOINT_LEFT_HIP, JOINT_LEFT_KNEE,

		JOINT_RIGHT_HIP, JOINT_RIGHT_KNEE,

		JOINT_LEFT_SHOULDER, JOINT_LEFT_ELBOW,

		JOINT_RIGHT_SHOULDER, JOINT_RIGHT_ELBOW,

		JOINT_COUNT
	};

	//From: http://www.exrx.net/Kinesiology/Segments.html
	static const double RAGDOLL_HEAD = 8.26;
	static const double RAGDOLL_THORAX = 20.1;
	static const double RAGDOLL_ABDOMENPELVIS = 26.72;
	static const double RAGDOLL_THIGH = 10.5;
	static const double RAGDOLL_LEG = 6.18;
	static const double RAGDOLL_UPPER_ARM = 3.25;
	static const double RAGDOLL_FOREARM = 2.52;

public:
	RagDoll(PopulationModel* const population, double size,
		const btVector3& positionOffset);

	virtual ~RagDoll();

	virtual void update(double timeSinceLastTick);

	virtual int addToWorld();

	virtual int addToPhysicsWorld();

	virtual void removeFromWorld();
};

#endif /* CONTROLLER_RAGDOLL_RAGDOLL_HPP_ */
