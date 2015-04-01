/*
 * Phenome.cpp
 *
 *  Created on: Mar 9, 2015
 *      Author: leviathan
 */

//# corresponding header
#include "Phenome.h"

//# forward declarations
//# system headers
#include <vector>

//## controller headers
//## model headers
//## view headers
//# custom headers
//## base headers
#include "SimulationManager.h"

//## configuration headers
#include "configuration/MorphologyConfiguration.h"

//## controller headers
#include "controller/evolution/population/creature/phenome/PhenotypeGenerator.h"
#include "controller/evolution/population/creature/phenome/morphology/Limb.h"
#include "controller/evolution/population/creature/phenome/morphology/joint/Joint.h"

//## model headers
#include <model/evolution/population/creature/genome/morphology/Morphogene.h>
#include <model/evolution/population/creature/genome/morphology/MorphogeneBranch.h>
#include "model/evolution/population/creature/phenome/morphology/LimbBt.h"
#include "model/evolution/population/creature/phenome/morphology/joint/JointBt.h"
#include "model/evolution/population/creature/genome/Gene.h"

//## view headers
//## utils headers

Phenome::Phenome() :
		mSimulationManager(NULL), mWorld(NULL) {

}

Phenome::~Phenome() {
	// TODO Auto-generated destructor stub
}

void Phenome::initialize(SimulationManager* simulationManager) {
	mSimulationManager = simulationManager;
	mWorld = mSimulationManager->getPhysicsController().getDynamicsWorld();
}

/**
 * Performs the embryogenesis of a genome.
 * @param genome The genome we perform embryogenesis.
 */
void Phenome::performEmbryogenesis(Genome* genome) {
	std::list<PhenotypeGenerator*> generatorList;
	int totalSegmentCounter = 0;

	Gene* gene = genome->getGenes().front();
	PhenotypeGenerator* generator = new PhenotypeGenerator();
	std::vector<int> repList;
	generator->initialize(repList, Ogre::Vector3(0, 100, 0),
			Ogre::Quaternion().IDENTITY, NULL, NULL);
	generator->setGene(gene);
	generator->setTotalQty(totalSegmentCounter);
	generator->setRoot2LeafPath(0);

	generatorList.push_back(generator);
	// find correct root-to-leaf path length
	while (!generatorList.empty()
			&& totalSegmentCounter <= genome->getTotalSegmentQtyLimit()) {
		PhenotypeGenerator* generator = generatorList.front();
		generatorList.pop_front();

		//if the current root to leaf path is shorter or equal to the maximal segments depth
		if (generator->getRoot2LeafPath() <= genome->getSegmentsDepthLimit()) {
			switch (generator->getGene()->getGeneType()) {
			case Gene::MorphoGene: {
				Morphogene* morphoParent = ((Morphogene*) generator->getGene());

				//build the limb out of the morphogene
				Limb* limb = new Limb();
				limb->initialize(mSimulationManager,
						morphoParent->getPrimitiveType(),
						generator->getPosition(), generator->getOrientation(),
						Ogre::Vector3(morphoParent->getX(),
								morphoParent->getY(), morphoParent->getZ()),
						morphoParent->getX() * morphoParent->getY()
								* morphoParent->getZ());
				limb->addToWorld();
				mLimbs.push_back(limb);

				//define joint
				//TODO: Remove this again
				double size = 1;

				btTransform transform;
				btTransform localA, localB;
				localA.setIdentity();
				localB.setIdentity();
				localA.getBasis().setEulerZYX(0, M_PI_2, 0);
				localA.setOrigin(
						btVector3(btScalar(size * 0.), btScalar(size * -0.225),
								btScalar(size * 0.)));
				localB.getBasis().setEulerZYX(0, M_PI_2, 0);
				localB.setOrigin(
						btVector3(btScalar(size * 0.), btScalar(size * 0.185),
								btScalar(size * 0.)));

				JointBt* joint = new JointBt();
				joint->initialize(
						((Limb*)generator->getParentComponent())->getLimbPhysics()->getRigidBody(),
						limb->getLimbPhysics()->getRigidBody(),
						localA, localB);
				joint->setAngularLimits(btVector3(0, 0, 0),
						btVector3(0, M_PI_2, 0));
				mJoints.push_back(joint);

				//iterate over all morphogene branches
				std::vector<MorphogeneBranch*>::iterator branchIt =
						morphoParent->getGeneBranches().begin();
				for (; branchIt != morphoParent->getGeneBranches().end();
						branchIt++) {
					totalSegmentCounter++;
					Morphogene* offspring =
							genome->getGenes()[(*branchIt)->getBranchGeneType()];

					PhenotypeGenerator* generatorFromBranch =
							new PhenotypeGenerator();

					//TODO move generator
					generatorFromBranch->initialize(
							generator->getRepetitionList(),
							generator->getPosition(),
							generator->getOrientation(), limb,
							(*branchIt.base()));

					//If repetition limit not exceeded
					if (generatorFromBranch->getRepetitionList()[(*branchIt)->getBranchGeneType()]
							<= offspring->getRepetitionLimit()) {

						//add another of this offspring type
						generatorFromBranch->getRepetitionList()[(*branchIt)->getBranchGeneType()]++;
						generatorFromBranch->setGene(offspring);
					} else {

						//add the offspring follower
						generatorFromBranch->setGene(
								genome->getGenes()[offspring->getFollowUpGene()]);
					}

					//set new total quantity and root to leaf path
					generatorFromBranch->setTotalQty(totalSegmentCounter);
					generatorFromBranch->setRoot2LeafPath(
							generator->getRoot2LeafPath() + 1);
					generatorList.push_back(generatorFromBranch);
					delete generator;
				}
				break;
			}
			default:
				break;
			}
		}
	}
}

