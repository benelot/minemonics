/*
 * GeneBranch.h
 *
 *  Created on: Mar 31, 2015
 *      Author: leviathan
 */

#ifndef MODEL_EVOLUTION_POPULATION_CREATURE_GENOME_GENEBRANCH_H_
#define MODEL_EVOLUTION_POPULATION_CREATURE_GENOME_GENEBRANCH_H_

//# corresponding header
//# forward declarations
//# system headers
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
//## view headers
//## utils headers

class GeneBranch {
public:
	enum GeneBranchType {
		MORPHOGENE_BRANCH, UNKNOWN_GENE_BRANCH
	};

	GeneBranch();
	virtual ~GeneBranch();

	void initialize(GeneBranchType geneBranchType);

	bool equals(const GeneBranch& geneBranch) const;


	/**
	 * Give access to boost serialization
	 */
	friend class boost::serialization::access;

	/**
	 * Serializes the gene branch to a string.
	 * @param os The ostream.
	 * @param geneBranch The creature we want to serialize.
	 * @return A string containing all information about the gene branch.
	 */
	friend std::ostream & operator<<(std::ostream &os,
			const GeneBranch &geneBranch) {
		return os << "GeneBranch: Type" << geneBranch.mGeneBranchType;
	}

	GeneBranchType getGeneBranchType() const {
		return mGeneBranchType;
	}

	void setGeneBranchType(GeneBranchType geneBranchType) {
		mGeneBranchType = geneBranchType;
	}

	/**
	 * Serializes the gene branch to an xml file.
	 * @param ar The archive.
	 * @param The file version.
	 */
	template<class Archive>
	void serialize(Archive & ar, const unsigned int /* file_version */) {
		ar & BOOST_SERIALIZATION_NVP(mGeneBranchType);
	}

private:
	GeneBranchType mGeneBranchType;

};

#endif /* MODEL_EVOLUTION_POPULATION_CREATURE_GENOME_GENEBRANCH_H_ */
