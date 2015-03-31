/*
 * Ragdoll.h
 *
 *  Created on: Mar 24, 2015
 *      Author: leviathan
 */

#ifndef CONTROLLER_PHYSICS_RAGDOLL_H_
#define CONTROLLER_PHYSICS_RAGDOLL_H_

//# corresponding header
//# forward declarations
class SimulationManager;
class Limb;
class Joint;

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
//## model headers
#include "model/evolution/population/creature/phenome/morphology/joint/JointBt.h"

//## view headers
//## utils headers

class RagDoll {
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
	std::vector<JointBt*> mJoints;

	btDynamicsWorld* mWorld;

public:
	RagDoll(SimulationManager* simulationManager,double size, const btVector3& positionOffset);

	virtual ~RagDoll();

	void update();

	btRigidBody* localCreateRigidBody (btScalar mass, const btTransform& startTransform, btCollisionShape* shape)
	{
		bool isDynamic = (mass != 0.f);

		btVector3 localInertia(0,0,0);
		if (isDynamic)
			shape->calculateLocalInertia(mass,localInertia);

		btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);

		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,myMotionState,shape,localInertia);
		btRigidBody* body = new btRigidBody(rbInfo);

		mWorld->addRigidBody(body);

		return body;
	}
};

#endif /* CONTROLLER_PHYSICS_RAGDOLL_H_ */
