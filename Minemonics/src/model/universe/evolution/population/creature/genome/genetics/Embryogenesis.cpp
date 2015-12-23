//# corresponding header
#include <model/universe/evolution/population/creature/genome/genetics/Embryogenesis.hpp>

//# forward declarations
//# system headers
#include <map>
#include <vector>

//## controller headers
//## model headers
#include <LinearMath/btTransform.h>
#include <OgreQuaternion.h>
#include <OgreVector3.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
#include <model/universe/evolution/population/creature/CreatureModel.hpp>
#include <model/universe/evolution/population/creature/genome/genetics/BaseGenerator.hpp>
#include <model/universe/evolution/population/creature/genome/Gene.hpp>
#include <model/universe/evolution/population/creature/genome/Genome.hpp>
#include <model/universe/evolution/population/creature/genome/morphology/MorphogeneBranch.hpp>
#include <model/universe/evolution/population/creature/genome/MixedGenome.hpp>

//## view headers
//## utils headers
#include <utils/MathUtils.hpp>

BoostLogger Embryogenesis::mBoostLogger; /*<! initialize the boost logger*/
Embryogenesis::_Init Embryogenesis::_initializer;
void Embryogenesis::transcribeGene(
	std::list<PhenotypeGenerator*>& generatorList, int& totalSegmentCounter,
	PhenomeModel* phenomeModel, BaseGenerator* generator) {

	switch (generator->getGene()->getType()) { 	// what is the next gene type?
	case Gene::MorphoGene: {
		transcribeMorphogene(generatorList, totalSegmentCounter, phenomeModel,
			(PhenotypeGenerator*) generator); // transcribe morphogene
		break;
	}
	default: {
		break;
	}
	}
}

void Embryogenesis::transcribeMorphogene(
	std::list<PhenotypeGenerator*>& generatorList, int& totalSegmentCounter,
	PhenomeModel* phenomeModel, PhenotypeGenerator* generator) {

	MixedGenome* genome = &phenomeModel->getCreatureModel()->getGenotype(); // get the genome of this phenome model

	if (generator->getRoot2LeafPath() == genome->getSegmentsDepthLimit() // return if this creature limb chain is longer than allowed OR
	|| totalSegmentCounter == genome->getTotalSegmentQtyLimit()) { // if the creature wants to use more limbs than allowed
		return;
	} else {
		totalSegmentCounter++; // otherwise increase total segment counter
	}

	//PARENT
	btTransform parentLimbSurfaceAnchor; /**!< The position on the surface of the parent limb */
	parentLimbSurfaceAnchor.setIdentity();

	Ogre::Vector3 jointPivotInW(0, 0, 0); /**!< The joint pivot in world coordinates */

	//CHILD
	Morphogene* childMorphogene = ((Morphogene*) generator->getGene());
	btTransform childLimbSurfaceAnchor; /**!< get the morphogene and start creating the limb and its joint to its parent */
	childLimbSurfaceAnchor.setIdentity();

	// APPEND TO PARENT?
	if (generator->getParentComponentModel() != NULL) { // if there exists a parent component
		// then we calculate the position of the new limb according to the parent component
		phenomeModel->calculateChildPositionRelativeToParent(generator,
			parentLimbSurfaceAnchor, childLimbSurfaceAnchor, childMorphogene,
			jointPivotInW);
	}

	// get the child limb rotation
	Ogre::Quaternion childLimbOrientation(childMorphogene->getOrientationW(),
		childMorphogene->getOrientationX(), childMorphogene->getOrientationY(),
		childMorphogene->getOrientationZ());

	if (!MathUtils::isFinite(generator->getOrientation())) {
		BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::fatal)<< " NaN/Inf detected in generator orientation: " << generator->getOrientation();
	}

	if (!MathUtils::isFinite(generator->getPosition())) {
		BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::fatal)<< " NaN/Inf detected in generator position: " << generator->getPosition();
	}

	generator->setOrientation(
		generator->getOrientation() * childLimbOrientation); // update the generator orientation using the child element rotation

	LimbModel* childLimb = phenomeModel->createLimb(generator, childMorphogene); // create new child limb

	if (generator->getParentComponentModel() != NULL) { // if there exists a parent component
		// we connect it to the child limb with a joint
		phenomeModel->appendToParentLimb(childLimb, generator, jointPivotInW,
			parentLimbSurfaceAnchor, childLimbSurfaceAnchor);
	}

	// create new generators from the morphogene branches
	createNewGenerators(phenomeModel, childMorphogene, childLimb, generator,
		generatorList, totalSegmentCounter);
}

