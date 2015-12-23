//# corresponding headers
#include <model/universe/evolution/population/creature/phenome/SRBPhenomeModel.hpp>

//# forward declarations
//# system headers
#include <cmath>
#include <list>
#include <map>

//## controller headers
//## model headers
#include <BulletDynamics/Dynamics/btDynamicsWorld.h>
#include <BulletDynamics/Dynamics/btRigidBody.h>
#include <LinearMath/btTransform.h>
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
#include <model/universe/evolution/population/creature/genome/controller/ChaoticControllerGene.hpp>
#include <model/universe/evolution/population/creature/genome/controller/ControllerGene.hpp>
#include <model/universe/evolution/population/creature/genome/controller/SineControllerGene.hpp>
#include <model/universe/evolution/population/creature/genome/genetics/BaseGenerator.hpp>
#include <model/universe/evolution/population/creature/genome/genetics/Embryogenesis.hpp>
#include <model/universe/evolution/population/creature/genome/Genome.hpp>
#include <model/universe/evolution/population/creature/genome/morphology/Morphogene.hpp>
#include <model/universe/evolution/population/creature/genome/morphology/MorphogeneBranch.hpp>
#include <model/universe/evolution/population/creature/phenome/controller/chaotic/ChaoticController.hpp>
#include <model/universe/evolution/population/creature/phenome/controller/sine/SineController.hpp>
#include <model/universe/evolution/population/creature/phenome/ComponentModel.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/effector/motor/SRBServoMotor.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/joint/SRBJointModel.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/limb/FSLimbBt.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/limb/SRBLimbBt.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/limb/SRBLimbModel.hpp>
#include <model/universe/evolution/population/creature/phenome/SRBPhenomeModel.hpp>

//## view headers
#include <view/visualization/bulletphysics/OgreBtDebugDrawer.hpp>

//## utils headers
#include <utils/MathUtils.hpp>
#include <utils/ogre3D/OgreBulletUtils.hpp>

BoostLogger SRBPhenomeModel::mBoostLogger; /*<! initialize the boost logger*/
SRBPhenomeModel::_Init SRBPhenomeModel::_initializer;
SRBPhenomeModel::SRBPhenomeModel() :
	mWorld(NULL) {
}

SRBPhenomeModel::SRBPhenomeModel(CreatureModel* const creatureModel) {
	mCreatureModel = creatureModel;
	mWorld = creatureModel->getWorld();
}

SRBPhenomeModel::SRBPhenomeModel(const SRBPhenomeModel& SRBPhenomeModel) {
	mInWorld = SRBPhenomeModel.mInWorld;
	mCreatureModel = SRBPhenomeModel.mCreatureModel;
	mDeveloped = SRBPhenomeModel.mDeveloped;
	mHasInterpenetrations = SRBPhenomeModel.mHasInterpenetrations;

	mWorld = SRBPhenomeModel.mWorld;

	for (std::vector<Controller*>::const_iterator cit =
		SRBPhenomeModel.mControllers.begin();
		cit != SRBPhenomeModel.mControllers.end(); cit++) {
		mControllers.push_back((*cit)->clone());
	}

	for (std::vector<ComponentModel*>::const_iterator coit =
		SRBPhenomeModel.mComponentModels.begin();
		coit != SRBPhenomeModel.mComponentModels.end(); coit++) {
		ComponentModel* componentModel = (*coit)->clone();
		mComponentModels.push_back(componentModel);
		switch (componentModel->getComponentType()) {
		case ComponentModel::LimbComponent:
			mLimbModels.push_back((LimbModel*) componentModel);
			break;
		case ComponentModel::JointComponent:
			mJointModels.push_back((JointModel*) componentModel);
			break;

		}
	}
}

SRBPhenomeModel::~SRBPhenomeModel() {
	mWorld = NULL;
}

