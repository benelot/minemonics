#ifndef MODEL_UNIVERSE_EVOLUTION_JURIES_GROUNDCONTACTRATIO_HPP_
#define MODEL_UNIVERSE_EVOLUTION_JURIES_GROUNDCONTACTRATIO_HPP_

//# corresponding header
#include <configuration/Definitions.hpp>
#include <model/universe/evolution/juries/Jury.hpp>

//# forward declarations
//# system headers
#include <vector>

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
 * @brief		The ground contact quantity jury evaluates how many ground contacts an individual has in relation to the total limbs during its evaluation time.
 * @details		Details
 * @date		2015-05-02
 * @author		Benjamin Ellenberger
 */
class GroundContactRatio: public Jury {
public:
	GroundContactRatio();
	GroundContactRatio(const bool higherIsBetter, const double weight);
	virtual ~GroundContactRatio();

	virtual void calculateFitness(CreatureModel* creature,
		double timeSinceLastTick);

	/**
	 * Evaluate the fitness.
	 */
	void evaluateFitness();

	virtual GroundContactRatio* clone();

	virtual std::string getScoreString();

	// Accessor methods ##########################

	// Serialization
	friend class boost::serialization::access; /**!< Give access to boost serialization */

	/**
	 * Serializes the average height jury to a string.
	 * @param os The ostream.
	 * @param avgHeightJury The average height jury we want to serialize.
	 * @return A string containing all information about the average height jury.
	 */
	friend std::ostream & operator<<(std::ostream &os,
		const GroundContactRatio &avgHeightJury) {
		return os;
	}

	/**
	 * Serializes the average height jury to an xml file.
	 * @param ar The archive.
	 * @param The file version.
	 */
	template<class Archive>
	void serialize(Archive & ar, const unsigned int /* file_version */) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Jury); /**!< Serialize the base object */
	}

private:
	int mSampleQty; /**!< The number of sample we used for this average */

	bool mIsFirstTime; /**!< Is this the first run of the jury? */

	int mGroundContacts; /**!< The ground contacts */
	double mGroundContactRatio; /**!< The ground contact ratio */
};

#endif /* MODEL_UNIVERSE_EVOLUTION_JURIES_GROUNDCONTACTRATIO_HPP_ */
