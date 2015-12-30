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
#include <configuration/GeneticsConfiguration.hpp>
#include <configuration/MorphologyConfiguration.hpp>

//## model headers
#include <model/universe/evolution/CreatureFitnessComparator.hpp>
#include <model/universe/evolution/CreatureFitnessScoreComparator.hpp>
#include <model/universe/evolution/population/creature/genome/MixedGenome.hpp>

//## view headers
//## utils headers
#include <utils/Randomness.hpp>

BoostLogger Reaper::mBoostLogger; /*<! initialize the boost logger*/
Reaper::_Init Reaper::_initializer;
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

	int headsToReap = ceil(
		population->getCreatureModels().size() * mReapPercentage);

	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Reap " << headsToReap << " creatures";
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

	int crossOverHeads = 0;
	{
		// calculate the number of offsprings for each ancestor
		crossOverHeads = round(((double) headsToSow) * mCrossOverPercentage);

		crossover(population, crossOverHeads);
		BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Crossover " << crossOverHeads << " creatures";
	}
	int start = 0;
	int untouched = round(((double) headsToSow) * mCrossOverPercentage);
	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Elite transfer " << untouched << " creatures" << "[" << start << ";" << start + untouched << "]";
	start += untouched;

	{
		// calculate the number of gene mutated heads
		int geneMutationHeads = round(
			((double) population->getCreatureModels().size() - untouched
				- crossOverHeads) * mGeneMutationPercentage);

		mutateGenes(population, start, geneMutationHeads);
		BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Mutate genes of " << geneMutationHeads << " creatures" << "[" << start << ";" << start + geneMutationHeads << "]";

		start += geneMutationHeads;
	}

	{
		// calculate the number of gene split heads
		int geneSplitHeads = round(
			((double) population->getCreatureModels().size() - untouched
				- crossOverHeads) * mGeneSplitPercentage);
		BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Split segments of " << geneSplitHeads << " creatures" << "[" << start << ";" << start + geneSplitHeads << "]";

		splitGenes(population, start, geneSplitHeads);

		start += geneSplitHeads;
	}

	{
		// calculate the number of gene branch mutated heads
		int branchMutationHeads = round(
			((double) population->getCreatureModels().size() - untouched
				- crossOverHeads) * mBranchMutationPercentage);
		BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Mutate branches of " << branchMutationHeads << " creatures" << "[" << start << ";" << start + branchMutationHeads << "]";

		mutateGeneBranches(population, start, branchMutationHeads);

		start += branchMutationHeads;
	}

	{
		// calculate the number of grafted heads
		int stubHeads = round(
			((double) population->getCreatureModels().size() - untouched
				- crossOverHeads) * mGrowStubPercentage);
		BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Grow stubs of " << stubHeads << " creatures" << "[" << start << ";" << start + stubHeads << "]";

		growStubs(population, start, stubHeads);

		start += stubHeads;
	}

	{
		// calculate the number of grafted heads
		int graftedHeads = round(
			((double) population->getCreatureModels().size() - untouched
				- crossOverHeads) * mGraftPercentage);
		BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Graft features of " << graftedHeads << " creatures" << "[" << start << ";" << start + graftedHeads << "]";

		graftFeatures(population, start, graftedHeads);

		start += graftedHeads;
	}

	{
		// calculate the number of freshly sown heads
		int freshlySownHeads = round(
			((double) headsToSow) * mSowFreshPercentage);
		BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Sow " << freshlySownHeads << " random creatures";

		sowFreshly(population, freshlySownHeads);
	}

	// erase the old creature models
	for (std::vector<CreatureModel*>::iterator cit =
		population->getCreatureModels().begin();
		cit != population->getCreatureModels().end();) {
		if ((*cit)->isCulled()) {
			cit = population->getCreatureModels().erase(cit);
		} else {
			cit++;
		}
	}

	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Population has now " << population->getCreatureModels().size() << " creatures";

	population->setOutOfSync(true);
	population->initialize(); // Reinitialize the population
}

void Reaper::crossover(PopulationModel* const population,
	const int crossoverHeads) {

	//how many offspring do we get per parent?
	int offspringPerParent = ceil(
		crossoverHeads
			/ (population->getCreatureModels().size() * mCrossOverPercentage));

	int crossOverSown = 0;

	//crossover the best creature with those in the ranking downwards according to the cross over percentage
	std::vector<CreatureModel*>::iterator cit =
		population->getCreatureModels().begin();
	for (int i = 0;
		cit != population->getCreatureModels().end() && i < crossoverHeads;
		i++) {
		CreatureModel* offspring = NULL;
		CreatureModel* partner = NULL;

		// find a partner for the creature
		if (Randomness::getSingleton()->nextUnifBoolean()) { // flip a coin; tournament of random creature
			for (int k = 0; k < offspringPerParent; k++) {
				int bestCreatureIndex = 0;
				int bestFitness = 0;

				for (int j = 0;
					j < EvolutionConfiguration::EVOLUTION_TOURNAMENT_SIZE;
					j++) {
					CreatureModel* model = population->getCreatureModels().at( // Whenever a parent is needed, we choose a number of individuals at random from
						Randomness::getSingleton()->nextNormalPosInt(0, // the previous generation. These individuals constitute a tournament.
							population->getCreatureModels().size() - 1, 1.0f)); // The creature with the highest fitness wins and becomes the selected parent.
					if (bestFitness < model->getFitnessScore()) {
						bestFitness = model->getFitnessScore();
						partner = model;
					}
				}
			}
		} else { //Cross over with one random creature
			partner = population->getCreatureModels().at(
				Randomness::getSingleton()->nextUnifPosInt(0,
					population->getCreatureModels().size() - 1));
		}

		offspring = (*cit)->clone(); // Clone the old creature
		offspring->setNew(true); // Make the creature a new creature
		offspring->giveRebirth(); // Give the creature a rebirth from its old clone
		offspring->setDeveloped(false); // Set the creature for an embryogenesis

		offspring->getGenotype().crossoverRandomly(&(partner->getGenotype())); // Crossover randomly with its partner
		offspring->getGenotype().recalculateRootIndex(); // Reposition the root index
		population->getCreatureModels().push_back(offspring);

		// Are we done?
		crossOverSown++;
		if (crossOverSown == crossoverHeads) {
			break;
		}
		cit++;
	}
}

