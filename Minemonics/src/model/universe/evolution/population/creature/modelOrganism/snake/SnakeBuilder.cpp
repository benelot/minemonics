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
//## controller headers
//## model headers
#include <model/universe/evolution/population/creature/genome/MixedGenome.hpp>
#include <model/universe/evolution/population/creature/genome/controller/SineControllerGene.hpp>
#include <model/universe/evolution/population/creature/genome/controller/ChaoticControllerGene.hpp>

//## view headers
//## utils headers

#ifndef UNIV_EPS
#define UNIV_EPS 0.01f
#endif

void SnakeBuilder::build(MixedGenome* genome,
	ControllerGene::ControllerType controllerType) {
	int snakeLength = 15;
	genome->setTotalSegmentQtyLimit(snakeLength);
	genome->setSegmentsDepthLimit(snakeLength);

	// create limb
	Morphogene* morphogene = new Morphogene(Ogre::Vector3(6, 6, 20),
		Ogre::Quaternion(1, 0, 0, 0), Ogre::Vector3(0, 0, 1),
		Ogre::Euler(0, 0, 0), LimbPhysics::BLOCK, Ogre::ColourValue(1, 0, 0), 1,
		0, true);
	morphogene->setRepetitionLimit(snakeLength);

	genome->addGene(morphogene);

	// create joint between the two limbs
	MorphogeneBranch* morphogeneBranch = new MorphogeneBranch(
		Ogre::Vector3(0, 0, -1), Ogre::Euler(0, 0, 0),
		Ogre::Vector3(-boost::math::constants::pi<double>() / 2.0f + UNIV_EPS,
			-boost::math::constants::pi<double>() * 1.5f + UNIV_EPS,
			-boost::math::constants::pi<double>() * 1.5f + UNIV_EPS),
		Ogre::Vector3(boost::math::constants::pi<double>() / 2.0f - UNIV_EPS,
			boost::math::constants::pi<double>() * 1.5f - UNIV_EPS,
			boost::math::constants::pi<double>() * 1.5f - UNIV_EPS),
		Ogre::Vector3(1, 0, 0));

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
	morphogeneBranch->setBranchGeneType(0);

	// add joint to the first limb branching to the second limb
	morphogene->getGeneBranches().push_back(morphogeneBranch);

}
