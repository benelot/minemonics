#ifndef MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_SENSOR_PROPRIOCEPTOR_JOINTLIMITCEPTOR_HPP_
#define MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_SENSOR_PROPRIOCEPTOR_JOINTLIMITCEPTOR_HPP_

//# corresponding header
#include <model/universe/evolution/population/creature/phenome/morphology/sensor/proprioceptor/JointProprioceptor.hpp>

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
#include <model/universe/evolution/population/creature/phenome/controller/ControlOutput.hpp>

//## view headers
//## utils headers

/**
 * @brief		A receptor to measure when the joint hits a joint limit.
 * @details		Details
 * @date		2015-08-18
 * @author		Benjamin Ellenberger
 */
class JointLimitceptor: public JointProprioceptor {
public:
	enum Limit {
		LOWER_LIMIT, UPPER_LIMIT, BOTH_LIMITS
	};
	JointLimitceptor();
	JointLimitceptor(std::vector<int*>::size_type jointIndex,
	JointPhysics::RotationalDegreeOfFreedom rotationalDOF, Limit limit);
	virtual ~JointLimitceptor();

	virtual void update(double timeSinceLastTick);

	//Accessor methods
	double getLimitError() const {
		return mLimitError;
	}

	void setLimitError(double limitError) {
		mLimitError = limitError;
		setOutputValue(limitError);
	}

	//Serialization
	friend class boost::serialization::access; /**!< Give access to boost serialization */

	/**
	 * Serializes the jointlimitceptor to a string.
	 * @param os The ostream.
	 * @param jointlimitceptor The jointlimitceptor we want to serialize.
	 * @return A string containing all information about the jointlimitceptor.
	 */
	friend std::ostream & operator<<(std::ostream &os,
	const JointLimitceptor &jointlimitceptor) {
		os << "JointLimitceptor";
		return os;
	}

	/**
	 * Serializes the jointlimitceptor to an xml file.
	 * @param ar The archive.
	 * @param The file version.
	 */
	template<class Archive>
	void serialize(Archive & ar, const unsigned int /* file_version */) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(JointProprioceptor); /**!< Serialize the base object */
	}

private:
	double mLimitError;
	Limit mLimit;
};
BOOST_CLASS_VERSION(JointLimitceptor, 1)
#endif /* MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_SENSOR_PROPRIOCEPTOR_JOINTLIMITCEPTOR_HPP_ */
