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
#include "model/evolution/population/creature/genome/MorphoGene.h"

//## view headers

//## utils headers

class Genome {
public:
	Genome();
	virtual ~Genome();

	void createRandomGenome(double bushiness);

	void addGene(MorphoGene* gene);

	void linkRandomGenes();

	bool equals(const Genome & genome) const;

	/**
	 * Give access to boost serialization
	 */
	friend class boost::serialization::access;

	/**
	 * Serializes the genome to a string.
	 * @param os The ostream.
	 * @param genome The genome we want to serialize.
	 * @return A string containing all information about the genome.
	 */
	friend std::ostream & operator<<(std::ostream &os, const Genome &genome) {
		std::vector<MorphoGene*>::const_iterator it;
		for (it = genome.mGenes.begin(); it != genome.mGenes.end(); it++) {
			os << (**it);
			os << "//";
		}
		return os;
	}

	template<class Archive>
	void serialize(Archive & ar, const unsigned int /* file_version */) {
		ar & BOOST_SERIALIZATION_NVP(mGenes);
	}

	std::vector<MorphoGene*>& getGenes() {
		return mGenes;
	}

private:


	std::vector<MorphoGene*> mGenes;

};
BOOST_CLASS_VERSION(Genome, 1)

#endif /* GENOME_H_ */
