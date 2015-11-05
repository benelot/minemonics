//# corresponding headers
#include <model/universe/evolution/population/creature/modelOrganism/modelLeg/ModelLegBuilder.hpp>

//# forward declarations
//# system headers
//## controller headers
//## model headers
//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
#include <model/universe/evolution/population/creature/genome/Genome.hpp>
//## view headers
//## utils headers

ModelLegBuilder::ModelLegBuilder() {
	// TODO Auto-generated constructor stub

}

ModelLegBuilder::~ModelLegBuilder() {
	// TODO Auto-generated destructor stub
}

void ModelLegBuilder::build(Genome* genome) {

	// create first limb
	Morphogene* morphogene = new Morphogene(Ogre::Vector3(1, 0.5, 0.5),
		Ogre::Quaternion(0, 0, 0, 1), Ogre::Vector3(1, 0, 0),
		Ogre::Euler(0, 0, 0), LimbPhysics::BLOCK, Ogre::ColourValue(1, 0, 0), 1,
		0, true);
	genome->addGene(morphogene);

	// creature second limb
	Morphogene* morphogene2 = new Morphogene(Ogre::Vector3(0.5, 1, 0.5),
		Ogre::Quaternion(0, 0, 0, 1), Ogre::Vector3(0, 1, 0),
		Ogre::Euler(0, 0, 0), LimbPhysics::BLOCK, Ogre::ColourValue(1, 0, 0), 1,
		0, true);
	genome->addGene(morphogene2);

	// create joint between the two limbs
	MorphogeneBranch* morphogeneBranch = new MorphogeneBranch(
		Ogre::Vector3(0, 1, 0), Ogre::Euler(0, 0, 0), Ogre::Vector3(0, 0, 0),
		Ogre::Vector3(0, 0, 0));
	morphogeneBranch->setBranchGeneType(1);

	// add joint to the first limb branching to the second limb
	morphogene->getGeneBranches().push_back(morphogeneBranch);
}
