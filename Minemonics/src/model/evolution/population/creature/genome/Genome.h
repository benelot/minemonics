/*
 * Genome.h
 *
 *  Created on: Nov 17, 2014
 *      Author: leviathan
 */

#ifndef GENOME_H_
#define GENOME_H_

//# forward declarations

//# system headers
#include <fstream>
#include <vector>
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
#include "Gene.h"

//## view headers

//## utils headers

class Genome {
public:
	Genome();
	virtual ~Genome();

	friend class boost::serialization::access;
	friend std::ostream & operator<<(std::ostream &os, const Genome &genome) {
		std::vector<Gene>::const_iterator it;
		for (it = genome.mGenes.begin(); it != genome.mGenes.end(); it++) {
			os << (*it);
		}
		return os;
	}

	template<class Archive>
	void serialize(Archive & ar, const unsigned int /* file_version */) {
		ar & BOOST_SERIALIZATION_NVP(mGenes);
	}

	void addGene(Gene gene) {
		mGenes.push_back(gene);
	}

private:
	std::vector<Gene> mGenes;

};
BOOST_CLASS_VERSION(Genome, 1)

#endif /* GENOME_H_ */
