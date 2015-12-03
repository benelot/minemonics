//# corresponding headers
#include <model/universe/evolution/population/creature/phenome/FSPhenomeModel.hpp>

//# forward declarations
//# system headers
#include <list>
#include <map>

//## controller headers
//## model headers
#include <BulletDynamics/Dynamics/btRigidBody.h>
#include <BulletDynamics/Featherstone/btMultiBodyJointLimitConstraint.h>
#include <BulletDynamics/Featherstone/btMultiBodyLink.h>
#include <LinearMath/btAlignedObjectArray.h>
#include <LinearMath/btQuadWord.h>
#include <LinearMath/btQuaternion.h>
#include <LinearMath/btScalar.h>
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
#include <model/universe/environments/EnvironmentModel.hpp>
#include <model/universe/environments/physics/PhysicsController.hpp>
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
#include <model/universe/evolution/population/creature/phenome/ComponentModel.hpp>
#include <model/universe/evolution/population/creature/phenome/FSPhenomeModel.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/effector/motor/FSServoMotor.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/joint/FSJointBt.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/joint/FSJointModel.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/joint/JointModel.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/joint/JointPhysics.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/limb/FSLimbBt.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/limb/FSLimbModel.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/limb/LimbModel.hpp>
#include <model/universe/evolution/population/PopulationModel.hpp>
#include <model/universe/PlanetModel.hpp>

//## view headers
#include <view/visualization/bulletphysics/OgreBtDebugDrawer.hpp>

//## utils headers
#include <utils/ogre3D/OgreBulletUtils.hpp>
#include <utils/MathUtils.hpp>

BoostLogger FSPhenomeModel::mBoostLogger; /*<! initialize the boost logger*/
FSPhenomeModel::_Init FSPhenomeModel::_initializer;
FSPhenomeModel::FSPhenomeModel() :
	mMultiBody(NULL), mWorld(NULL) {
}

FSPhenomeModel::FSPhenomeModel(CreatureModel* const creatureModel) :
	PhenomeModel(creatureModel), mMultiBody(NULL), mWorld(NULL) {

	//set the dynamics world for the phenome model
#ifndef EXCLUDE_FROM_TEST
	mWorld =
		(btMultiBodyDynamicsWorld*) mCreatureModel->getPopulationModel()->getPlanetModel()->getEnvironmentModel()->getPhysicsController()->getDynamicsWorld();
#endif
	mControllers.clear();
}

