/*
 Bullet Continuous Collision Detection and Physics Library
 Copyright (c) 2003-2007 Erwin Coumans  http://continuousphysics.com/Bullet/

 This software is provided 'as-is', without any express or implied warranty.
 In no event will the authors be held liable for any damages arising from the use of this software.
 Permission is granted to anyone to use this software for any purpose,
 including commercial applications, and to alter it and redistribute it freely,
 subject to the following restrictions:

 1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
 3. This notice may not be removed or altered from any source distribution.
 */

#include "btBulletDynamicsCommon.h"
#include "BulletSoftBody/btSoftRigidDynamicsWorld.h"
#include "BulletSoftBody/btSoftBodyRigidBodyCollisionConfiguration.h"
#include "BulletSoftBody/btSoftBodyHelpers.h"
#include <stdio.h>

class TetraSleeve {
public:
	TetraSleeve() :
			nodesBuf(NULL), elemBuf(NULL) {
	}

	const char* getNodes() {
		if (nodesBuf != NULL)
			return nodesBuf;
		FILE * f = fopen(
				"C:\\txtsense-2012\\SleeveDelaunay\\Mesh_1_high_res.1.node",
				"r");
		fseek(f, 0, SEEK_END); // seek to end of file
		long size = ftell(f); // get current file pointer
		fseek(f, 0, SEEK_SET); // seek back to beginning of file
// proceed with allocating memory and reading the file
		nodesBuf = new char[size + 2];
//		assert(nodesBuf != NULL);
		fread(nodesBuf, sizeof(char), size, f);
		fclose(f);
		printf("Read %ld bytes of node data\n", size);
		nodesBuf[size + 1] = 0;
		return nodesBuf;
	}

	const char* getElements() {
		if (elemBuf != NULL)
			return elemBuf;
		FILE * f = fopen(
				"C:\\txtsense-2012\\SleeveDelaunay\\Mesh_1_high_res.1.ele",
				"r");
		fseek(f, 0, SEEK_END); // seek to end of file
		long size = ftell(f); // get current file pointer
		fseek(f, 0, SEEK_SET); // seek back to beginning of file
// proceed with allocating memory and reading the file
		elemBuf = new char[size + 2];
		fread(elemBuf, sizeof(char), size, f);
		fclose(f);
		elemBuf[size + 1] = 0;
		printf("Read %ld bytes of element data\n", size);
		return elemBuf;
	}

	~TetraSleeve() {
		if (nodesBuf != NULL)
			delete[] nodesBuf;
		if (elemBuf != NULL)
			delete[] elemBuf;
	}

private:
	char * nodesBuf;
	char * elemBuf;
};

/// This is a Hello World program for running a basic Bullet physics simulation

