//# corresponding headers
#include <model/universe/evolution/population/creature/genome/genetics/FSEmbryogenesis.hpp>

#include <cmath>
#include <iostream>
#include <iterator>
#include <map>
#include <vector>
#include <stddef.h>

//## controller headers
//## model headers
#include <LinearMath/btMatrix3x3.h>
#include <LinearMath/btQuaternion.h>
#include <LinearMath/btScalar.h>
#include <LinearMath/btTransform.h>
#include <LinearMath/btVector3.h>
#include <OgreColourValue.h>
#include <OgreQuaternion.h>
#include <OgreVector3.h>

//## view headers
//# custom headers
//## base headers
#include <SimulationManager.hpp>

//## configuration headers
#include <configuration/MorphologyConfiguration.hpp>

//## controller headers
//## model headers
#include <model/universe/evolution/population/creature/CreatureModel.hpp>
#include <model/universe/evolution/population/creature/genome/Gene.hpp>
#include <model/universe/evolution/population/creature/genome/GeneBranch.hpp>
#include <model/universe/evolution/population/creature/genome/Genome.hpp>
#include <model/universe/evolution/population/creature/genome/morphology/Morphogene.hpp>
#include <model/universe/evolution/population/creature/genome/morphology/MorphogeneBranch.hpp>
#include <model/universe/evolution/population/creature/genome/MixedGenome.hpp>
#include <model/universe/evolution/population/creature/phenome/controller/sine/SineController.hpp>
#include <model/universe/evolution/population/creature/phenome/ComponentModel.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/effector/motor/Motor.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/joint/JointPhysics.hpp>
#include <model/universe/evolution/population/creature/genome/genetics/BaseGenerator.hpp>
#include <model/universe/evolution/population/creature/phenome/FSPhenomeModel.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/joint/FSJointModel.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/limb/FSLimbBt.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/limb/FSLimbModel.hpp>
#include <view/visualization/bulletphysics/OgreBtDebugDrawer.hpp>

//## utils headers
#include <utils/ogre3D/Euler.hpp>
#include <utils/ogre3D/OgreBulletUtils.hpp>

