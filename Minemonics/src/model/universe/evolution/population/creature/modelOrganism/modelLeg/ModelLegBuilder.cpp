//# corresponding headers
#include <model/universe/evolution/population/creature/modelOrganism/modelLeg/ModelLegBuilder.hpp>

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

//## controller headers
//## model headers
#include <model/universe/evolution/population/creature/genome/controller/SineControllerGene.hpp>
#include <model/universe/evolution/population/creature/genome/controller/ChaoticControllerGene.hpp>

//## view headers
//## utils headers

void ModelLegBuilder::build(MixedGenome* genome,
	ControllerGene::ControllerType controllerType) {
	genome->setTotalSegmentQtyLimit(2);
	genome->setSegmentsDepthLimit(2);

	// create first limb
	Morphogene* morphogene = new Morphogene(LimbPhysics::BLOCK,
		Ogre::Vector3(20, 6, 6), Ogre::Quaternion::IDENTITY, 1, 10, true,
		Ogre::ColourValue(1, 0, 0), Ogre::Vector3(1, 0, 0));
//	morphogene->initialize(0);
	genome->addGene(morphogene);

	// creature second limb
	Morphogene* morphogene2 = new Morphogene(LimbPhysics::BLOCK,
		Ogre::Vector3(6, 20, 6), Ogre::Quaternion::IDENTITY, 1, 10, true,
		Ogre::ColourValue(1, 0, 0), Ogre::Vector3(0, 1, 0));
//	morphogene2->initialize(0);
	genome->addGene(morphogene2);

	double damping = 0.5f; //[0.005;0.5] 0.05
	// create joint between the two limbs
	// Hingelike
	MorphogeneBranch* morphogeneBranch = new MorphogeneBranch(
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
				- PhysicsConfiguration::UNIV_EPS), Ogre::Vector3(1, 0, 0));

//	MorphogeneBranch* morphogeneBranch = new MorphogeneBranch(
//		JointPhysics::HINGE_JOINT, false, false, Ogre::Vector3(0, 0, 1),
//		Ogre::Vector3(0, 1, 0), Ogre::Vector3(0, 0, 0),
//		Ogre::Vector3(0.5f, 0.5f, 0.5f),
//		Ogre::Vector3(-boost::math::constants::pi<double>() / 2.0f + UNIV_EPS,
//			-boost::math::constants::pi<double>() * 2.0f + UNIV_EPS,
//			-boost::math::constants::pi<double>() * 2.0f + UNIV_EPS),
//		Ogre::Vector3(boost::math::constants::pi<double>() / 2.0f - UNIV_EPS,
//			boost::math::constants::pi<double>() * 2.0f - UNIV_EPS,
//			boost::math::constants::pi<double>() * 2.0f - UNIV_EPS),
//		Ogre::Vector3(1, 0, 0));
//	morphogeneBranch->initialize();

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

	morphogeneBranch->setActive(true);
	morphogeneBranch->setBranchGeneType(1);

	// add joint to the first limb branching to the second limb
	morphogene->getGeneBranches().push_back(morphogeneBranch);
}
