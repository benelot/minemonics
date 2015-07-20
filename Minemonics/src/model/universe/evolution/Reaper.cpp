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

//## controller headers
//## model headers
#include <model/universe/evolution/population/creature/CreatureModel.hpp>
#include <model/universe/evolution/population/creature/genome/MixedGenome.hpp>

//## view headers
//## utils headers
#include <utils/Randomness.hpp>

Reaper::Reaper() :
		mAttributeMutationPercentage(0), mBranchAttributeMutationPercentage(0), mBranchMutationPercentage(
				0), mCrossOverPercentage(0), mGeneMutationPercentage(0), mReapPercentage(
				0), mSowFreshPercentage(0){
}

Reaper::~Reaper() {
}

void Reaper::initialize(const double reapPercentage,
		const double crossOverPercentage, const double geneMutationPercentage,
		const double attributeMutationPercentage,
		const double branchMutationPercentage,
		const double branchAttributeMutationPercentage,
		const double sowFreshPercentage) {
	mReapPercentage = reapPercentage;
	mCrossOverPercentage = crossOverPercentage;
	mGeneMutationPercentage = geneMutationPercentage;
	mAttributeMutationPercentage = attributeMutationPercentage;
	mBranchMutationPercentage = branchMutationPercentage;
	mBranchAttributeMutationPercentage = branchAttributeMutationPercentage;
	mSowFreshPercentage = sowFreshPercentage;
}

bool Reaper::compareCreatureFitness(CreatureModel* const creature1,
		CreatureModel* const creature2) {
	// lesser means ascending/ greater means descending
	return (creature1->getFitness() < creature2->getFitness());
}

void Reaper::reap(PopulationModel* const population) {
	int headsToReap = ceil(
			population->getCreatureModels().size() * mReapPercentage);

	std::sort(population->getCreatureModels().begin(),
			population->getCreatureModels().end(),
			Reaper::compareCreatureFitness);

	for (std::vector<CreatureModel*>::iterator cit =
			population->getCreatureModels().begin();
			cit != population->getCreatureModels().end() && headsToReap != 0;
			headsToReap--) {
		(*cit)->setCulled(true);
		cit = population->getCreatureModels().erase(cit);
	}

}

void Reaper::sow(PopulationModel* const population) {

	int headsToSow = population->getCreatureQty()
			- population->getCreatureModels().size();
	if (headsToSow <= 0) {
		return;
	}

	int sown = 0;

	// #############
	// crossover
	// #############

	// calculate the number of offsprings for each ancestor
	int crossOverHeads = ceil(((double) headsToSow) * mCrossOverPercentage);

	crossover(population, crossOverHeads);

	sown += crossOverHeads;

	if (headsToSow <= sown) {
		return;
	}

	// calculate the number of gene mutated heads
	int geneMutationHeads = ceil(
			((double) headsToSow) * mGeneMutationPercentage);

	mutateGenes(population, geneMutationHeads);

	sown += geneMutationHeads;

	if (headsToSow <= sown) {
		return;
	}

//	// calculate the number of gene attribute mutated heads
//	int attributeMutationHeads = headsToSow * mAttributeMutationPercentage;
//
//	mutateGeneAttributes(population, attributeMutationHeads);

	// calculate the number of gene branch mutated heads
	int branchMutationHeads = ceil(
			((double) headsToSow) * mBranchMutationPercentage);

	mutateGeneBranches(population, branchMutationHeads);

	sown += branchMutationHeads;

	if (headsToSow <= sown) {
		return;
	}

//	// calculate the number of gene branch attribute mutated heads
//	int branchAttributeMutationHeads = headsToSow
//			* mBranchAttributeMutationPercentage;
//
//	mutateGeneBranchAttributes(population, branchAttributeMutationHeads);

	// calculate the number of freshly sown heads
	int freshlySownHeads = headsToSow - sown;

	sowFreshly(population, freshlySownHeads);

	sown += freshlySownHeads;
}

