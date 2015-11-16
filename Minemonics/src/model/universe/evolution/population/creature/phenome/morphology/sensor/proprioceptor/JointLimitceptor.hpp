#ifndef MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_SENSOR_PROPRIOCEPTOR_JOINTLIMITCEPTOR_HPP_
#define MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_SENSOR_PROPRIOCEPTOR_JOINTLIMITCEPTOR_HPP_

//# corresponding header
#include <model/universe/evolution/population/creature/phenome/morphology/sensor/proprioceptor/JointProprioceptor.hpp>

//# forward declarations
class PhenomeModel;

//# system headers
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
 * @brief		A receptor to measure the reaching of a joint limit.
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
	JointLimitceptor(JointModel* jointModel,
		JointPhysics::RotationalDegreeOfFreedom rotationalDOF, Limit limit);
	virtual ~JointLimitceptor();

	virtual void initialize();

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
	/**
	 * Give access to boost serialization
	 */
	friend class boost::serialization::access;

	/**
	 * Serializes the joint limit proprioceptor to a string.
	 * @param os The ostream.
	 * @param jointLimitProprioceptor The joint limit proprioceptor we want to serialize.
	 * @return A string containing all information about the joint limit proprioceptor.
	 */
	friend std::ostream & operator<<(std::ostream &os,
		const JointLimitceptor &jointProprioceptor) {
		return os
		/**The joint index*/
		<< "JointAngleProprioceptor: Joint index="
//			<< jointProprioceptor.mJointIndex
			/** The motor index*/
			<< "/Motor index=" << jointProprioceptor.mMotorIndex;
	}

	/**
	 * Serializes the joint limit proprioceptor to an xml file.
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
