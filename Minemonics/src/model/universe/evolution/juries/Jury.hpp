#ifndef MODEL_UNIVERSE_EVOLUTION_JURIES_JURY_HPP_
#define MODEL_UNIVERSE_EVOLUTION_JURIES_JURY_HPP_

//# corresponding headers
//# forward declarations
namespace boost {
namespace serialization {
class access;
} /* namespace serialization */
} /* namespace boost */

//# system headers
#include <iostream>

//## controller headers
//## model headers
#include <boost/serialization/nvp.hpp>
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
 * @brief		The jury class is the base class for all juries (fitness functions).
 * @details		Details
 * @date		2014-12-07
 * @author		Benjamin Ellenberger
 */
class Jury {
public:
	enum JuryType {
		VELOCITY, ONES
	};

	Jury(JuryType juryType, int weight);
	virtual ~Jury();

	/**
	 * Calculates the fitness value at the end of the evaluation.
	 * Therefore it should be called when the evaluation ends.
	 */
	virtual void evaluateFitness() = 0;

	/**
	 * Compare a jury to another jury.
	 * @param jury Another jury
	 * @return If the jury is equal to the other jury.
	 */
	bool equals(const Jury & jury) const;

	/**
	 * Give access to boost serialization
	 */
	friend class boost::serialization::access;

	/**
	 * Serializes the jury to a string.
	 * @param os The ostream.
	 * @param jury The jury we want to serialize.
	 * @return A string containing all information about the jury.
	 */
	friend std::ostream & operator<<(std::ostream &os, const Jury &jury) {
		return os
		/**The type of jury*/
		<< "Jury: Type=" << jury.mJuryType

		/**The weight of the jury*/
		<< "/Weight=" << jury.mWeight

		/**The fitness score of the jury.*/
		<< "Fitness=" << jury.mFitness;
	}

	/**
	 * Serializes the creature to an xml file.
	 * @param ar The archive.
	 * @param The file version.
	 */
	template<class Archive>
	void serialize(Archive & ar, const unsigned int /* file_version */) {
		ar
		/**The type of jury*/
		& BOOST_SERIALIZATION_NVP(mJuryType)

		/**The weight of the jury*/
		& BOOST_SERIALIZATION_NVP(mWeight)

		/**The fitness score of the jury.*/
		& BOOST_SERIALIZATION_NVP(mFitness);
	}

	//Accessor methods
	/**
	 * Returns the weight associated with this jury component.
	 * @return the weight
	 */
	double getWeight();

	/**
	 * Returns the fitness value that this jury assigns.
	 * @return the fitness value
	 */
	double getFitness();

	JuryType getJuryType();

protected:
	/**
	 * The type of jury.
	 */
	JuryType mJuryType;

	/**
	 * The summation weight of this jury.
	 */
	double mWeight;

	/**
	 * The fitness evaluated by this jury.
	 */
	double mFitness;
};

#endif /* MODEL_UNIVERSE_EVOLUTION_JURIES_JURY_HPP_ */
