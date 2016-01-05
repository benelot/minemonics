//# corresponding headers
#include <model/universe/evolution/population/creature/modelOrganism/ragdoll/RagDollBuilder.hpp>

//# forward declarations
//# system headers
//## controller headers
//## model headers
#include <boost/math/constants/constants.hpp>

//## view headers
//# custom headers
//## base headers
//## configuration headers
#include <configuration/PhysicsConfiguration.hpp>
#include <configuration/MorphologyConfiguration.hpp>

//## controller headers
//## model headers
#include <model/universe/evolution/population/creature/genome/MixedGenome.hpp>
#include <model/universe/evolution/population/creature/genome/controller/SineControllerGene.hpp>
#include <model/universe/evolution/population/creature/genome/controller/ChaoticControllerGene.hpp>
#include <model/universe/evolution/population/creature/genome/morphology/MorphogeneBranch.hpp>

//## view headers
//## utils headers
#include <utils/ogre3D/Euler.hpp>

void RagDollBuilder::build(MixedGenome* genome,
	ControllerGene::ControllerType controllerType) {
	genome->setTotalSegmentQtyLimit(11);
	genome->setSegmentsDepthLimit(11);

	btTransform transform;
	btTransform localA, localB;

	LimbPhysics::PrimitiveType type = LimbPhysics::BLOCK;

	bool attachHead = false;
	bool enableMotor = true;
	double ragDollSize = MorphologyConfiguration::LIMB_MAX_SIZE;
	double gapSize = ragDollSize * 1.0f;

	double damping = 0.05f; //[0.005;0.5] 0.05

	// Build the ragdoll

	// BODYPART_ABDOMENPELVIS
	Morphogene* morphogene = new Morphogene(type,
		Ogre::Vector3(ragDollSize * 0.3f, ragDollSize * 0.2f,
			ragDollSize * 0.3f), Ogre::Quaternion::IDENTITY, 1, 10, true,
		Ogre::ColourValue(1, 0, 0), Ogre::Vector3(1, 0, 0));
	//	morphogene->initialize(0);
	genome->addGene(morphogene);

	// ##################################################################
	// create joint between the two limbs
	Ogre::Euler jointRotation(0, 0, 0);
	MorphogeneBranch* morphogeneBranch = new MorphogeneBranch(
		JointPhysics::HINGE_JOINT, false, false,
		jointRotation * Ogre::Vector3(1, 0, 0),
		jointRotation * Ogre::Vector3(0, 1, 0), Ogre::Vector3(0, 0, 0),
		Ogre::Vector3(damping, damping, damping),
		Ogre::Vector3(-0.2 * M_PI, -M_PI_2, -0.1 * M_PI),
		Ogre::Vector3(0.2 * M_PI, M_PI_2, M_PI_2),
		Ogre::Vector3(btScalar(gapSize * 0.f), btScalar(gapSize * 0.15f),
			btScalar(gapSize * 0.f)));

	switch (controllerType) {
	case ControllerGene::SineControllerGene:
		// create instances of the sine controller gene for the morphogene.
		for (int i = 0; i < 3; i++) {
			SineControllerGene* sineController = new SineControllerGene();
			sineController->initialize();
			morphogeneBranch->getControllerGenes().push_back(sineController);
		}
		break;
	case ControllerGene::ChaoticControllerGene:
		double x = -1.5f; // x
		double y = 0; // y
		double z = 0; // z

		// stronger initial force output on z
//		double x = 0.0f; // x
//		double y = 0.0f; // y
//		double z = 2.0f; // z

		double speed = 1;

		// create instances of the chaotic controller gene for the morphogene.
		for (int i = 0; i < 3; i++) {
			ChaoticControllerGene* chaoticController =
				new ChaoticControllerGene(ChaoticControllerGene::CHUA_CIRCUIT,
					x, y, z, speed);

//			chaoticController->initialize();

			morphogeneBranch->getControllerGenes().push_back(chaoticController);
		}
	}

	//	morphogeneBranch->initialize();
	morphogeneBranch->setActive(true);
	morphogeneBranch->setBranchGeneType(BODYPART_THORAX);

	// add joint to the first limb branching to the second limb
	((Morphogene*) genome->getGenes()[BODYPART_ABDOMENPELVIS])->getGeneBranches().push_back(
		morphogeneBranch);

	localA.getBasis().setEulerZYX(0, M_PI_2, 0); // PELVIS
	localB.getBasis().setEulerZYX(0, M_PI_2, 0); // THORAX

	// ##################################################################
	// create joint between the two limbs
	jointRotation = Ogre::Euler(0, 0, 0);
	morphogeneBranch = new MorphogeneBranch(JointPhysics::HINGE_JOINT, false,
		false, jointRotation * Ogre::Vector3(1, 0, 0),
		jointRotation * Ogre::Vector3(0, 1, 0), Ogre::Vector3(0, 0, 0),
		Ogre::Vector3(damping, damping, damping),
		Ogre::Vector3(-M_PI_4, -M_PI_4, -PhysicsConfiguration::UNIV_EPS),
		Ogre::Vector3(M_PI_4, M_PI_4, PhysicsConfiguration::UNIV_EPS),
		Ogre::Vector3(btScalar(gapSize * -0.18f), btScalar(gapSize * -0.10f),
			btScalar(gapSize * 0.f)));

	switch (controllerType) {
	case ControllerGene::SineControllerGene:
		// create instances of the sine controller gene for the morphogene.
		for (int i = 0; i < 3; i++) {
			SineControllerGene* sineController = new SineControllerGene();
			sineController->initialize();
			morphogeneBranch->getControllerGenes().push_back(sineController);
		}
		break;
	case ControllerGene::ChaoticControllerGene:
		// create instances of the chaotic controller gene for the morphogene.
		for (int i = 0; i < 3; i++) {
			ChaoticControllerGene* chaoticController =
				new ChaoticControllerGene();
			chaoticController->initialize();
			morphogeneBranch->getControllerGenes().push_back(chaoticController);
		}
	}

	//	morphogeneBranch->initialize();
	morphogeneBranch->setActive(true);
	morphogeneBranch->setBranchGeneType(BODYPART_LEFT_THIGH);

	// add joint to the first limb branching to the second limb
	((Morphogene*) genome->getGenes()[BODYPART_ABDOMENPELVIS])->getGeneBranches().push_back(
		morphogeneBranch);

	localA.getBasis().setEulerZYX(0, 0, M_PI_4); // PELVIS
	localB.getBasis().setEulerZYX(0, 0, M_PI_4); // LEFT THIGH

	// ##################################################################
	// create joint between the two limbs
	jointRotation = Ogre::Euler(0, 0, 0);
	morphogeneBranch = new MorphogeneBranch(JointPhysics::HINGE_JOINT, false,
		false, jointRotation * Ogre::Vector3(1, 0, 0),
		jointRotation * Ogre::Vector3(0, 1, 0), Ogre::Vector3(0, 0, 0),
		Ogre::Vector3(damping, damping, damping),
		Ogre::Vector3(-M_PI_4, -M_PI_4, -PhysicsConfiguration::UNIV_EPS),
		Ogre::Vector3(M_PI_4, M_PI_4, PhysicsConfiguration::UNIV_EPS),
		Ogre::Vector3(btScalar(gapSize * 0.18f), btScalar(gapSize * -0.10f),
			btScalar(ragDollSize * 0.f)));

	switch (controllerType) {
	case ControllerGene::SineControllerGene:
		// create instances of the sine controller gene for the morphogene.
		for (int i = 0; i < 3; i++) {
			SineControllerGene* sineController = new SineControllerGene();
			sineController->initialize();
			morphogeneBranch->getControllerGenes().push_back(sineController);
		}
		break;
	case ControllerGene::ChaoticControllerGene:
		// create instances of the chaotic controller gene for the morphogene.
		for (int i = 0; i < 3; i++) {
			ChaoticControllerGene* chaoticController =
				new ChaoticControllerGene();
			chaoticController->initialize();
			morphogeneBranch->getControllerGenes().push_back(chaoticController);
		}
	}

	//	morphogeneBranch->initialize();
	morphogeneBranch->setActive(true);
	morphogeneBranch->setBranchGeneType(BODYPART_RIGHT_THIGH);

	// add joint to the first limb branching to the second limb
	((Morphogene*) genome->getGenes()[BODYPART_ABDOMENPELVIS])->getGeneBranches().push_back(
		morphogeneBranch);

	localA.getBasis().setEulerZYX(0, 0, M_PI_4); // PELVIS
	localB.getBasis().setEulerZYX(0, 0, M_PI_4); // RIGHT THIGH

	// BODYPART_THORAX
	morphogene = new Morphogene(type,
		Ogre::Vector3(ragDollSize * 0.3f, ragDollSize * 0.28f,
			ragDollSize * 0.3f), Ogre::Quaternion::IDENTITY, 1, 10, true,
		Ogre::ColourValue(1, 0, 0),
		Ogre::Vector3(btScalar(gapSize * 0.f), btScalar(gapSize * -0.15f),
			btScalar(gapSize * 0.f)));
	//	morphogene->initialize(0);
	genome->addGene(morphogene);

	// ##################################################################
	// create joint between the two limbs
	jointRotation = Ogre::Euler(0, 0, 0);
	morphogeneBranch = new MorphogeneBranch(JointPhysics::HINGE_JOINT, false,
		false, jointRotation * Ogre::Vector3(1, 0, 0),
		jointRotation * Ogre::Vector3(0, 1, 0), Ogre::Vector3(0, 0, 0),
		Ogre::Vector3(damping, damping, damping),
		Ogre::Vector3(-M_PI_2, -M_PI_2, -M_PI_2),
		Ogre::Vector3(M_PI_2, M_PI_2, M_PI_2),
		Ogre::Vector3(btScalar(gapSize * 0.2f), btScalar(gapSize * 0.15f),
			btScalar(gapSize * 0.f)));

	switch (controllerType) {
	case ControllerGene::SineControllerGene:
		// create instances of the sine controller gene for the morphogene.
		for (int i = 0; i < 3; i++) {
			SineControllerGene* sineController = new SineControllerGene();
			sineController->initialize();
			morphogeneBranch->getControllerGenes().push_back(sineController);
		}
		break;
	case ControllerGene::ChaoticControllerGene:
		// create instances of the chaotic controller gene for the morphogene.
		for (int i = 0; i < 3; i++) {
			ChaoticControllerGene* chaoticController =
				new ChaoticControllerGene();
			chaoticController->initialize();
			morphogeneBranch->getControllerGenes().push_back(chaoticController);
		}
	}

//	morphogeneBranch->initialize();
	morphogeneBranch->setActive(true);
	morphogeneBranch->setBranchGeneType(BODYPART_RIGHT_UPPER_ARM);

	// add joint to the first limb branching to the second limb
	((Morphogene*) genome->getGenes()[BODYPART_THORAX])->getGeneBranches().push_back(
		morphogeneBranch);

	localA.getBasis().setEulerZYX(M_PI, 0, 0); // THORAX
	localB.getBasis().setEulerZYX(0, M_PI, 0); // UPPER ARM

	// ##################################################################
	// create joint between the two limbs
	jointRotation = Ogre::Euler(0, 0, 0);
	morphogeneBranch = new MorphogeneBranch(JointPhysics::HINGE_JOINT, false,
		false, jointRotation * Ogre::Vector3(1, 0, 0),
		jointRotation * Ogre::Vector3(0, 1, 0), Ogre::Vector3(0, 0, 0),
		Ogre::Vector3(damping, damping, damping),
		Ogre::Vector3(-M_PI_2, -M_PI_2, -M_PI_2),
		Ogre::Vector3(M_PI_2, M_PI_2, M_PI_2),
		Ogre::Vector3(btScalar(gapSize * -0.2f), btScalar(gapSize * 0.15f),
			btScalar(gapSize * 0.f)));

	switch (controllerType) {
	case ControllerGene::SineControllerGene:
		// create instances of the sine controller gene for the morphogene.
		for (int i = 0; i < 3; i++) {
			SineControllerGene* sineController = new SineControllerGene();
			sineController->initialize();
			morphogeneBranch->getControllerGenes().push_back(sineController);
		}
		break;
	case ControllerGene::ChaoticControllerGene:
		// create instances of the chaotic controller gene for the morphogene.
		for (int i = 0; i < 3; i++) {
			ChaoticControllerGene* chaoticController =
				new ChaoticControllerGene();
			chaoticController->initialize();
			morphogeneBranch->getControllerGenes().push_back(chaoticController);
		}
	}

//	morphogeneBranch->initialize();
	morphogeneBranch->setActive(true);
	morphogeneBranch->setBranchGeneType(BODYPART_LEFT_UPPER_ARM);

	// add joint to the first limb branching to the second limb
	((Morphogene*) genome->getGenes()[BODYPART_THORAX])->getGeneBranches().push_back(
		morphogeneBranch);

	localA.getBasis().setEulerZYX(0, M_PI, 0); // LEFT UPPER ARM
	localB.getBasis().setEulerZYX(0, M_PI, 0); // THORAX

	// ##################################################################
	// create joint between the two limbs
	jointRotation = Ogre::Euler(0, 0, 0);
	morphogeneBranch = new MorphogeneBranch(JointPhysics::HINGE_JOINT, false,
		false, jointRotation * Ogre::Vector3(1, 0, 0),
		jointRotation * Ogre::Vector3(0, 1, 0), Ogre::Vector3(0, 0, 0),
		Ogre::Vector3(damping, damping, damping),
		Ogre::Vector3(-M_PI_4, -M_PI_4, -M_PI_2),
		Ogre::Vector3(M_PI_4, M_PI_4, M_PI_2),
		Ogre::Vector3(btScalar(gapSize * 0.f), btScalar(gapSize * 0.30f),
			btScalar(gapSize * 0.f)));

	switch (controllerType) {
	case ControllerGene::SineControllerGene:
		// create instances of the sine controller gene for the morphogene.
		for (int i = 0; i < 3; i++) {
			SineControllerGene* sineController = new SineControllerGene();
			sineController->initialize();
			morphogeneBranch->getControllerGenes().push_back(sineController);
		}
		break;
	case ControllerGene::ChaoticControllerGene:
		// create instances of the chaotic controller gene for the morphogene.
		for (int i = 0; i < 3; i++) {
			ChaoticControllerGene* chaoticController =
				new ChaoticControllerGene();
			chaoticController->initialize();
			morphogeneBranch->getControllerGenes().push_back(chaoticController);
		}
	}

//	morphogeneBranch->initialize();
	morphogeneBranch->setActive(true);
	morphogeneBranch->setBranchGeneType(BODYPART_HEAD);

	// add joint to the first limb branching to the second limb
	((Morphogene*) genome->getGenes()[BODYPART_THORAX])->getGeneBranches().push_back(
		morphogeneBranch);

	localA.getBasis().setEulerZYX(0, 0, M_PI_2); // THORAX
	localB.getBasis().setEulerZYX(0, 0, M_PI_2); // HEAD

	//BODYPART_HEAD
	morphogene = new Morphogene(type,
		Ogre::Vector3(ragDollSize * 0.2f, ragDollSize * 0.2f,
			ragDollSize * 0.2f), Ogre::Quaternion::IDENTITY, 1, 10, true,
		Ogre::ColourValue(1, 0, 0),
		Ogre::Vector3(btScalar(gapSize * 0.f), btScalar(gapSize * -0.14f),
			btScalar(gapSize * 0.f)));
	//	morphogene->initialize(0);
	genome->addGene(morphogene);

	//BODYPART_LEFT_THIGH
	morphogene = new Morphogene(type,
		Ogre::Vector3(ragDollSize * 0.14f, ragDollSize * 0.45f,
			ragDollSize * 0.14f), Ogre::Quaternion::IDENTITY, 1, 10, true,
		Ogre::ColourValue(1, 0, 0),
		Ogre::Vector3(btScalar(gapSize * 0.f), btScalar(gapSize * 0.225f),
			btScalar(gapSize * 0.f)));
	//	morphogene->initialize(0);
	genome->addGene(morphogene);

	// ##################################################################
	// create joint between the two limbs
	jointRotation = Ogre::Euler(0, 0, 0);
	morphogeneBranch = new MorphogeneBranch(JointPhysics::HINGE_JOINT, false,
		false, jointRotation * Ogre::Vector3(1, 0, 0),
		jointRotation * Ogre::Vector3(0, 1, 0), Ogre::Vector3(0, 0, 0),
		Ogre::Vector3(damping, damping, damping),
		Ogre::Vector3(-PhysicsConfiguration::UNIV_EPS,
			-PhysicsConfiguration::UNIV_EPS, -PhysicsConfiguration::UNIV_EPS),
		Ogre::Vector3(PhysicsConfiguration::UNIV_EPS,
			PhysicsConfiguration::UNIV_EPS, 3 * M_PI_4),
		Ogre::Vector3(btScalar(gapSize * 0.f), btScalar(gapSize * -0.225f),
			btScalar(gapSize * 0.f)));

	switch (controllerType) {
	case ControllerGene::SineControllerGene:
		// create instances of the sine controller gene for the morphogene.
		for (int i = 0; i < 3; i++) {
			SineControllerGene* sineController = new SineControllerGene();
			sineController->initialize();
			morphogeneBranch->getControllerGenes().push_back(sineController);
		}
		break;
	case ControllerGene::ChaoticControllerGene:
		// create instances of the chaotic controller gene for the morphogene.
		for (int i = 0; i < 3; i++) {
			ChaoticControllerGene* chaoticController =
				new ChaoticControllerGene();
			chaoticController->initialize();
			morphogeneBranch->getControllerGenes().push_back(chaoticController);
		}
	}

//	morphogeneBranch->initialize();
	morphogeneBranch->setActive(true);
	morphogeneBranch->setBranchGeneType(BODYPART_LEFT_LEG);

	// add joint to the first limb branching to the second limb
	((Morphogene*) genome->getGenes()[BODYPART_LEFT_THIGH])->getGeneBranches().push_back(
		morphogeneBranch);

	localA.getBasis().setEulerZYX(0, M_PI_2, 0); // LEFT THIGH
	localB.getBasis().setEulerZYX(0, M_PI_2, 0); // LEFT LEG

	//	BODYPART_LEFTLEG
	morphogene = new Morphogene(type,
		Ogre::Vector3(ragDollSize * 0.1f, ragDollSize * 0.37f,
			ragDollSize * 0.1f), Ogre::Quaternion::IDENTITY, 1, 10, true,
		Ogre::ColourValue(1, 0, 0),
		Ogre::Vector3(btScalar(gapSize * 0.f), btScalar(gapSize * 0.185f),
			btScalar(gapSize * 0.f)));
	//	morphogene->initialize(0);
	genome->addGene(morphogene);

	//BODYPART_RIGHT_THIGH
	morphogene = new Morphogene(type,
		Ogre::Vector3(ragDollSize * 0.14f, ragDollSize * 0.45f,
			ragDollSize * 0.14f), Ogre::Quaternion::IDENTITY, 1, 10, true,
		Ogre::ColourValue(1, 0, 0),
		Ogre::Vector3(btScalar(gapSize * 0.f), btScalar(gapSize * 0.225f),
			btScalar(gapSize * 0.f)));
	//	morphogene->initialize(0);
	genome->addGene(morphogene);

	// ##################################################################
	// create joint between the two limbs
	jointRotation = Ogre::Euler(0, 0, 0);
	morphogeneBranch = new MorphogeneBranch(JointPhysics::HINGE_JOINT, false,
		false, jointRotation * Ogre::Vector3(1, 0, 0),
		jointRotation * Ogre::Vector3(0, 1, 0), Ogre::Vector3(0, 0, 0),
		Ogre::Vector3(damping, damping, damping),
		Ogre::Vector3(-PhysicsConfiguration::UNIV_EPS,
			-PhysicsConfiguration::UNIV_EPS, -PhysicsConfiguration::UNIV_EPS),
		Ogre::Vector3(PhysicsConfiguration::UNIV_EPS,
			PhysicsConfiguration::UNIV_EPS, 3 * M_PI_4),
		Ogre::Vector3(btScalar(gapSize * 0.f), btScalar(gapSize * -0.225f),
			btScalar(gapSize * 0.f)));

	switch (controllerType) {
	case ControllerGene::SineControllerGene:
		// create instances of the sine controller gene for the morphogene.
		for (int i = 0; i < 3; i++) {
			SineControllerGene* sineController = new SineControllerGene();
			sineController->initialize();
			morphogeneBranch->getControllerGenes().push_back(sineController);
		}
		break;
	case ControllerGene::ChaoticControllerGene:
		// create instances of the chaotic controller gene for the morphogene.
		for (int i = 0; i < 3; i++) {
			ChaoticControllerGene* chaoticController =
				new ChaoticControllerGene();
			chaoticController->initialize();
			morphogeneBranch->getControllerGenes().push_back(chaoticController);
		}
	}

//	morphogeneBranch->initialize();
	morphogeneBranch->setActive(true);
	morphogeneBranch->setBranchGeneType(BODYPART_RIGHT_LEG);

	// add joint to the first limb branching to the second limb
	((Morphogene*) genome->getGenes()[BODYPART_RIGHT_THIGH])->getGeneBranches().push_back(
		morphogeneBranch);

	localA.getBasis().setEulerZYX(0, M_PI_2, 0); // RIGHT THIGH
	localB.getBasis().setEulerZYX(0, M_PI_2, 0); // RIGHT LEG

	// BODYPART_RIGHT_LEG
	morphogene = new Morphogene(type,
		Ogre::Vector3(ragDollSize * 0.1f, ragDollSize * 0.37f,
			ragDollSize * 0.1f), Ogre::Quaternion::IDENTITY, 1, 10, true,
		Ogre::ColourValue(1, 0, 0),
		Ogre::Vector3(btScalar(gapSize * 0.f), btScalar(gapSize * 0.185f),
			btScalar(gapSize * 0.f)));
	//	morphogene->initialize(0);
	genome->addGene(morphogene);

	// BODYPART_LEFT_UPPER_ARM
	morphogene = new Morphogene(type,
		Ogre::Vector3(ragDollSize * 0.1f, ragDollSize * 0.33f,
			ragDollSize * 0.1f), Ogre::Euler(0, 0, M_PI_2).toQuaternion(), 1,
		10, true, Ogre::ColourValue(1, 0, 0),
		Ogre::Vector3(btScalar(gapSize * 0.f), btScalar(gapSize * -0.18f),
			btScalar(gapSize * 0.f)));
	//	morphogene->initialize(0);
	genome->addGene(morphogene);

	// ##################################################################
	// create joint between the two limbs
	jointRotation = Ogre::Euler(0, 0, 0);
	morphogeneBranch = new MorphogeneBranch(JointPhysics::HINGE_JOINT, false,
		false, jointRotation * Ogre::Vector3(1, 0, 0),
		jointRotation * Ogre::Vector3(0, 1, 0), Ogre::Vector3(0, 0, 0),
		Ogre::Vector3(damping, damping, damping),
		Ogre::Vector3(-PhysicsConfiguration::UNIV_EPS,
			-PhysicsConfiguration::UNIV_EPS, -PhysicsConfiguration::UNIV_EPS),
		Ogre::Vector3(3 * M_PI_4, PhysicsConfiguration::UNIV_EPS,
			PhysicsConfiguration::UNIV_EPS),
		Ogre::Vector3(btScalar(gapSize * 0.f), btScalar(gapSize * 0.18f),
			btScalar(gapSize * 0.f)));

	switch (controllerType) {
	case ControllerGene::SineControllerGene:
		// create instances of the sine controller gene for the morphogene.
		for (int i = 0; i < 3; i++) {
			SineControllerGene* sineController = new SineControllerGene();
			sineController->initialize();
			morphogeneBranch->getControllerGenes().push_back(sineController);
		}
		break;
	case ControllerGene::ChaoticControllerGene:
		// create instances of the chaotic controller gene for the morphogene.
		for (int i = 0; i < 3; i++) {
			ChaoticControllerGene* chaoticController =
				new ChaoticControllerGene();
			chaoticController->initialize();
			morphogeneBranch->getControllerGenes().push_back(chaoticController);
		}
	}

//	morphogeneBranch->initialize();
	morphogeneBranch->setActive(true);
	morphogeneBranch->setBranchGeneType(BODYPART_LEFT_FOREARM);

	// add joint to the first limb branching to the second limb
	((Morphogene*) genome->getGenes()[BODYPART_LEFT_UPPER_ARM])->getGeneBranches().push_back(
		morphogeneBranch);

	localA.getBasis().setEulerZYX(0, 0, 0); // LEFT UPPER ARM
	localB.getBasis().setEulerZYX(0, 0, 0); // LEFT FOREARM

	//BODYPART_LEFT_FOREARM
	morphogene = new Morphogene(type,
		Ogre::Vector3(ragDollSize * 0.08f, ragDollSize * 0.25f,
			ragDollSize * 0.08f), Ogre::Euler(0, 0, M_PI_2).toQuaternion(), 1,
		10, true, Ogre::ColourValue(1, 0, 0),
		Ogre::Vector3(btScalar(gapSize * 0.f), btScalar(gapSize * -0.14f),
			btScalar(gapSize * 0.f)));
	//	morphogene->initialize(0);
	genome->addGene(morphogene);

	//BODYPART_RIGHT_UPPER_ARM
	morphogene = new Morphogene(type,
		Ogre::Vector3(ragDollSize * 0.1f, ragDollSize * 0.33f,
			ragDollSize * 0.1f), Ogre::Euler(0, 0, -M_PI_2).toQuaternion(), 1,
		10, true, Ogre::ColourValue(1, 0, 0),
		Ogre::Vector3(btScalar(gapSize * 0.f), btScalar(gapSize * -0.18f),
			btScalar(gapSize * 0.f)));
	//	morphogene->initialize(0);
	genome->addGene(morphogene);

	// ##################################################################
	// create joint between the two limbs
	jointRotation = Ogre::Euler(0, 0, 0);
	morphogeneBranch = new MorphogeneBranch(JointPhysics::HINGE_JOINT, false,
		false, jointRotation * Ogre::Vector3(1, 0, 0),
		jointRotation * Ogre::Vector3(0, 1, 0), Ogre::Vector3(0, 0, 0),
		Ogre::Vector3(damping, damping, damping),
		Ogre::Vector3(-PhysicsConfiguration::UNIV_EPS,
			-PhysicsConfiguration::UNIV_EPS, -PhysicsConfiguration::UNIV_EPS),
		Ogre::Vector3(3 * M_PI_4, PhysicsConfiguration::UNIV_EPS,
			PhysicsConfiguration::UNIV_EPS),
		Ogre::Vector3(btScalar(gapSize * 0.f), btScalar(gapSize * 0.18f),
			btScalar(gapSize * 0.f)));

	switch (controllerType) {
	case ControllerGene::SineControllerGene:
		// create instances of the sine controller gene for the morphogene.
		for (int i = 0; i < 3; i++) {
			SineControllerGene* sineController = new SineControllerGene();
			sineController->initialize();
			morphogeneBranch->getControllerGenes().push_back(sineController);
		}
		break;
	case ControllerGene::ChaoticControllerGene:
		// create instances of the chaotic controller gene for the morphogene.
		for (int i = 0; i < 3; i++) {
			ChaoticControllerGene* chaoticController =
				new ChaoticControllerGene();
			chaoticController->initialize();
			morphogeneBranch->getControllerGenes().push_back(chaoticController);
		}
	}

//	morphogeneBranch->initialize();
	morphogeneBranch->setActive(true);
	morphogeneBranch->setBranchGeneType(BODYPART_RIGHT_FOREARM);

	// add joint to the first limb branching to the second limb
	((Morphogene*) genome->getGenes()[BODYPART_RIGHT_UPPER_ARM])->getGeneBranches().push_back(
		morphogeneBranch);

	// BODYPART_RIGHT_LOWER_ARM
	morphogene = new Morphogene(type,
		Ogre::Vector3(ragDollSize * 0.08f, ragDollSize * 0.25f,
			ragDollSize * 0.08f), Ogre::Euler(0, 0, -M_PI_2).toQuaternion(), 1,
		10, true, Ogre::ColourValue(1, 0, 0),
		Ogre::Vector3(btScalar(gapSize * 0.f), btScalar(gapSize * 0.14f),
			btScalar(gapSize * 0.f)));
	//	morphogene->initialize(0);
	genome->addGene(morphogene);

}
