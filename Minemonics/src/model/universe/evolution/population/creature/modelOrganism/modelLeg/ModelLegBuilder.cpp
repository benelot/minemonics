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
//## controller headers
//## model headers
#include <model/universe/evolution/population/creature/genome/MixedGenome.hpp>

//## view headers
//## utils headers

#ifndef UNIV_EPS
#define UNIV_EPS 0.01f
#endif

ModelLegBuilder::ModelLegBuilder() {
	// TODO Auto-generated constructor stub

}

ModelLegBuilder::~ModelLegBuilder() {
	// TODO Auto-generated destructor stub
}

void ModelLegBuilder::build(MixedGenome* genome) {
	genome->setTotalSegmentQtyLimit(2);
	genome->setSegmentsDepthLimit(2);

	// create first limb
	Morphogene* morphogene = new Morphogene(Ogre::Vector3(10, 2, 2),
		Ogre::Quaternion(0, 0, 0, 1), Ogre::Vector3(1, 0, 0),
		Ogre::Euler(0, 0, 0), LimbPhysics::BLOCK, Ogre::ColourValue(1, 0, 0), 1,
		0, true);
	morphogene->initialize(0);
	genome->addGene(morphogene);

	// creature second limb
	Morphogene* morphogene2 = new Morphogene(Ogre::Vector3(10, 2, 2),
		Ogre::Quaternion(0, 0, 0, 1), Ogre::Vector3(-1, 0, 0),
		Ogre::Euler(0, 0, 0), LimbPhysics::BLOCK, Ogre::ColourValue(1, 0, 0), 1,
		0, true);
	morphogene2->initialize(0);
	genome->addGene(morphogene2);

	// create joint between the two limbs
	MorphogeneBranch* morphogeneBranch = new MorphogeneBranch(
		Ogre::Vector3(-1, 0, 0), Ogre::Euler(0, 0, 0), Ogre::Vector3(0, 0, 0),
		Ogre::Vector3(boost::math::constants::pi<double>() / 2.0f - UNIV_EPS,
			boost::math::constants::pi<double>() - UNIV_EPS,
			boost::math::constants::pi<double>() - UNIV_EPS));
	morphogeneBranch->initialize();
	morphogeneBranch->setActive(true);
	morphogeneBranch->setBranchGeneType(1);

	// add joint to the first limb branching to the second limb
	morphogene->getGeneBranches().push_back(morphogeneBranch);
}