FSPhenomeModel::FSPhenomeModel(const FSPhenomeModel& phenomeModel) {
	mInWorld = phenomeModel.mInWorld;
	mCreatureModel = phenomeModel.mCreatureModel;
	mDeveloped = phenomeModel.mDeveloped;
	mHasInterpenetrations = phenomeModel.mHasInterpenetrations;
	mMultiBody = phenomeModel.mMultiBody;
	mWorld = phenomeModel.mWorld;
	for (std::vector<Controller*>::const_iterator cit =
		phenomeModel.mControllers.begin();
		cit != phenomeModel.mControllers.end(); cit++) {
		mControllers.push_back((*cit)->clone());
	}

	for (std::vector<ComponentModel*>::const_iterator coit =
		phenomeModel.mComponentModels.begin();
		coit != phenomeModel.mComponentModels.end(); coit++) {
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

FSPhenomeModel::~FSPhenomeModel() {
	delete mMultiBody;
	mMultiBody = NULL;

	mWorld = NULL;

	while (!mLimitConstraints.empty()) {
		delete mLimitConstraints.back();
		mLimitConstraints.pop_back();
	}
}

void FSPhenomeModel::initialize() {

	performEmbryogenesis(); /**!< Perform embryogenesis to build a body plan*/

	//initialize the limb models if it did not already happen in embryogenesis
	for (std::vector<LimbModel*>::iterator lit = mLimbModels.begin();
		lit != mLimbModels.end(); lit++) {
		(*lit)->setWorld(getWorld());
		(*lit)->initialize();
	}

	generateBody(); /**!< Build the body from the body plan */

	collectControlInputs(); /**!< Collect the control inputs to wire the controller */

	collectControlOutputs(); /**!< Collect the control outputs to wire the controller */

	addJointConstraints(); /**!< Add the joint constraints */

}

void FSPhenomeModel::update(const double timeSinceLastTick) {
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

void FSPhenomeModel::addToWorld() {
	if (!isInWorld()) {
		if (mMultiBody != NULL) {
			getWorld()->addMultiBody(mMultiBody);
		}
	}
}

void FSPhenomeModel::removeFromWorld() {
	if (isInWorld()) {
		if (mMultiBody != NULL) {
			getWorld()->removeMultiBody(mMultiBody);
		}
	}
}

void FSPhenomeModel::calm() {

	if (mMultiBody) {
		mMultiBody->clearConstraintForces();
		mMultiBody->clearForcesAndTorques();
		mMultiBody->clearVelocities();
	}

	for (std::vector<LimbModel*>::iterator lit = mLimbModels.begin();
		lit != mLimbModels.end(); lit++) {
		(*lit)->calm();
	}
}

int FSPhenomeModel::performEmbryogenesis() {
	int totalSegmentCounter = 0;
	if (!mDeveloped) {
		BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "--Perform an embryogenesis";
		cleanup();
		mBodyGenerated = false;
		std::list<PhenotypeGenerator*> generatorList;

		// get the first gene from the genome
		Gene* gene =
		mCreatureModel->getGenotype().getGenes()[mCreatureModel->getGenotype().getRootIndex()];

		//create a phenotype generator and initialize it with the starting point of the creation of the creature
		PhenotypeGenerator* rootGenerator = new PhenotypeGenerator();
		std::map<int, int> repList;
		rootGenerator->initialize(repList, mCreatureModel->getInitialPosition(),
			Ogre::Quaternion::IDENTITY, NULL, NULL, 1);
		rootGenerator->setGene(gene);
		rootGenerator->setRoot2LeafPath(0);
		generatorList.push_back(rootGenerator);

		while (!generatorList.empty()) { // this loop creates the creature up to the point at which we reach the correct root-to-leaf path length

			BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Phenome generator qty:" << generatorList.size();

			PhenotypeGenerator* generator = generatorList.front();
			generatorList.pop_front();

			Embryogenesis::transcribeGene(generatorList, totalSegmentCounter,
				this, generator);

			delete generator;// delete the generator of this gene
		}

		mDeveloped = true;
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

void FSPhenomeModel::calculateChildPositionRelativeToParent(
	PhenotypeGenerator* generator, /**!< The generator of the child limb*/
	btTransform& parentJointAnchor,/**!< The joint anchor on the parent limb surface*/
	btTransform& childJointAnchor,/**!< joint anchor on the child limb surface*/
	Morphogene* childMorphogene,/**!< The morphogene to build the child limb*/
	Ogre::Vector3& jointPivotInW/**!< The joint pivot in the world ref.*/) {

	//prepare parent side
	MorphogeneBranch* parentMorphogeneBranch =
		((MorphogeneBranch*) generator->getGeneBranch()); //get the morphogene branch that defines the joint connecting the limbs

	FSLimbBt* parentLimb =
		((FSLimbBt*) ((FSLimbModel*) generator->getParentComponentModel())->getLimbPhysics()); // get the parent limb model

	Ogre::Vector3 parentLimbCOM = OgreBulletUtils::convert(
		parentLimb->getPosition()); // get the parent limb's center of mass position

	Ogre::Vector3 parentAnchorDirInParent = Ogre::Vector3(
		parentMorphogeneBranch->getJointAnchorX(),
		parentMorphogeneBranch->getJointAnchorY(),
		parentMorphogeneBranch->getJointAnchorZ()); // get parent joint's anchor direction

	//if the generator is the mirrored version of another generator
	//mirrored is: -O  -> O- | \O -> O\   mirroring = sign inversion
	if (generator->isMirrored()) {
		parentAnchorDirInParent = -parentAnchorDirInParent; //get mirrored direction
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

	Ogre::Vector3 childAnchorDirInChild(childMorphogene->getJointAnchorX(),
		childMorphogene->getJointAnchorY(), childMorphogene->getJointAnchorZ()); // get anchor direction of limb child in the local reference frame of child

	Ogre::Quaternion childLimbRotation(childMorphogene->getOrientationW(),
		childMorphogene->getOrientationX(), childMorphogene->getOrientationY(),
		childMorphogene->getOrientationZ());

	if (!MathUtils::isFinite(childLimbRotation)) {
		BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::fatal)<< " NaN/Inf detected in childLimb orientation: " << childLimbRotation;
	}

	childAnchorDirInChild = childLimbRotation * childAnchorDirInChild; // Rotate the child anchor in the direction of its own rotation

	// CHILD LIMB ANCHOR POINT IN CHILD REFERENCE FRAME
	childJointAnchor = getOwnIntersection(childMorphogene, generator,
		childAnchorDirInChild); // find the joint anchor position of the limb by positioning the limb at an arbitrary position to cast a ray

	Ogre::Vector3 childAnchorInChild(
		OgreBulletUtils::convert(childJointAnchor.getOrigin())); // get the surface point of child limb in the global reference frame

	Ogre::Vector3 childJointPivotInChild = childAnchorInChild; // get local joint rotation point in reference frame child

	Ogre::Vector3 childLimbCOM(jointPivotInW - childAnchorInChild); // global center of mass of child limb

#ifndef EXCLUDE_FROM_TEST
	// draw line from limb A to surface anchor point of A (GREEN LINE)
	SimulationManager::getSingleton()->getDebugDrawer().drawLine(parentLimbCOM,
		jointPivotInW, Ogre::ColourValue(0, 1, 0));

	SimulationManager::getSingleton()->getDebugDrawer().drawSphere(
		parentLimbCOM, 0.1, Ogre::ColourValue(0, 1, 0));

	SimulationManager::getSingleton()->getDebugDrawer().drawSphere(
		jointPivotInW, 0.1, Ogre::ColourValue(0, 1, 0));

	// draw line from anchor point of A to joint rotation point (BLUE LINE)
//	SimulationManager::getSingleton()->getDebugDrawer().drawLine(
//		parentLimbCOM + parentAnchorInParent,
//		parentLimbCOM + parentJointPivotInParent, Ogre::ColourValue(0, 0, 1));

//	SimulationManager::getSingleton()->getDebugDrawer().drawSphere(
//		parentLimbCOM + parentAnchorInParent, 0.1, Ogre::ColourValue(0, 0, 1));
//	SimulationManager::getSingleton()->getDebugDrawer().drawSphere(
//		parentLimbCOM + parentJointPivotInParent, 0.1,
//		Ogre::ColourValue(0, 0, 1));

//	// draw line from joint rotation point to surface anchor point of B (BLUE LINE)
	SimulationManager::getSingleton()->getDebugDrawer().drawLine(jointPivotInW,
		parentLimbCOM + childAnchorInParent, Ogre::ColourValue(0, 0, 1));

//	SimulationManager::getSingleton()->getDebugDrawer().drawSphere(
//		parentLimbCOM + parentJointPivotInParent, 0.1,
//		Ogre::ColourValue(0, 0, 1));
//	SimulationManager::getSingleton()->getDebugDrawer().drawSphere(
//		parentLimbCOM + childAnchorInParent, 0.1, Ogre::ColourValue(0, 0, 1));

	// draw line from limb B to anchor point of B (GREEN LINE)
	SimulationManager::getSingleton()->getDebugDrawer().drawLine(childLimbCOM,
		childLimbCOM + childAnchorInChild, Ogre::ColourValue(0, 1, 0));

	SimulationManager::getSingleton()->getDebugDrawer().drawSphere(childLimbCOM,
		0.1, Ogre::ColourValue(0, 1, 0));
//	SimulationManager::getSingleton()->getDebugDrawer().drawSphere(
//		childLimbCOM + childAnchorInChild, 0.1, Ogre::ColourValue(0, 1, 0));

	// draw line from limb A to limb B (WHITE LINE)
	SimulationManager::getSingleton()->getDebugDrawer().drawLine(childLimbCOM,
		parentLimbCOM, Ogre::ColourValue(1, 1, 1));
#endif

	// set global center of mass of child limb as the new generation point for generation
	generator->setPosition(childLimbCOM);
}

LimbModel* FSPhenomeModel::createLimb(PhenotypeGenerator* generator,
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
	FSLimbModel* childLimb = new FSLimbModel(getCreatureModel()->getWorld(),
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

void FSPhenomeModel::appendToParentLimb(LimbModel* childLimb,
	PhenotypeGenerator* generator, Ogre::Vector3& jointPivotInW,
	btTransform& parentHitTransform, btTransform& childHitTransform) {

	//PARENT
	//get the morphogene branch that defines the joint and connects the limbs
	MorphogeneBranch* parentMorphogeneBranch =
		((MorphogeneBranch*) generator->getGeneBranch());

	// get parent limb
	FSLimbModel* parentLimb =
		(FSLimbModel*) generator->getParentComponentModel();

	//create the joint from the two limbs using limb A, limb B and their joint definitions in the respective reference frames
	FSJointModel* joint = new FSJointModel(getCreatureModel()->getWorld(),
	/*parent limb*/
	((FSLimbBt*) parentLimb->getLimbPhysics())->getRigidBody(),
	/*child limb*/
	((FSLimbBt*) childLimb->getLimbPhysics())->getRigidBody(), jointPivotInW,
		parentLimb->getOwnIndex(), childLimb->getOwnIndex(),
		getJointModels().size(), parentMorphogeneBranch->getJointType(),
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
//	double maxTorque = 5000 * (mass1 + mass2);
	double maxTorque = 1.0f * (mass1 * mass2);
//		(MorphologyConfiguration::MUSCLE_MAX_TORQUE_LINEAR_CONSTANT
//			* (mass1 + mass2)
//			+ MorphologyConfiguration::MUSCLE_MAX_TORQUE_SQUARE_CONSTANT
//				* pow(mass1 + mass2, 2));

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
			ChaoticController* controller =
				new ChaoticController(
					((ChaoticControllerGene*) parentMorphogeneBranch->getControllerGenes()[i])->getSystemType());

			controller->addControlInput(joint->getAngleceptors()[0]); // Add the first angleceptor as input
			controller->addControlInput(joint->getVelocityceptors()[0]); // add the first velocityceptor as input

			controller->initialize();
			controller->addControlOutput(joint->getMotors()[i]);
			getControllers().push_back(controller);
		}
		}
	}
}

btTransform FSPhenomeModel::getParentIntersectionInW(LimbPhysics* parentLimb,
	MorphogeneBranch* parentMorphogeneBranch, Ogre::Vector3 parentLimbCOM,
	Ogre::Vector3 parentAnchorDirInParent) {

	((FSLimbBt*) parentLimb)->addToWorld(); // add parent limb to world

	btTransform parentHitLocation =
		parentLimb->getIntersection(
			OgreBulletUtils::convert(
				parentLimbCOM) /**!< origin of limb parent*/,
			OgreBulletUtils::convert(
				parentAnchorDirInParent) /**!< direction of anchor of limb parent*/);

	((FSLimbBt*) parentLimb)->removeFromWorld(); // remove parent limb from world

	return parentHitLocation;
}

btTransform FSPhenomeModel::getOwnIntersection(Morphogene* childMorphogene,
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

void FSPhenomeModel::generateBody() {
	bool isFixedBase = false;
	bool setDamping = false;
	bool gyro = false;
	bool canSleep = true;

	if (mBodyGenerated) {
		return;
	}

	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "--Generate the body";

	if (mJointModels.size() != 0) {
		bool selfCollision = true; /**!< The collision is handled on a per-limb basis*/

		int linkQty = 0;
		for (int i = 0; i < mJointModels.size(); i++) {
			mJointModels[i]->initialize();
			switch (mJointModels[i]->getType()) {
			case JointPhysics::HINGE_JOINT:
				linkQty++;
				break;
			case JointPhysics::SPHERICAL_JOINT:
				linkQty += 3;
				break;
			}
		}
		mMultiBody = new btMultiBody(linkQty,
			btScalar(mLimbModels[0]->getMass()), mLimbModels[0]->getInertia(),
			isFixedBase, canSleep);

		mMultiBody->setBasePos(
			OgreBulletUtils::convert(mLimbModels[0]->getPosition()));
		mMultiBody->setWorldToBaseRot(
			OgreBulletUtils::convert(mLimbModels[0]->getOrientation()));

		btScalar linkLength = MorphologyConfiguration::LINK_LENGTH;

		linkQty = 0;
		for (int i = 0; i < mJointModels.size(); i++) {
			switch (mJointModels[i]->getType()) {
			case JointPhysics::HINGE_JOINT:
				mMultiBody->setupRevolute(
					((long) mJointModels[i]->getChildIndex()) - 1,
					btScalar(mLimbModels[i + 1]->getMass()),
					mLimbModels[i + 1]->getInertia(),
					((long) mJointModels[i]->getParentIndex()) - 1,
					mJointModels[i]->getParentComToPivot().getRotation().normalized()
						* mJointModels[i]->getPivotToChildCom().getRotation().normalized(),
					mJointModels[i]->getJointPitchAxis().normalized(),
					mJointModels[i]->getParentComToPivot().getOrigin()
						* linkLength,
					-mJointModels[i]->getPivotToChildCom().getOrigin()
						* linkLength, true);
				break;
			case JointPhysics::SPHERICAL_JOINT:
				mMultiBody->setupSpherical(
					((long) mJointModels[i]->getChildIndex()) - 1,
					btScalar(mLimbModels[i + 1]->getMass()),
					mLimbModels[i + 1]->getInertia(),
					((long) mJointModels[i]->getParentIndex()) - 1,
					mJointModels[i]->getParentComToPivot().getRotation().normalized()
						* mJointModels[i]->getPivotToChildCom().getRotation().normalized(),
					mJointModels[i]->getParentComToPivot().getOrigin()
						* linkLength,
					-mJointModels[i]->getPivotToChildCom().getOrigin()
						* linkLength, true);
				break;
			default:
				break;
			}

			((FSJointBt*) mJointModels[i]->getJointPhysics())->setMultiBody(
				mMultiBody);
			for (std::vector<Motor*>::iterator mit =
				mJointModels[i]->getMotors().begin();
				mit != mJointModels[i]->getMotors().end(); mit++) {
				((FSServoMotor*) (*mit))->instantiate(
					mJointModels[i]->getJointPhysics(),
					mJointModels[i]->getIndex());
			}
		}

		mMultiBody->finalizeMultiDof();

		mMultiBody->setCanSleep(canSleep);
		mMultiBody->setHasSelfCollision(selfCollision);
		mMultiBody->setUseGyroTerm(gyro);

		if (!setDamping) { /**<! Pay attention, damping affects the whole motion of a body */
			mMultiBody->setLinearDamping(0.f);
			mMultiBody->setAngularDamping(0.f);
		} else {
			mMultiBody->setLinearDamping(0.1f);
			mMultiBody->setAngularDamping(0.9f);
		}

		btAlignedObjectArray<btQuaternion> worldtoLocal;
		worldtoLocal.resize(mMultiBody->getNumLinks() + 1);

		btAlignedObjectArray<btVector3> localOrigin;
		localOrigin.resize(mMultiBody->getNumLinks() + 1);

		worldtoLocal[0] = mMultiBody->getWorldToBaseRot();
		localOrigin[0] = mMultiBody->getBasePos();
		for (int i = 0; i < mMultiBody->getNumLinks(); ++i) {
			const int parent = mMultiBody->getParent(i);
			worldtoLocal[i + 1] = mMultiBody->getParentToLocalRot(i)
				* worldtoLocal[parent + 1];
			localOrigin[i + 1] = localOrigin[parent + 1]
				+ (quatRotate(worldtoLocal[i + 1].inverse(),
					mMultiBody->getRVector(i)));
		}

		{
			btVector3 origin = localOrigin[0];

			btQuaternion orientation(-worldtoLocal[0].x(), -worldtoLocal[0].y(),
				-worldtoLocal[0].z(), worldtoLocal[0].w());

			((FSLimbBt*) mLimbModels[0]->getLimbPhysics())->generateLink(
				mMultiBody, mLimbModels[0], origin, orientation, -1);
			mMultiBody->setBaseCollider(
				((FSLimbBt*) mLimbModels[0]->getLimbPhysics())->getLink());
		}

		for (int i = 0; i < mMultiBody->getNumLinks(); ++i) {

			btVector3 origin = localOrigin[i + 1];

			btQuaternion orientation(-worldtoLocal[i + 1].x(),
				-worldtoLocal[i + 1].y(), -worldtoLocal[i + 1].z(),
				worldtoLocal[i + 1].w());
			((FSLimbBt*) mLimbModels[i + 1]->getLimbPhysics())->generateLink(
				mMultiBody, mLimbModels[i + 1], origin, orientation, i);

			mMultiBody->getLink(i).m_collider =
				((FSLimbBt*) mLimbModels[i + 1]->getLimbPhysics())->getLink();
		}
	}

	mBodyGenerated = true;
}

void FSPhenomeModel::addJointConstraints() {
	for (std::vector<btMultiBodyConstraint*>::iterator lit =
		mLimitConstraints.begin(); lit != mLimitConstraints.end();) {
		delete *lit;
		lit = mLimitConstraints.erase(lit);
	}

	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "--Add joint constraints";

	for (int i = 0; i < mJointModels.size(); i++) {
		//TODO: Limit joints that way, the joint limit constraint does not yet support the limiting of the spherical joint
		// Link joint limits
		btMultiBodyConstraint* limitCons = new btMultiBodyJointLimitConstraint(
			mMultiBody, i,
			btScalar(
				mJointModels[i]->getLowerLimits()[JointPhysics::RDOF_PITCH]),
			btScalar(
				mJointModels[i]->getUpperLimits()[JointPhysics::RDOF_PITCH]));
		// The default value (100) behaves like a lock on -1.6
//		limitCons->setMaxAppliedImpulse(40);
		mLimitConstraints.push_back(limitCons);
	}

}

void FSPhenomeModel::reset(const Ogre::Vector3 position) {
	/**The vector of limb models.*/
	//TODO: Some creatures just do not have a multibody. Why?
	if (mMultiBody && mLimbModels.size() > 0) {

		btTransform initialTransform;
		initialTransform.setIdentity();

		btVector3 initialRelativePosition;
		initialRelativePosition.setValue(
			mLimbModels[0]->getLimbPhysics()->getInitialRelativeXPosition(),
			mLimbModels[0]->getLimbPhysics()->getInitialRelativeYPosition(),
			mLimbModels[0]->getLimbPhysics()->getInitialRelativeZPosition());

		btQuaternion initialOrientation;
		initialOrientation.setValue(
			mLimbModels[0]->getLimbPhysics()->getInitialXOrientation(),
			mLimbModels[0]->getLimbPhysics()->getInitialYOrientation(),
			mLimbModels[0]->getLimbPhysics()->getInitialZOrientation(),
			mLimbModels[0]->getLimbPhysics()->getInitialWOrientation());

		initialTransform.setOrigin(
			OgreBulletUtils::convert(position) + initialRelativePosition);
		initialTransform.setRotation(initialOrientation);

		mMultiBody->setBaseWorldTransform(initialTransform);
		calm();
	}

	for (std::vector<LimbModel*>::const_iterator it = mLimbModels.begin();
		it != mLimbModels.end(); it++) {
		(*it)->reset(position);
	}
}

void FSPhenomeModel::cleanup() {
	for (std::vector<ComponentModel*>::iterator cit = mComponentModels.begin();
		cit != mComponentModels.end();) {
		delete *cit;
		cit = mComponentModels.erase(cit);
	}
	mLimbModels.clear();
	mJointModels.clear();
	if (mMultiBody) {
		delete mMultiBody;
		mMultiBody = NULL;
	}
}

void FSPhenomeModel::reposition(const Ogre::Vector3 position) {
	/**The vector of limb models.*/
	if (mMultiBody) {
		mMultiBody->setBasePos(OgreBulletUtils::convert(position));
	}
	for (std::vector<LimbModel*>::const_iterator it = mLimbModels.begin();
		it != mLimbModels.end(); it++) {
		(*it)->reposition(position);

	}
}

bool FSPhenomeModel::equals(const FSPhenomeModel& phenomeModel) const {
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

PhenomeModel* FSPhenomeModel::clone() {
	return new FSPhenomeModel(*this);
}

btMultiBodyDynamicsWorld* FSPhenomeModel::getWorld() {
	if (!mWorld) {
#ifndef EXCLUDE_FROM_TEST
		mWorld = (btMultiBodyDynamicsWorld*) mCreatureModel->getWorld();
#endif
	}
	return mWorld;
}