void FSEmbryogenesis::transcribeGene(
	std::list<PhenotypeGenerator*>& generatorList, int& totalSegmentCounter,
	FSPhenomeModel* phenomeModel, BaseGenerator* generator) {

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

void FSEmbryogenesis::transcribeMorphogene(
	std::list<PhenotypeGenerator*>& generatorList, int& totalSegmentCounter,
	FSPhenomeModel* phenomeModel, PhenotypeGenerator* generator) {

	//#####################
	// Continuation checks
	//#####################
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

	//PARENT
	Ogre::Vector3 localParentJointInRefParent; /**!< joint position in local reference frame of the parent */
	btTransform parentLimbSurfaceTransform; /**!< The position on the surface of the parent limb*/

	//CHILD
	Morphogene * childMorphogene = ((Morphogene*) generator->getGene());
	btTransform childLimbSurfaceTransform; /**!< get the morphogene and start creating the limb and its joint to its parent */
	Ogre::Vector3 localChildJointInRefChild; /**!< joint position in local reference frame of the child */

	// CONTINUE FROM PARENT?
	// if there exists a parent component, then we calculate the position of the new limb according to the parent component
	if (generator->getParentComponentModel() != NULL) {

		calculateChildPositionRelativeToParent(generator,
			parentLimbSurfaceTransform, childLimbSurfaceTransform,
			childMorphogene, phenomeModel, localParentJointInRefParent,
			localChildJointInRefChild);
	}

	//CREATE NEW CHILD LIMB
	FSLimbModel* childLimb = createLimb(generator, childMorphogene,
		phenomeModel);

	// if there is a parent limb, we connect them with a joint
	if (generator->getParentComponentModel() != NULL) {
		appendToParentLimb(phenomeModel, childLimb, generator,
			localParentJointInRefParent, localChildJointInRefChild,
			parentLimbSurfaceTransform, childLimbSurfaceTransform);
	}

	//Create new generators from the morphogene branches
	createNewGenerators(phenomeModel, childMorphogene, childLimb, generator,
		generatorList, totalSegmentCounter);
}

void FSEmbryogenesis::calculateChildPositionRelativeToParent(
	PhenotypeGenerator* generator, btTransform& parentHitTransform,
	btTransform& childHitTransform, Morphogene* childMorphogene,
	FSPhenomeModel* phenomeModel, Ogre::Vector3& localParentJointInRefParent,
	Ogre::Vector3& localChildJointInRefChild) {
	//PARENT
	//get the morphogene branch that defines the joint and connects the limbs
	MorphogeneBranch* parentMorphogeneBranch =
		((MorphogeneBranch*) generator->getGeneBranch());

	// get parent limb
	FSLimbBt* parentLimb =
		((FSLimbBt*) ((FSLimbModel*) generator->getParentComponentModel())->getLimbPhysics());

	//get the parent limb's center of mass position
	Ogre::Vector3 parentLimbCOM =
		((LimbModel*) generator->getParentComponentModel())->getPosition();

	Ogre::Vector3 localParentAnchorDirInRefParent = Ogre::Vector3(
		parentMorphogeneBranch->getJointAnchorX(),
		parentMorphogeneBranch->getJointAnchorY(),
		parentMorphogeneBranch->getJointAnchorZ());

	//if the generator is the mirrored version of another generator
	//mirrored is: -O  -> O- | \O -> O\   mirroring = sign inversion  //
	if (generator->isMirrored()) {

		//get mirrored direction
		localParentAnchorDirInRefParent = -localParentAnchorDirInRefParent;
		//if the generator is the flipped version of another generator
		//flipped is: \O -> O/ and the flipping axis is the parent limb direction
	}

	if (generator->isFlipped()) {

		//	get direction vector of parent limb
		Ogre::Vector3 parentLimbDir(1, 0, 0);
		parentLimbDir = OgreBulletUtils::convert(parentLimb->getOrientation())
			* parentLimbDir;

		//reflect on the direction vector
		localParentAnchorDirInRefParent = -localParentAnchorDirInRefParent
			- 2 * ((-localParentAnchorDirInRefParent).dotProduct(parentLimbDir))
				* parentLimbDir;
	}

	// ##
	// PARENT ANCHOR DIRECTION
	// ##
	//get anchor direction of the parent limb in reference frame of itself
	parentHitTransform = getParentIntersection(generator, parentLimb,
		parentMorphogeneBranch, parentLimbCOM, localParentAnchorDirInRefParent);

	//get surface point of the parent limb in reference frame itself
	Ogre::Vector3 localParentAnchorInRefParent(
		OgreBulletUtils::convert(parentHitTransform.getOrigin()));

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
			* localParentAnchorDirInRefParent.normalisedCopy();

	//##
	// CHILD LIMB ANCHOR POINT IN PARENT REFERENCE FRAME
	// get local joint direction in the local reference frame of child
	Ogre::Euler childEulerJointDir(childMorphogene->getJointYaw(),
		childMorphogene->getJointPitch(), childMorphogene->getJointRoll());

	//	get direction vector of child joint anchor
	Ogre::Vector3 childJointDir(1, 0, 0);
	childJointDir = childEulerJointDir * childJointDir;

	//get local surface anchor point of child in reference frame parent
	Ogre::Vector3 localChildAnchorInRefParent(
		localParentJointInRefParent - childJointDir.normalisedCopy());

	// get anchor direction of limb child in the local reference frame of child
	Ogre::Vector3 localChildAnchorDirInRefChild(
		childMorphogene->getJointAnchorX(), childMorphogene->getJointAnchorY(),
		childMorphogene->getJointAnchorZ());

	//##
	// CHILD LIMB ANCHOR POINT IN CHILD REFERENCE FRAME
	// find the joint anchor position of the limb by positioning the limb at an arbitrary position to cast a ray
	childHitTransform = getOwnIntersection(phenomeModel, childMorphogene,
		generator, localChildAnchorDirInRefChild);

	//get the surface point of child limb in the local reference frame of itself
	Ogre::Vector3 localChildAnchorInRefChild(
		OgreBulletUtils::convert(childHitTransform.getOrigin()));

	localChildJointInRefChild = localChildAnchorInRefChild
		+ childJointDir.normalisedCopy();

	// global center of mass of child limb
	Ogre::Vector3 childLimbCOM(
		parentLimbCOM + localChildAnchorInRefParent
			- localChildAnchorInRefChild);

#ifndef EXCLUDE_FROM_TEST
	// draw line from limb A to surface anchor point of A (GREEN LINE)
	SimulationManager::getSingleton()->getDebugDrawer().drawLine(parentLimbCOM,
		parentLimbCOM + localParentAnchorInRefParent,
		Ogre::ColourValue(0, 1, 0));

	SimulationManager::getSingleton()->getDebugDrawer().drawSphere(
		parentLimbCOM, 0.1, Ogre::ColourValue(0, 1, 0));

	SimulationManager::getSingleton()->getDebugDrawer().drawSphere(
		parentLimbCOM + localParentAnchorInRefParent, 0.1,
		Ogre::ColourValue(0, 1, 0));

	// draw line from anchor point of A to joint rotation point (BLUE LINE)
	SimulationManager::getSingleton()->getDebugDrawer().drawLine(
		parentLimbCOM + localParentAnchorInRefParent,
		parentLimbCOM + localParentJointInRefParent,
		Ogre::ColourValue(0, 0, 1));

	SimulationManager::getSingleton()->getDebugDrawer().drawSphere(
		parentLimbCOM + localParentAnchorInRefParent, 0.1,
		Ogre::ColourValue(0, 0, 1));
	SimulationManager::getSingleton()->getDebugDrawer().drawSphere(
		parentLimbCOM + localParentJointInRefParent, 0.1,
		Ogre::ColourValue(0, 0, 1));

	// draw line from joint rotation point to surface anchor point of B (BLUE LINE)
	SimulationManager::getSingleton()->getDebugDrawer().drawLine(
		parentLimbCOM + localParentJointInRefParent,
		parentLimbCOM + localChildAnchorInRefParent,
		Ogre::ColourValue(0, 0, 1));

	SimulationManager::getSingleton()->getDebugDrawer().drawSphere(
		parentLimbCOM + localParentJointInRefParent, 0.1,
		Ogre::ColourValue(0, 0, 1));
	SimulationManager::getSingleton()->getDebugDrawer().drawSphere(
		parentLimbCOM + localChildAnchorInRefParent, 0.1,
		Ogre::ColourValue(0, 0, 1));

	// draw line from limb B to anchor point of B (GREEN LINE)
	SimulationManager::getSingleton()->getDebugDrawer().drawLine(childLimbCOM,
		childLimbCOM + localChildAnchorInRefChild, Ogre::ColourValue(0, 1, 0));

	SimulationManager::getSingleton()->getDebugDrawer().drawSphere(childLimbCOM,
		0.1, Ogre::ColourValue(0, 1, 0));
	SimulationManager::getSingleton()->getDebugDrawer().drawSphere(
		childLimbCOM + localChildAnchorInRefChild, 0.1,
		Ogre::ColourValue(0, 1, 0));

	// draw line from limb A to limb B (WHITE LINE)
	SimulationManager::getSingleton()->getDebugDrawer().drawLine(childLimbCOM,
		parentLimbCOM, Ogre::ColourValue(1, 1, 1));
#endif

	// set global center of mass of child limb as the new generation point for generation
	generator->setPosition(childLimbCOM);
	generator->setOrientation(
		generator->getOrientation()
			* Ogre::Quaternion(childMorphogene->getOrientationW(),
				childMorphogene->getOrientationX(),
				childMorphogene->getOrientationY(),
				childMorphogene->getOrientationZ()));

}

FSLimbModel* FSEmbryogenesis::createLimb(PhenotypeGenerator* generator,
	Morphogene* childMorphogene, FSPhenomeModel* phenomeModel) {
	double sizeX =
		(generator->getCurrentShrinkageFactor() * childMorphogene->getX()
			< MorphologyConfiguration::LIMB_MIN_SIZE) ?
			MorphologyConfiguration::LIMB_MIN_SIZE :
		(generator->getCurrentShrinkageFactor() * childMorphogene->getX()
			> MorphologyConfiguration::LIMB_MAX_SIZE) ?
			MorphologyConfiguration::LIMB_MAX_SIZE :
			generator->getCurrentShrinkageFactor() * childMorphogene->getX();

	double sizeY =
		(generator->getCurrentShrinkageFactor() * childMorphogene->getY()
			< MorphologyConfiguration::LIMB_MIN_SIZE) ?
			MorphologyConfiguration::LIMB_MIN_SIZE :
		(generator->getCurrentShrinkageFactor() * childMorphogene->getY()
			> MorphologyConfiguration::LIMB_MAX_SIZE) ?
			MorphologyConfiguration::LIMB_MAX_SIZE :
			generator->getCurrentShrinkageFactor() * childMorphogene->getY();

	double sizeZ =
		(generator->getCurrentShrinkageFactor() * childMorphogene->getZ()
			< MorphologyConfiguration::LIMB_MIN_SIZE) ?
			MorphologyConfiguration::LIMB_MIN_SIZE :
		(generator->getCurrentShrinkageFactor() * childMorphogene->getZ()
			> MorphologyConfiguration::LIMB_MAX_SIZE) ?
			MorphologyConfiguration::LIMB_MAX_SIZE :
			generator->getCurrentShrinkageFactor() * childMorphogene->getZ();

	//build the limb out of the morphogene
	FSLimbModel* childLimb = new FSLimbModel(
		phenomeModel->getCreatureModel()->getWorld(),
		phenomeModel->getCreatureModel(), childMorphogene->getPrimitiveType(),
		generator->getPosition(), generator->getOrientation(),
		Ogre::Vector3(
			generator->getPosition()
				- phenomeModel->getCreatureModel()->getPosition()),
		generator->getOrientation(),
		/*size*/
		Ogre::Vector3(sizeX, sizeY, sizeZ),
		/*mass*/
		sizeX * sizeY * sizeZ,
		//log2(sizeX * sizeY * sizeZ)/log2(PhysicsConfiguration::WEIGHT_SCALE_SHRINK_LOGBASE),
		childMorphogene->getRestitution(), childMorphogene->getFriction(),
		Ogre::ColourValue(childMorphogene->getColorR(),
			childMorphogene->getColorB(), childMorphogene->getColorG()),
		childMorphogene->isIntraBodyColliding(),
		phenomeModel->getLimbModels().size());

	childLimb->initialize();

	std::cout << "Limb: " << phenomeModel->getLimbModels().size() << std::endl;
	phenomeModel->getLimbModels().push_back(childLimb);
	phenomeModel->getComponentModels().push_back(childLimb);

	return childLimb;
}

void FSEmbryogenesis::appendToParentLimb(FSPhenomeModel* phenomeModel,
	FSLimbModel* childLimb, PhenotypeGenerator* generator,
	Ogre::Vector3& localParentJointInRefParent,
	Ogre::Vector3& localChildJointInRefChild, btTransform& parentHitTransform,
	btTransform& childHitTransform) {

	//PARENT
	//get the morphogene branch that defines the joint and connects the limbs
	MorphogeneBranch* parentMorphogeneBranch =
		((MorphogeneBranch*) generator->getGeneBranch());

	// get parent limb
	FSLimbModel* parentLimb =
		(FSLimbModel*) generator->getParentComponentModel();

	// transformation from the parent limb and child limb center of mass to the joint in the respective reference frames
	btTransform localParentJointTransform, localChildJointTransform;
	localParentJointTransform.setIdentity();
	localChildJointTransform.setIdentity();

	// define the position and direction of the joint in the reference frame of the parent
	localParentJointTransform.setOrigin(
		OgreBulletUtils::convert(localParentJointInRefParent));
	localParentJointTransform.getBasis().setRotation(
		parentHitTransform.getRotation());
	//		localParentJointTransform.getBasis().setEulerYPR(
	//				parentMorphogeneBranch->getJointYaw(),
	//				parentMorphogeneBranch->getJointPitch(),
	//				parentMorphogeneBranch->getJointRoll());

	// define the position and direction of the joint in the reference frame of child
	localChildJointTransform.setOrigin(
		OgreBulletUtils::convert(localChildJointInRefChild));
	//set the direction of the joint normals
	localChildJointTransform.getBasis().setRotation(
		childHitTransform.getRotation());
	//correct the direction of the joint by some random rotation
	//		localChildJointTransform.getBasis().setEulerYPR(
	//				childMorphogene->getJointYaw(),
	//				childMorphogene->getJointPitch(),
	//				childMorphogene->getJointRoll());

	//create the joint from the two limbs using limb A, limb B and their joint definitions in the respective reference frames
	FSJointModel* joint = new FSJointModel(
		phenomeModel->getCreatureModel()->getWorld(),
		/*parent limb*/
		((FSLimbBt*) parentLimb->getLimbPhysics())->getRigidBody(),
		/*child limb*/
		((FSLimbBt*) childLimb->getLimbPhysics())->getRigidBody(),
		localParentJointTransform, localChildJointTransform,
		parentLimb->getOwnIndex(), childLimb->getOwnIndex(),
		phenomeModel->getJointModels().size(),
		parentMorphogeneBranch->getJointType(),
		parentMorphogeneBranch->isJointPitchEnabled(),
		parentMorphogeneBranch->isJointYawEnabled(),
		parentMorphogeneBranch->isJointRollEnabled(),
		Ogre::Vector3(parentMorphogeneBranch->getJointPitchAxisX(),
			parentMorphogeneBranch->getJointPitchAxisY(),
			parentMorphogeneBranch->getJointPitchAxisZ()),
		Ogre::Vector3(parentMorphogeneBranch->getJointPitchMinAngle(),
			parentMorphogeneBranch->getJointYawMinAngle(),
			parentMorphogeneBranch->getJointRollMinAngle()),
		Ogre::Vector3(parentMorphogeneBranch->getJointPitchMaxAngle(),
			parentMorphogeneBranch->getJointYawMaxAngle(),
			parentMorphogeneBranch->getJointRollMaxAngle()));

	joint->initialize();

	std::cout << "Joint: Parent: " << joint->getParentIndex() << " /Child: "
		<< joint->getChildIndex() << std::endl;

	parentLimb->addChildJointIndex(joint->getIndex());
	childLimb->setParentJointIndex(joint->getIndex());

	// add the joint to the phenotype joints
	phenomeModel->getJointModels().push_back(joint);
	phenomeModel->getComponentModels().push_back(joint);

	//initialize rotational limit motors
	//TODO: Remove max speed if not necessary
	double mass1 = parentLimb->getMass();
	double mass2 = childLimb->getMass();
	double maxTorque =
		(MorphologyConfiguration::MUSCLE_MAX_TORQUE_LINEAR_CONSTANT
			* (mass1 + mass2)
			+ MorphologyConfiguration::MUSCLE_MAX_TORQUE_SQUARE_CONSTANT
				* pow(mass1 + mass2, 2));
	//		double maxTorque = (15.0f * (mass1 + mass2)
	//			+ 0.01f * pow(mass1 + mass2, 2));

	//		std::cout << mass1 << "," << mass2 << "," << maxTorque << std::endl;
	joint->generateMotors(Ogre::Vector3(maxTorque, maxTorque, maxTorque),
		Ogre::Vector3(parentMorphogeneBranch->getJointPitchMinAngle(),
			parentMorphogeneBranch->getJointYawMinAngle(),
			parentMorphogeneBranch->getJointRollMinAngle()),
		Ogre::Vector3(parentMorphogeneBranch->getJointPitchMaxAngle(),
			parentMorphogeneBranch->getJointYawMaxAngle(),
			parentMorphogeneBranch->getJointRollMaxAngle()));

	//TODO: Quick controller hack
	SineController* controller = new SineController();
	controller->initialize(parentMorphogeneBranch->getJointPitchAmplitude(),
		parentMorphogeneBranch->getJointPitchFrequency(),
		parentMorphogeneBranch->getJointPitchXOffset(),
		parentMorphogeneBranch->getJointPitchYOffset());
	controller->addControlOutput(joint->getMotors()[0]);
	phenomeModel->getControllers().push_back(controller);

	if (joint->getType() == JointPhysics::SPHERICAL_JOINT) {
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
	}
}

void FSEmbryogenesis::createNewGenerators(FSPhenomeModel* phenomeModel,
	Morphogene * childMorphogene, FSLimbModel* childLimb,
	PhenotypeGenerator* generator,
	std::list<PhenotypeGenerator*>& generatorList, int& totalSegmentCounter) {

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
					generator->getRepetitionList(), generator->getPosition(),
					generator->getOrientation(), childLimb, (*branchIt.base()),
					childMorphogene->getSegmentShrinkFactor()
						* generator->getCurrentShrinkageFactor(),
					true != generator->isFlipped() /*Flipped*/, false);

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
					generator->getRepetitionList(), generator->getPosition(),
					generator->getOrientation(), childLimb, (*branchIt.base()),
					childMorphogene->getSegmentShrinkFactor()
						* generator->getCurrentShrinkageFactor(), false,
					true != generator->isMirrored()/*Mirrored*/);

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