void Reaper::mutateGenes(PopulationModel* const population, int startIndex,
	const int mutatedGeneHeads) {
	if (population->getCreatureModels().size() != 0) {
		for (int i = 0; i < mutatedGeneHeads; i++) {
			if (population->getCreatureModels().size() > startIndex + i) { // Size must be bigger than the current index
				CreatureModel* offspring =
					population->getCreatureModels()[startIndex + i]->clone(); // Clone the old creature
				population->getCreatureModels()[startIndex + i]->setCulled(
						true);
				offspring->setNew(true); // Make the creature a new creature
				offspring->setDeveloped(false); // Set the creature for an embryogenesis

				offspring->getGenotype().mutateRandomGenes(
					EvolutionConfiguration::REAPER_GENE_MUTATION_PROBABILITY); // Mutate random genes
				offspring->getGenotype().recalculateRootIndex(); // Reposition the root index
				population->getCreatureModels().push_back(offspring);
			}
		}
	}
}

void Reaper::splitGenes(PopulationModel* const population, const int startIndex,
	const int splitGeneHeads) {
	if (population->getCreatureModels().size() != 0) {
		for (int i = 0; i < splitGeneHeads; i++) {
			if (population->getCreatureModels().size() > startIndex + i) { // Size must be bigger than the current index
				population->getCreatureModels()[startIndex + i]->setCulled(
					true);
				CreatureModel* offspring =
					population->getCreatureModels()[startIndex + i]->clone(); // Clone the old creature
				offspring->setNew(true); // Make the creature a new creature
				offspring->setDeveloped(false); // Set the creature for an embryogenesis

				offspring->getGenotype().splitRandomGenes(
					EvolutionConfiguration::REAPER_GENE_SPLIT_PROBABILITY);
				offspring->getGenotype().recalculateRootIndex(); // Reposition the root index
				population->getCreatureModels().push_back(offspring);
			}
		}
	}
}

void Reaper::mutateGeneBranches(PopulationModel* const population,
	const int startIndex, const int mutatedGeneBranchHeads) {
	if (population->getCreatureModels().size() != 0) {
		for (int i = 0; i < mutatedGeneBranchHeads; i++) {
			if (population->getCreatureModels().size() > startIndex + i) { // Size must be bigger than the current index
				CreatureModel* offspring =
					population->getCreatureModels()[startIndex + i]->clone(); // Clone the old creature
				population->getCreatureModels()[startIndex + i]->setCulled(
						true);
				offspring->setNew(true); // Make the creature a new creature
				offspring->setDeveloped(false); // Set the creature for an embryogenesis

				offspring->getGenotype().mutateRandomBranches(
					EvolutionConfiguration::REAPER_LINK_MUTATION_PROBABILITY);
				offspring->getGenotype().recalculateRootIndex(); // Reposition the root index
				population->getCreatureModels().push_back(offspring);
			}
		}
	}
}

void Reaper::growStubs(PopulationModel* const population, const int startIndex,
	const int growStubHeads) {
	if (population->getCreatureModels().size() != 0) {
		for (int i = 0; i < growStubHeads; i++) {
			if (population->getCreatureModels().size() > startIndex + i) { // Size must be bigger than the current index
				CreatureModel* offspring =
					population->getCreatureModels()[startIndex + i]->clone(); // Clone the old creature
				population->getCreatureModels()[startIndex + i]->setCulled(
						true);
				offspring->setNew(true); // Make the creature a new creature
				offspring->setDeveloped(false); // Set the creature for an embryogenesis

				offspring->getGenotype().growRandomStubs(
					EvolutionConfiguration::REAPER_GROW_STUB_PROBABILITY);
				offspring->getGenotype().recalculateRootIndex(); // Reposition the root index
				population->getCreatureModels().push_back(offspring);
			}
		}
	}
}

void Reaper::graftFeatures(PopulationModel* const population,
	const int startIndex, const int graftedHeads) {
	if (population->getCreatureModels().size() != 0) {
		for (int i = 0; i < graftedHeads; i++) {
			if (population->getCreatureModels().size() > startIndex + i) { // Size must be bigger than the current index
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

				CreatureModel* offspring =
					population->getCreatureModels()[startIndex + i]->clone(); // Clone the old creature
				population->getCreatureModels()[startIndex + i]->setCulled(
						true);
				offspring->setNew(true); // Make the creature a new creature
				offspring->setDeveloped(false); // Set the creature for an embryogenesis

				offspring->getGenotype().graftRandomlyFrom(
					&tournament[bestCreatureIndex]->getGenotype());
				offspring->getGenotype().recalculateRootIndex(); // Reposition the root index
				population->getCreatureModels().push_back(offspring);
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
			GeneticsConfiguration::GENE_BRANCH_INITIAL_MEAN,
			GeneticsConfiguration::GENE_BRANCH_INITIAL_VAR);
		population->addNewMember(branchiness,
			EvolutionConfiguration::ROOT_POSITION);
	}
}
