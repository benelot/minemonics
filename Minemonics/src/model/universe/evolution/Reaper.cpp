//# corresponding header
#include <model/universe/evolution/Reaper.hpp>

//# forward declarations
//# system headers
#include <cmath>
#include <vector>

//## controller headers
//## model headers
#include <OgreVector3.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
#include <configuration/EvolutionConfiguration.hpp>
#include <configuration/MorphologyConfiguration.hpp>

//## model headers
#include <model/universe/evolution/population/PopulationModel.hpp>
#include <model/universe/evolution/population/creature/CreatureModel.hpp>
#include <model/universe/evolution/population/creature/genome/MixedGenome.hpp>
#include <model/universe/evolution/CreatureFitnessComparator.hpp>
#include <model/universe/evolution/CreatureFitnessScoreComparator.hpp>
#include <model/universe/environments/EnvironmentModel.hpp>
#include <model/universe/environments/physics/PhysicsController.hpp>
#include <model/universe/PlanetModel.hpp>

//## view headers
//## utils headers
#include <utils/Randomness.hpp>

Reaper::Reaper() :
	mGeneSplitPercentage(0), mGrowStubPercentage(0), mGraftPercentage(0), mBranchMutationPercentage(
		0), mCrossOverPercentage(0), mGeneMutationPercentage(0), mReapPercentage(
		0), mSowFreshPercentage(0) {
}

Reaper::~Reaper() {
}

void Reaper::initialize(const double reapPercentage,
	const double crossOverPercentage, const double geneMutationPercentage,
	const double geneSplitPercentage, const double branchMutationPercentage,
	const double growStubPercentage, const double graftPercentage,
	const double sowFreshPercentage) {
	mReapPercentage = reapPercentage;
	mCrossOverPercentage = crossOverPercentage;
	mGeneMutationPercentage = geneMutationPercentage;
	mGeneSplitPercentage = geneSplitPercentage;
	mBranchMutationPercentage = branchMutationPercentage;
	mGrowStubPercentage = growStubPercentage;
	mGraftPercentage = graftPercentage;
	mSowFreshPercentage = sowFreshPercentage;
}

void Reaper::reap(PopulationModel* const population) {

	//cull all preselected ones
	for (std::vector<CreatureModel*>::iterator cit =
		population->getCreatureModels().begin();
		cit != population->getCreatureModels().end();) {
		if ((*cit)->isCulled()) {
			cit = population->getCreatureModels().erase(cit);
		} else {
			cit++;
		}
	}

	int headsToReap = ceil(
		population->getCreatureModels().size() * mReapPercentage);

	//for each jury type
	for (int i = 0; i < population->getCreatureModels()[0]->getJuries().size();
		i++) {

		//sort by the ith criterium
		CreatureFitnessComparator comparator(i);
		std::sort(population->getCreatureModels().begin(),
			population->getCreatureModels().end(),
			comparator.compareCreatureFitness);

		//add linear scoring descending
		int j = population->getCreatureModels().size();
		for (std::vector<CreatureModel*>::iterator cit =
			population->getCreatureModels().begin();
			cit != population->getCreatureModels().end(); cit++, j--) {
			(*cit)->getJuries()[i]->setScore(j);
		}
	}

	// sort by the fitness score
	CreatureFitnessScoreComparator scoreComparator;
	std::sort(population->getCreatureModels().begin(),
		population->getCreatureModels().end(),
		scoreComparator.compareCreatureFitnessScore);

	for (; headsToReap != 0; headsToReap--) {
		population->getCreatureModels().back()->setCulled(true);
		population->getCreatureModels().pop_back();
	}
}

