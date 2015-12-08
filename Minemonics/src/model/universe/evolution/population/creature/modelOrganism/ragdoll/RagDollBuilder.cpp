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
//## controller headers
//## model headers
#include <model/universe/evolution/population/creature/genome/MixedGenome.hpp>
#include <model/universe/evolution/population/creature/genome/controller/SineControllerGene.hpp>
#include <model/universe/evolution/population/creature/genome/controller/ChaoticControllerGene.hpp>
#include <model/universe/evolution/population/creature/genome/morphology/MorphogeneBranch.hpp>

//## view headers
//## utils headers
#include <utils/ogre3D/Euler.hpp>

#ifndef UNIV_EPS
#define UNIV_EPS 0.01f
#endif

void RagDollBuilder::build(MixedGenome* genome,
	ControllerGene::ControllerType controllerType) {
	genome->setTotalSegmentQtyLimit(2);
	genome->setSegmentsDepthLimit(2);

	btTransform transform;
	btTransform localA, localB;

	LimbPhysics::PrimitiveType type = LimbPhysics::CAPSULE;

	bool attachHead = false;
	bool enableMotor = true;
	double ragDollSize = 10.0f;
	double gapSize = ragDollSize * 1.0f;

	double damping = 0.05f; //[0.005;0.5] 0.05

	// Build the ragdoll

	// BODYPART_ABDOMENPELVIS
	Morphogene* morphogene = new Morphogene(type,
		Ogre::Vector3(ragDollSize * 0.3, ragDollSize * 0.2, ragDollSize * 0.3),
		Ogre::Quaternion::IDENTITY, 1, 10, true, Ogre::ColourValue(1, 0, 0),
		Ogre::Vector3(1, 0, 0));
	//	morphogene->initialize(0);
	genome->addGene(morphogene);

	// ##################################################################
	// create joint between the two limbs

	MorphogeneBranch* morphogeneBranch = new MorphogeneBranch(
		JointPhysics::HINGE_JOINT, false, false, Ogre::Vector3(0, 0, 1),
		Ogre::Vector3(0, 1, 0), Ogre::Vector3(0, 0, 0),
		Ogre::Vector3(damping, 0, 0),
		Ogre::Vector3(-0.2 * M_PI, -M_PI_2, -0.1 * M_PI),
		Ogre::Vector3(0.2 * M_PI, M_PI_2, M_PI_2),
		Ogre::Vector3(btScalar(gapSize * 0.), btScalar(gapSize * 0.15),
			btScalar(gapSize * 0.)));

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
	morphogeneBranch->setBranchGeneType(BODYPART_THORAX);

	// add joint to the first limb branching to the second limb
	((Morphogene*) genome->getGenes()[BODYPART_ABDOMENPELVIS])->getGeneBranches().push_back(
		morphogeneBranch);

	localA.getBasis().setEulerZYX(0, M_PI_2, 0); // PELVIS
	localB.getBasis().setEulerZYX(0, M_PI_2, 0); // THORAX

	// ##################################################################
	// create joint between the two limbs
	morphogeneBranch = new MorphogeneBranch(JointPhysics::HINGE_JOINT, false,
		false, Ogre::Vector3(0, 0, 1), Ogre::Vector3(0, 1, 0),
		Ogre::Vector3(0, 0, 0), Ogre::Vector3(damping, 0, 0),
		Ogre::Vector3(-M_PI_4, -M_PI_4, 0), Ogre::Vector3(M_PI_4, M_PI_4, 0),
		Ogre::Vector3(btScalar(gapSize * -0.18), btScalar(gapSize * -0.10),
			btScalar(gapSize * 0.)));

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
	morphogeneBranch = new MorphogeneBranch(JointPhysics::HINGE_JOINT, false,
		false, Ogre::Vector3(0, 0, 1), Ogre::Vector3(0, 1, 0),
		Ogre::Vector3(0, 0, 0), Ogre::Vector3(damping, 0, 0),
		Ogre::Vector3(-M_PI_4, -M_PI_4, 0), Ogre::Vector3(M_PI_4, M_PI_4, 0),
		Ogre::Vector3(btScalar(gapSize * 0.18), btScalar(gapSize * -0.10),
			btScalar(ragDollSize * 0.)));

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
		Ogre::Vector3(ragDollSize * 0.3, ragDollSize * 0.28, ragDollSize * 0.3),
		Ogre::Quaternion::IDENTITY, 1, 10, true, Ogre::ColourValue(1, 0, 0),
		Ogre::Vector3(btScalar(gapSize * 0.), btScalar(gapSize * -0.15),
			btScalar(gapSize * 0.)));
	//	morphogene->initialize(0);
	genome->addGene(morphogene);

	// ##################################################################
	// create joint between the two limbs
	morphogeneBranch = new MorphogeneBranch(JointPhysics::HINGE_JOINT, false,
		false, Ogre::Vector3(0, 0, 1), Ogre::Vector3(0, 1, 0),
		Ogre::Vector3(0, 0, 0), Ogre::Vector3(damping, 0, 0),
		Ogre::Vector3(-M_PI_2, -M_PI_2, -M_PI_2),
		Ogre::Vector3(M_PI_2, M_PI_2, M_PI_2),
		Ogre::Vector3(btScalar(gapSize * 0.2), btScalar(gapSize * 0.15),
			btScalar(gapSize * 0.)));

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
	morphogeneBranch = new MorphogeneBranch(JointPhysics::HINGE_JOINT, false,
		false, Ogre::Vector3(0, 0, 1), Ogre::Vector3(0, 1, 0),
		Ogre::Vector3(0, 0, 0), Ogre::Vector3(damping, 0, 0),
		Ogre::Vector3(-M_PI_2, -M_PI_2, -M_PI_2),
		Ogre::Vector3(M_PI_2, M_PI_2, M_PI_2),
		Ogre::Vector3(btScalar(gapSize * -0.2), btScalar(gapSize * 0.15),
			btScalar(gapSize * 0.)));

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
	morphogeneBranch = new MorphogeneBranch(JointPhysics::HINGE_JOINT, false,
		false, Ogre::Vector3(0, 0, 1), Ogre::Vector3(0, 1, 0),
		Ogre::Vector3(0, 0, 0), Ogre::Vector3(damping, 0, 0),
		Ogre::Vector3(-M_PI_4, -M_PI_4, -M_PI_2),
		Ogre::Vector3(M_PI_4, M_PI_4, M_PI_2),
		Ogre::Vector3(btScalar(gapSize * 0.), btScalar(gapSize * 0.30),
			btScalar(gapSize * 0.)));

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
		Ogre::Vector3(ragDollSize * 0.2, ragDollSize * 0.2, ragDollSize * 0.2),
		Ogre::Quaternion::IDENTITY, 1, 10, true, Ogre::ColourValue(1, 0, 0),
		Ogre::Vector3(btScalar(gapSize * 0.), btScalar(gapSize * -0.14),
			btScalar(gapSize * 0.)));
	//	morphogene->initialize(0);
	genome->addGene(morphogene);

	//BODYPART_LEFT_THIGH
	morphogene = new Morphogene(type,
		Ogre::Vector3(ragDollSize * 0.14, ragDollSize * 0.45,
			ragDollSize * 0.14), Ogre::Quaternion::IDENTITY, 1, 10, true,
		Ogre::ColourValue(1, 0, 0),
		Ogre::Vector3(btScalar(gapSize * 0.), btScalar(gapSize * 0.225),
			btScalar(gapSize * 0.)));
	//	morphogene->initialize(0);
	genome->addGene(morphogene);

	// ##################################################################
	// create joint between the two limbs
	morphogeneBranch = new MorphogeneBranch(JointPhysics::HINGE_JOINT, false,
		false, Ogre::Vector3(0, 0, 1), Ogre::Vector3(0, 1, 0),
		Ogre::Vector3(0, 0, 0), Ogre::Vector3(damping, 0, 0),
		Ogre::Vector3(0, 0, 0), Ogre::Vector3(0, 0, 3 * M_PI_4),
		Ogre::Vector3(btScalar(gapSize * 0.), btScalar(gapSize * -0.225),
			btScalar(gapSize * 0.)));

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
		Ogre::Vector3(ragDollSize * 0.1, ragDollSize * 0.37, ragDollSize * 0.1),
		Ogre::Quaternion::IDENTITY, 1, 10, true, Ogre::ColourValue(1, 0, 0),
		Ogre::Vector3(btScalar(gapSize * 0.), btScalar(gapSize * 0.185),
			btScalar(gapSize * 0.)));
	//	morphogene->initialize(0);
	genome->addGene(morphogene);

	//BODYPART_RIGHT_THIGH
	morphogene = new Morphogene(type,
		Ogre::Vector3(ragDollSize * 0.14, ragDollSize * 0.45,
			ragDollSize * 0.14), Ogre::Quaternion::IDENTITY, 1, 10, true,
		Ogre::ColourValue(1, 0, 0),
		Ogre::Vector3(btScalar(gapSize * 0.), btScalar(gapSize * 0.225),
			btScalar(gapSize * 0.)));
	//	morphogene->initialize(0);
	genome->addGene(morphogene);

	// ##################################################################
	// create joint between the two limbs
	morphogeneBranch = new MorphogeneBranch(JointPhysics::HINGE_JOINT, false,
		false, Ogre::Vector3(0, 0, 1), Ogre::Vector3(0, 1, 0),
		Ogre::Vector3(0, 0, 0), Ogre::Vector3(damping, 0, 0),
		Ogre::Vector3(0, 0, 0), Ogre::Vector3(0, 0, 3 * M_PI_4),
		Ogre::Vector3(btScalar(gapSize * 0.), btScalar(gapSize * -0.225),
			btScalar(gapSize * 0.)));

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
		Ogre::Vector3(ragDollSize * 0.1, ragDollSize * 0.37, ragDollSize * 0.1),
		Ogre::Quaternion::IDENTITY, 1, 10, true, Ogre::ColourValue(1, 0, 0),
		Ogre::Vector3(btScalar(gapSize * 0.), btScalar(gapSize * 0.185),
			btScalar(gapSize * 0.)));
	//	morphogene->initialize(0);
	genome->addGene(morphogene);

	// BODYPART_LEFT_UPPER_ARM
	morphogene = new Morphogene(type,
		Ogre::Vector3(ragDollSize * 0.1, ragDollSize * 0.33, ragDollSize * 0.1),
		Ogre::Euler(0, 0, M_PI_2).toQuaternion(), 1, 10, true,
		Ogre::ColourValue(1, 0, 0),
		Ogre::Vector3(btScalar(gapSize * 0.), btScalar(gapSize * -0.18),
			btScalar(gapSize * 0.)));
	//	morphogene->initialize(0);
	genome->addGene(morphogene);

	// ##################################################################
	// create joint between the two limbs
	morphogeneBranch = new MorphogeneBranch(JointPhysics::HINGE_JOINT, false,
		false, Ogre::Vector3(0, 0, 1), Ogre::Vector3(0, 1, 0),
		Ogre::Vector3(0, 0, 0), Ogre::Vector3(damping, 0, 0),
		Ogre::Vector3(0, 0, 0), Ogre::Vector3(3 * M_PI_4, 0, 0),
		Ogre::Vector3(btScalar(gapSize * 0.), btScalar(gapSize * 0.18),
			btScalar(gapSize * 0.)));

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
		Ogre::Vector3(ragDollSize * 0.08, ragDollSize * 0.25,
			ragDollSize * 0.08), Ogre::Euler(0, 0, M_PI_2).toQuaternion(), 1,
		10, true, Ogre::ColourValue(1, 0, 0),
		Ogre::Vector3(btScalar(gapSize * 0.), btScalar(gapSize * -0.14),
			btScalar(gapSize * 0.)));
	//	morphogene->initialize(0);
	genome->addGene(morphogene);

	//BODYPART_RIGHT_UPPER_ARM
	morphogene = new Morphogene(type,
		Ogre::Vector3(ragDollSize * 0.1, ragDollSize * 0.33, ragDollSize * 0.1),
		Ogre::Euler(0, 0, -M_PI_2).toQuaternion(), 1, 10, true,
		Ogre::ColourValue(1, 0, 0),
		Ogre::Vector3(btScalar(gapSize * 0.), btScalar(gapSize * -0.18),
			btScalar(gapSize * 0.)));
	//	morphogene->initialize(0);
	genome->addGene(morphogene);

	// ##################################################################
	// create joint between the two limbs
	morphogeneBranch = new MorphogeneBranch(JointPhysics::HINGE_JOINT, false,
		false, Ogre::Vector3(0, 0, 1), Ogre::Vector3(0, 1, 0),
		Ogre::Vector3(0, 0, 0), Ogre::Vector3(damping, 0, 0),
		Ogre::Vector3(0, 0, 0), Ogre::Vector3(3 * M_PI_4, 0, 0),
		Ogre::Vector3(btScalar(gapSize * 0.), btScalar(gapSize * 0.18),
			btScalar(gapSize * 0.)));

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
		Ogre::Vector3(ragDollSize * 0.08, ragDollSize * 0.25,
			ragDollSize * 0.08), Ogre::Euler(0, 0, -M_PI_2).toQuaternion(), 1,
		10, true, Ogre::ColourValue(1, 0, 0), Ogre::Vector3(1, 0, 0));
	//	morphogene->initialize(0);
	genome->addGene(morphogene);

}
