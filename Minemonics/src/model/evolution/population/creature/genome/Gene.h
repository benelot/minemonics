/*
 * Gene.h
 *
 *  Created on: Nov 17, 2014
 *      Author: leviathan
 */

#ifndef GENE_H_
#define GENE_H_

/**
 * A gene is part of the complete genome of a creature. It encodes for a certain
 * part of it, be it a certain body part, sensor type, an actuator or a neuronal
 * network connection.
 *
 * @author leviathan
 *
 */

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
#include <boost/serialization/version.hpp>
//## view headers

//# custom headers
//## base headers

//## configuration headers

//## controller headers

//## model headers
#include "GeneBranch.h"

//## view headers

//## utils headers

class Gene {
public:
	Gene();
	virtual ~Gene();

    friend class boost::serialization::access;
    friend std::ostream & operator<<(std::ostream &os, const Gene &gene) {
    	return os << gene.mActive;
    }

	virtual void print();

	bool isActive() const {
		return mActive;
	}

	void setActive(bool active) {
		mActive = active;
	}

	template<class Archive>
	    void serialize(Archive & ar, const unsigned int /* file_version */){
		ar & BOOST_SERIALIZATION_NVP(mActive);
	    }

	bool mActive;
	// genetic branches
//	std::vector<GeneBranch> branches;
};
BOOST_CLASS_VERSION(Gene, 1)


#endif /* GENE_H_ */
