//# corresponding header
//# forward declarations
//# system headers
#include <configuration/MorphologyConfiguration.hpp>
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
#include <SimulationManager.hpp>

//## configuration headers
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
#include <view/visualization/bulletphysics/OgreBtDebugDrawer.hpp>

//## utils headers
#include <utils/ogre3D/Euler.hpp>
#include <utils/ogre3D/OgreBulletUtils.hpp>

Embryogenesis::Embryogenesis() {
}

Embryogenesis::~Embryogenesis() {
}

void Embryogenesis::transcribeGene(
		std::list<PhenotypeGenerator*>& generatorList, int& totalSegmentCounter,
		PhenomeModel* phenomeModel, BaseGenerator* generator) {
	// what is the next gene type
	switch (generator->getGene()->getType()) {
	case Gene::MorphoGene: {
		transcribeMorphogene(generatorList, totalSegmentCounter, phenomeModel,
				(PhenotypeGenerator*) generator);
		break;
	}
	default: {
		break;
	}
	}
}

void Embryogenesis::transcribeMorphogene(
		std::list<PhenotypeGenerator*>& generatorList, int& totalSegmentCounter,
		PhenomeModel* phenomeModel, PhenotypeGenerator* generator) {

	//##
	// Continuation checks
	//##
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

	// ##
	// Start generating
	// ##

	//PARENT CONNECTION

	// joint position in local reference frame of the parent
	Ogre::Vector3 localParentJointInRefParent(0, 0, 0);

	//CHILD
	// get the morphogene and start creating the limb and its joint to its parent
	Morphogene * childMorphogene = ((Morphogene*) generator->getGene());

	// joint position in local reference frame of the child
	Ogre::Vector3 localChildJointInRefChild(0, 0, 0);

	// CONTINUE FROM PARENT?
	// if there exists a parent component, then we calculate the position of the new limb according to the parent component
	if (generator->getParentComponentModel() != NULL) {

		//PARENT
		//get the morphogene branch that defines the joint and connects the limbs
		MorphogeneBranch* parentMorphogeneBranch =
				((MorphogeneBranch*) generator->getGeneBranch());

		// get parent limb
		LimbBt* parentLimb =
				((LimbBt*) ((LimbModel*) generator->getParentComponentModel())->getLimbPhysics());

		//get the parent limb's center of mass position
		Ogre::Vector3 parentLimbCOM =
				((LimbModel*) generator->getParentComponentModel())->getPosition();

		// ##
		// PARENT ANCHOR DIRECTION
		// ##
		//get anchor direction of the parent limb in reference frame of itself
		Ogre::Vector3 localParentAnchorDirInRefParent;

		//if the generator is the mirrored version of another generator
		//mirrored is: -O  -> O- | \O -> O\   mirroring = sign inversion  //
		if (generator->isMirrored()) {

			//get mirrored direction
			localParentAnchorDirInRefParent =
					(-((MorphogeneBranch*) generator->getGeneBranch())->getJointAnchorX(), -((MorphogeneBranch*) generator->getGeneBranch())->getJointAnchorY(), -((MorphogeneBranch*) generator->getGeneBranch())->getJointAnchorZ());
			//if the generator is the flipped version of another generator
			//flipped is: \O -> O/ and the flipping axis is the parent limb direction
		} else if (generator->isFlipped()) {

			// get flipped direction
			localParentAnchorDirInRefParent =
					(((MorphogeneBranch*) generator->getGeneBranch())->getJointAnchorX(), ((MorphogeneBranch*) generator->getGeneBranch())->getJointAnchorY(), ((MorphogeneBranch*) generator->getGeneBranch())->getJointAnchorZ());
			//	get direction vector of parent limb
			Ogre::Vector3 parentLimbDir(1, 0, 0);
			parentLimbDir = OgreBulletUtils::convert(
					parentLimb->getOrientation()) * parentLimbDir;

			//reflect on the direction vector
			localParentAnchorDirInRefParent = -localParentAnchorDirInRefParent
					- 2
							* ((-localParentAnchorDirInRefParent).dotProduct(
									parentLimbDir)) * parentLimbDir;
		} else {

			//get normal direction
			localParentAnchorDirInRefParent = Ogre::Vector3(
					parentMorphogeneBranch->getJointAnchorX(),
					parentMorphogeneBranch->getJointAnchorY(),
					parentMorphogeneBranch->getJointAnchorZ());
		}

		//##
		// PARENT LIMB ANCHOR POINT
		//##

		// add parent limb to world
		parentLimb->addToWorld();
		//get surface point of the parent limb in reference frame itself
		Ogre::Vector3 localParentAnchorInRefParent(
				parentLimb->getLocalIntersection(
				/*origin of limb parent*/
				OgreBulletUtils::convert(parentLimbCOM),
				/*direction of anchor of limb parent*/
				OgreBulletUtils::convert(localParentAnchorDirInRefParent)));

		// remove parent limb from world
		parentLimb->removeFromWorld();

		//##
		// PARENT JOINT POSITION
		//##
		// joint direction of joint part of parent
		Ogre::Euler parentEulerJointDir(parentMorphogeneBranch->getJointYaw(),
				parentMorphogeneBranch->getJointPitch(),
				parentMorphogeneBranch->getJointRoll());

		//get local joint rotation point in reference frame parent
		localParentJointInRefParent = localParentAnchorInRefParent
				+ parentEulerJointDir
						* localParentAnchorDirInRefParent.normalisedCopy()
						* MorphologyConfiguration::JOINT_LENGTH;

		//##
		// CHILD LIMB ANCHOR POINT IN PARENT REFERENCE FRAME
		//##
		// get local joint direction in the local reference frame of child
		Ogre::Euler childEulerJointDir(childMorphogene->getJointYaw(),
				childMorphogene->getJointPitch(),
				childMorphogene->getJointRoll());

		//	get direction vector of child joint anchor
		Ogre::Vector3 childJointDir(1, 0, 0);
		childJointDir = childEulerJointDir * childJointDir;

		//get local surface anchor point of child in reference frame parent
		Ogre::Vector3 localChildAnchorInRefParent(
				localParentJointInRefParent
						- childJointDir.normalisedCopy()
								* MorphologyConfiguration::JOINT_LENGTH);

		//##
		// CHILD LIMB ANCHOR POINT IN CHILD REFERENCE FRAME
		//##
		// find the joint anchor position of the limb by positioning the limb at an arbitrary position to cast a ray
		LimbBt* childLimbBt = new LimbBt();

		childLimbBt->initialize(
				phenomeModel->getCreatureModel()->getPopulationModel()->getPlanetModel()->getEnvironmentModel()->getPhysicsController()->getDynamicsWorld(),
				NULL, childMorphogene->getPrimitiveType(),
				OgreBulletUtils::convert(generator->getPosition()),
				btQuaternion(childMorphogene->getOrientationX(),
						childMorphogene->getOrientationY(),
						childMorphogene->getOrientationZ(),
						childMorphogene->getOrientationW()), btVector3(),
				btQuaternion(),
				/*size*/
				btVector3(
						generator->getCurrentShrinkageFactor()
								* childMorphogene->getX(),
						generator->getCurrentShrinkageFactor()
								* childMorphogene->getY(),
						generator->getCurrentShrinkageFactor()
								* childMorphogene->getZ()),
				/*mass*/
				btScalar(
						generator->getCurrentShrinkageFactor()
								* childMorphogene->getX()
								* generator->getCurrentShrinkageFactor()
								* childMorphogene->getY()
								* generator->getCurrentShrinkageFactor()
								* childMorphogene->getZ()),
				childMorphogene->getRestitution(),
				childMorphogene->getFriction(), btVector3(0, 0, 0));

		// get anchor direction of limb child in the local reference frame of child
		Ogre::Vector3 localChildAnchorDirInRefChild(
				childMorphogene->getJointAnchorX(),
				childMorphogene->getJointAnchorY(),
				childMorphogene->getJointAnchorZ());

		// add child limb to world
		childLimbBt->addToWorld();

		//get the surface point of child limb in the local reference frame of itself
		Ogre::Vector3 localChildAnchorInRefChild(
				OgreBulletUtils::convert(childLimbBt->getLocalIntersection(
				/*origin of child limb*/
				OgreBulletUtils::convert(generator->getPosition()),
				/*direction of anchor of child limb*/
				OgreBulletUtils::convert(localChildAnchorDirInRefChild))));

		// remove child limb from world
		childLimbBt->removeFromWorld();

		delete childLimbBt;
		childLimbBt = NULL;

		//
		localChildJointInRefChild = localChildAnchorInRefChild
				+ childJointDir.normalisedCopy()
						* MorphologyConfiguration::JOINT_LENGTH;

		// global center of mass of child limb
		Ogre::Vector3 childLimbCOM(
				parentLimbCOM + localChildAnchorInRefParent
						- localChildAnchorInRefChild);

//		// draw line from limb A to surface anchor point of A (GREEN LINE)
//		SimulationManager::getSingleton()->getDebugDrawer().drawLine(
//				parentLimbCOM, parentLimbCOM + localParentAnchorInRefParent,
//				Ogre::ColourValue(0, 1, 0));
//
//		SimulationManager::getSingleton()->getDebugDrawer().drawSphere(
//				parentLimbCOM, 0.1, Ogre::ColourValue(0, 1, 0));
//
//		SimulationManager::getSingleton()->getDebugDrawer().drawSphere(
//				parentLimbCOM + localParentAnchorInRefParent, 0.1,
//				Ogre::ColourValue(0, 1, 0));
//
//		// draw line from anchor point of A to joint rotation point (BLUE LINE)
//		SimulationManager::getSingleton()->getDebugDrawer().drawLine(
//				parentLimbCOM + localParentAnchorInRefParent,
//				parentLimbCOM + localParentJointInRefParent,
//				Ogre::ColourValue(0, 0, 1));
//
//		SimulationManager::getSingleton()->getDebugDrawer().drawSphere(
//				parentLimbCOM + localParentAnchorInRefParent, 0.1,
//				Ogre::ColourValue(0, 0, 1));
//		SimulationManager::getSingleton()->getDebugDrawer().drawSphere(
//				parentLimbCOM + localParentJointInRefParent, 0.1,
//				Ogre::ColourValue(0, 0, 1));
//
//		// draw line from joint rotation point to surface anchor point of B (BLUE LINE)
//		SimulationManager::getSingleton()->getDebugDrawer().drawLine(
//				parentLimbCOM + localParentJointInRefParent,
//				parentLimbCOM + localChildAnchorInRefParent,
//				Ogre::ColourValue(0, 0, 1));
//
//		SimulationManager::getSingleton()->getDebugDrawer().drawSphere(
//				parentLimbCOM + localParentJointInRefParent, 0.1,
//				Ogre::ColourValue(0, 0, 1));
//		SimulationManager::getSingleton()->getDebugDrawer().drawSphere(
//				parentLimbCOM + localChildAnchorInRefParent, 0.1,
//				Ogre::ColourValue(0, 0, 1));
//
//		// draw line from limb B to anchor point of B (GREEN LINE)
//		SimulationManager::getSingleton()->getDebugDrawer().drawLine(
//				childLimbCOM, childLimbCOM + localChildAnchorInRefChild,
//				Ogre::ColourValue(0, 1, 0));
//
//		SimulationManager::getSingleton()->getDebugDrawer().drawSphere(
//				childLimbCOM, 0.1, Ogre::ColourValue(0, 1, 0));
//		SimulationManager::getSingleton()->getDebugDrawer().drawSphere(
//				childLimbCOM + localChildAnchorInRefChild, 0.1,
//				Ogre::ColourValue(0, 1, 0));

//		// draw line from limb A to limb B (WHITE LINE)
//		SimulationManager::getSingleton()->getDebugDrawer().drawLine(
//				childLimbCOM, parentLimbCOM, Ogre::ColourValue(1, 1, 1));

		// set global center of mass of child limb as the new generation point for generation
		generator->setPosition(childLimbCOM);
		generator->setOrientation(
				Ogre::Quaternion(childMorphogene->getOrientationW(),
						childMorphogene->getOrientationX(),
						childMorphogene->getOrientationY(),
						childMorphogene->getOrientationZ()));
	}

	//build the limb out of the morphogene
	LimbModel* childLimb = new LimbModel();

	childLimb->initialize(
			phenomeModel->getCreatureModel()->getPopulationModel()->getPlanetModel()->getEnvironmentModel()->getPhysicsController()->getDynamicsWorld(),
			phenomeModel->getCreatureModel(),
			childMorphogene->getPrimitiveType(), generator->getPosition(),
			generator->getOrientation(),
			Ogre::Vector3(
					generator->getPosition()
							- phenomeModel->getCreatureModel()->getPosition()),
			generator->getOrientation(),
			/*size*/
			Ogre::Vector3(
					generator->getCurrentShrinkageFactor()
							* childMorphogene->getX(),
					generator->getCurrentShrinkageFactor()
							* childMorphogene->getY(),
					generator->getCurrentShrinkageFactor()
							* childMorphogene->getZ()),
			/*mass*/
			//TODO: Root element is static, remove it
			//							(generator == rootGenerator)?0:
			generator->getCurrentShrinkageFactor() * childMorphogene->getX()
					* generator->getCurrentShrinkageFactor()
					* childMorphogene->getY()
					* generator->getCurrentShrinkageFactor()
					* childMorphogene->getZ(),
			childMorphogene->getRestitution(), childMorphogene->getFriction(),
			Ogre::ColourValue(childMorphogene->getColorR(),
					childMorphogene->getColorB(), childMorphogene->getColorG()),
			phenomeModel->getComponentModels().size() - 1);

	phenomeModel->getLimbModels().push_back(childLimb);
	phenomeModel->getComponentModels().push_back(childLimb);

	if (generator->getParentComponentModel() != NULL) {

		//PARENT
		//get the morphogene branch that defines the joint and connects the limbs
		MorphogeneBranch* parentMorphogeneBranch =
				((MorphogeneBranch*) generator->getGeneBranch());

		// get parent limb
		LimbModel* parentLimb =
				(LimbModel*) generator->getParentComponentModel();

		// transformation from the parent limb and child limb center of mass to the joint in the respective reference frames
		btTransform localParentJointTransform, localChildJointTransform;
		localParentJointTransform.setIdentity();
		localChildJointTransform.setIdentity();

		// define the position and direction of the joint in the reference frame of the parent
		localParentJointTransform.setOrigin(
				OgreBulletUtils::convert(localParentJointInRefParent));
		localParentJointTransform.getBasis().setEulerYPR(
				parentMorphogeneBranch->getJointYaw(),
				parentMorphogeneBranch->getJointPitch(),
				parentMorphogeneBranch->getJointRoll());

		// define the position and direction of the joint in the reference frame of child
		localChildJointTransform.setOrigin(
				OgreBulletUtils::convert(localChildJointInRefChild));
		localChildJointTransform.getBasis().setEulerYPR(
				childMorphogene->getJointYaw(),
				childMorphogene->getJointPitch(),
				childMorphogene->getJointRoll());

		//create the joint from the two limbs using limb A, limb B and their joint definitions in the respective reference frames
		JointModel* joint = new JointModel();

		joint->initialize(
				phenomeModel->getCreatureModel()->getPopulationModel()->getPlanetModel()->getEnvironmentModel()->getPhysicsController()->getDynamicsWorld(),
				/*parent limb*/
				((LimbBt*) parentLimb->getLimbPhysics())->getRigidBody(),
				/*child limb*/
				((LimbBt*) childLimb->getLimbPhysics())->getRigidBody(),
				localParentJointTransform, localChildJointTransform,
				parentLimb->getOwnIndex(), childLimb->getOwnIndex(),
				phenomeModel->getComponentModels().size() - 1);
		parentLimb->setJointIndex(joint->getIndex());
		childLimb->setJointIndex(joint->getIndex());

		// add the joint to the phenotype joints
		phenomeModel->getJointModels().push_back(joint);
		phenomeModel->getComponentModels().push_back(joint);

		//initialize rotational limit motors
		joint->initializeRotationalLimitMotors(
				Ogre::Vector3(parentMorphogeneBranch->getJointMaxPitchForce(),
						parentMorphogeneBranch->getJointMaxYawForce(),
						parentMorphogeneBranch->getJointMaxRollForce()),
				Ogre::Vector3(parentMorphogeneBranch->getJointMaxPitchForce(),
						parentMorphogeneBranch->getJointMaxYawForce(),
						parentMorphogeneBranch->getJointMaxRollForce()));

		//TODO: Quick controller hack
//		for (std::vector<Motor*>::const_iterator motorIterator =
//				joint->getMotors().begin();
//				motorIterator != joint->getMotors().end(); motorIterator++) {
//			SineController* controller = new SineController();
//			controller->initialize(0.5f, 0.1f, 0, 0.5f);
//			controller->addControlOutput((*motorIterator));
//			phenomeModel->getControllers().push_back(controller);
//		}

		SineController* controller = new SineController();
		controller->initialize(parentMorphogeneBranch->getJointPitchAmplitude(),
				parentMorphogeneBranch->getJointPitchFrequency(),
				parentMorphogeneBranch->getJointPitchXOffset(),
				parentMorphogeneBranch->getJointPitchYOffset());
		controller->addControlOutput(joint->getMotors()[0]);
		phenomeModel->getControllers().push_back(controller);

		controller = new SineController();
		controller->initialize(parentMorphogeneBranch->getJointYawAmplitude(),
				parentMorphogeneBranch->getJointYawFrequency(),
				parentMorphogeneBranch->getJointYawXOffset(),
				parentMorphogeneBranch->getJointYawYOffset());
		controller->addControlOutput(joint->getMotors()[1]);
		phenomeModel->getControllers().push_back(controller);

		controller = new SineController();
		controller->initialize(parentMorphogeneBranch->getJointRollAmplitude(),
				parentMorphogeneBranch->getJointRollFrequency(),
				parentMorphogeneBranch->getJointRollXOffset(),
				parentMorphogeneBranch->getJointRollYOffset());
		controller->addControlOutput(joint->getMotors()[2]);
		phenomeModel->getControllers().push_back(controller);

		//set the angular limits of the joint
		joint->setAngularLimits(
				Ogre::Vector3(parentMorphogeneBranch->getJointPitchMinAngle(),
						parentMorphogeneBranch->getJointYawMinAngle(),
						parentMorphogeneBranch->getJointRollMinAngle()),
				Ogre::Vector3(parentMorphogeneBranch->getJointPitchMaxAngle(),
						parentMorphogeneBranch->getJointYawMaxAngle(),
						parentMorphogeneBranch->getJointRollMaxAngle()));

		//set the angular stiffness of the joint
		joint->setAngularStiffness(
				parentMorphogeneBranch->getJointPitchStiffness(),
				parentMorphogeneBranch->getJointYawStiffness(),
				parentMorphogeneBranch->getJointRollStiffness());

		//set the angular spring damping coefficients of the joint
		joint->setAngularDamping(
				parentMorphogeneBranch->getSpringPitchDampingCoefficient(),
				parentMorphogeneBranch->getSpringYawDampingCoefficient(),
				parentMorphogeneBranch->getSpringRollDampingCoefficient());

		//set if the angular motor is enabled
		joint->enableAngularMotor(
				parentMorphogeneBranch->isJointPitchMotorEnabled(),
				parentMorphogeneBranch->isJointYawMotorEnabled(),
				parentMorphogeneBranch->isJointRollMotorEnabled());
	}

	//Create new generators from the morphogene branches

	//iterate over all morphogene branches
	for (std::vector<MorphogeneBranch*>::iterator branchIt =
			childMorphogene->getGeneBranches().begin();
			branchIt != childMorphogene->getGeneBranches().end(); branchIt++) {

		// only add a new generator if the branch is active
		if ((*branchIt)->isActive()) {
			// get the branch gene type defined by the branch
			Morphogene* branchingMorphoGeneType =
					(Morphogene*) phenomeModel->getCreatureModel()->getGenotype().getGenes()[(*branchIt)->getBranchGeneType()];

			// create a new generator from the branch
			PhenotypeGenerator* generatorFromBranch = new PhenotypeGenerator();
			generatorFromBranch->initialize(generator->getRepetitionList(),
					generator->getPosition(), generator->getOrientation(),
					childLimb, (*branchIt.base()),
					childMorphogene->getSegmentShrinkFactor()
							* generator->getCurrentShrinkageFactor());

			// If repetition limit of this component is not exceeded
			// (if it does not find the key OR if the repetition limit of the key is not exceeded)
			if (generatorFromBranch->getRepetitionList().find(
					(*branchIt)->getBranchGeneType())
					== generatorFromBranch->getRepetitionList().end()
					|| generatorFromBranch->getRepetitionList()[(*branchIt)->getBranchGeneType()]
							<= branchingMorphoGeneType->getRepetitionLimit()) {

				//add another of this branching morphogene type
				generatorFromBranch->getRepetitionList()[(*branchIt)->getBranchGeneType()]++;
				generatorFromBranch->setGene(branchingMorphoGeneType);
			} else {

				//add the branching morphogene's follow up gene because the repetition limit of the branching morphogene is exceeded
				generatorFromBranch->setGene(
						phenomeModel->getCreatureModel()->getGenotype().getGenes()[branchingMorphoGeneType->getFollowUpGene()]);
			}

			// increase root to leaf path length by 1
			generatorFromBranch->setRoot2LeafPath(
					generator->getRoot2LeafPath() + 1);

			//add generator to the list
			generatorList.push_back(generatorFromBranch);

			// if the branch also defines a flipped branch
			if ((*branchIt)->isFlipped()) {
				// create a new generator with the flipped flag set
				PhenotypeGenerator* flippedGeneratorFromBranch =
						new PhenotypeGenerator();
				flippedGeneratorFromBranch->initialize(
						generator->getRepetitionList(),
						generator->getPosition(), generator->getOrientation(),
						childLimb, (*branchIt.base()),
						childMorphogene->getSegmentShrinkFactor()
								* generator->getCurrentShrinkageFactor(),
						true/*Flipped*/, false);

				// If repetition limit not exceeded
				// (if it does not find the key OR if the repetition limit of the key is not exceeded)
				if (flippedGeneratorFromBranch->getRepetitionList().find(
						(*branchIt)->getBranchGeneType())
						== flippedGeneratorFromBranch->getRepetitionList().end()
						|| flippedGeneratorFromBranch->getRepetitionList()[(*branchIt)->getBranchGeneType()]
								<= branchingMorphoGeneType->getRepetitionLimit()) {

					//add another of this offspring type
					flippedGeneratorFromBranch->getRepetitionList()[(*branchIt)->getBranchGeneType()]++;
					flippedGeneratorFromBranch->setGene(
							branchingMorphoGeneType);
				} else {

					//add the branching morphogene's follow up gene because the repetition limit of the branching morphogene is exceeded
					flippedGeneratorFromBranch->setGene(
							phenomeModel->getCreatureModel()->getGenotype().getGenes()[branchingMorphoGeneType->getFollowUpGene()]);
				}

				// increase root to leaf path length by 1
				flippedGeneratorFromBranch->setRoot2LeafPath(
						generator->getRoot2LeafPath() + 1);

				//add generator to the list
				generatorList.push_back(flippedGeneratorFromBranch);
			}

			// if the branch also defines a mirrored branch
			if ((*branchIt)->isMirrored()) {
				// create the new generator
				PhenotypeGenerator* mirroredGeneratorFromBranch =
						new PhenotypeGenerator();
				mirroredGeneratorFromBranch->initialize(
						generator->getRepetitionList(),
						generator->getPosition(), generator->getOrientation(),
						childLimb, (*branchIt.base()),
						childMorphogene->getSegmentShrinkFactor()
								* generator->getCurrentShrinkageFactor(), false,
						true/*Mirrored*/);

				// If repetition limit not exceeded
				// (if it does not find the key OR if the repetition limit of the key is not exceeded)
				if (mirroredGeneratorFromBranch->getRepetitionList().find(
						(*branchIt)->getBranchGeneType())
						== mirroredGeneratorFromBranch->getRepetitionList().end()
						|| mirroredGeneratorFromBranch->getRepetitionList()[(*branchIt)->getBranchGeneType()]
								<= branchingMorphoGeneType->getRepetitionLimit()) {

					//add another of this branching morphogene type
					mirroredGeneratorFromBranch->getRepetitionList()[(*branchIt)->getBranchGeneType()]++;
					mirroredGeneratorFromBranch->setGene(
							branchingMorphoGeneType);
				} else {

					//add the branching morphogene's follow up gene because the repetition limit of the branching morphogene is exceeded
					mirroredGeneratorFromBranch->setGene(
							phenomeModel->getCreatureModel()->getGenotype().getGenes()[branchingMorphoGeneType->getFollowUpGene()]);
				}

				// increase root to leaf path length by 1
				mirroredGeneratorFromBranch->setRoot2LeafPath(
						generator->getRoot2LeafPath() + 1);

				//add generator to the list
				generatorList.push_back(mirroredGeneratorFromBranch);
			}
		}
	}
}