void SRBPhenomeModel::initialize() {

	performEmbryogenesis(); /**!< Perform embryogenesis to build a body plan*/

	//initialize the limb models if it did not already happen in embryogenesis
	for (std::vector<LimbModel*>::iterator lit = mLimbModels.begin();
		lit != mLimbModels.end(); lit++) {
		(*lit)->setWorld(getWorld());
		(*lit)->initialize();
	}

	if (!mBodyGenerated) {
		generateBody(); /**!< Build the body from the body plan */

		collectControlInputs(); /**!< Collect the control inputs to wire the controller */

		collectControlOutputs(); /**!< Collect the control outputs to wire the controller */

		wireController(); /**!< Wire the controller */

		storeControlIndices(); /**!< Store the control indices for serialization */
	}

}

void SRBPhenomeModel::update(const double timeSinceLastTick) {
	//update all controllers
	for (std::vector<Controller*>::iterator cit = mControllers.begin();
		cit != mControllers.end(); cit++) {
		(*cit)->perform(timeSinceLastTick);
	}

	// Update all limb models
	mHasInterpenetrations = false;
	for (std::vector<LimbModel*>::iterator lit = mLimbModels.begin();
		lit != mLimbModels.end(); lit++) {

		//detect interpenetrations
		if ((*lit)->getInterpenetrationDepth() < 0 && !mHasInterpenetrations) {

			mHasInterpenetrations = true;
			break;
		}
		(*lit)->setInterpenetrationDepth(0);
	}

}

void SRBPhenomeModel::calm() {
	for (std::vector<LimbModel*>::iterator lit = mLimbModels.begin();
		lit != mLimbModels.end(); lit++) {
		(*lit)->calm();
	}
}

int SRBPhenomeModel::performEmbryogenesis() {
	int totalSegmentCounter = 0;
	if (!mDeveloped) {
		BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "--Perform an embryogenesis";
		cleanup();
		mBodyGenerated = false;
		std::list<PhenotypeGenerator*> generatorList;

		// get the root gene from the genome
		Gene* gene =
		mCreatureModel->getGenotype().getGenes()[mCreatureModel->getGenotype().getRootIndex()];

		//create a phenotype generator and initialize it with the starting point of the creation of the creature
		PhenotypeGenerator* rootGenerator = new PhenotypeGenerator();
		std::map<int, int> repList;
		rootGenerator->initialize(repList, mCreatureModel->getInitialPosition(),
			Ogre::Quaternion::IDENTITY, NULL, NULL, 1);
		rootGenerator->getRepetitionList()[mCreatureModel->getGenotype().getRootIndex()] = 0; // add another of this branching morphogene type
		rootGenerator->setGene(gene);
		rootGenerator->setRoot2LeafPath(0);
		generatorList.push_back(rootGenerator);

		while (!generatorList.empty()) { // this loop creates the creature up to the point at which we reach the correct root-to-leaf path length

			BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Phenome generator qty:" << generatorList.size();

			PhenotypeGenerator* generator = generatorList.front();// get next generator in list
			generatorList.pop_front();// remove it from the list

			Embryogenesis::transcribeGene(generatorList, totalSegmentCounter,
				this, generator);// transcribe the gene

			delete generator;// delete the generator
		}

		mDeveloped = true; // set the creature to developed
	} else {
		mComponentModels.clear();
		for (std::vector<LimbModel*>::const_iterator it = mLimbModels.begin();
			it != mLimbModels.end(); it++) {
			mComponentModels.push_back((*it));
		}

		for (std::vector<JointModel*>::const_iterator it = mJointModels.begin();
			it != mJointModels.end(); it++) {
			mComponentModels.push_back((*it));
		}
	}
	return totalSegmentCounter;
}

