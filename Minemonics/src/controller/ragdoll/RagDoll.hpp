#ifndef CONTROLLER_RAGDOLL_RAGDOLL_HPP_
#define CONTROLLER_RAGDOLL_RAGDOLL_HPP_

//# corresponding header
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
class RagDoll: public Creature {
	enum {
		BODYPART_PELVIS = 0, BODYPART_SPINE, BODYPART_HEAD,

		BODYPART_LEFT_UPPER_LEG, BODYPART_LEFT_LOWER_LEG,

		BODYPART_RIGHT_UPPER_LEG, BODYPART_RIGHT_LOWER_LEG,

		BODYPART_LEFT_UPPER_ARM, BODYPART_LEFT_LOWER_ARM,

		BODYPART_RIGHT_UPPER_ARM, BODYPART_RIGHT_LOWER_ARM,

		BODYPART_COUNT
	};

	enum {
		JOINT_PELVIS_SPINE = 0, JOINT_SPINE_HEAD,

		JOINT_LEFT_HIP, JOINT_LEFT_KNEE,

		JOINT_RIGHT_HIP, JOINT_RIGHT_KNEE,

		JOINT_LEFT_SHOULDER, JOINT_LEFT_ELBOW,

		JOINT_RIGHT_SHOULDER, JOINT_RIGHT_ELBOW,

		JOINT_COUNT
	};

	std::vector<Limb*> mLimbs;
	std::vector<Joint*> mJoints;

	btDynamicsWorld* mWorld;

public:
	RagDoll(double size,
			const btVector3& positionOffset);

	virtual ~RagDoll();

	void update();

	void addToWorld();

	void removeFromWorld();
};

#endif /* CONTROLLER_RAGDOLL_RAGDOLL_HPP_ */
