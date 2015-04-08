/*
 * Gene.h
 *
 *  Created on: Mar 20, 2015
 *      Author: leviathan
 */

#ifndef MODEL_EVOLUTION_POPULATION_CREATURE_GENOME_GENE_H_
#define MODEL_EVOLUTION_POPULATION_CREATURE_GENOME_GENE_H_

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

class Gene {
public:
	Gene();
	virtual ~Gene();

	enum GeneType{
		UnknownGene,
		MorphoGene
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
		os << "Gene: Active=" << gene.mActive  << "/Gene type="<< gene.mGeneType;
		return os;
	}

	bool isActive() const {
		return mActive;
	}

	void setActive(bool active) {
		mActive = active;
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
		ar & BOOST_SERIALIZATION_NVP(mActive) & BOOST_SERIALIZATION_NVP(mGeneType);
	}

protected:
	bool mActive;

	GeneType mGeneType;
};

#endif /* MODEL_EVOLUTION_POPULATION_CREATURE_GENOME_GENE_H_ */
