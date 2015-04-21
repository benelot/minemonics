/*
 * Phenome.cpp
 *
 *  Created on: Mar 9, 2015
 *      Author: leviathan
 */
//TODO: Separate Phenome into model and controller classes
//# corresponding header
#include <controller/evolution/genetics/PhenotypeGenerator.h>
#include "Phenome.h"

//# forward declarations
//# system headers
#include <vector>
#include <map>

//## controller headers
//## model headers
//## view headers
//# custom headers
//## base headers
#include "SimulationManager.h"

//## configuration headers
#include "configuration/MorphologyConfiguration.h"
#include "configuration/PhysicsConfiguration.h"

//## controller headers
#include "controller/evolution/population/creature/phenome/morphology/Limb.h"
#include "controller/evolution/population/creature/phenome/morphology/Joint.h"

//## model headers
#include "model/evolution/population/creature/genome/morphology/Morphogene.h"
#include "model/evolution/population/creature/genome/morphology/MorphogeneBranch.h"
#include "model/evolution/population/creature/phenome/morphology/LimbBt.h"
#include "model/evolution/population/creature/phenome/morphology/JointBt.h"
#include "model/evolution/population/creature/genome/Gene.h"

//## view headers
#include "view/ogre3D/evolution/population/creature/phenome/morphology/LimbO3D.h"
#include "view/ogre3D/picking/OgreMeshRay.h"
#include "view/ogre3D/bullet/OgreBulletUtils.h"

//## utils headers
#include "utils/ogre3D/Euler.h"

Phenome::Phenome() :
		mSimulationManager(NULL), mWorld(NULL) {

}

Phenome::~Phenome() {
}

void Phenome::initialize(SimulationManager* simulationManager) {
	mSimulationManager = simulationManager;
	mWorld = mSimulationManager->getPhysicsController().getDynamicsWorld();
}

/**
 * Performs the embryogenesis of a genome. We follow each part of the tree with the phenotype generators.
 * @param genome The genome we perform embryogenesis with.
 */
