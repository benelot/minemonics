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
#include <map>

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
#include "controller/evolution/population/creature/phenome/morphology/Joint.h"

//## model headers
#include "model/evolution/population/creature/genome/morphology/Morphogene.h"
#include "model/evolution/population/creature/genome/morphology/MorphogeneBranch.h"
#include "model/evolution/population/creature/phenome/morphology/LimbBt.h"
#include "model/evolution/population/creature/phenome/morphology/JointBt.h"
#include "model/evolution/population/creature/genome/Gene.h"

//## view headers
#include "view/ogre3D/evolution/population/creature/phenome/morphology/LimbO3D.h"

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

		std::cout << "Phenome generator qty:" << generatorList.size()
				<< std::endl;

		PhenotypeGenerator* generator = generatorList.front();
		generatorList.pop_front();

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

			Ogre::Vector3 localJointOA;
			Ogre::Vector3 localJointOB;

			if (generator->getParentComponent() != NULL) {

				// find the joint anchor position of the limb A
				LimbGraphics* limbA =
						((Limb*) generator->getParentComponent())->getLimbGraphics();

				//get anchor direction of limb A
				Ogre::Vector3 anchorDirOA(
						((MorphogeneBranch*) generator->getGeneBranch())->getJointAnchorX(),
						((MorphogeneBranch*) generator->getGeneBranch())->getJointAnchorY(),
						((MorphogeneBranch*) generator->getGeneBranch())->getJointAnchorZ());

				//get local surface point of limb A
				Ogre::Vector3 localAnchorOA(
				/*get the surface point of limb A in the local reference frame of A*/
				limbA->getLocalIntersection(
				/*origin of limb A*/
				Ogre::Vector3(limbA->getPosition()),
				/*direction of anchor of limb A*/
				anchorDirOA));

				//get local joint rotation point in A
				Ogre::Euler euler1(
						((MorphogeneBranch*) generator->getGeneBranch())->getJointYaw(),
						((MorphogeneBranch*) generator->getGeneBranch())->getJointPitch(),
						((MorphogeneBranch*) generator->getGeneBranch())->getJointRoll());
				localJointOA = localAnchorOA
						+ euler1 * anchorDirOA.UNIT_SCALE
								* MorphologyConfiguration::JOINT_LENGTH;

				//get anchor direction of limb B
				Ogre::Vector3 anchorDirOB(morphogene->getJointAnchorX(),
						morphogene->getJointAnchorY(),
						morphogene->getJointAnchorZ());

				//get local surface anchor point of B in A
				Ogre::Euler euler2(morphogene->getJointYaw(),
						morphogene->getJointPitch(),
						morphogene->getJointRoll());
				Ogre::Vector3 localAnchorOBinA(
						localJointOA
								- euler2 * anchorDirOB.UNIT_SCALE
										* MorphologyConfiguration::JOINT_LENGTH);

				// find the joint anchor position of the limb by positioning the limb at an arbitrary position to cast a ray
				LimbO3D* limbOB = new LimbO3D();
				limbOB->initialize(mSimulationManager,
						morphogene->getPrimitiveType(),
						/*size*/
						Ogre::Vector3(
								generator->getCurrentShrinkageFactor()
										* morphogene->getX(),
								generator->getCurrentShrinkageFactor()
										* morphogene->getY(),
								generator->getCurrentShrinkageFactor()
										* morphogene->getZ()));
				limbOB->setPosition(generator->getPosition());

				limbOB->addToWorld();

				//get the surface point of limb B in the local reference frame of B
				Ogre::Vector3 localAnchorOB(
						limbOB->getLocalIntersection(
						/*origin of limb B*/
						limbOB->getPosition(),
								/*direction of anchor of limb B*/
								Ogre::Vector3(morphogene->getJointAnchorX(),
										morphogene->getJointAnchorY(),
										morphogene->getJointAnchorZ())));

				limbOB->removeFromWorld();
				delete limbOB;
				limbOB = 0;

				// global center of mass of limb B
				Ogre::Vector3 globalCOMOB(
						limbA->getPosition() + localAnchorOBinA
								- localAnchorOB);

				// set global center of mass of limb B as the new generation point
				generator->setPosition(globalCOMOB);

				// get local joint rotation point in the local reference frame of B
				Ogre::Euler euler3(morphogene->getJointYaw(),
						morphogene->getJointPitch(),
						morphogene->getJointRoll());

				localJointOB = localAnchorOB
						+ euler3 * anchorDirOB.UNIT_SCALE
								* MorphologyConfiguration::JOINT_LENGTH;
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
					generator->getCurrentShrinkageFactor()
					/*mass*/
					* morphogene->getX()
							* generator->getCurrentShrinkageFactor()
							* morphogene->getY()
							* generator->getCurrentShrinkageFactor()
							* morphogene->getZ());
			//limb->addToWorld();
			mLimbs.push_back(limb);

			if (generator->getParentComponent() != NULL) {

				btVector3 localbtA(localJointOA.x, localJointOA.y,
						localJointOA.z);

				//define joint
				btTransform transform;
				btTransform localA, localB;
				localA.setIdentity();
				localB.setIdentity();

				localA.setOrigin(localbtA);
				localA.getBasis().setEulerZYX(
						((MorphogeneBranch*) generator->getGeneBranch())->getJointPitch(),
						((MorphogeneBranch*) generator->getGeneBranch())->getJointYaw(),
						((MorphogeneBranch*) generator->getGeneBranch())->getJointRoll());

				//set the joint of the morphogene
				btVector3 localbtB(localJointOB.x, localJointOB.y,
						localJointOB.z);
				localB.setOrigin(localbtB);
				localA.getBasis().setEulerZYX(morphogene->getJointPitch(),
						morphogene->getJointYaw(), morphogene->getJointRoll());

				Joint* joint = new Joint();
				joint->initialize(mSimulationManager,
						((Limb*) generator->getParentComponent()), limb, localA,
						localB);
				joint->setAngularLimits(
						Ogre::Vector3(
								((MorphogeneBranch*) generator->getGeneBranch())->getJointPitchMinAngle(),
								((MorphogeneBranch*) generator->getGeneBranch())->getJointYawMinAngle(),
								((MorphogeneBranch*) generator->getGeneBranch())->getJointRollMinAngle()),
						Ogre::Vector3(
								((MorphogeneBranch*) generator->getGeneBranch())->getJointPitchMaxAngle(),
								((MorphogeneBranch*) generator->getGeneBranch())->getJointYawMaxAngle(),
								((MorphogeneBranch*) generator->getGeneBranch())->getJointRollMaxAngle()));
				mJoints.push_back(joint);
			}

			//iterate over all morphogene branches
			std::vector<MorphogeneBranch*>::iterator branchIt =
					morphogene->getGeneBranches().begin();
			for (; branchIt != morphogene->getGeneBranches().end();
					branchIt++) {

				Morphogene* offspring =
						genome->getGenes()[(*branchIt)->getBranchGeneType()];

				PhenotypeGenerator* generatorFromBranch =
						new PhenotypeGenerator();

				//TODO move generator
				generatorFromBranch->initialize(generator->getRepetitionList(),
						generator->getPosition(), generator->getOrientation(),
						limb, (*branchIt.base()),
						morphogene->getSegmentShrinkFactor()
								* generator->getCurrentShrinkageFactor());

				//If repetition limit not exceeded (if it does not find the key OR if the repetition limit is not exceeded)
				if (generatorFromBranch->getRepetitionList().find(
						(*branchIt)->getBranchGeneType())
						== generatorFromBranch->getRepetitionList().end()
						|| generatorFromBranch->getRepetitionList()[(*branchIt)->getBranchGeneType()]
								<= offspring->getRepetitionLimit()) {

					//add another of this offspring type
					generatorFromBranch->getRepetitionList()[(*branchIt)->getBranchGeneType()]++;
					generatorFromBranch->setGene(offspring);
				} else {

					//add the offspring follower
					generatorFromBranch->setGene(
							genome->getGenes()[offspring->getFollowUpGene()]);
				}

				//set new root to leaf path
				generatorFromBranch->setRoot2LeafPath(
						generator->getRoot2LeafPath() + 1);
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

void Phenome::transcribeGene(Gene* gene) {
	//TODO: Implement transcribeGene method
}

void Phenome::update() {
	std::vector<Limb*>::iterator it = mLimbs.begin();
	for (; it != mLimbs.end(); it++) {
		(*it)->update();
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
