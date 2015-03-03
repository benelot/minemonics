/*
 * Creature.h
 *
 *  Created on: Dec 2, 2014
 *      Author: leviathan
 */

#ifndef CREATURE_H_
#define CREATURE_H_

//# forward declarations

//# system headers
#include <fstream>
//## controller headers

//## model headers
// include headers that implement a archive in xmlformat
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
#include "model/evolution/population/creature/genome/Genome.h"

//## view headers

//## utils headers

class Creature {
public:
	Creature(std::string name);
	virtual ~Creature();

	friend class boost::serialization::access;
	friend std::ostream & operator<<(std::ostream &os,
			const Creature &creature) {
		return os << creature.mName << ": " << creature.mDeveloped << ':'
				<< creature.mGenotype << ' ';
	}

	template<class Archive>
	void serialize(Archive & ar, const unsigned int /* file_version */) {
		ar & BOOST_SERIALIZATION_NVP(mName) & BOOST_SERIALIZATION_NVP(
				mDeveloped) & BOOST_SERIALIZATION_NVP(mGenotype);
	}

	Genome& getGenotype() {
		return mGenotype;
	}

private:

	std::string mName;

	bool mDeveloped;

	Genome mGenotype;

};
BOOST_CLASS_VERSION(Creature, 1)

#endif /* CREATURE_H_ */