void Reaper::sow(PopulationModel* const population) {

	int headsToSow = population->getCreatureQty()
		- population->getCreatureModels().size();
	if (headsToSow <= 0) {
		return;
	}

//	{
//		// calculate the number of offsprings for each ancestor
//		int crossOverHeads = round(
//			((double) headsToSow) * mCrossOverPercentage);
//
//		crossover(population, crossOverHeads);
//	}
//
	int untouched = round(((double) headsToSow) * mCrossOverPercentage);

	int start = untouched;

//	{
//		// calculate the number of gene mutated heads
//		int geneMutationHeads = round(
//			((double) population->getCreatureModels().size() - untouched)
//				* mGeneMutationPercentage);
//
//		mutateGenes(population, start, geneMutationHeads);
//
//		start += geneMutationHeads;
//	}
//
//	{
//		// calculate the number of gene split heads
//		int geneSplitHeads = round(
//			((double) population->getCreatureModels().size() - untouched)
//				* mGeneSplitPercentage);
//
//		splitGenes(population, start, geneSplitHeads);
//
//		start += geneSplitHeads;
//	}
//
//	{
//		// calculate the number of gene branch mutated heads
//		int branchMutationHeads = round(
//			((double) population->getCreatureModels().size() - untouched)
//				* mBranchMutationPercentage);
//
//		mutateGeneBranches(population, start, branchMutationHeads);
//
//		start += branchMutationHeads;
//	}
//
//	{
//		// calculate the number of grafted heads
//		int stubHeads = round(
//			((double) population->getCreatureModels().size() - untouched)
//				* mGrowStubPercentage);
//
//		growStubs(population, start, stubHeads);
//
//		start += stubHeads;
//	}
//
//	{
//		// calculate the number of grafted heads
//		int graftedHeads = round(
//			((double) population->getCreatureModels().size() - untouched)
//				* mGraftPercentage);
//
//		graftFeatures(population, start, graftedHeads);
//
//		start += graftedHeads;
//	}

	{
		// calculate the number of freshly sown heads
		int freshlySownHeads = round(((double) headsToSow)); // * mSowFreshPercentage);
		std::cout << "Sow " << freshlySownHeads << " random creatures" << std::endl;

		sowFreshly(population, freshlySownHeads);
	}
	population->initialize();
}

void Reaper::crossover(PopulationModel* const population,
	const int crossoverHeads) {

	std::vector<CreatureModel*>::iterator cit =
		population->getCreatureModels().end();

	//how many offspring do we get per parent?
	int offspringPerParent = ceil(
		crossoverHeads
			/ (population->getCreatureModels().size() * mCrossOverPercentage));

	int crossOverSown = 0;

	//crossover the best creature with those in the ranking downwards according to the cross over percentage
	for (int i = 0;
		cit != population->getCreatureModels().begin() && i < crossoverHeads;
		i++) {

		if (Randomness::getSingleton()->nextUnifBoolean()) {
			for (int k = 0; k < offspringPerParent; k++) {

				/**
				 * Whenever a parent is needed, we choose a number of individuals at random from
				 * the previous generation. These individuals constitute a tournament.
				 * The creature with the highest fitness wins and becomes the selected parent.
				 */
				std::vector<CreatureModel*> tournament;
				int bestCreatureIndex = 0;
				int bestFitness = 0;

				for (int j = 0;
					j < EvolutionConfiguration::EVOLUTION_TOURNAMENT_SIZE;
					j++) {
					CreatureModel* model = population->getCreatureModels().at(
						Randomness::getSingleton()->nextNormalPosInt(0,
							population->getCreatureModels().size() - 1, 1.0f));
					if (bestFitness < model->getFitnessScore()) {
						bestFitness = model->getFitnessScore();
						bestCreatureIndex = j;
					}
					tournament.push_back(model);
				}

				CreatureModel* offspring = (*cit)->clone();
				offspring->setNew(true);
				offspring->setDeveloped(false);
				offspring->getGenotype().crossoverRandomly(
					&(tournament.at(bestCreatureIndex)->getGenotype()));
				offspring->giveRebirth();
				population->getCreatureModels().push_back(offspring);
			}
		} else {
			//Cross over with one random creature
			CreatureModel* offspring = (*cit)->clone();
			offspring->setNew(true);
			offspring->setDeveloped(false);
			offspring->getGenotype().crossoverRandomly(
				&(population->getCreatureModels().at(
					Randomness::getSingleton()->nextUnifPosInt(0,
						population->getCreatureModels().size() - 1))->getGenotype()));
			offspring->giveRebirth();
			population->getCreatureModels().push_back(offspring);
		}
		crossOverSown++;
		if (crossOverSown == crossoverHeads) {
			break;
		}
		cit--;
	}
}

