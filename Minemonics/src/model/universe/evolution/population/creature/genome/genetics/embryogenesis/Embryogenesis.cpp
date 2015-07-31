/*
 * Embryogenesis.cpp
 *
 *  Created on: Apr 20, 2015
 *      Author: leviathan
 */

//# corresponding header
//# forward declarations
//# system headers
#include <map>
#include <vector>

//## controller headers
//## model headers
#include <OgreColourValue.h>
#include <OgreQuaternion.h>
#include <OgreVector3.h>
#include <LinearMath/btMatrix3x3.h>
#include <LinearMath/btQuaternion.h>
#include <LinearMath/btScalar.h>
#include <LinearMath/btTransform.h>
#include <LinearMath/btVector3.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
#include <configuration/MorphologyConfiguration.hpp>

//## controller headers
//## model headers
#include <model/universe/environments/EnvironmentModel.hpp>
#include <model/universe/environments/physics/PhysicsController.hpp>
#include <model/universe/evolution/population/creature/CreatureModel.hpp>
#include <model/universe/evolution/population/creature/genome/genetics/embryogenesis/BaseGenerator.hpp>
#include <model/universe/evolution/population/creature/genome/genetics/embryogenesis/Embryogenesis.hpp>
#include <model/universe/evolution/population/creature/genome/Gene.hpp>
#include <model/universe/evolution/population/creature/genome/Genome.hpp>
#include <model/universe/evolution/population/creature/genome/morphology/Morphogene.hpp>
#include <model/universe/evolution/population/creature/genome/morphology/MorphogeneBranch.hpp>
#include <model/universe/evolution/population/creature/genome/MixedGenome.hpp>
#include <model/universe/evolution/population/creature/phenome/controller/sine/SineController.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/effector/motor/Motor.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/joint/JointModel.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/limb/LimbBt.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/limb/LimbModel.hpp>
#include <model/universe/evolution/population/creature/phenome/PhenomeModel.hpp>
#include <model/universe/evolution/population/PopulationModel.hpp>
#include <model/universe/PlanetModel.hpp>

//## view headers
//## utils headers
#include <utils/ogre3D/Euler.hpp>
#include <utils/ogre3D/OgreBulletUtils.hpp>

Embryogenesis::Embryogenesis() {
	// TODO Auto-generated constructor stub

}

Embryogenesis::~Embryogenesis() {
	// TODO Auto-generated destructor stub
}

void Embryogenesis::transcribeGene(
		std::list<PhenotypeGenerator*>& generatorList, int& totalSegmentCounter,
		PhenomeModel* phenomeModel, BaseGenerator* generator) {
	// what is the next gene type
	switch (generator->getGene()->getType()) {
		case Gene::MorphoGene: {
			transcribeMorphoGene(generatorList, totalSegmentCounter, phenomeModel,
					(PhenotypeGenerator*) generator);
			break;
		}
		default: {
			break;
		}
	}
}