//void Phenome::transcribeGene(Gene* gene) {
//
//}

//void Phenotype::createBox(int index, double x, double y, double z,
//		double length, double width, double height) {
////...
////body[index] = ...
////...
////geom[index] = ...
////...
////m_dynamicsWorld->addRigidBody(body[index]);
//}
//
//void Phenotype::createCylinder(int index, double x, double y, double z,
//	double length, double width, double height) {
//
////...
////body[index] = ...
////...
////geom[index] = ...
////...
////m_dynamicsWorld->addRigidBody(body[index]);
//}
//
//void Phenotype::addToWorld() {
//
//}
//
//void Phenotype::removeFromWorld() {
//m_dynamicsWorld->removeRigidBody(body[index]);
//}
//
//
//void Phenotype::addConstraint()
//{
//	// Add to simulation
//	m_dynamicsWorld->addConstraint( joints[index] , true );
//}
//
//void Phenotype::removeConstraint()
//{
//	// Remove from simulation
//	m_dynamicsWorld->removeConstraint( joints[index] );
//}
//
//void Phenotype::createHinge(int index, int body1, int body2, double x, double y,
//double z, double ax, double ay, double az) {
//	 btVector3 p(x, y, z);
//	  btVector3 a(ax, ay, az);
////	  btVector3 p1 = PointWorldToLocal(body1, p);
////	  btVector3 p2 = PointWorldToLocal(body2, p);
////	  btVector3 a1 = AxisWorldToLocal(body1, a);
////	  btVector3 a2 = AxisWorldToLocal(body2, a);
//
//	  btVector3 p1 = PointWorldToLocal(body1, flipZY(p));
//	  btVector3 p2 = PointWorldToLocal(body2, flipZY(p));
//	  btVector3 a1 = AxisWorldToLocal(body1, flipZY(a));
//	  btVector3 a2 = AxisWorldToLocal(body2, flipZY(a));
//	  // create
//	    joints[index] = new btHingeConstraint(*body[body1], *body[body2],
//	                                                     p1, p2,
//	                                                     a1, a2, false);
//}
//
//void Phenotype::destroyHinge(int index)
//{
//
//}
//
//btVector3 Phenotype::flipZY(btVector3 input) {
//  btScalar temp;
//  temp = input[1];
//  input[1] = input[2];
//  input[2] = temp;
//  return input;
//}
//
//btVector3 Phenotype::PointWorldToLocal(int index, btVector3 &p) {
//	  btTransform local1 = body[index]->getCenterOfMassTransform().inverse();
//	  return local1 * p;
//	}
//
//btVector3 Phenotype::AxisWorldToLocal(int index, btVector3 &a) {
//	  btTransform local1 = body[index]->getCenterOfMassTransform().inverse();
//	  btVector3 zero(0,0,0);
//	  local1.setOrigin(zero);
//	  return local1 * a;
//	}
//
//
//addJointLimit(){
//	joints[index]->setLimit(-45.*3.14159/180., 45.*3.14159/180.);
////
////	  if ( index==0 ):
////	      joints[index]->setLimit( (-45. + 90.)*3.14159/180., (45. + 90.)*3.14159/180.);
////	  else if ( index==1 ):
////	      joints[index]->setLimit( (-45. - 90.)*3.14159/180., (45. - 90.)*3.14159/180.);
////	  else:
////	      joints[index]->setLimit( (-45. + 0.)*3.14159/180., (45. + 0.)*3.14159/180.);
//}
//
//void actuateJoint(int jointIndex, double desiredAngle,
//                  double jointOffset, double timeStep) {
//    ...
//}