btTransform FSEmbryogenesis::getParentIntersection(
	PhenotypeGenerator* generator, FSLimbBt* parentLimb,
	MorphogeneBranch* parentMorphogeneBranch, Ogre::Vector3 parentLimbCOM,
	Ogre::Vector3 localParentAnchorDirInRefParent) {
	//##
	// PARENT LIMB ANCHOR POINT
	//##

	// add parent limb to world
	parentLimb->addToWorld();
	btTransform parentHitTransform = parentLimb->getLocalIntersection(
	/*origin of limb parent*/
	OgreBulletUtils::convert(parentLimbCOM),
	/*direction of anchor of limb parent*/
	OgreBulletUtils::convert(localParentAnchorDirInRefParent));

	// remove parent limb from world
	parentLimb->removeFromWorld();

	return parentHitTransform;
}

btTransform FSEmbryogenesis::getOwnIntersection(FSPhenomeModel* phenomeModel,
	Morphogene* childMorphogene, PhenotypeGenerator* generator,
	Ogre::Vector3 localChildAnchorDirInRefChild) {
	FSLimbBt* childLimbBt = new FSLimbBt(
		phenomeModel->getCreatureModel()->getWorld(),
		NULL, childMorphogene->getPrimitiveType(), generator->getPosition(),
		Ogre::Quaternion(childMorphogene->getOrientationW(),
			childMorphogene->getOrientationX(),
			childMorphogene->getOrientationY(),
			childMorphogene->getOrientationZ()), Ogre::Vector3(),
		Ogre::Quaternion(childMorphogene->getOrientationW(),
			childMorphogene->getOrientationX(),
			childMorphogene->getOrientationY(),
			childMorphogene->getOrientationZ()),
		/*dimensions*/
		Ogre::Vector3(
			generator->getCurrentShrinkageFactor() * childMorphogene->getX(),
			generator->getCurrentShrinkageFactor() * childMorphogene->getY(),
			generator->getCurrentShrinkageFactor() * childMorphogene->getZ()),
		/*mass*/
		generator->getCurrentShrinkageFactor() * childMorphogene->getX()
			* generator->getCurrentShrinkageFactor() * childMorphogene->getY()
			* generator->getCurrentShrinkageFactor() * childMorphogene->getZ(),
		childMorphogene->getRestitution(), childMorphogene->getFriction(),
		Ogre::ColourValue(0, 0, 0), false);

	childLimbBt->initialize();

	// add child limb to world
	childLimbBt->addToWorld();

	btTransform childHitTransform = childLimbBt->getLocalIntersection(
	/*origin of child limb*/
	OgreBulletUtils::convert(generator->getPosition()),
	/*direction of anchor of child limb*/
	OgreBulletUtils::convert(localChildAnchorDirInRefChild));

	// remove child limb from world
	childLimbBt->removeFromWorld();

	delete childLimbBt;
	childLimbBt = NULL;
	return childHitTransform;
}