void Reaper::crossover(PopulationModel* const population,
		const int crossoverHeads) {
	Randomness randomness;

	std::vector<CreatureModel*>::iterator cit =
			population->getCreatureModels().end();

	//how many offspring do we get per parent?
	int offspringPerParent = ceil(
			crossoverHeads
					/ (population->getCreatureModels().size()
							* mCrossOverPercentage));

	int crossOverSown = 0;

//crossover the best creature with those in the ranking downwards according to the cross over percentage
	for (int i = 0;
			cit != population->getCreatureModels().begin() && i < crossoverHeads;
			i++) {

		if (randomness.nextUnifBoolean()) {
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
							randomness.nextUnifPosInt(0,
									population->getCreatureModels().size()
											- 1));
					if (bestFitness < model->getFitness()) {
						bestFitness = model->getFitness();
						bestCreatureIndex = j;
					}
					tournament.push_back(model);
				}

				CreatureModel* offspring = (*cit)->clone();
				offspring->setNew(true);
				offspring->getGenotype().crossoverRandomly(
						&(tournament.at(bestCreatureIndex)->getGenotype()));
				offspring->giveRebirth();
				population->getCreatureModels().push_back(offspring);
			}
		} else {
			//Cross over with one random creature
			Randomness randomness;
			CreatureModel* offspring = (*cit)->clone();
			offspring->setNew(true);
			offspring->getGenotype().crossoverRandomly(
					&(population->getCreatureModels().at(
							randomness.nextUnifPosInt(0,
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

void Reaper::mutateGenes(PopulationModel* const population,
		const int mutatedGeneHeads) {
	Randomness randomness;

	for (int i = 0; i < mutatedGeneHeads; i++) {
		std::vector<CreatureModel*> tournament;
		int bestCreatureIndex = 0;
		int bestFitness = 0;

		for (int j = 0; j < EvolutionConfiguration::EVOLUTION_TOURNAMENT_SIZE;
				j++) {
			CreatureModel* model = population->getCreatureModels().at(
					randomness.nextUnifPosInt(0,
							population->getCreatureModels().size() - 1));
			if (bestFitness < model->getFitness()) {
				bestFitness = model->getFitness();
				bestCreatureIndex = j;
			}
			tournament.push_back(model);
		}
		CreatureModel* offspring = tournament.at(bestCreatureIndex)->clone();
		offspring->setNew(true);
		offspring->getGenotype().mutateRandomGenes(
				EvolutionConfiguration::REAPER_GENE_MUTATION_PROBABILITY);
		offspring->giveRebirth();
		population->getCreatureModels().push_back(offspring);

	}

}

void Reaper::mutateGeneAttributes(PopulationModel* const population,
		const int mutatedGeneAttributeHeads) {
	Randomness randomness;

	for (int i = 0; i < mutatedGeneAttributeHeads; i++) {
		std::vector<CreatureModel*> tournament;
		int bestCreatureIndex = 0;
		int bestFitness = 0;

		for (int j = 0; j < EvolutionConfiguration::EVOLUTION_TOURNAMENT_SIZE;
				j++) {
			CreatureModel* model = population->getCreatureModels().at(
					randomness.nextUnifPosInt(0,
							population->getCreatureModels().size() - 1));
			if (bestFitness < model->getFitness()) {
				bestFitness = model->getFitness();
				bestCreatureIndex = j;
			}
			tournament.push_back(model);
		}
		CreatureModel* offspring = tournament.at(bestCreatureIndex)->clone();
		offspring->setNew(true);
		offspring->getGenotype().mutateRandomGenes(
				EvolutionConfiguration::REAPER_GENE_MUTATION_PROBABILITY);
		population->getCreatureModels().push_back(offspring);
	}
}

void Reaper::mutateGeneBranches(PopulationModel* const population,
		const int mutatedGeneBranchHeads) {
	Randomness randomness;

	for (int i = 0; i < mutatedGeneBranchHeads; i++) {
		std::vector<CreatureModel*> tournament;
		int bestCreatureIndex = 0;
		int bestFitness = 0;

		for (int j = 0; j < EvolutionConfiguration::EVOLUTION_TOURNAMENT_SIZE;
				j++) {
			CreatureModel* model = population->getCreatureModels().at(
					randomness.nextUnifPosInt(0,
							population->getCreatureModels().size() - 1));
			if (bestFitness < model->getFitness()) {
				bestFitness = model->getFitness();
				bestCreatureIndex = j;
			}
			tournament.push_back(model);
		}
		CreatureModel* offspring = tournament.at(bestCreatureIndex)->clone();
		offspring->setNew(true);
		offspring->getGenotype().mutateRandomBranches(
				EvolutionConfiguration::REAPER_LINK_MUTATION_PROBABILITY);
		population->getCreatureModels().push_back(offspring);
	}

}

void Reaper::mutateGeneBranchAttributes(PopulationModel* const population,
		const int mutatedGeneBranchAttributeHeads) {
}

void Reaper::sowFreshly(PopulationModel* const population,
		const int sowFreshlyHeads) {
	double branchiness = 0;
	Randomness randomness;
	for (int i = 0; i < sowFreshlyHeads; i++) {
		branchiness = randomness.nextNormalDouble(
				MorphologyConfiguration::BODY_BRANCH_INITIAL_MEAN,
				MorphologyConfiguration::BODY_BRANCH_INITIAL_VAR);
		CreatureModel* offspring = new CreatureModel();
		offspring->setNew(true);
		offspring->initialize(population,
				Ogre::Vector3(0, 0, 0), branchiness);
		population->getCreatureModels().push_back(offspring);
	}
}