void SRBPhenomeModel::calculateChildPositionRelativeToParent(
	PhenotypeGenerator* generator, /**!< The generator of the child limb*/
	btTransform& parentJointAnchor,/**!< The joint anchor on the parent limb surface*/
	btTransform& childJointAnchor,/**!< joint anchor on the child limb surface*/
	Morphogene* childMorphogene,/**!< The morphogene to build the child limb*/
	Ogre::Vector3& jointPivotInW/**!< The joint pivot in the world ref.*/) {

	//prepare parent side
	MorphogeneBranch* parentMorphogeneBranch =
		((MorphogeneBranch*) generator->getGeneBranch()); //get the morphogene branch that defines the joint connecting the limbs

	SRBLimbBt* parentLimb =
		((SRBLimbBt*) ((SRBLimbModel*) generator->getParentComponentModel())->getLimbPhysics()); // get the parent limb model

	Ogre::Vector3 parentLimbCOM = OgreBulletUtils::convert(
		parentLimb->getPosition()); // get the parent limb's center of mass position

	Ogre::Vector3 parentAnchorDirInParent = Ogre::Vector3(
		parentMorphogeneBranch->getJointAnchorX(),
		parentMorphogeneBranch->getJointAnchorY(),
		parentMorphogeneBranch->getJointAnchorZ()); // get parent joint's anchor direction

	Ogre::Vector3 childAnchorDirInChild(childMorphogene->getJointAnchorX(),
		childMorphogene->getJointAnchorY(), childMorphogene->getJointAnchorZ()); // get anchor direction of limb child in the local reference frame of child

	//if the generator is the mirrored version of another generator
	//mirrored is: -O  -> O- | \O -> O\   mirroring = sign inversion
	if (generator->isMirrored()) {
		parentAnchorDirInParent = -parentAnchorDirInParent; //get mirrored direction
		childAnchorDirInChild = -childAnchorDirInChild; // get mirrored direction
		generator->setOrientation(generator->getOrientation().Inverse());
	}

	//if the generator is the flipped version of another generator
	//flipped is: \O -> O/ and the flipping axis is the parent limb direction
	if (generator->isFlipped()) {
		Ogre::Vector3 parentLimbDir(1, 0, 0); // get direction vector of parent limb
		parentLimbDir = OgreBulletUtils::convert(parentLimb->getOrientation())
			* parentLimbDir;

		//reflect on the direction vector
		parentAnchorDirInParent = -parentAnchorDirInParent
			- 2 * ((-parentAnchorDirInParent).dotProduct(parentLimbDir))
				* parentLimbDir;

		childAnchorDirInChild = -childAnchorDirInChild
			- 2 * ((-childAnchorDirInChild).dotProduct(parentLimbDir))
				* parentLimbDir;

		// get rotation axis
		Ogre::Vector3 rotationAxis(generator->getOrientation().x,
			generator->getOrientation().y, generator->getOrientation().z);

		// reflect on the direction vector
		rotationAxis = -rotationAxis
			- 2 * ((-rotationAxis).dotProduct(parentLimbDir)) * parentLimbDir;

		// set new orientation
		generator->setOrientation(
			Ogre::Quaternion(-generator->getOrientation().w, rotationAxis.x,
				rotationAxis.y, rotationAxis.z));
	}

	parentAnchorDirInParent = generator->getOrientation()
		* parentAnchorDirInParent; // Rotate the parent anchor in the direction of the current orientation

	//PARENT JOINT ANCHOR
	//TODO: What to do with the surface normal?
	jointPivotInW =
		OgreBulletUtils::convert(
			getParentIntersectionInW(parentLimb, // get anchor direction of the parent limb in reference frame of itself
				parentMorphogeneBranch, parentLimbCOM, parentAnchorDirInParent).getOrigin());

	parentJointAnchor.setOrigin(
		OgreBulletUtils::convert(jointPivotInW - parentLimbCOM)); // Set the joint anchor in the parent reference frame

	Ogre::Vector3 parentAnchorInParent(
		OgreBulletUtils::convert(parentJointAnchor.getOrigin())); // get surface point of the parent limb in reference frame of itself

	// PARENT JOINT POSITION
	Ogre::Vector3 parentJointPivotInParent = parentAnchorInParent; //get local joint rotation point in reference frame parent

	// CHILD LIMB ANCHOR POINT IN PARENT REFERENCE FRAME
	Ogre::Vector3 childAnchorInParent(parentJointPivotInParent); //get local surface anchor point of child in reference frame parent

	Ogre::Quaternion childLimbOrientation(childMorphogene->getOrientationW(),
		childMorphogene->getOrientationX(), childMorphogene->getOrientationY(),
		childMorphogene->getOrientationZ());

	if (!MathUtils::isFinite(childLimbOrientation)) {
		BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::fatal)<< " NaN/Inf detected in childLimb orientation: " << childLimbOrientation;
	}

	childAnchorDirInChild = childLimbOrientation * childAnchorDirInChild; // Rotate the child anchor in the direction of its own limb's rotation and additionally when it is flipped/mirrored

	// CHILD LIMB ANCHOR POINT IN CHILD REFERENCE FRAME
	childJointAnchor = getOwnIntersection(childMorphogene, generator,
		childAnchorDirInChild); // find the joint anchor position of the limb by positioning the limb at an arbitrary position to cast a ray

	Ogre::Vector3 childAnchorInChild(
		OgreBulletUtils::convert(childJointAnchor.getOrigin())); // get the surface point of child limb in the global reference frame

	Ogre::Vector3 childJointPivotInChild = childAnchorInChild; // get local joint rotation point in reference frame child

	Ogre::Vector3 childLimbCOM(jointPivotInW - childAnchorInChild); // global center of mass of child limb

