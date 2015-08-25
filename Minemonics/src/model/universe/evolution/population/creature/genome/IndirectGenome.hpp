#ifndef MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_GENOME_INDIRECTGENOME_HPP_
#define MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_GENOME_INDIRECTGENOME_HPP_

//# corresponding headers
#include <model/universe/evolution/population/creature/genome/Genome.hpp>

//# forward declarations
namespace boost {
namespace serialization {
class access;
} /* namespace serialization */
} /* namespace boost */

//# system headers
#include <iostream>
#include <iterator>
#include <vector>

//## controller headers
//## model headers
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/version.hpp>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
#include <model/universe/evolution/population/creature/genome/Gene.hpp>

//## view headers
//## utils headers

/**
 * @brief		The indirectly encoded genome encodes the phenotype in classes.
 * @details		Details
 * @date		2015-04-27
 * @author		Benjamin Ellenberger
 */
class IndirectGenome: public Genome {
public:
	IndirectGenome();
	virtual ~IndirectGenome();

	/**
	 * @brief Compare this indirect genome to another indirect genome.
	 * @param genome another indirect genome.
	 * @return If the indirect genome is equal to the other indirect genome.
	 */
	bool equals(const IndirectGenome& genome) const;

	/**
	 * Clone the indirect genome.
	 * @return The clone of the indirect genome.
	 */
	IndirectGenome* clone() = 0;

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
	const IndirectGenome &genome) {
		os << "MixedGenome: Type: " << genome.mGenomeType /**!< The type of genome*/

		<< "/length=" << genome.mLength; /**!< The length of the genome*/

		for (std::vector<Gene*>::const_iterator it = genome.mGenes.begin(); /**!< The vector of genes.*/
		it != genome.mGenes.end(); it++) {
			os << (**it);
			os << "||";
		}

		return os;
	}

	template<class Archive>
	void serialize(Archive & ar, const unsigned int /* file_version */) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Genome); /**!< Serialize the base object */
	}
};
BOOST_CLASS_VERSION(IndirectGenome, 1)
BOOST_SERIALIZATION_ASSUME_ABSTRACT(IndirectGenome)
#endif /* MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_GENOME_INDIRECTGENOME_HPP_ */
