//# corresponding headers
#include <model/universe/evolution/population/creature/modelOrganism/snake/SnakeBuilder.hpp>

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

void SnakeBuilder::build(MixedGenome* genome,
	ControllerGene::ControllerType controllerType) {
	int snakeLength = 15;
	genome->setTotalSegmentQtyLimit(snakeLength);
	genome->setSegmentsDepthLimit(snakeLength);

	// create limb
	Morphogene* morphogene = new Morphogene(LimbPhysics::BLOCK,
		Ogre::Vector3(20, 6, 6), Ogre::Quaternion(1, 0, 0, 0), 1, 10, true,
		Ogre::ColourValue(1, 0, 0), Ogre::Vector3(1, 0, 0));
	morphogene->setRepetitionLimit(snakeLength);

	genome->addGene(morphogene);

	double damping = 0.05f;//[0.005;0.5] 0.05
	// create joint between the two limbs
	MorphogeneBranch* morphogeneBranch = new MorphogeneBranch(
		JointPhysics::HINGE_JOINT, false, false, Ogre::Vector3(0, 0, 1),
		Ogre::Vector3(0, 1, 0), Ogre::Vector3(0, 0, 0),
		Ogre::Vector3(damping, damping, damping),
		Ogre::Vector3(-boost::math::constants::pi<double>() / 2.0f + PhysicsConfiguration::UNIV_EPS,
			-boost::math::constants::pi<double>() * 1.5f + PhysicsConfiguration::UNIV_EPS,
			-boost::math::constants::pi<double>() * 1.5f + PhysicsConfiguration::UNIV_EPS),
		Ogre::Vector3(boost::math::constants::pi<double>() / 2.0f - PhysicsConfiguration::UNIV_EPS,
			boost::math::constants::pi<double>() * 1.5f - PhysicsConfiguration::UNIV_EPS,
			boost::math::constants::pi<double>() * 1.5f - PhysicsConfiguration::UNIV_EPS),
		Ogre::Vector3(-1, 0, 0));

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
		double x = -1.5f; // x
		double y = 0; // y
		double z = 0; // z

		//	// stronger initial force output on z
//		double x = 0.0f; // x
//		double y = 0.0f; // y
//		double z = 2.0f; // z

		double speed = 1;

		for (int i = 0; i < 3; i++) {
			// create instances of the chaotic controller gene for the morphogene.
				ChaoticControllerGene* chaoticController =
					new ChaoticControllerGene(ChaoticControllerGene::CHUA_CIRCUIT,
						x, y, z, speed);
			morphogeneBranch->getControllerGenes().push_back(chaoticController);
		}
	}

	morphogeneBranch->setActive(true);
	morphogeneBranch->setBranchGeneType(0);

	// add joint to the first limb branching to the second limb
	morphogene->getGeneBranches().push_back(morphogeneBranch);

}
