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
#include <vector>

//## controller headers
//## model headers
// include headers that implement a archive in xmlformat
#include <boost/archive/tmpdir.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/version.hpp>
#include <boost/math/special_functions/cbrt.hpp>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//#include <controller/evolution/population/creature/phenome/Phenome.h>

//## model headers
#include "model/evolution/juries/Jury.h"
#include "model/evolution/population/creature/genome/Genome.h"

//## view headers
//## utils headers

class Creature {
public:
	Creature();
	virtual ~Creature();

	/**
	 * Initializes a creature with random values for its genome, name, total segments quantity and segments path limit.
	 * @param bushiness
	 */
	void initialize(double bushiness);

	/**
	 * Provides a creature size to scale certain values in compensation for the overall size
	 * of a creature's body. We do this by summing all creature volumes of all cuboids and
	 * then we take the cube square of it (size(C) = sqrt^3{\sum\limits^{N(C)}_{i=1} v(c_i)}).
	 * @return The size of a creature.
	 */
	double getCreatureSize() {
		return boost::math::cbrt(getCreatureVolume());
	}

	/**
	 * Provides the total volume of the whole creature body.
	 * @return The total volume of the whole creature body.
	 */
	double getCreatureVolume() {
		std::vector<Morphogene*>::const_iterator it;
		double totalVolume = 0;
		for (it = mGenotype.getGenes().begin();
				it != mGenotype.getGenes().end(); it++) {
			totalVolume += (*it)->getX() * (*it)->getY() * (*it)->getZ();
		}
		return totalVolume;
	}

	/**
	 * Give access to boost serialization
	 */
	friend class boost::serialization::access;

	/**
	 * Serializes the creature to a string.
	 * @param os The ostream.
	 * @param creature The creature we want to serialize.
	 * @return A string containing all information about the creature.
	 */
	friend std::ostream & operator<<(std::ostream &os,
			const Creature &creature) {
		return os << creature.mName << ": " << creature.mDeveloped << ':'
				<< creature.mGenotype << ' ';
	}

	/**
	 * Serializes the creature to an xml file.
	 * @param ar The archive.
	 * @param The file version.
	 */
	template<class Archive>
	void serialize(Archive & ar, const unsigned int /* file_version */) {
		ar
				& BOOST_SERIALIZATION_NVP(
						mName) & BOOST_SERIALIZATION_NVP(
								mDeveloped) & BOOST_SERIALIZATION_NVP(mGenotype) & BOOST_SERIALIZATION_NVP(mJuries);
	}

	bool equals(const Creature & creature) const;

	//Accessor methods
	Genome& getGenotype() {
		return mGenotype;
	}

	bool isDeveloped() const {
		return mDeveloped;
	}

	const std::vector<Jury*>& getJuries() const {
		return mJuries;
	}

	const std::string& getName() const {
		return mName;
	}

private:

	/**
	 * The name of the creature.
	 */
	std::string mName;

	/**
	 * The genotype (genomic individual) of the creature.
	 */
	Genome mGenotype;

	/**
	 * Is the phenotype developed?
	 */
	bool mDeveloped;

	/**
	 * The phenotype of the creature.
	 */
	//Phenome mPhenotype;

	std::vector<Jury*> mJuries;

};
BOOST_CLASS_VERSION(Creature, 1)

#endif /* CREATURE_H_ */