#ifndef EXCLUDE_FROM_TEST
	// mark the three important points of the joint
	SimulationManager::getSingleton()->getDebugDrawer().drawSphere(
		parentLimbCOM, 0.1, Ogre::ColourValue(0, 1, 0));

	SimulationManager::getSingleton()->getDebugDrawer().drawSphere(
		jointPivotInW, 0.1, Ogre::ColourValue(0, 1, 0));

	SimulationManager::getSingleton()->getDebugDrawer().drawSphere(childLimbCOM,
		0.1, Ogre::ColourValue(0, 1, 0));

	// draw line from limb A to surface anchor point of A (GREEN LINE)
	SimulationManager::getSingleton()->getDebugDrawer().drawLine(parentLimbCOM,
		jointPivotInW, Ogre::ColourValue(0, 1, 0));

	// draw line from joint rotation point to surface anchor point of B (BLUE LINE)
	SimulationManager::getSingleton()->getDebugDrawer().drawLine(jointPivotInW,
		parentLimbCOM + childAnchorInParent, Ogre::ColourValue(0, 0, 1));

	// draw line from limb B to anchor point of B (GREEN LINE)
	SimulationManager::getSingleton()->getDebugDrawer().drawLine(childLimbCOM,
		childLimbCOM + childAnchorInChild, Ogre::ColourValue(0, 1, 0));

#endif

	generator->setPosition(childLimbCOM); // set global center of mass of child limb as the new generation point for generation
}

LimbModel* SRBPhenomeModel::createLimb(PhenotypeGenerator* generator,
	Morphogene* childMorphogene) {
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

	if (!MathUtils::isFinite(generator->getOrientation())) {
		BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::fatal)<< " NaN/Inf detected in generator orientation: " << generator->getOrientation();
	}

	if (!MathUtils::isFinite(generator->getPosition())) {
		BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::fatal)<< " NaN/Inf detected in generator position: " << generator->getPosition();
	}

	//build the limb out of the morphogene
	SRBLimbModel* childLimb = new SRBLimbModel(getCreatureModel()->getWorld(),
		getCreatureModel(), childMorphogene->getPrimitiveType(),
		generator->getPosition(), generator->getOrientation(),
		Ogre::Vector3(
			generator->getPosition() - getCreatureModel()->getPosition()),
		generator->getOrientation(),
		/*size*/
		Ogre::Vector3(sizeX, sizeY, sizeZ),
		/*mass*/
		sizeX * sizeY * sizeZ, childMorphogene->getRestitution(),
		childMorphogene->getFriction(),
		Ogre::ColourValue(childMorphogene->getColorR(),
			childMorphogene->getColorB(), childMorphogene->getColorG()),
		childMorphogene->isIntraBodyColliding(), getLimbModels().size());

	childLimb->initialize();

	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Limb: " << getLimbModels().size();
	getLimbModels().push_back(childLimb);
	getComponentModels().push_back(childLimb);

	return childLimb;
}

