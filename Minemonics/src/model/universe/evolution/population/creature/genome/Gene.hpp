#ifndef MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_GENOME_GENE_HPP_
#define MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_GENOME_GENE_HPP_

//# corresponding header
//# forward declarations
//# system headers
//## controller headers
//## model headers
// include headers that implement a archive in xml format
#include <boost/archive/tmpdir.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/vector.hpp>
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
	Gene();
	virtual ~Gene();

	/**
	 * The type of the gene
	 */
	enum GeneType{
		UnknownGene,//!< UnknownGene
		MorphoGene  //!< MorphoGene
	};

	void initialize(GeneType geneType);

	bool equals(const Gene& gene) const;

	/**
	 * Give access to boost serialization
	 */
	friend class boost::serialization::access;

	/**
	 * Serializes the gene to a string.
	 * @param os The ostream.
	 * @param gene The gene we want to serialize.
	 * @return A string containing all information about the gene.
	 */
	friend std::ostream & operator<<(std::ostream &os, const Gene &gene) {
		os << "Gene: type="<< gene.mGeneType;
		return os;
	}


	GeneType getGeneType() const {
		return mGeneType;
	}

	void setGeneType(GeneType geneType) {
		mGeneType = geneType;
	}

	/**
	 * Serializes the gene to an xml file.
	 * @param ar The archive.
	 * @param The file version.
	 */
	template<class Archive>
	void serialize(Archive & ar, const unsigned int /* file_version */) {
		ar & BOOST_SERIALIZATION_NVP(mGeneType);
	}

protected:

	/**
	 * The type of the gene.
	 */
	GeneType mGeneType;
};

#endif /* MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_GENOME_GENE_HPP_ */
