#ifndef MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_GENOME_DIRECTGENOME_HPP_
#define MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_GENOME_DIRECTGENOME_HPP_

//# corresponding headers
#include <model/universe/evolution/population/creature/genome/Genome.hpp>

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

/**
 * @brief		The directly encoded genome is a one-to-one mapping from genotype to phenotype.
 * @details		Details
 * @date		2015-04-27
 * @author		Benjamin Ellenberger
 */
class DirectGenome: public Genome {
public:
	DirectGenome();
	virtual ~DirectGenome();

	/**
	 * @brief Compare this direct genome to another direct genome.
	 * @param genome another direct genome.
	 * @return If the direct genome is equal to the other direct genome.
	 */
	bool equals(const DirectGenome & genome) const;

	/**
	 * Clone the direct genome.
	 * @return The clone of the direct genome.
	 */
	virtual DirectGenome* clone() = 0;

	//Serialization
	/**
	 * @brief Give access to boost serialization.
	 */
	friend class boost::serialization::access;

	/**
	 * @brief Serializes the genome to a string.
	 * @param os
	 * 			The ostream.
	 * @param genome
	 * 			The genome we want to serialize.
	 * @return A string containing all information about the genome.
	 */

	friend std::ostream & operator<<(std::ostream &os,
			const DirectGenome &genome) {
		os
		/**The type of genome*/
		<< "MixedGenome: Type: " << genome.mGenomeType

		/**The length of the genome*/
		<< "/length=" << genome.mLength;

		/**The vector of genes.*/
		std::vector<Gene*>::const_iterator it;
		for (it = genome.mGenes.begin(); it != genome.mGenes.end(); it++) {
			os << (**it);
			os << "||";
		}

		return os;
	}

	template<class Archive>
	void serialize(Archive & ar, const unsigned int /* file_version */) {
		ar /** Serialize the base object */
		& BOOST_SERIALIZATION_BASE_OBJECT_NVP(Genome);
	}
};
BOOST_CLASS_VERSION(DirectGenome, 1)
BOOST_SERIALIZATION_ASSUME_ABSTRACT(DirectGenome)
#endif /* MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_GENOME_DIRECTGENOME_HPP_ */
