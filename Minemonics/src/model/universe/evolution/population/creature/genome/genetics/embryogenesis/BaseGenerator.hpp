#ifndef MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_GENOME_GENETICS_EMBRYOGENESIS_BASEGENERATOR_HPP_
#define MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_GENOME_GENETICS_EMBRYOGENESIS_BASEGENERATOR_HPP_

//# corresponding headers
//# forward declarations
class Gene;

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

/**
 * @brief		The base generator is the base class for all generator classes.
 * @details		Details
 * @date		2015-04-20
 * @author		Benjamin Ellenberger
 */
class BaseGenerator {
public:
	BaseGenerator();
	virtual ~BaseGenerator();

	/**
	 * Clone the base generator.
	 * @return The clone of the base generator.
	 */
	virtual BaseGenerator* clone() = 0;

	//Accessor methods
	Gene* getGene() const {
		return mGene;
	}

	void setGene(Gene* const gene) {
		this->mGene = gene;
	}

protected:
	/**
	 * The gene the generator transcribes.
	 */
	Gene* mGene;
};

#endif /* MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_GENOME_GENETICS_EMBRYOGENESIS_BASEGENERATOR_HPP_ */
