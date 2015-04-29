/*
 * Genome.h
 *
 *  Created on: Nov 17, 2014
 *      Author: leviathan
 */

#ifndef GENOME_H_
#define GENOME_H_

//# corresponding header
#include "model/evolution/population/creature/genome/IndirectGenome.h"

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
#include "model/evolution/population/creature/genome/morphology/Morphogene.h"

//## view headers
//## utils headers

/**
 * @brief		The mixed genome is an genome type that encodes the morphology and the neural network in a compact/indirect encoding.
 * @details		 A creature's genotype dictates a potentially-recursive (both indirectly and directly recursive)
 * branching pattern. The genome encodes properties for a fixed number of segment types, and associated
 * with each type is a fixed number of branch specifications that dictate the way in which a segment of
 * a given type sprouts branches of other segment types. The encoded information also specifies the scaling,
 * positioning, and other aspects of the branching.
 * @date		2015-04-27
 * @author		Benjamin Ellenberger
 */
class MixedGenome: public IndirectGenome {
public:
	MixedGenome();
	virtual ~MixedGenome();

	void createRandomGenome(double branchiness);

	void addGene(Morphogene* gene);

	void linkRandomGenes();

	bool equals(const MixedGenome & genome) const;

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
	friend std::ostream & operator<<(std::ostream &os, const MixedGenome &genome) {
		std::vector<Morphogene*>::const_iterator it;
		for (it = genome.mGenes.begin(); it != genome.mGenes.end(); it++) {
			os << (**it);
			os << "//";
		}
		return os;
	}

	template<class Archive>
	void serialize(Archive & ar, const unsigned int /* file_version */) {
		ar & BOOST_SERIALIZATION_NVP(mGenes) & BOOST_SERIALIZATION_NVP(mTotalSegmentQtyLimit) & BOOST_SERIALIZATION_NVP(mSegmentsDepthLimit);
	}

	std::vector<Morphogene*>& getGenes() {
		return mGenes;
	}

	int getSegmentsDepthLimit() const {
		return mSegmentsDepthLimit;
	}

	void setSegmentsDepthLimit(int segmentsDepthLimit) {
		mSegmentsDepthLimit = segmentsDepthLimit;
	}

	int getTotalSegmentQtyLimit() const {
		return mTotalSegmentQtyLimit;
	}

	void setTotalSegmentQtyLimit(int totalSegmentQtyLimit) {
		mTotalSegmentQtyLimit = totalSegmentQtyLimit;
	}

private:


	std::vector<Morphogene*> mGenes;

	/**
	 * A hard limit on the total number of body segments allowed.
	 */
	int mTotalSegmentQtyLimit;

	/**
	 * A bound on the depth of the body's tree structure (the number of segments along any root-to-leaf path).
	 * This bound is iteratively adjusted until both it and the segment quantity limit are satisfied.
	 * First, the creature is instantiated using the depth bound provided
	 * in the evolution configuration. If, during that process, the total number of body
	 * segments exceeds the segment count limit, the body is deleted, the depth bound is
	 * decreased, and the body is constructed again. This process will repeat, decreasing the
	 * depth bound each time, until the segment count falls within the specific limit.
	 */
	int mSegmentsDepthLimit;

};
BOOST_CLASS_VERSION(MixedGenome, 1)

#endif /* GENOME_H_ */
