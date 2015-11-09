#ifndef MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_GENOME_GENE_HPP_
#define MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_GENOME_GENE_HPP_

//# corresponding header
//# forward declarations
namespace boost {
namespace serialization {
class access;
} /* namespace serialization */
} /* namespace boost */

//# system headers
#include <iostream>

//## controller headers
//## model headers
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/version.hpp>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers

/**
 * @brief		The gene base class holds the basic information about a gene in general.
 * @details		Details
 * @date		2015-03-20
 * @author		Benjamin Ellenberger
 */
class Gene {
public:
	enum GeneType { /**!< The type of the gene */
		MorphoGene,  //!< MorphoGene
		NUM_GENES
	};

	Gene();
	Gene(GeneType geneType);
	virtual ~Gene();

	/**
	 * Initializes the gene with a gene type.
	 * @param geneType
	 *				A gene type.
	 */
	void initialize(const GeneType geneType);

	/**
	 * Compare gene with another gene.
	 * @param gene
	 * 			Another gene.
	 * @return if the gene is equal to the other gene.
	 */
	bool equals(const Gene& gene) const;

	/**
	 * Clone the gene.
	 * @return The clone of the gene.
	 */
	virtual Gene* clone() = 0;

	/**
	 * Mutate the gene.
	 */
	virtual void mutate() = 0;

	/**
	 * Grow some branches to the gene.
	 * @param branchiness
	 */
	virtual void grow(const int branchiness) = 0;

	//Accessor methods

	GeneType getType() const {
		return mType;
	}

	void setType(GeneType geneType) {
		mType = geneType;
	}

	//Serialization
	friend class boost::serialization::access; /**!< Give access to boost serialization */

	/**
	 * Serializes the gene to a string.
	 * @param os The ostream.
	 * @param gene The gene we want to serialize.
	 * @return A string containing all information about the gene.
	 */
	friend std::ostream & operator<<(std::ostream &os, const Gene &gene) {
		return os << "Gene: type=" << gene.mType; /**!< The type of gene*/
	}

	/**
	 * Serializes the gene to an xml file.
	 * @param ar The archive.
	 * @param The file version.
	 */
	template<class Archive>
	void serialize(Archive & ar, const unsigned int /* file_version */) {
		ar & BOOST_SERIALIZATION_NVP(mType); /**!< The type of gene. */
	}

protected:
	GeneType mType; /**!< The type of the gene. */
};
BOOST_CLASS_VERSION(Gene, 1)
BOOST_SERIALIZATION_ASSUME_ABSTRACT(Gene)
#endif /* MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_GENOME_GENE_HPP_ */