void Embryogenesis::createNewGenerators(PhenomeModel* phenomeModel,
	Morphogene* childMorphogene, LimbModel* childLimb,
	PhenotypeGenerator* generator,
	std::list<PhenotypeGenerator*>& generatorList, int& totalSegmentCounter) {

	//iterate over all morphogene branches
	for (std::vector<MorphogeneBranch*>::iterator branchIt =
		childMorphogene->getGeneBranches().begin();
		branchIt != childMorphogene->getGeneBranches().end(); branchIt++) {

		// only add a new generator if the branch is active and its branching gene type is valid
		if ((*branchIt)->isActive() && (*branchIt)->getBranchGeneType() >= 0
			&& (*branchIt)->getBranchGeneType()
				< phenomeModel->getCreatureModel()->getGenotype().getGenes().size()) {

			Morphogene* branchingMorphoGeneType =
				(Morphogene*) phenomeModel->getCreatureModel()->getGenotype().getGenes()[(*branchIt)->getBranchGeneType()]; // get the branch gene type defined by the branch

			PhenotypeGenerator* generatorFromBranch = new PhenotypeGenerator(); // create a new generator from the branch
			generatorFromBranch->initialize(generator->getRepetitionList(),
				generator->getPosition(), generator->getOrientation(),
				childLimb, (*branchIt.base()),
				childMorphogene->getSegmentShrinkFactor()
					* generator->getCurrentShrinkageFactor(),
				generator->isFlipped(), generator->isMirrored()/*Mirrored*/);

			// If repetition limit of this gene is not exceeded within this path
			// if the repetition limit is higher than 0 AND (if it does not find the key OR if the repetition limit of the key is not exceeded)
			if (generatorFromBranch->getRepetitionList().find(
				(*branchIt)->getBranchGeneType())
				== generatorFromBranch->getRepetitionList().end()) {

				generatorFromBranch->getRepetitionList()[(*branchIt)->getBranchGeneType()] =
					0; // set zero repetitions of this branching morphogene type
				generatorFromBranch->setGene(branchingMorphoGeneType);
			} else if (generatorFromBranch->getRepetitionList()[(*branchIt)->getBranchGeneType()]
				< branchingMorphoGeneType->getRepetitionLimit()) {

				generatorFromBranch->getRepetitionList()[(*branchIt)->getBranchGeneType()]++; //add another of this branching morphogene type
				generatorFromBranch->setGene(branchingMorphoGeneType);
			} else {

				//add the branching morphogene's follow up gene because the repetition limit of the branching morphogene is exceeded
				if (branchingMorphoGeneType->getFollowUpGene() >= 0
					&& phenomeModel->getCreatureModel()->getGenotype().getGenes().size()
						> branchingMorphoGeneType->getFollowUpGene()) { // if the follow up gene is defined in a valid range
					generatorFromBranch->setGene(
						phenomeModel->getCreatureModel()->getGenotype().getGenes()[branchingMorphoGeneType->getFollowUpGene()]);
				}
			}

			if (generatorFromBranch->getGene() != NULL) {

				generatorFromBranch->setRoot2LeafPath(
					generator->getRoot2LeafPath() + 1); // increase root to leaf path length by 1

				generatorList.push_back(generatorFromBranch); //add generator to the list
			} else {
				delete generatorFromBranch; // delete the generator because its gene is not set
				generatorFromBranch = NULL;
			}

			// if the branch also defines a flipped branch
			if ((*branchIt)->isFlipped()) {

				PhenotypeGenerator* flippedGeneratorFromBranch =
					new PhenotypeGenerator(); // create a new generator with the flipped flag set

				flippedGeneratorFromBranch->initialize(
					generator->getRepetitionList(), generator->getPosition(),
					generator->getOrientation(), childLimb, (*branchIt.base()),
					childMorphogene->getSegmentShrinkFactor()
						* generator->getCurrentShrinkageFactor(),
					!generator->isFlipped() /*Flipped*/,
					generator->isMirrored());

				// If repetition limit not exceeded
				// (if it does not find the key OR if the repetition limit of the key is not exceeded)
				if (flippedGeneratorFromBranch->getRepetitionList().find(
					(*branchIt)->getBranchGeneType())
					== flippedGeneratorFromBranch->getRepetitionList().end()) {

					flippedGeneratorFromBranch->getRepetitionList()[(*branchIt)->getBranchGeneType()] =
						0; // set zero repetitions of this branching morphogene type
					flippedGeneratorFromBranch->setGene(
						branchingMorphoGeneType);
				} else if (flippedGeneratorFromBranch->getRepetitionList()[(*branchIt)->getBranchGeneType()]
					< branchingMorphoGeneType->getRepetitionLimit()) {

					flippedGeneratorFromBranch->getRepetitionList()[(*branchIt)->getBranchGeneType()]++; //add another of this branching morphogene type
					flippedGeneratorFromBranch->setGene(
						branchingMorphoGeneType);
				} else {

					//add the branching morphogene's follow up gene because the repetition limit of the branching morphogene is exceeded
					// if the follow up gene is defined in a valid range
					if (branchingMorphoGeneType->getFollowUpGene() >= 0
						&& phenomeModel->getCreatureModel()->getGenotype().getGenes().size()
							> branchingMorphoGeneType->getFollowUpGene()) {

						Morphogene* followupGene =
							(Morphogene*) phenomeModel->getCreatureModel()->getGenotype().getGenes()[branchingMorphoGeneType->getFollowUpGene()]; // get the branch follow up gene type defined by the branch
						flippedGeneratorFromBranch->setGene(followupGene);
					}
				}

				if (flippedGeneratorFromBranch->getGene() != NULL) {
					flippedGeneratorFromBranch->setRoot2LeafPath(
						generator->getRoot2LeafPath() + 1); // increase root to leaf path length by 1

					generatorList.push_back(flippedGeneratorFromBranch); //add generator to the list
				} else {
					delete flippedGeneratorFromBranch; // delete the generator because its gene is not set
					flippedGeneratorFromBranch = NULL;
				}
			}

			// if the branch also defines a mirrored branch
			if ((*branchIt)->isMirrored()) {
				// create the new generator
				PhenotypeGenerator* mirroredGeneratorFromBranch =
					new PhenotypeGenerator();
				mirroredGeneratorFromBranch->initialize(
					generator->getRepetitionList(), generator->getPosition(),
					generator->getOrientation(), childLimb, (*branchIt.base()),
					childMorphogene->getSegmentShrinkFactor()
						* generator->getCurrentShrinkageFactor(),
					generator->isFlipped(),
					!generator->isMirrored()/*Mirrored*/);

				// If repetition limit not exceeded
				// if the repetition limit is higher than 0 AND (if it does not find the key OR if the repetition limit of the key is not exceeded)
				if (mirroredGeneratorFromBranch->getRepetitionList().find(
					(*branchIt)->getBranchGeneType())
					== mirroredGeneratorFromBranch->getRepetitionList().end()) {

					mirroredGeneratorFromBranch->getRepetitionList()[(*branchIt)->getBranchGeneType()] =
						0; // set zero repetitions of this branching morphogene type
					mirroredGeneratorFromBranch->setGene(
						branchingMorphoGeneType);
				} else if (mirroredGeneratorFromBranch->getRepetitionList()[(*branchIt)->getBranchGeneType()]
					< branchingMorphoGeneType->getRepetitionLimit()) {

					mirroredGeneratorFromBranch->getRepetitionList()[(*branchIt)->getBranchGeneType()]++; //add another of this branching morphogene type
					mirroredGeneratorFromBranch->setGene(
						branchingMorphoGeneType);
				} else {

					//add the branching morphogene's follow up gene because the repetition limit of the branching morphogene is exceeded
					if (branchingMorphoGeneType->getFollowUpGene() >= 0
						&& phenomeModel->getCreatureModel()->getGenotype().getGenes().size()
							> branchingMorphoGeneType->getFollowUpGene()) { // if the follow up gene is defined in a valid range
						mirroredGeneratorFromBranch->setGene(
							phenomeModel->getCreatureModel()->getGenotype().getGenes()[branchingMorphoGeneType->getFollowUpGene()]);
					}
				}

				if (mirroredGeneratorFromBranch->getGene() != NULL) {
					mirroredGeneratorFromBranch->setRoot2LeafPath(
						generator->getRoot2LeafPath() + 1); // increase root to leaf path length by 1

					generatorList.push_back(mirroredGeneratorFromBranch); //add generator to the list
				} else {
					delete mirroredGeneratorFromBranch; // delete the generator because its gene is not set
					mirroredGeneratorFromBranch = NULL;
				}
			}
		}
	}

}