void Embryogenesis::transcribeMorphoGene(
		std::list<PhenotypeGenerator*>& generatorList, int& totalSegmentCounter,
		PhenomeModel* phenomeModel, PhenotypeGenerator* generator) {
	// if the current root to leaf path is equal to the maximal segments depth, break
	if (generator->getRoot2LeafPath()
			== phenomeModel->getCreatureModel()->getGenotype().getSegmentsDepthLimit()) {
		return;
	}

	//if the total segment counter reached the total segment quantity, break
	if (totalSegmentCounter
			== phenomeModel->getCreatureModel()->getGenotype().getTotalSegmentQtyLimit()) {
		return;
	}

	totalSegmentCounter++;

	// get the morphogene and start creating the limb and its joint to its parent
	Morphogene * morphogene = ((Morphogene*) generator->getGene());

	// joint position in reference frame A
	Ogre::Vector3 localJointOA(0, 0, 0);

	// joint position in reference frame B
	Ogre::Vector3 localJointOB(0, 0, 0);

	// if there exists a parent component, then we calculate the position of the new limb according to the parent component
	if (generator->getParentComponentModel() != NULL) {

		// get parent limb A
		LimbPhysics* limbA =
				((LimbModel*) generator->getParentComponentModel())->getLimbPhysics();

		//get the limb A'a center of mass
		Ogre::Vector3 limbACOM =
				((LimbModel*) generator->getParentComponentModel())->getPosition();

		//get anchor direction of limb A in reference frame of A
		Ogre::Vector3 localAnchorDirOA;

		if (generator->isMirrored()) {
			localAnchorDirOA =
					(-((MorphogeneBranch*) generator->getGeneBranch())->getJointAnchorX(), -((MorphogeneBranch*) generator->getGeneBranch())->getJointAnchorY(), -((MorphogeneBranch*) generator->getGeneBranch())->getJointAnchorZ());
		} else if (generator->isFlipped()) {
			localAnchorDirOA =
					(((MorphogeneBranch*) generator->getGeneBranch())->getJointAnchorX(), ((MorphogeneBranch*) generator->getGeneBranch())->getJointAnchorY(), ((MorphogeneBranch*) generator->getGeneBranch())->getJointAnchorZ());
			//	get direction vector of object
			Ogre::Vector3 n(1, 0, 0);
			n =
					((LimbModel*) generator->getParentComponentModel())->getOrientation()
							* n;

			//reflect on the direction vector
			localAnchorDirOA = -localAnchorDirOA
					- 2 * ((-localAnchorDirOA).dotProduct(n)) * n;
		} else {
			localAnchorDirOA =
					(((MorphogeneBranch*) generator->getGeneBranch())->getJointAnchorX(), ((MorphogeneBranch*) generator->getGeneBranch())->getJointAnchorY(), ((MorphogeneBranch*) generator->getGeneBranch())->getJointAnchorZ());
		}

		//get surface point of limb A in reference frame of A
		Ogre::Vector3 localAnchorOA(limbA->getLocalIntersection(
		/*origin of limb A*/
		OgreBulletUtils::convert(limbACOM),
		/*direction of anchor of limb A*/
		OgreBulletUtils::convert(localAnchorDirOA)));

		// joint direction of joint part of A
		Ogre::Euler eulerA(
				((MorphogeneBranch*) generator->getGeneBranch())->getJointYaw(),
				((MorphogeneBranch*) generator->getGeneBranch())->getJointPitch(),
				((MorphogeneBranch*) generator->getGeneBranch())->getJointRoll());

		//get local joint rotation point in reference frame A
		localJointOA = localAnchorOA
				+ eulerA * localAnchorDirOA.normalisedCopy()
						* MorphologyConfiguration::JOINT_LENGTH;

		//get anchor direction of limb B
		Ogre::Vector3 localAnchorDirOB(morphogene->getJointAnchorX(),
				morphogene->getJointAnchorY(), morphogene->getJointAnchorZ());

		// get local joint rotation point in the local reference frame of B
		Ogre::Euler eulerB(morphogene->getJointYaw(),
				morphogene->getJointPitch(), morphogene->getJointRoll());

		//get local surface anchor point of B in reference frame A
		Ogre::Vector3 localAnchorOBinA(
				localJointOA
						- eulerB * localAnchorDirOB.normalisedCopy()
								* MorphologyConfiguration::JOINT_LENGTH);

		// find the joint anchor position of the limb by positioning the limb at an arbitrary position to cast a ray
		LimbBt* limbBBt = new LimbBt();

		limbBBt->initialize(
				phenomeModel->getCreatureModel()->getPopulationModel()->getPlanetModel()->getEnvironmentModel()->getPhysicsController()->getDynamicsWorld(),
				NULL, morphogene->getPrimitiveType(),
				OgreBulletUtils::convert(generator->getPosition()),
				btQuaternion(morphogene->getOrientationX(),
						morphogene->getOrientationY(),
						morphogene->getOrientationZ(),
						morphogene->getOrientationW()), btVector3(),
				btQuaternion(),
				/*size*/
				btVector3(
						generator->getCurrentShrinkageFactor()
								* morphogene->getX(),
						generator->getCurrentShrinkageFactor()
								* morphogene->getY(),
						generator->getCurrentShrinkageFactor()
								* morphogene->getZ()),
				/*mass*/
				btScalar(
						generator->getCurrentShrinkageFactor()
								* morphogene->getX()
								* generator->getCurrentShrinkageFactor()
								* morphogene->getY()
								* generator->getCurrentShrinkageFactor()
								* morphogene->getZ()),
				morphogene->getRestitution(), morphogene->getFriction());
		limbBBt->addToWorld();

		//get the surface point of limb B in the local reference frame of B
		Ogre::Vector3 localAnchorOB(
				OgreBulletUtils::convert(limbBBt->getLocalIntersection(
				/*origin of limb B*/
				OgreBulletUtils::convert(generator->getPosition()),
				/*direction of anchor of limb B*/
				OgreBulletUtils::convert(localAnchorDirOB))));

		limbBBt->removeFromWorld();

		delete limbBBt;
		limbBBt = NULL;

		// global center of mass of limb B
		Ogre::Vector3 limbBCOM(limbACOM + localAnchorOBinA - localAnchorOB);
		// set global center of mass of limb B as the new generation point

		generator->setPosition(limbBCOM);
		generator->setOrientation(
				Ogre::Quaternion(morphogene->getOrientationW(),
						morphogene->getOrientationX(),
						morphogene->getOrientationY(),
						morphogene->getOrientationZ()));

		localJointOB = localAnchorOB
				+ eulerB * localAnchorDirOB.normalisedCopy()
						* MorphologyConfiguration::JOINT_LENGTH;

		//				// draw line from limb A along test ray (RED LINE)
		//				//TODO: Debug lines
		//				SimulationManager::getSingleton()->getDebugDrawer()->drawLine(limbACOM,
		//						limbACOM + 10000.0f * localAnchorDirOA,
		//						Ogre::ColourValue(1, 0, 0));
		//
		//				// draw line from limb B along test ray (RED LINE)
		//				SimulationManager::getSingleton()->getDebugDrawer()->drawLine(limbBCOM,
		//						limbBCOM + 10000.0f * localAnchorDirOB,
		//						Ogre::ColourValue(1, 0, 0));

		//				// draw line from limb A to surface anchor point of A (GREEN LINE)
		//				SimulationManager::getSingleton()->getDebugDrawer()->drawLine(limbACOM,
		//						limbACOM + localAnchorOA, Ogre::ColourValue(0, 1, 0));
		//
		//				// draw line from anchor point of A to joint rotation point (BLUE LINE)
		//				SimulationManager::getSingleton()->getDebugDrawer()->drawLine(
		//						limbACOM + localAnchorOA, limbACOM + localJointOA,
		//						Ogre::ColourValue(0, 0, 1));
		//
		//				// draw line from joint rotation point to surface anchor point of B (BLUE LINE)
		//				SimulationManager::getSingleton()->getDebugDrawer()->drawLine(
		//						limbACOM + localJointOA, limbACOM + localAnchorOBinA,
		//						Ogre::ColourValue(0, 0, 1));
		//
		//				// draw line from limb B to anchor point of B (GREEN LINE)
		//				SimulationManager::getSingleton()->getDebugDrawer()->drawLine(limbBCOM,
		//						limbBCOM + localAnchorOB, Ogre::ColourValue(0, 1, 0));
		//
		//				// draw line from limb A to limb B (WHITE LINE)
		//				SimulationManager::getSingleton()->getDebugDrawer()->drawLine(limbBCOM,
		//						limbACOM, Ogre::ColourValue(1, 1, 1));
	}

	//build the limb out of the morphogene
	LimbModel* limbB = new LimbModel();
	phenomeModel->getLimbModels().push_back(limbB);
	phenomeModel->getComponentModels().push_back(limbB);

	limbB->initialize(
			phenomeModel->getCreatureModel()->getPopulationModel()->getPlanetModel()->getEnvironmentModel()->getPhysicsController()->getDynamicsWorld(),
			phenomeModel->getCreatureModel(), morphogene->getPrimitiveType(),
			generator->getPosition(), generator->getOrientation(),
			Ogre::Vector3(
					generator->getPosition()
							- phenomeModel->getCreatureModel()->getPosition()),
			Ogre::Quaternion(generator->getOrientation()),
			/*size*/
			Ogre::Vector3(
					generator->getCurrentShrinkageFactor() * morphogene->getX(),
					generator->getCurrentShrinkageFactor() * morphogene->getY(),
					generator->getCurrentShrinkageFactor()
							* morphogene->getZ()),
			/*mass*/
			//TODO: Root element is static, remove it
			//							(generator == rootGenerator)?0:
			generator->getCurrentShrinkageFactor() * morphogene->getX()
					* generator->getCurrentShrinkageFactor()
					* morphogene->getY()
					* generator->getCurrentShrinkageFactor()
					* morphogene->getZ(), morphogene->getRestitution(),
			morphogene->getFriction(),
			Ogre::ColourValue(morphogene->getColorR(), morphogene->getColorB(),
					morphogene->getColorG()),
			phenomeModel->getComponentModels().size() - 1);

	if (generator->getParentComponentModel() != NULL) {

		// transformation from the limb A and limb B center of mass to the joint in the respective reference frames
		btTransform localA, localB;
		localA.setIdentity();
		localB.setIdentity();

		MorphogeneBranch* morphogeneBranch =
				((MorphogeneBranch*) generator->getGeneBranch());

		// define the position and direction of the joint in the reference frame of A
		localA.setOrigin(OgreBulletUtils::convert(localJointOA));
		localA.getBasis().setEulerZYX(morphogeneBranch->getJointRoll(),
				morphogeneBranch->getJointYaw(),
				morphogeneBranch->getJointPitch());

		// define the position and direction of the joint in the reference frame of B
		localB.setOrigin(OgreBulletUtils::convert(localJointOB));
		localB.getBasis().setEulerZYX(morphogene->getJointRoll(),
				morphogene->getJointYaw(), morphogene->getJointPitch());

		//create the joint from the two limbs using limb A, limb B and their joint definitions in the respective reference frames
		JointModel* joint = new JointModel();

		// add the joint to the phenotype joints
		phenomeModel->getJointModels().push_back(joint);
		phenomeModel->getComponentModels().push_back(joint);

		joint->initialize(
				phenomeModel->getCreatureModel()->getPopulationModel()->getPlanetModel()->getEnvironmentModel()->getPhysicsController()->getDynamicsWorld(),
				/*limbA*/
				((LimbBt*) ((LimbModel*) generator->getParentComponentModel())->getLimbPhysics())->getRigidBody(),
				((LimbBt*) limbB->getLimbPhysics())->getRigidBody(), localA,
				localB,
				((LimbModel*) generator->getParentComponentModel())->getOwnIndex(),
				limbB->getOwnIndex(),
				phenomeModel->getComponentModels().size() - 1);

		//initialize rotational limit motors
		joint->initializeRotationalLimitMotors(
				Ogre::Vector3(morphogeneBranch->getJointMaxPitchForce(),
						morphogeneBranch->getJointMaxYawForce(),
						morphogeneBranch->getJointMaxRollForce()),
				Ogre::Vector3(morphogeneBranch->getJointMaxPitchForce(),
						morphogeneBranch->getJointMaxYawForce(),
						morphogeneBranch->getJointMaxRollForce()));

		//TODO: Quick controller hack
		for (std::vector<Motor*>::const_iterator motorIterator =
				joint->getMotors().begin();
				motorIterator != joint->getMotors().end(); motorIterator++) {
			SineController* controller = new SineController();
			controller->initialize(0.5f, 0.1f, 0, 0);
			controller->addControlOutput((*motorIterator));
			phenomeModel->getControllers().push_back(controller);
		}

		//set the angular limits of the joint
		joint->setAngularLimits(
				Ogre::Vector3(morphogeneBranch->getJointPitchMinAngle(),
						morphogeneBranch->getJointYawMinAngle(),
						morphogeneBranch->getJointRollMinAngle()),
				Ogre::Vector3(morphogeneBranch->getJointPitchMaxAngle(),
						morphogeneBranch->getJointYawMaxAngle(),
						morphogeneBranch->getJointRollMaxAngle()));

		//set the angular stiffness of the joint
		//						joint->setAngularStiffness(
		//								morphogeneBranch->getJointPitchStiffness(),
		//								morphogeneBranch->getJointYawStiffness(),
		//								morphogeneBranch->getJointRollStiffness());
		joint->setAngularStiffness(0, 0, 0);
		//set the angular spring damping coefficients of the joint
		//						joint->setAngularDamping(
		//								morphogeneBranch->getSpringPitchDampingCoefficient(),
		//								morphogeneBranch->getSpringYawDampingCoefficient(),
		//								morphogeneBranch->getSpringRollDampingCoefficient());
		joint->setAngularDamping(0, 0, 0);

		//set if the angular motor is enabled
		//TODO: Reenable if working motors
		//						joint->enableAngularMotor(
		//								morphogeneBranch->isJointPitchMotorEnabled(),
		//								morphogeneBranch->isJointYawMotorEnabled(),
		//								morphogeneBranch->isJointRollMotorEnabled());
	}

	//iterate over all morphogene branches
	for (std::vector<MorphogeneBranch*>::iterator branchIt =
			morphogene->getGeneBranches().begin();
			branchIt != morphogene->getGeneBranches().end(); branchIt++) {

		// only add new generator if the branch is active
		if ((*branchIt)->isActive()) {
			// get the branch gene type defined by the branch
			Morphogene* offspring =
					(Morphogene*) phenomeModel->getCreatureModel()->getGenotype().getGenes()[(*branchIt)->getBranchGeneType()];

			// create the new generator
			PhenotypeGenerator* generatorFromBranch = new PhenotypeGenerator();
			generatorFromBranch->initialize(generator->getRepetitionList(),
					generator->getPosition(), generator->getOrientation(),
					limbB, (*branchIt.base()),
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
						phenomeModel->getCreatureModel()->getGenotype().getGenes()[offspring->getFollowUpGene()]);
			}

			//set new root to leaf path length
			generatorFromBranch->setRoot2LeafPath(
					generator->getRoot2LeafPath() + 1);

			//add generator to the list
			generatorList.push_back(generatorFromBranch);

			if ((*branchIt)->isFlipped()) {
				// create the new generator
				PhenotypeGenerator* flippedGeneratorFromBranch =
						new PhenotypeGenerator();
				flippedGeneratorFromBranch->initialize(
						generator->getRepetitionList(),
						generator->getPosition(), generator->getOrientation(),
						limbB, (*branchIt.base()),
						morphogene->getSegmentShrinkFactor()
								* generator->getCurrentShrinkageFactor(),
						true/*Flipped*/, false);

				//If repetition limit not exceeded (if it does not find the key OR if the repetition limit of the key is not exceeded)
				if (flippedGeneratorFromBranch->getRepetitionList().find(
						(*branchIt)->getBranchGeneType())
						== flippedGeneratorFromBranch->getRepetitionList().end()
						|| flippedGeneratorFromBranch->getRepetitionList()[(*branchIt)->getBranchGeneType()]
								<= offspring->getRepetitionLimit()) {

					//add another of this offspring type
					flippedGeneratorFromBranch->getRepetitionList()[(*branchIt)->getBranchGeneType()]++;
					flippedGeneratorFromBranch->setGene(offspring);
				} else {

					//add the offspring's follower because the repetition limit of the offspring is exceeded
					flippedGeneratorFromBranch->setGene(
							phenomeModel->getCreatureModel()->getGenotype().getGenes()[offspring->getFollowUpGene()]);
				}

				//set new root to leaf path length
				flippedGeneratorFromBranch->setRoot2LeafPath(
						generator->getRoot2LeafPath() + 1);

				//add generator to the list
				generatorList.push_back(flippedGeneratorFromBranch);
			}

			if ((*branchIt)->isMirrored()) {
				// create the new generator
				PhenotypeGenerator* mirroredGeneratorFromBranch =
						new PhenotypeGenerator();
				mirroredGeneratorFromBranch->initialize(
						generator->getRepetitionList(),
						generator->getPosition(), generator->getOrientation(),
						limbB, (*branchIt.base()),
						morphogene->getSegmentShrinkFactor()
								* generator->getCurrentShrinkageFactor(), false,
						true/*Mirrored*/);

				//If repetition limit not exceeded (if it does not find the key OR if the repetition limit of the key is not exceeded)
				if (mirroredGeneratorFromBranch->getRepetitionList().find(
						(*branchIt)->getBranchGeneType())
						== mirroredGeneratorFromBranch->getRepetitionList().end()
						|| mirroredGeneratorFromBranch->getRepetitionList()[(*branchIt)->getBranchGeneType()]
								<= offspring->getRepetitionLimit()) {

					//add another of this offspring type
					mirroredGeneratorFromBranch->getRepetitionList()[(*branchIt)->getBranchGeneType()]++;
					mirroredGeneratorFromBranch->setGene(offspring);
				} else {

					//add the offspring's follower because the repetition limit of the offspring is exceeded
					mirroredGeneratorFromBranch->setGene(
							phenomeModel->getCreatureModel()->getGenotype().getGenes()[offspring->getFollowUpGene()]);
				}

				//set new root to leaf path length
				mirroredGeneratorFromBranch->setRoot2LeafPath(
						generator->getRoot2LeafPath() + 1);

				//add generator to the list
				generatorList.push_back(mirroredGeneratorFromBranch);
			}
		}
	}
}