void Reaper::mutateGenes(PopulationModel* const population, int startIndex,
	const int mutatedGeneHeads) {
	if (population->getCreatureModels().size() != 0) {
		for (int i = 0; i < mutatedGeneHeads; i++) {
			if (population->getCreatureModels().size() > startIndex + i) {
				population->getCreatureModels()[startIndex + i]->getGenotype().mutateRandomGenes(
					EvolutionConfiguration::REAPER_GENE_MUTATION_PROBABILITY);
				population->getCreatureModels()[startIndex + i]->setDeveloped(
					false);
			}
		}
	}
}

void Reaper::splitGenes(PopulationModel* const population, const int startIndex,
	const int splitGeneHeads) {
	if (population->getCreatureModels().size() != 0) {
		for (int i = 0; i < splitGeneHeads; i++) {
			if (population->getCreatureModels().size() > startIndex + i) {
				population->getCreatureModels()[startIndex + i]->getGenotype().splitRandomGenes(
					EvolutionConfiguration::REAPER_GENE_SPLIT_PROBABILITY);
				population->getCreatureModels()[startIndex + i]->setDeveloped(
					false);
			}
		}
	}
}

void Reaper::mutateGeneBranches(PopulationModel* const population,
	const int startIndex, const int mutatedGeneBranchHeads) {
	if (population->getCreatureModels().size() != 0) {
		for (int i = 0; i < mutatedGeneBranchHeads; i++) {
			if (population->getCreatureModels().size() > startIndex + i) {
				population->getCreatureModels()[startIndex + i]->getGenotype().mutateRandomBranches(
					EvolutionConfiguration::REAPER_LINK_MUTATION_PROBABILITY);
				population->getCreatureModels()[startIndex + i]->setDeveloped(
					false);
			}
		}
	}
}

void Reaper::growStubs(PopulationModel* const population, const int startIndex,
	const int growStubHeads) {
	if (population->getCreatureModels().size() != 0) {
		for (int i = 0; i < growStubHeads; i++) {
			if (population->getCreatureModels().size() > startIndex + i) {
				population->getCreatureModels()[startIndex + i]->getGenotype().growRandomStubs(
					EvolutionConfiguration::REAPER_GROW_STUB_PROBABILITY);
				population->getCreatureModels()[startIndex + i]->setDeveloped(
					false);
			}
		}
	}
}

void Reaper::graftFeatures(PopulationModel* const population,
	const int startIndex, const int graftedHeads) {
	if (population->getCreatureModels().size() != 0) {
		for (int i = 0; i < graftedHeads; i++) {
			if (population->getCreatureModels().size() > startIndex + i) {
				/**
				 * Whenever a parent is needed, we choose a number of individuals at random from
				 * the previous generation. These individuals constitute a tournament.
				 * The creature with the highest fitness wins and becomes the selected parent.
				 */
				std::vector<CreatureModel*> tournament;
				int bestCreatureIndex = 0;
				int bestFitness = 0;

				for (int j = 0;
					j < EvolutionConfiguration::EVOLUTION_TOURNAMENT_SIZE;
					j++) {
					CreatureModel* model = population->getCreatureModels().at(
						Randomness::getSingleton()->nextNormalPosInt(0,
							population->getCreatureModels().size() - 1, 1.0f));
					if (bestFitness < model->getFitnessScore()) {
						bestFitness = model->getFitnessScore();
						bestCreatureIndex = j;
					}
					tournament.push_back(model);
				}

				population->getCreatureModels()[startIndex + i]->getGenotype().graftRandomlyFrom(
					&tournament[bestCreatureIndex]->getGenotype());
				population->getCreatureModels()[startIndex + i]->setDeveloped(
					false);
			}
		}
	}
}

void Reaper::sowFreshly(PopulationModel* const population,
	const int sowFreshlyHeads) {
	// add the number of new born creatures
	double branchiness = 0;
	for (int i = 0; i < sowFreshlyHeads; i++) {
		branchiness = Randomness::getSingleton()->nextNormalDouble(
			MorphologyConfiguration::BODY_BRANCH_INITIAL_MEAN,
			MorphologyConfiguration::BODY_BRANCH_INITIAL_VAR);
		population->addNewMember(branchiness,
			EvolutionConfiguration::ROOT_POSITION);
	}
}