void Phenome::performEmbryogenesis(Genome* genome, Ogre::Vector3 rootPosition) {
	std::list<PhenotypeGenerator*> generatorList;
	int totalSegmentCounter = 0;

	// get the first gene from the genome
	Gene* gene = genome->getGenes().front();

	//create a phenotype generator and initialize it with the starting point of the creation of the creature
	PhenotypeGenerator* rootGenerator = new PhenotypeGenerator();
	std::map<int, int> repList;
	rootGenerator->initialize(repList, rootPosition,
			Ogre::Quaternion().IDENTITY, NULL, NULL, 1);
	rootGenerator->setGene(gene);
	rootGenerator->setRoot2LeafPath(0);
	generatorList.push_back(rootGenerator);

	// this loop creates the creature up to the point at which we reach the correct root-to-leaf path length
	while (!generatorList.empty()) {

//		std::cout << "Phenome generator qty:" << generatorList.size()
//				<< std::endl;

		PhenotypeGenerator* generator = generatorList.front();
		generatorList.pop_front();

//		Embryogenesis::transcribeGene(generator);

// what is the next gene type
		switch (generator->getGene()->getGeneType()) {
		case Gene::MorphoGene: {
			// if the current root to leaf path is equal to the maximal segments depth, break
			if (generator->getRoot2LeafPath()
					== genome->getSegmentsDepthLimit()) {
				break;
			}
			//if the total segment counter reached the total segment quantity, break
			if (totalSegmentCounter == genome->getTotalSegmentQtyLimit()) {
				break;
			}

			totalSegmentCounter++;

			// get the morphogene and start creating the limb and its joint to its parent
			Morphogene* morphogene = ((Morphogene*) generator->getGene());

			// joint position in reference frame A
			Ogre::Vector3 localJointOA;

			// joint position in reference frame B
			Ogre::Vector3 localJointOB;

			// if there exists a parent component, then we connect the new limb to it
			if (generator->getParentComponent() != NULL) {

				// get parent limb A
				LimbPhysics* limbA =
						((Limb*) generator->getParentComponent())->getLimbPhysics();

				//get the limb A COM
				Ogre::Vector3 limbACOM =
						((Limb*) generator->getParentComponent())->getPosition();

				//get anchor direction of limb A in reference frame of A
				Ogre::Vector3 localAnchorDirOA(
						((MorphogeneBranch*) generator->getGeneBranch())->getJointAnchorX(),
						((MorphogeneBranch*) generator->getGeneBranch())->getJointAnchorY(),
						((MorphogeneBranch*) generator->getGeneBranch())->getJointAnchorZ());

				//get surface point of limb A in reference frame of A
				Ogre::Vector3 localAnchorOA(limbA->getLocalIntersection(
				/*origin of limb A*/
				OgreBulletUtils::convert(limbACOM),
				/*direction of anchor of limb A*/
				OgreBulletUtils::convert(localAnchorDirOA)));

				// draw line from limbA along ray test
				//TODO: Debug lines
				mSimulationManager->getDebugDrawer()->drawLine(limbACOM,
						limbACOM + 1000.0f * localAnchorDirOA,
						Ogre::ColourValue(1, 0, 0));

				// draw line from limbA to anchor point of A
				//TODO: Debug lines
				mSimulationManager->getDebugDrawer()->drawLine(limbACOM,
						limbACOM + localAnchorOA, Ogre::ColourValue(0, 1, 0));

				// joint direction of joint part of A
				Ogre::Euler eulerA(
						((MorphogeneBranch*) generator->getGeneBranch())->getJointYaw(),
						((MorphogeneBranch*) generator->getGeneBranch())->getJointPitch(),
						((MorphogeneBranch*) generator->getGeneBranch())->getJointRoll());

				//get local joint rotation point in reference frame A
				localJointOA = localAnchorOA
						+ eulerA * localAnchorDirOA.normalisedCopy()
								* MorphologyConfiguration::JOINT_LENGTH;


				// draw line from anchor point of A to joint rotation point
				//TODO: Debug lines
				mSimulationManager->getDebugDrawer()->drawLine(limbACOM + localAnchorOA,
						limbACOM + localJointOA, Ogre::ColourValue(0, 0, 1));

				//get anchor direction of limb B
				Ogre::Vector3 localAnchorDirOB(morphogene->getJointAnchorX(),
						morphogene->getJointAnchorY(),
						morphogene->getJointAnchorZ());

				// joint direction of joint part of B
				Ogre::Euler eulerB(morphogene->getJointYaw(),
						morphogene->getJointPitch(),
						morphogene->getJointRoll());

				//get local surface anchor point of B in reference frame A
				Ogre::Vector3 localAnchorOBinA(
						localJointOA
								- eulerB * localAnchorDirOB.normalisedCopy()
										* MorphologyConfiguration::JOINT_LENGTH);

				// draw line from anchor point of A to joint rotation point
				//TODO: Debug lines
				mSimulationManager->getDebugDrawer()->drawLine(limbACOM + localJointOA,
							limbACOM + localAnchorOBinA, Ogre::ColourValue(0, 0, 1));

				// find the joint anchor position of the limb by positioning the limb at an arbitrary position to cast a ray
				LimbBt* limbBBt = new LimbBt();
				limbBBt->initialize(
						mSimulationManager->getPhysicsController().getDynamicsWorld(),
						morphogene->getPrimitiveType(),
						OgreBulletUtils::convert(generator->getPosition()),
						btQuaternion(morphogene->getOrientationX(),
								morphogene->getOrientationY(),
								morphogene->getOrientationZ(),
								morphogene->getOrientationW()),
						/*size*/
						btVector3(
								generator->getCurrentShrinkageFactor()
										* morphogene->getX(),
								generator->getCurrentShrinkageFactor()
										* morphogene->getY(),
								generator->getCurrentShrinkageFactor()
										* morphogene->getZ()),/*mass*/
						btScalar(
								generator->getCurrentShrinkageFactor()
										* morphogene->getX()
										* generator->getCurrentShrinkageFactor()
										* morphogene->getY()
										* generator->getCurrentShrinkageFactor()
										* morphogene->getZ()));
				limbBBt->addToWorld();

				//get the surface point of limb B in the local reference frame of B
				Ogre::Vector3 localAnchorOB(
						OgreBulletUtils::convert(limbBBt->getLocalIntersection(
						/*origin of limb B*/
						OgreBulletUtils::convert(generator->getPosition()),
						/*direction of anchor of limb B*/
						OgreBulletUtils::convert(localAnchorDirOB))));


				// draw line from anchor point of B to joint rotation point
				//TODO: Debug lines
				mSimulationManager->getDebugDrawer()->drawLine(generator->getPosition(),
						generator->getPosition() + localAnchorOB, Ogre::ColourValue(0, 0, 1));

				limbBBt->removeFromWorld();
				delete limbBBt;
				limbBBt = 0;

				// draw line from anchor point of A to joint rotation point
				//TODO: Debug lines
				mSimulationManager->getDebugDrawer()->drawLine(localAnchorOA,
						localJointOA, Ogre::ColourValue(0, 0, 1));

				// global center of mass of limb B
				Ogre::Vector3 limbBCOM(
						limbACOM + localAnchorOBinA - localAnchorOB);
				// set global center of mass of limb B as the new generation point
				generator->setPosition(limbBCOM);
				generator->setOrientation(
						Ogre::Quaternion(morphogene->getOrientationW(),
								morphogene->getOrientationX(),
								morphogene->getOrientationY(),
								morphogene->getOrientationZ()));

				// get local joint rotation point in the local reference frame of B
				Ogre::Euler euler3(morphogene->getJointYaw(),
						morphogene->getJointPitch(),
						morphogene->getJointRoll());

				localJointOB = localAnchorOB
						+ euler3 * localAnchorDirOB.normalisedCopy()
								* MorphologyConfiguration::JOINT_LENGTH;

				// draw line from limbA along ray test
				//TODO: Debug lines
				mSimulationManager->getDebugDrawer()->drawLine(limbBCOM,
						limbBCOM + 1000.0f * localAnchorDirOB,
						Ogre::ColourValue(1, 0, 0));

				// draw line from limbA to limbB
				mSimulationManager->getDebugDrawer()->drawLine(limbBCOM,
							limbACOM,
							Ogre::ColourValue(1, 0.5, 0.5));
			}

			//build the limb out of the morphogene
			Limb* limb = new Limb();
			limb->initialize(mSimulationManager, morphogene->getPrimitiveType(),
					generator->getPosition(), generator->getOrientation(),
					/*size*/
					Ogre::Vector3(
							generator->getCurrentShrinkageFactor()
									* morphogene->getX(),
							generator->getCurrentShrinkageFactor()
									* morphogene->getY(),
							generator->getCurrentShrinkageFactor()
									* morphogene->getZ()),
					/*mass*/
					generator->getCurrentShrinkageFactor() * morphogene->getX()
							* generator->getCurrentShrinkageFactor()
							* morphogene->getY()
							* generator->getCurrentShrinkageFactor()
							* morphogene->getZ(),
					Ogre::ColourValue(morphogene->getColorR(),
							morphogene->getColorB(), morphogene->getColorB()));
			mLimbs.push_back(limb);

			if (generator->getParentComponent() != NULL) {

				//define joint
				btTransform transform;
				btTransform localA, localB;
				localA.setIdentity();
				localB.setIdentity();

				localA.setOrigin(OgreBulletUtils::convert(localJointOA));
				localA.getBasis().setEulerZYX(
						((MorphogeneBranch*) generator->getGeneBranch())->getJointRoll(),
						((MorphogeneBranch*) generator->getGeneBranch())->getJointYaw(),
						((MorphogeneBranch*) generator->getGeneBranch())->getJointPitch());

				localB.setOrigin(OgreBulletUtils::convert(localJointOB));
				localB.getBasis().setEulerZYX(morphogene->getJointRoll(),
						morphogene->getJointYaw(), morphogene->getJointPitch());

				//create the joint
				Joint* joint = new Joint();
				joint->initialize(mSimulationManager,
						((Limb*) generator->getParentComponent()), limb, localA,
						localB);

				//set the angular limits
				joint->setAngularLimits(
						Ogre::Vector3(
								((MorphogeneBranch*) generator->getGeneBranch())->getJointPitchMinAngle(),
								((MorphogeneBranch*) generator->getGeneBranch())->getJointYawMinAngle(),
								((MorphogeneBranch*) generator->getGeneBranch())->getJointRollMinAngle()),
						Ogre::Vector3(
								((MorphogeneBranch*) generator->getGeneBranch())->getJointPitchMaxAngle(),
								((MorphogeneBranch*) generator->getGeneBranch())->getJointYawMaxAngle(),
								((MorphogeneBranch*) generator->getGeneBranch())->getJointRollMaxAngle()));

				// add to phenotype joints
				mJoints.push_back(joint);
			}

			//iterate over all morphogene branches
			std::vector<MorphogeneBranch*>::iterator branchIt =
					morphogene->getGeneBranches().begin();
			for (; branchIt != morphogene->getGeneBranches().end();
					branchIt++) {

				// get the branch gene type defined by the branch
				Morphogene* offspring =
						genome->getGenes()[(*branchIt)->getBranchGeneType()];

				// create the new generator
				PhenotypeGenerator* generatorFromBranch =
						new PhenotypeGenerator();
				generatorFromBranch->initialize(generator->getRepetitionList(),
						generator->getPosition(), generator->getOrientation(),
						limb, (*branchIt.base()),
						morphogene->getSegmentShrinkFactor()
								* generator->getCurrentShrinkageFactor());

				//If repetition limit not exceeded (if it does not find the key OR if the repetition limit of the key is not exceeded)
				if (generatorFromBranch->getRepetitionList().find(
						(*branchIt)->getBranchGeneType())
						== generatorFromBranch->getRepetitionList().end()
						|| generatorFromBranch->getRepetitionList()[(*branchIt)->getBranchGeneType()]
								<= offspring->getRepetitionLimit()) {

					//add another of this offspring type
					generatorFromBranch->getRepetitionList()[(*branchIt)->getBranchGeneType()]++;
					generatorFromBranch->setGene(offspring);
				} else {

					//add the offspring's follower because the repetition limit of the offspring is exceeded
					generatorFromBranch->setGene(
							genome->getGenes()[offspring->getFollowUpGene()]);
				}

				//set new root to leaf path length
				generatorFromBranch->setRoot2LeafPath(
						generator->getRoot2LeafPath() + 1);

				//add generator to the list
				generatorList.push_back(generatorFromBranch);
			}
			break;
		}
		default:
			break;
		}
		// delete the generator of this gene
		delete generator;
	}
}

void Phenome::update() {
	// Add all limbs
	std::vector<Limb*>::iterator lit = mLimbs.begin();
	for (; lit != mLimbs.end(); lit++) {
		(*lit)->update();
	}

	// Add all constraints
	std::vector<Joint*>::iterator jit = mJoints.begin();
	for (; jit != mJoints.end(); jit++) {
		(*jit)->update();
	}
}

void Phenome::addToWorld() {
	// Add all limbs
	std::vector<Limb*>::iterator lit = mLimbs.begin();
	for (; lit != mLimbs.end(); lit++) {
		(*lit)->addToWorld();
	}

	// Add all constraints
	std::vector<Joint*>::iterator jit = mJoints.begin();
	for (; jit != mJoints.end(); jit++) {
		(*jit)->addToWorld();
	}
}

void Phenome::removeFromWorld() {
	// Remove all constraints
	std::vector<Joint*>::iterator jit = mJoints.begin();
	for (; jit != mJoints.end(); jit++) {
		(*jit)->removeFromWorld();
	}

	// Remove all limbs
	std::vector<Limb*>::iterator lit = mLimbs.begin();
	for (; lit != mLimbs.end(); lit++) {
		(*lit)->removeFromWorld();
	}
}