int main(int argc, char** argv) {
	TetraSleeve tetraSleeve;

///collision configuration contains default setup for memory, collision setup. Advanced users can create their own configuration.
	btSoftBodyRigidBodyCollisionConfiguration* collisionConfiguration =
			new btSoftBodyRigidBodyCollisionConfiguration();

///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
	btCollisionDispatcher* dispatcher = new btCollisionDispatcher(
			collisionConfiguration);

///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
//btBroadphaseInterface* overlappingPairCache = new btDbvtBroadphase();
	btVector3 worldAabbMin(-1000, -1000, -1000);
	btVector3 worldAabbMax(1000, 1000, 1000);
	const int maxProxies = 32766;
	btBroadphaseInterface* overlappingPairCache = new btAxisSweep3(worldAabbMin,
			worldAabbMax, maxProxies);

///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
	btSequentialImpulseConstraintSolver* solver =
			new btSequentialImpulseConstraintSolver;
	btSoftBodySolver* softBodySolver = 0;

	btSoftRigidDynamicsWorld* dynamicsWorld = new btSoftRigidDynamicsWorld(
			dispatcher, overlappingPairCache, solver, collisionConfiguration,
			softBodySolver);

	dynamicsWorld->setGravity(btVector3(0, -10, 0));
	dynamicsWorld->getDispatchInfo().m_enableSPU = true;

	btSoftBodyWorldInfo m_softBodyWorldInfo;
	m_softBodyWorldInfo.air_density = (btScalar) 1.2;
	m_softBodyWorldInfo.water_density = 0;
	m_softBodyWorldInfo.water_offset = 0;
	m_softBodyWorldInfo.water_normal = btVector3(0, 0, 0);
	m_softBodyWorldInfo.m_gravity.setValue(0, 0, -30);
	m_softBodyWorldInfo.m_sparsesdf.Initialize();
	m_softBodyWorldInfo.m_broadphase = overlappingPairCache;
	m_softBodyWorldInfo.m_dispatcher = dispatcher;

///create a few basic rigid bodies
	btCollisionShape* groundShape = new btBoxShape(
			btVector3(btScalar(500.), btScalar(500.), btScalar(0.01)));

//keep track of the shapes, we release memory at exit.
//make sure to re-use collision shapes among rigid bodies whenever possible!
	btAlignedObjectArray<btCollisionShape*> collisionShapes;
	btAlignedObjectArray<btSoftBody*> softBodies;

	collisionShapes.push_back(groundShape);

	btTransform groundTransform;
	groundTransform.setIdentity();
	groundTransform.setOrigin(btVector3(0, 0, 0));

	{
		btScalar mass(0.);

//rigidbody is dynamic if and only if mass is non zero, otherwise static
		bool isDynamic = (mass != 0.f);

		btVector3 localInertia(0, 0, 0);
		if (isDynamic)
			groundShape->calculateLocalInertia(mass, localInertia);

//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
		btDefaultMotionState* myMotionState = new btDefaultMotionState(
				groundTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState,
				groundShape, localInertia);
		btRigidBody* body = new btRigidBody(rbInfo);

		body->setCollisionFlags(btCollisionObject::CF_STATIC_OBJECT);

//add the body to the dynamics world
		dynamicsWorld->addRigidBody(body);
	}

	/*{
	 //create a dynamic softbody

	 //btCollisionShape* colShape = new btBoxShape(btVector3(1,1,1));
	 //btCollisionShape* colShape = new btSphereShape(btScalar(1.0));
	 btSoftBody* psb = btSoftBodyHelpers::CreateEllipsoid(m_softBodyWorldInfo, btVector3(0., 20., 0.), btVector3(3.,3.,3.), 50);
	 btTransform tr;
	 tr.setIdentity();
	 tr.setOrigin(btVector3(0, 150, 0));

	 softBodies.push_back(psb);

	 btSoftBody::Material*	pm=psb->appendMaterial();
	 pm->m_kLST	=	0.9;
	 pm->m_kAST	=	0.1;
	 pm->m_kVST	=	0.1;
	 psb->scale(btVector3(1,1,1));
	 psb->setCollisionFlags(0);

	 ///pass zero in generateClusters to create  cluster for each tetrahedron or triangle
	 psb->m_cfg.kDF    =   0.1f;
	 psb->m_cfg.kMT   =   0.25f;
	 psb->m_cfg.kVC                =   0.5f;
	 psb->m_cfg.piterations   =   5;
	 psb->m_cfg.collisions      = btSoftBody::fCollision::CL_RS;
	 psb->randomizeConstraints();
	 psb->generateClusters(5);

	 psb->m_cfg.kSRHR_CL = 0.1;
	 psb->m_cfg.kSR_SPLT_CL = 0.1;


	 psb->setTotalMass(10,true);
	 psb->setPose(false,true);

	 dynamicsWorld->addSoftBody(psb);
	 }*/
	{
		printf("Attemping Creation of SleeveTetra.\n");
		const char * telems = tetraSleeve.getElements();
		for (int ic = 0; ic < 50; ic++)
			printf("%c", telems[ic]);
		printf("\n");
		btSoftBody* psb = btSoftBodyHelpers::CreateFromTetGenData(
				m_softBodyWorldInfo, telems, 0, tetraSleeve.getNodes(), false,
				true, true);

		printf("Created SleeveTetra.\n");

		psb->scale(btVector3(4, 4, 4));
		psb->translate(btVector3(0, 0, 20));
		psb->setVolumeMass(300);

///fix one vertex
//psb->setMass(0,0);
//psb->setMass(10,0);
//psb->setMass(20,0);
		psb->m_cfg.piterations = 1;
//psb->generateClusters(128);
		psb->generateClusters(128);
//psb->getCollisionShape()->setMargin(0.5);

		psb->getCollisionShape()->setMargin(0.01);
		psb->m_cfg.collisions = btSoftBody::fCollision::CL_SS
				+ btSoftBody::fCollision::CL_RS
//+ btSoftBody::fCollision::CL_SELF
				;
		psb->m_materials[0]->m_kLST = 0.1;
		psb->setCollisionFlags(0);
		dynamicsWorld->addSoftBody(psb);
	}

/// Do some simulation
	const int N_TIMESTEPS = 300;

	printf("Starting simulation\n");

// output tetrahedral and initial position data
	{
		FILE * fpTetra = fopen("Tetra.txt", "w");

		fprintf(fpTetra, "%s", tetraSleeve.getElements());

		fclose(fpTetra);

		FILE * fpNodes = fopen("NodesIntial.txt", "w");

		fprintf(fpNodes, "%s", tetraSleeve.getNodes());

		fclose(fpNodes);

	}

	for (int i = 0; i < N_TIMESTEPS; i++) {
//printf("Simulation step %d\n", i);
		dynamicsWorld->stepSimulation(1.f / 60.f, 100);

		char fname[1000];
		sprintf(fname, "TimeStep%05d.txt", i);
		FILE * fpPos = fopen(fname, "w");

// print positions of all objects
		for (int j = dynamicsWorld->getNumCollisionObjects(); j >= 0; j--) {
			btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[j];
			btRigidBody* body = btRigidBody::upcast(obj);
			if (body && body->getMotionState()) {
				btTransform trans;
				body->getMotionState()->getWorldTransform(trans);
//printf("Rigid, %d,: world pos =, %f,%f,%f\n", j, float(trans.getOrigin().getX()),float(trans.getOrigin().getY()),float(trans.getOrigin().getZ()));
			}
			btSoftBody* softbody = btSoftBody::upcast(obj);
			if (softbody) {
				btVector3 meanNodePos(0., 0., 0.);
				for (int ns = 0; ns < softbody->m_nodes.size(); ns++) {
					btVector3 npos = softbody->m_nodes[ns].m_x;
					meanNodePos += npos;
//printf("Soft, %d, %d: world pos =, %f,%f,%f\n", j, ns, float(npos.getX()),float(npos.getY()),float(npos.getZ()));
					fprintf(fpPos, "%d %d %f %f %f\n", j, ns,
							float(npos.getX()), float(npos.getY()),
							float(npos.getZ()));
				}
				meanNodePos /= btScalar(softbody->m_nodes.size());
//printf("Soft, %d: world pos =, %f,%f,%f\n", j, float(meanNodePos.getX()),float(meanNodePos.getY()),float(meanNodePos.getZ()));
			}
		}
		fclose(fpPos);
	}

//cleanup in the reverse order of creation/initialization

	for (int i = dynamicsWorld->getNumCollisionObjects(); i >= 0; i--) {
		btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[i];
		btRigidBody* body = btRigidBody::upcast(obj);
		if (body && body->getMotionState()) {
			delete body->getMotionState();
		}
		while (dynamicsWorld->getNumConstraints()) {
			btTypedConstraint* pc = dynamicsWorld->getConstraint(0);
			dynamicsWorld->removeConstraint(pc);
			delete pc;
		}
		btSoftBody* softBody = btSoftBody::upcast(obj);
		if (softBody) {
			dynamicsWorld->removeSoftBody(softBody);
		} else {
			btRigidBody* body = btRigidBody::upcast(obj);
			if (body)
				dynamicsWorld->removeRigidBody(body);
			else
				dynamicsWorld->removeCollisionObject(obj);
		}
		delete obj;
	}

//delete dynamics world
	delete dynamicsWorld;

//delete solver
	delete solver;

//delete broadphase
	delete overlappingPairCache;

//delete dispatcher
	delete dispatcher;

	delete collisionConfiguration;

//next line is optional: it will be cleared by the destructor when the array goes out of scope
	collisionShapes.clear();

}