void SRBPhenomeModel::appendToParentLimb(LimbModel* childLimb,
	PhenotypeGenerator* generator, Ogre::Vector3& jointPivotInW,
	btTransform& parentHitTransform, btTransform& childHitTransform) {

	//PARENT
	//get the morphogene branch that defines the joint and connects the limbs
	MorphogeneBranch* parentMorphogeneBranch =
		((MorphogeneBranch*) generator->getGeneBranch());

	// get parent limb
	SRBLimbModel* parentLimb =
		(SRBLimbModel*) generator->getParentComponentModel();

	//create the joint from the two limbs using limb A, limb B and their joint definitions in the respective reference frames
	SRBJointModel* joint = new SRBJointModel(getCreatureModel()->getWorld(),
	/*parent limb*/
	parentLimb,
	/*child limb*/
	(SRBLimbModel*) childLimb, jointPivotInW, parentLimb->getOwnIndex(),
		childLimb->getOwnIndex(), getJointModels().size(),
		parentMorphogeneBranch->getJointType(),
		Ogre::Vector3(parentMorphogeneBranch->getJointPitchAxisX(),
			parentMorphogeneBranch->getJointPitchAxisY(),
			parentMorphogeneBranch->getJointPitchAxisZ()),
		Ogre::Vector3(parentMorphogeneBranch->getJointYawAxisX(),
			parentMorphogeneBranch->getJointYawAxisY(),
			parentMorphogeneBranch->getJointYawAxisZ()),
		Ogre::Vector3(parentMorphogeneBranch->getJointRollMinAngle(),
			parentMorphogeneBranch->getJointPitchMinAngle(),
			parentMorphogeneBranch->getJointYawMinAngle()),
		Ogre::Vector3(parentMorphogeneBranch->getJointRollMaxAngle(),
			parentMorphogeneBranch->getJointPitchMaxAngle(),
			parentMorphogeneBranch->getJointYawMaxAngle()));

	joint->setAngularStiffness(/**!< Set spring stiffness for the joint*/
	parentMorphogeneBranch->getPitchStiffnessCoefficient(),
		parentMorphogeneBranch->getYawStiffnessCoefficient(),
		parentMorphogeneBranch->getRollStiffnessCoefficient());

	joint->setAngularDamping( /**!< Set the damping coefficients for the joint */
	parentMorphogeneBranch->getPitchDampingCoefficient(),
		parentMorphogeneBranch->getYawDampingCoefficient(),
		parentMorphogeneBranch->getRollDampingCoefficient());

	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Joint: Parent: " << joint->getParentIndex() << " /Child: "
	<< joint->getChildIndex();

	parentLimb->addChildJointIndex(joint->getIndex());
	childLimb->setParentJointIndex(joint->getIndex());

	// add the joint to the phenotype joints
	getJointModels().push_back(joint);
	getComponentModels().push_back(joint);

	//initialize rotational limit motors
	double mass1 = parentLimb->getMass();
	double mass2 = childLimb->getMass();
	//TODO: Fix the force curve
	double maxTorque =
		MorphologyConfiguration::MUSCLE_MAX_TORQUE_LINEAR_CONSTANT
			* (mass1 * mass2)
			+ MorphologyConfiguration::MUSCLE_MAX_TORQUE_SQUARE_CONSTANT
				* pow(mass1 * mass2, 2);

	//TODO: Make position controlled defined in the settings
	joint->generateMotors(Ogre::Vector3(maxTorque, maxTorque, maxTorque),
		Ogre::Vector3(parentMorphogeneBranch->getJointPitchMinAngle(),
			parentMorphogeneBranch->getJointYawMinAngle(),
			parentMorphogeneBranch->getJointRollMinAngle()),
		Ogre::Vector3(parentMorphogeneBranch->getJointPitchMaxAngle(),
			parentMorphogeneBranch->getJointYawMaxAngle(),
			parentMorphogeneBranch->getJointRollMaxAngle()), false);

	// add controllers
	for (int i = 0; i < joint->getMotors().size(); i++) {
		switch (parentMorphogeneBranch->getControllerGenes()[i]->getControllerType()) {
		case ControllerGene::SineControllerGene: {
			SineController* controller =
				new SineController(
					((SineControllerGene*) parentMorphogeneBranch->getControllerGenes()[i])->getAmplitude(),
					((SineControllerGene*) parentMorphogeneBranch->getControllerGenes()[i])->getFrequency(),
					((SineControllerGene*) parentMorphogeneBranch->getControllerGenes()[i])->getXOffset(),
					((SineControllerGene*) parentMorphogeneBranch->getControllerGenes()[i])->getYOffset());
			controller->initialize();
			controller->addControlOutput(joint->getMotors()[i]);
			getControllers().push_back(controller);
			break;
		}
		case ControllerGene::ChaoticControllerGene: {
			ChaoticControllerGene* chaoticControllerGene =
				((ChaoticControllerGene*) parentMorphogeneBranch->getControllerGenes()[i]);
			ChaoticController* controller = new ChaoticController(
				chaoticControllerGene->getSystemType(),
				chaoticControllerGene->getInitialX(),
				chaoticControllerGene->getInitialY(),
				chaoticControllerGene->getInitialZ(),
				chaoticControllerGene->getSpeed());

			controller->initialize();

			controller->addControlInput(joint->getAngleceptors()[0]); // Add the first angleceptor as input
			controller->addControlInput(joint->getVelocityceptors()[0]); // add the first velocityceptor as input
			controller->addControlOutput(joint->getMotors()[i]);
			getControllers().push_back(controller);
		}
		}
	}
}

