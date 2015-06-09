#ifndef MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_GENOME_GENEBRANCH_HPP_
#define MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_GENOME_GENEBRANCH_HPP_

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

/**
 * @brief		The gene branch base class defines how a gene class branches into another gene class.
 * @details		Details
 * @date		2015-03-31
 * @author		Benjamin Ellenberger
 */
class GeneBranch {
public:
	enum GeneBranchType {
		MORPHOGENE_BRANCH, UNKNOWN_GENE_BRANCH
	};

	GeneBranch();
	virtual ~GeneBranch();

	/**
	 * Initialize the genebranch with
	 * @param geneBranchType its gene branch type.
	 */
	void initialize(GeneBranchType geneBranchType);

	/**
	 * Compare the gene branch to
	 * @param geneBranch another gene branch
	 * @return If the gene branch is equal to the other gene branch.
	 */
	bool equals(const GeneBranch& geneBranch) const;

	//Serialization

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
		return os
		/**If the gene branch is active or not*/
		<< "GeneBranch: Active:" << geneBranch.mActive

		/**The type of gene branch*/
		<< "/Type" << geneBranch.mType;
	}

	/**
	 * Serializes the gene branch to an xml file.
	 * @param ar The archive.
	 * @param The file version.
	 */
	template<class Archive>
	void serialize(Archive & ar, const unsigned int /* file_version */) {
		ar
		/**If the gene branch is active or not*/
		& BOOST_SERIALIZATION_NVP(mActive)

		/**The type of gene branch*/
		& BOOST_SERIALIZATION_NVP(mType);
	}

	//Accessor methods

	GeneBranchType getType() const {
		return mType;
	}

	void setType(GeneBranchType geneBranchType) {
		mType = geneBranchType;
	}

	bool isActive() const {
		return mActive;
	}

	void setActive(bool active) {
		mActive = active;
	}

protected:
	/**
	 * Determines if this branch is active.
	 */
	bool mActive;

	/**
	 * The type of gene branch.
	 */
	GeneBranchType mType;
};
BOOST_CLASS_VERSION(GeneBranch, 1)
BOOST_SERIALIZATION_ASSUME_ABSTRACT(GeneBranch)
#endif /* MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_GENOME_GENEBRANCH_HPP_ */
