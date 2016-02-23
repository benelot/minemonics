//# corresponding headers
#include <model/universe/evolution/population/creature/modelOrganism/pod/PodBuilder.hpp>

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
#include <model/universe/evolution/population/creature/genome/controller/SineControllerGene.hpp>
#include <model/universe/evolution/population/creature/genome/controller/ChaoticControllerGene.hpp>
#include <model/universe/evolution/population/creature/genome/morphology/Morphogene.hpp>
#include <model/universe/evolution/population/creature/genome/morphology/MorphogeneBranch.hpp>

//## view headers
//## utils headers
#include <utils/ogre3D/Euler.hpp>

#define NUM_BODIES 10
#define NUM_LEGS NUM_BODIES * 2
#define NUM_LEG_SEGMENTS 2
#define BODYPART_COUNT NUM_LEGS*NUM_LEG_SEGMENTS + NUM_BODIES

void PodBuilder::build(MixedGenome* genome,
	ControllerGene::ControllerType controllerType) {
	genome->setTotalSegmentQtyLimit(BODYPART_COUNT);
	genome->setSegmentsDepthLimit(BODYPART_COUNT);

	LimbPhysics::PrimitiveType primitiveType = LimbPhysics::BLOCK; // the primitive type of the creature
	double podSize = MorphologyConfiguration::LIMB_MAX_SIZE; // size of the hole pod
	double bodySize = podSize * 0.33f; // size of a single body of the whole creature
	double upperLegLength = podSize * 0.75f; //upper leg length
	double legThickness = podSize*0.1f;
	double lowerLegLength = podSize * 0.3f; // upper lower leg length
	double totalLegsAngle = boost::math::constants::pi<double>() / 2.0f; // the angle over which all legs are symmetrically distributed centered around the middle
	double damping = 0.0f; //[0.005;0.5] 0.05 // damping coefficient for the joints

	{
		// define body segments
		Morphogene* bodyMorphogene = new Morphogene(primitiveType,
			Ogre::Vector3(bodySize * 2.0f, bodySize / 2.0f, bodySize),
			Ogre::Quaternion::IDENTITY, 1, 10, true, Ogre::ColourValue(1, 0, 0),
			Ogre::Vector3(1, 0, 0));
		bodyMorphogene->setSegmentShrinkFactor(1.01);
		bodyMorphogene->setRepetitionLimit(NUM_BODIES - 1); // number of repetitions of the body element and its branches
		genome->addGene(bodyMorphogene);

		// define the joints between the body segments
		MorphogeneBranch* bodyBranch = new MorphogeneBranch(
			JointPhysics::HINGE_JOINT, false, false, Ogre::Vector3(0, 0, 1),
			Ogre::Vector3(0, 1, 0), Ogre::Vector3(0, 0, 0),
			Ogre::Vector3(damping, damping, damping),
			Ogre::Vector3(
				-boost::math::constants::pi<double>() / 2.0f
					+ PhysicsConfiguration::UNIV_EPS,
				-boost::math::constants::pi<double>() * 1.5f
					+ PhysicsConfiguration::UNIV_EPS,
				-boost::math::constants::pi<double>() * 1.5f
					+ PhysicsConfiguration::UNIV_EPS),
			Ogre::Vector3(
				boost::math::constants::pi<double>() / 2.0f
					- PhysicsConfiguration::UNIV_EPS,
				boost::math::constants::pi<double>() * 1.5f
					- PhysicsConfiguration::UNIV_EPS,
				boost::math::constants::pi<double>() * 1.5f
					- PhysicsConfiguration::UNIV_EPS), Ogre::Vector3(-1, 0, 0));

		switch (controllerType) { // add controllers to the joint
		case ControllerGene::SineControllerGene:
			// create instances of the sine controller gene for the morphogene.
			for (int i = 0; i < 3; i++) {
				SineControllerGene* sineController = new SineControllerGene();
				sineController->initialize();
				bodyBranch->getControllerGenes().push_back(sineController);
			}
			break;
		case ControllerGene::ChaoticControllerGene:
			// create instances of the chaotic controller gene for the morphogene.
			double x = -1.5f; // x
			double y = 0; // y
			double z = 0; // z

			// stronger initial force output on z
//			double x = 0.0f; // x
//			double y = 0.0f; // y
//			double z = 2.0f; // z

			double speed = 1;

			for (int i = 0; i < 3; i++) {
				// create instances of the chaotic controller gene for the morphogene.
				ChaoticControllerGene* chaoticController =
					new ChaoticControllerGene(
						ChaoticControllerGene::CHUA_CIRCUIT, x, y, z, speed);

				chaoticController->initialize();

				bodyBranch->getControllerGenes().push_back(chaoticController);
			}
			break;

		}

		bodyBranch->setActive(true);
		bodyBranch->setBranchGeneType(0);

		bodyMorphogene->getGeneBranches().push_back(bodyBranch); // add joint to the first limb branching to the second limb

		// setup starting conditions to attach legs to the abdomen
		Ogre::Vector3 centerLegAngleVector(0, 0, 1); // right center of leg distribution
		int legsPerBody = NUM_LEGS / NUM_BODIES; // number of legs per body segment
		double angularStep = 2.0f * totalLegsAngle / legsPerBody; // the angular step between each leg on a body
		double currentAngle = totalLegsAngle / 2.0f
			- totalLegsAngle / (legsPerBody / 2.0f + 1.0f); // the current angular rotation of the leg attachment vector

			// attach legs to the abdomen
		for (int i = 0; i < legsPerBody / 2.0f; i++) {
			Ogre::Vector3 legAngleVector =
				Ogre::Euler(currentAngle, 0, 0).toQuaternion()
					* centerLegAngleVector; // rotate the right vector appropriately

			// define the joint between the upper and the lower legs
			// Hingelike
			MorphogeneBranch* rightLegBranch = new MorphogeneBranch(
				JointPhysics::HINGE_JOINT, false, false, Ogre::Vector3(0, 0, 1),
				Ogre::Vector3(0, 1, 0), Ogre::Vector3(0, 0, 0),
				Ogre::Vector3(damping, damping, damping),
				Ogre::Vector3(-PhysicsConfiguration::UNIV_EPS,
					-PhysicsConfiguration::UNIV_EPS,
					-boost::math::constants::pi<double>() * 2.0f
						+ PhysicsConfiguration::UNIV_EPS),
				Ogre::Vector3(PhysicsConfiguration::UNIV_EPS,
					PhysicsConfiguration::UNIV_EPS,
					boost::math::constants::pi<double>() * 2.0f
						- PhysicsConfiguration::UNIV_EPS), legAngleVector);

//			MorphogeneBranch* rightLegBranch = new MorphogeneBranch(
//				JointPhysics::HINGE_JOINT, false, true, Ogre::Vector3(0, 0, 1),
//				Ogre::Vector3(0, 1, 0), Ogre::Vector3(0, 0, 0),
//				Ogre::Vector3(damping, damping, damping),
//				Ogre::Vector3(
//					-boost::math::constants::pi<double>() / 2.0f + UNIV_EPS,
//					-boost::math::constants::pi<double>() * 2.0f + UNIV_EPS,
//					-boost::math::constants::pi<double>() * 2.0f + UNIV_EPS),
//				Ogre::Vector3(
//					boost::math::constants::pi<double>() / 2.0f - UNIV_EPS,
//					boost::math::constants::pi<double>() * 2.0f - UNIV_EPS,
//					boost::math::constants::pi<double>() * 2.0f - UNIV_EPS),
//				legAngleVector);
//			rightLegBranch->initialize();

			switch (controllerType) { // add controllers to the joint
			case ControllerGene::SineControllerGene:
				// create instances of the sine controller gene for the morphogene.
				for (int i = 0; i < 3; i++) {
					SineControllerGene* sineController =
						new SineControllerGene();
					sineController->initialize();
					rightLegBranch->getControllerGenes().push_back(
						sineController);
				}
				break;
			case ControllerGene::ChaoticControllerGene:
				// create instances of the chaotic controller gene for the morphogene.
				double x = -1.5f; // x
				double y = 0; // y
				double z = 0; // z

				// stronger initial force output on z
//				double x = 0.0f; // x
//				double y = 0.0f; // y
//				double z = 2.0f; // z

				double speed = 1;

				for (int i = 0; i < 3; i++) {
					ChaoticControllerGene* chaoticController =
						new ChaoticControllerGene(
							ChaoticControllerGene::CHUA_CIRCUIT, x, y, z,
							speed);

					chaoticController->initialize();
					rightLegBranch->getControllerGenes().push_back(
						chaoticController);
				}
			}

			rightLegBranch->setActive(true);
			rightLegBranch->setBranchGeneType(genome->getGenes().size());
			bodyMorphogene->getGeneBranches().push_back(rightLegBranch); // add joint to the upper limb branching to the lower limb

			currentAngle -= angularStep; // increase angular step

		}

		legsPerBody = NUM_LEGS / NUM_BODIES; // number of legs per body segment
		angularStep = 2.0f * totalLegsAngle / legsPerBody; // the angular step between each leg on a body
		currentAngle = totalLegsAngle / 2.0f
			- totalLegsAngle / (legsPerBody / 2.0f + 1.0f); // the current angular rotation of the leg attachment vector
		// attach legs to the abdomen
		for (int i = 0; i < legsPerBody / 2.0f; i++) {
			Ogre::Vector3 legAngleVector =
				Ogre::Euler(currentAngle, 0, 0).toQuaternion()
					* centerLegAngleVector; // rotate the right vector appropriately

			// define the joint between the upper and the lower legs
			// Hingelike
			MorphogeneBranch* leftLegBranch = new MorphogeneBranch(
				JointPhysics::HINGE_JOINT, false, false, Ogre::Vector3(0, 0, 1),
				Ogre::Vector3(0, 1, 0), Ogre::Vector3(0, 0, 0),
				Ogre::Vector3(damping, damping, damping),
				Ogre::Vector3(-PhysicsConfiguration::UNIV_EPS,
					-PhysicsConfiguration::UNIV_EPS,
					-boost::math::constants::pi<double>() * 2.0f
						+ PhysicsConfiguration::UNIV_EPS),
				Ogre::Vector3(PhysicsConfiguration::UNIV_EPS,
					PhysicsConfiguration::UNIV_EPS,
					boost::math::constants::pi<double>() * 2.0f
						- PhysicsConfiguration::UNIV_EPS), -legAngleVector);

			//			MorphogeneBranch* leftLegBranch = new MorphogeneBranch(
			//				JointPhysics::HINGE_JOINT, false, false, Ogre::Vector3(0, 0, 1),
			//				Ogre::Vector3(0, 1, 0), Ogre::Vector3(0, 0, 0),
			//				Ogre::Vector3(damping, damping, damping),
			//				Ogre::Vector3(
			//					-boost::math::constants::pi<double>() / 2.0f + UNIV_EPS,
			//					-boost::math::constants::pi<double>() * 2.0f + UNIV_EPS,
			//					-boost::math::constants::pi<double>() * 2.0f + UNIV_EPS),
			//				Ogre::Vector3(
			//					boost::math::constants::pi<double>() / 2.0f - UNIV_EPS,
			//					boost::math::constants::pi<double>() * 2.0f - UNIV_EPS,
			//					boost::math::constants::pi<double>() * 2.0f - UNIV_EPS),
			//				legAngleVector);
			//			rightLegBranch->initialize();

			switch (controllerType) { // add controllers to the joint
			case ControllerGene::SineControllerGene:
				// create instances of the sine controller gene for the morphogene.
				for (int i = 0; i < 3; i++) {
					SineControllerGene* sineController =
						new SineControllerGene();
					sineController->initialize();
					leftLegBranch->getControllerGenes().push_back(
						sineController);
				}
				break;
			case ControllerGene::ChaoticControllerGene:
				// create instances of the chaotic controller gene for the morphogene.
				double x = -1.5f; // x
				double y = 0; // y
				double z = 0; // z

				// stronger initial force output on z
				//				double x = 0.0f; // x
				//				double y = 0.0f; // y
				//				double z = 2.0f; // z

				double speed = 1;

				for (int i = 0; i < 3; i++) {
					ChaoticControllerGene* chaoticController =
						new ChaoticControllerGene(
							ChaoticControllerGene::CHUA_CIRCUIT, x, y, z,
							speed);

					chaoticController->initialize();
					leftLegBranch->getControllerGenes().push_back(
						chaoticController);
				}
			}

			leftLegBranch->setActive(true);
			leftLegBranch->setBranchGeneType(genome->getGenes().size()+1);
			bodyMorphogene->getGeneBranches().push_back(leftLegBranch); // add joint to the upper limb branching to the lower limb

			currentAngle -= angularStep; // increase angular step

		}

	}

	{
		// create upper leg limb
		Morphogene* upperLegMorphogene = new Morphogene(primitiveType,
			Ogre::Vector3(legThickness, legThickness, upperLegLength),
			Ogre::Quaternion::IDENTITY, 1, 10, true, Ogre::ColourValue(1, 0, 0),
			Ogre::Vector3(1, 0, 0));
//		upperLegMorphogene->initialize(0);
		genome->addGene(upperLegMorphogene);

		// create joint between the upper and lower leg
		// Hingelike
		MorphogeneBranch* legBranch = new MorphogeneBranch(
			JointPhysics::HINGE_JOINT, false, false, Ogre::Vector3(1, 0, 0),
			Ogre::Vector3(0, 1, 0), Ogre::Vector3(0, 0, 0),
			Ogre::Vector3(damping, damping, damping),
			Ogre::Vector3(-PhysicsConfiguration::UNIV_EPS,
				-PhysicsConfiguration::UNIV_EPS,
				-boost::math::constants::pi<double>() * 2.0f
					+ PhysicsConfiguration::UNIV_EPS),
			Ogre::Vector3(PhysicsConfiguration::UNIV_EPS,
				PhysicsConfiguration::UNIV_EPS,
				boost::math::constants::pi<double>() * 2.0f
					- PhysicsConfiguration::UNIV_EPS), Ogre::Vector3(0, 0, 1));

//		MorphogeneBranch* legBranch = new MorphogeneBranch(
//			JointPhysics::HINGE_JOINT, false, false, Ogre::Vector3(0, 0, 1),
//			Ogre::Vector3(0, 1, 0), Ogre::Vector3(0, 0, 0),
//			Ogre::Vector3(0.5f, 0.5f, 0.5f),
//			Ogre::Vector3(
//				-boost::math::constants::pi<double>() / 2.0f + UNIV_EPS,
//				-boost::math::constants::pi<double>() * 2.0f + UNIV_EPS,
//				-boost::math::constants::pi<double>() * 2.0f + UNIV_EPS),
//			Ogre::Vector3(
//				boost::math::constants::pi<double>() / 2.0f - UNIV_EPS,
//				boost::math::constants::pi<double>() * 2.0f - UNIV_EPS,
//				boost::math::constants::pi<double>() * 2.0f - UNIV_EPS),
//			Ogre::Vector3(1, 0, 0));
//		legBranch->initialize();

		switch (controllerType) {
		case ControllerGene::SineControllerGene:
			// create instances of the sine controller gene for the morphogene.
			for (int i = 0; i < 3; i++) {
				SineControllerGene* sineController = new SineControllerGene();
				sineController->initialize();
				legBranch->getControllerGenes().push_back(sineController);
			}
			break;
		case ControllerGene::ChaoticControllerGene:
			// create instances of the chaotic controller gene for the morphogene.
			double x = -1.5f; // x
			double y = 0; // y
			double z = 0; // z

			// stronger initial force output on z
//			double x = 0.0f; // x
//			double y = 0.0f; // y
//			double z = 2.0f; // z

			double speed = 1;

			for (int i = 0; i < 3; i++) {
				ChaoticControllerGene* chaoticController =
					new ChaoticControllerGene(
						ChaoticControllerGene::CHUA_CIRCUIT, x, y, z, speed);

//			chaoticController->initialize();
				legBranch->getControllerGenes().push_back(chaoticController);
			}
		}

		legBranch->setActive(true);
		legBranch->setBranchGeneType(genome->getGenes().size()+1);

		// add joint to the first limb branching to the second limb
		upperLegMorphogene->getGeneBranches().push_back(legBranch);
	}

	{
		// create upper leg limb
		Morphogene* upperLegMorphogene = new Morphogene(primitiveType,
			Ogre::Vector3(legThickness, legThickness, upperLegLength),
			Ogre::Quaternion::IDENTITY, 1, 10, true, Ogre::ColourValue(1, 0, 0),
			Ogre::Vector3(-1, 0, 0));
//		upperLegMorphogene->initialize(0);
		genome->addGene(upperLegMorphogene);

		// create joint between the upper and lower leg
		// Hingelike
		MorphogeneBranch* legBranch = new MorphogeneBranch(
			JointPhysics::HINGE_JOINT, false, false, Ogre::Vector3(1, 0, 0),
			Ogre::Vector3(0, 1, 0), Ogre::Vector3(0, 0, 0),
			Ogre::Vector3(damping, damping, damping),
			Ogre::Vector3(-PhysicsConfiguration::UNIV_EPS,
				-PhysicsConfiguration::UNIV_EPS,
				-boost::math::constants::pi<double>() * 2.0f
					+ PhysicsConfiguration::UNIV_EPS),
			Ogre::Vector3(PhysicsConfiguration::UNIV_EPS,
				PhysicsConfiguration::UNIV_EPS,
				boost::math::constants::pi<double>() * 2.0f
					- PhysicsConfiguration::UNIV_EPS), Ogre::Vector3(0, 0, -1));

//		MorphogeneBranch* legBranch = new MorphogeneBranch(
//			JointPhysics::HINGE_JOINT, false, false, Ogre::Vector3(0, 0, 1),
//			Ogre::Vector3(0, 1, 0), Ogre::Vector3(0, 0, 0),
//			Ogre::Vector3(0.5f, 0.5f, 0.5f),
//			Ogre::Vector3(
//				-boost::math::constants::pi<double>() / 2.0f + UNIV_EPS,
//				-boost::math::constants::pi<double>() * 2.0f + UNIV_EPS,
//				-boost::math::constants::pi<double>() * 2.0f + UNIV_EPS),
//			Ogre::Vector3(
//				boost::math::constants::pi<double>() / 2.0f - UNIV_EPS,
//				boost::math::constants::pi<double>() * 2.0f - UNIV_EPS,
//				boost::math::constants::pi<double>() * 2.0f - UNIV_EPS),
//			Ogre::Vector3(1, 0, 0));
//		legBranch->initialize();

		switch (controllerType) {
		case ControllerGene::SineControllerGene:
			// create instances of the sine controller gene for the morphogene.
			for (int i = 0; i < 3; i++) {
				SineControllerGene* sineController = new SineControllerGene();
				sineController->initialize();
				legBranch->getControllerGenes().push_back(sineController);
			}
			break;
		case ControllerGene::ChaoticControllerGene:
			// create instances of the chaotic controller gene for the morphogene.
			double x = -1.5f; // x
			double y = 0; // y
			double z = 0; // z

			// stronger initial force output on z
//			double x = 0.0f; // x
//			double y = 0.0f; // y
//			double z = 2.0f; // z

			double speed = 1;

			for (int i = 0; i < 3; i++) {
				ChaoticControllerGene* chaoticController =
					new ChaoticControllerGene(
						ChaoticControllerGene::CHUA_CIRCUIT, x, y, z, speed);

//			chaoticController->initialize();
				legBranch->getControllerGenes().push_back(chaoticController);
			}
		}

		legBranch->setActive(true);
		legBranch->setBranchGeneType(genome->getGenes().size());

		// add joint to the first limb branching to the second limb
		upperLegMorphogene->getGeneBranches().push_back(legBranch);
	}

	// creature lower leg limb
	Morphogene* lowerLegMorphogene = new Morphogene(primitiveType,
		Ogre::Vector3(legThickness, lowerLegLength, legThickness),
		Ogre::Quaternion::IDENTITY, 1, 10, true, Ogre::ColourValue(1, 0, 0),
		Ogre::Vector3(0, 1, 0));
//	lowerLegMorphogene->initialize(0);
	genome->addGene(lowerLegMorphogene);
}