btTransform SRBPhenomeModel::getParentIntersectionInW(LimbPhysics* parentLimb,
	MorphogeneBranch* parentMorphogeneBranch, Ogre::Vector3 parentLimbCOM,
	Ogre::Vector3 parentAnchorDirInParent) {

	((SRBLimbBt*) parentLimb)->addToWorld(); // add parent limb to world

	btTransform parentHitLocation =
		parentLimb->getIntersection(
			OgreBulletUtils::convert(
				parentLimbCOM) /**!< origin of limb parent*/,
			OgreBulletUtils::convert(
				parentAnchorDirInParent) /**!< direction of anchor of limb parent*/);

	((SRBLimbBt*) parentLimb)->removeFromWorld(); // remove parent limb from world

	return parentHitLocation;
}

btTransform SRBPhenomeModel::getOwnIntersection(Morphogene* childMorphogene,
	PhenotypeGenerator* generator,
	Ogre::Vector3 localChildAnchorDirInRefChild) {

	Ogre::Quaternion childLimbRotation(childMorphogene->getOrientationW(),
		childMorphogene->getOrientationX(), childMorphogene->getOrientationY(),
		childMorphogene->getOrientationZ());

	FSLimbBt* childLimbBt = new FSLimbBt(getCreatureModel()->getWorld(),
	NULL, childMorphogene->getPrimitiveType(), generator->getPosition(),
		generator->getOrientation() * childLimbRotation, Ogre::Vector3(),
		Ogre::Quaternion(),
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
		OgreBulletUtils::convert(
			generator->getOrientation() * localChildAnchorDirInRefChild));

	// remove child limb from world
	childLimbBt->removeFromWorld();

	delete childLimbBt;
	childLimbBt = NULL;
	return childHitTransform;
}

void SRBPhenomeModel::generateBody() {
	bool isFixedBase = false;
	bool setDamping = false;
	bool gyro = false;
	bool canSleep = false;

	if (mBodyGenerated) {
		return;
	}

	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "--Generate the body";

	if (mJointModels.size() != 0) {

		for (int i = 0; i < mJointModels.size(); i++) {

			((SRBJointModel*) mJointModels[i])->setBodyA(
				((SRBLimbModel*) mLimbModels[((long) mJointModels[i]->getParentIndex())])->getRigidBody());

			((SRBJointModel*) mJointModels[i])->setFrameInA(
				mJointModels[i]->getParentComToPivot());

			((SRBJointModel*) mJointModels[i])->setBodyB(
				((SRBLimbModel*) mLimbModels[((long) mJointModels[i]->getChildIndex())])->getRigidBody());

			((SRBJointModel*) mJointModels[i])->setFrameInB(
				mJointModels[i]->getPivotToChildCom());

			BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Joint: Parent: " << mJointModels[i]->getParentIndex() << " /Child: "
			<< mJointModels[i]->getChildIndex();

			((SRBJointModel*) mJointModels[i])->setWorld(getWorld());

//			if (!setDamping) {
//				mJointModels[i]->setLinearDamping(0.f,0.f,0.f);
//				mJointModels[i]->setAngularDamping(0.f, 0.f, 0.f);
//			} else {
//				mJointModels[i]->setLinearDamping(0.1f,0.1f,0.1f);
//				mJointModels[i]->setAngularDamping(0.9f, 0.9f, 0.9f);
//			}

			mJointModels[i]->initialize();

			for (std::vector<Motor*>::iterator mit =
				mJointModels[i]->getMotors().begin();
				mit != mJointModels[i]->getMotors().end(); mit++) {
				((SRBServoMotor*) (*mit))->instantiate(
					mJointModels[i]->getJointPhysics(),
					mJointModels[i]->getIndex());
			}
		}
	}
}

