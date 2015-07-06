//# corresponding header
#include <model/universe/evolution/population/PopulationModel.hpp>
#include <model/universe/evolution/Reaper.hpp>

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
//## view headers
//## utils headers

bool compareCreatureFitness(CreatureModel* i, CreatureModel* j) {
	return (i->getFitness() < j->getFitness());
}

Reaper::Reaper() :
		mAttributeMutationPercentage(0), mBranchAttributeMutationPercentage(0), mBranchMutationPercentage(
				0), mCrossOverPercentage(0), mGeneMutationPercentage(0), mReapPercentage(
				0), mSowFreshPercentage(0) {
}

Reaper::~Reaper() {
	// TODO Auto-generated destructor stub
}

void Reaper::initialize(double reapPercentage, double crossOverPercentage,
		double geneMutationPercentage, double attributeMutationPercentage,
		double branchMutationPercentage,
		double branchAttributeMutationPercentage, double sowFreshPercentage) {
	mReapPercentage = reapPercentage;
	mCrossOverPercentage = crossOverPercentage;
	mGeneMutationPercentage = geneMutationPercentage;
	mAttributeMutationPercentage = attributeMutationPercentage;
	mBranchMutationPercentage = branchMutationPercentage;
	mBranchAttributeMutationPercentage = branchAttributeMutationPercentage;
	mSowFreshPercentage = sowFreshPercentage;
}

void Reaper::reap(PopulationModel* population) {
	int headsToReap = ceil(
			population->getCreatureModels().size() * mReapPercentage);

	//TODO: Check whether the sort is descending or ascending
	std::sort(population->getCreatureModels().begin(),
			population->getCreatureModels().end(), compareCreatureFitness);
	std::vector<CreatureModel*>::iterator cit =
			population->getCreatureModels().begin();
	for (; cit != population->getCreatureModels().end() || headsToReap != 0;
			headsToReap--) {
		cit = population->getCreatureModels().erase(cit);
	}

}

