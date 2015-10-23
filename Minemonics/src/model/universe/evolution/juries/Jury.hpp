#ifndef MODEL_UNIVERSE_EVOLUTION_JURIES_JURY_HPP_
#define MODEL_UNIVERSE_EVOLUTION_JURIES_JURY_HPP_

//# corresponding headers
//# forward declarations
class CreatureModel;
namespace boost {
namespace serialization {
class access;
} /* namespace serialization */
} /* namespace boost */

//# system headers
#include <iostream>

//## controller headers
//## model headers
#include <boost/serialization/assume_abstract.hpp>
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
		AVG_VELOCITY, AVG_HEIGHT
	};

	Jury(JuryType juryType, bool higherIsBetter, int weight);
	virtual ~Jury();

	virtual void calculateFitness(CreatureModel* creature,
			double timeSinceLastTick) = 0;

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

	virtual Jury* clone() = 0;

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
		<< "/Fitness=" << jury.mFitness

		<< "/HigherIsBetter=" << jury.mHigherIsBetter;
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
		& BOOST_SERIALIZATION_NVP(mFitness)

		& BOOST_SERIALIZATION_NVP(mHigherIsBetter);
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

	bool isHigherBetter() const {
		return mHigherIsBetter;
	}

	double getScore() const {
		return mScore;
	}

	void setScore(double score) {
		mScore = score;
	}

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
	 * If a higher score is better or not.
	 */
	bool mHigherIsBetter;

	/**
	 * The fitness evaluated by this jury.
	 */
	double mFitness;

	/**
	 * The score it received in the comparative rating.
	 */
	double mScore;
};
BOOST_CLASS_VERSION(Jury, 1)
BOOST_SERIALIZATION_ASSUME_ABSTRACT(Jury)
#endif /* MODEL_UNIVERSE_EVOLUTION_JURIES_JURY_HPP_ */