void SRBPhenomeModel::reset(const Ogre::Vector3 position) {
	/**The vector of limb models.*/
	for (std::vector<LimbModel*>::const_iterator it = mLimbModels.begin();
		it != mLimbModels.end(); it++) {
		(*it)->reset(position);
	}
}

void SRBPhenomeModel::cleanup() {
	for (std::vector<ComponentModel*>::iterator cit = mComponentModels.begin();
		cit != mComponentModels.end();) {
		delete *cit;
		cit = mComponentModels.erase(cit);
	}
	mLimbModels.clear();
	mJointModels.clear();
}

void SRBPhenomeModel::reposition(const Ogre::Vector3 position) {
	/**The vector of limb models.*/
	for (std::vector<LimbModel*>::const_iterator it = mLimbModels.begin();
		it != mLimbModels.end(); it++) {
		(*it)->reposition(position);

	}
}

bool SRBPhenomeModel::equals(const SRBPhenomeModel& phenomeModel) const {
	if (mInWorld != phenomeModel.mInWorld) {
		return false;
	}

	if (mDeveloped != phenomeModel.mDeveloped) {
		return false;
	}

	/**The vector of limb models.*/
	if (mLimbModels.size() != phenomeModel.mLimbModels.size()) {
		return false;
	}
	std::vector<LimbModel*>::const_iterator it = mLimbModels.begin();
	std::vector<LimbModel*>::const_iterator it2 =
		phenomeModel.mLimbModels.begin();
	for (; it != mLimbModels.end(), it2 != phenomeModel.mLimbModels.end();
		it++, it2++) {
		if (!(*it)->equals(**(it2))) {
			return false;
		}
	}

	/**The vector of joint models.*/
	if (mJointModels.size() != phenomeModel.mJointModels.size()) {
		return false;
	}
	std::vector<JointModel*>::const_iterator it3 = mJointModels.begin();
	std::vector<JointModel*>::const_iterator it4 =
		phenomeModel.mJointModels.begin();
	for (; it3 != mJointModels.end(), it4 != phenomeModel.mJointModels.end();
		it3++, it4++) {
		if (!(*it3)->equals(**(it4))) {
			return false;
		}
	}

	/**The vector of controllers.*/
	if (mControllers.size() != phenomeModel.mControllers.size()) {
		return false;
	}
	std::vector<Controller*>::const_iterator it5 = mControllers.begin();
	std::vector<Controller*>::const_iterator it6 =
		phenomeModel.mControllers.begin();
	for (; it5 != mControllers.end(), it6 != phenomeModel.mControllers.end();
		it5++, it6++) {
		if (!(*it5)->equals(**(it6))) {
			return false;
		}
	}
	return true;
}

void SRBPhenomeModel::addToWorld() {
	if (!isInWorld()) {

	}
}

void SRBPhenomeModel::removeFromWorld() {
	if (isInWorld()) {

	}
}

PhenomeModel* SRBPhenomeModel::clone() {
	return new SRBPhenomeModel(*this);
}

btDynamicsWorld* SRBPhenomeModel::getWorld() {
	if (!mWorld) {
#ifndef EXCLUDE_FROM_TEST
		mWorld = (btDynamicsWorld*) mCreatureModel->getWorld();
#endif
	}
	return mWorld;

}