void Reaper::sow(PopulationModel* population) {

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
	int crossOverHeads = headsToSow * mCrossOverPercentage;
	std::vector<CreatureModel*>::iterator cit =
			population->getCreatureModels().end();
	int offspringPerParent = crossOverHeads
			/ (population->getCreatureModels().size() * mCrossOverPercentage);
	for (;
			cit != population->getCreatureModels().begin()
					|| crossOverHeads != 0; crossOverHeads--) {

		std::vector<CreatureModel*>::iterator cit2 = cit;
		for (int i = 0; i < offspringPerParent; i++) {
			cit2--;
			MixedGenome* offspring = (*cit)->getGenotype().clone();
			(*cit)->getGenotype().crossoverRandomly(&((*cit2)->getGenotype()));
		}
		cit--;
	}

//	int ancestorIndex = 0;
//	ArrayList < Integer > offspringQts = new ArrayList<>();
//	ArrayList<Creature> ancestors = new ArrayList<>();
//	int offsprings = 0;
//	for (int i = 0; i < EvolutionConfiguration.REAPER_SOW_OFFSPRING.length;
//			i++) {
//		double offspringPerc = EvolutionConfiguration.REAPER_SOW_OFFSPRING[i];
//		int offspringQty = (int) (Math.ceil(
//				offspringPerc * headsToSow
//						* EvolutionConfiguration.REAPER_CROSSOVER_PERCENTAGE));
//
//		// add number of offsprings for each ancestor
//		if (offsprings + offspringQty < headsToSow) {
//			offspringQts.add(offspringQty);
//			offsprings += offspringQty;
//		} else {
//			// if we (nearly) reached the number heads to sow we add the
//			// remaining heads
//			offspringQts.add(headsToSow - offsprings);
//			offsprings = headsToSow;
//		}
//		Creature creature = population.getCreatures().get(0);
//		ancestors.add(creature);
//		// remove creature from top
//		population.getCreatures().remove(0);
//
//		// and add to the end of the list
//		population.addCreature(creature);
//		creature.generation++;
//	}
//
//	// as long as we did not already generate all offspring or all heads to
//	// be sown
//	while (ancestorIndex != offspringQts.size() && sown < headsToSow) {
//		if (offspringQts.get(ancestorIndex) != 0) {
//			Creature mate1 = ancestors.get(ancestorIndex);
//			Creature mate2 = ancestors.get(
//					Randomness.nextPosInt(0, ancestors.size() - 1));
//			Genome genotype = Genetics.performCrossOver(mate1.getGenotype(),
//					mate2.getGenotype());
//
//			if (genotype.size() > 1) {
//				for (int i = 0;
//						i < EvolutionConfiguration.REAPER_GENE_MUTATION_QTY;
//						i++) {
//					Genetics.performGeneMutation(genotype);
//				}
//			}
//			for (int i = 0; i < EvolutionConfiguration.REAPER_GENE_MUTATION_QTY;
//					i++) {
//				Genetics.performAttributeMutation(genotype);
//			}
//			for (int i = 0; i < EvolutionConfiguration.REAPER_LINK_MUTATION_QTY;
//					i++) {
//				Genetics.performLinkMutation(genotype);
//			}
//
//			CreaturejME3 creature = new CreaturejME3(evolution, genotype);
//			population.addCreature(creature);
//			offspringQts.set(ancestorIndex,
//					offspringQts.get(ancestorIndex) - 1);
//			sown++;
//		} else {
//			ancestorIndex++;
//		}
//	}
//
//	// gene mutation
//	int geneMutationHeads = (int) (headsToSow
//			* EvolutionConfiguration.REAPER_GENE_MUTATION_PERCENTAGE);
//	for (int i = 0; i < geneMutationHeads; i++) {
//		if (sown == headsToSow) {
//			break;
//		}
//
//		Creature ancestor = population.getCreatures().get(0);
//
//		// remove creature from top
//		population.getCreatures().remove(0);
//
//		// and add to the end of the list
//		population.getCreatures().add(ancestor);
//
//		Genome genotype = new Genome();
//		genotype.append(ancestor.getGenotype(), 0,
//				ancestor.getGenotype().size());
//
//		// Gene mutations
//		for (int j = 0; j < EvolutionConfiguration.REAPER_GENE_MUTATION_QTY;
//				j++) {
//			Genetics.performGeneMutation(genotype);
//		}
//
//		// Attribute mutations
//		for (int j = 0;
//				j < EvolutionConfiguration.REAPER_ATTRIBUTE_MUTATION_QTY; j++) {
//			Genetics.performAttributeMutation(genotype);
//		}
//
//		for (int j = 0; j < EvolutionConfiguration.REAPER_LINK_MUTATION_QTY;
//				j++) {
//			Genetics.performLinkMutation(genotype);
//		}
//		Creature creature = new CreaturejME3(genotype);
//		population.addCreature(creature);
//		sown++;
//	}
//
//	// attribute mutation
//	int attributeMutationHeads = (int) (headsToSow
//			* EvolutionConfiguration.REAPER_ATTRIBUTE_MUTATION_PERCENTAGE);
//	for (int i = 0; i < attributeMutationHeads; i++) {
//		if (sown == headsToSow) {
//			break;
//		}
//
//		Creature ancestor = population.getCreatures().get(0);
//
//		// remove creature from top
//		population.getCreatures().remove(0);
//
//		// and add to the end of the list
//		population.addCreature(ancestor);
//
//		Genome genotype = new Genome();
//		genotype.append(ancestor.getGenotype(), 0,
//				ancestor.getGenotype().size());
//
//		// Attribute mutations
//		for (int j = 0;
//				j < EvolutionConfiguration.REAPER_ATTRIBUTE_MUTATION_QTY; j++) {
//			Genetics.performAttributeMutation(genotype);
//		}
//
//		for (int j = 0; j < EvolutionConfiguration.REAPER_LINK_MUTATION_QTY;
//				j++) {
//			Genetics.performLinkMutation(genotype);
//		}
//		Creature creature = new CreaturejME3(genotype);
//		population.addCreature(creature);
//		sown++;
//	}
//
//	while (sown < headsToSow) {
//		population.addNewCreature(evolution);
//	}
//
//	// recreate the creature from the last generation to the next
//	for (Creature creature : population.getCreatures()) {
//		if (!creature.isDeveloped()) {
//			creature.getGenotype().rewire();
//			creature.getPhenotype().buildPhenotypeFromGenotype(
//					creature.getGenotype());
//		}
//
//	}

}
