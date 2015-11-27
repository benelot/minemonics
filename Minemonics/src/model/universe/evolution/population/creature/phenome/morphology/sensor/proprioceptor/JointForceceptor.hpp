#ifndef MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_SENSOR_PROPRIOCEPTOR_JOINTFORCECEPTOR_HPP_
#define MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_SENSOR_PROPRIOCEPTOR_JOINTFORCECEPTOR_HPP_

//# corresponding header
#include <configuration/Definitions.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/sensor/proprioceptor/JointProprioceptor.hpp>

//# forward declarations
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
 * @brief		A receptor to measure the force applied to a joint.
 * @details		Details
 * @date		2015-08-18
 * @author		Benjamin Ellenberger
 */
class JointForceceptor: public JointProprioceptor {
public:
	JointForceceptor();
	JointForceceptor(JointModel* jointModel,
		JointPhysics::RotationalDegreeOfFreedom rotationalDOF);
	virtual ~JointForceceptor();

	virtual void initialize();

	virtual void update(double timeSinceLastTick);

	// Accessor methods ##########################
	double getForce() const {
		return mForce;
	}

	void setForce(double force) {
		mForce = force;
		setOutputValue(force);
	}

	// Serialization ##########################
	/**
	 * Give access to boost serialization
	 */
	friend class boost::serialization::access;

	/**
	 * Serializes the joint force proprioceptor to a string.
	 * @param os The ostream.
	 * @param jointForceProprioceptor The joint force proprioceptor we want to serialize.
	 * @return A string containing all information about the joint force proprioceptor.
	 */
	friend std::ostream & operator<<(std::ostream &os,
		const JointForceceptor &jointProprioceptor) {
		return os
		/**The joint index*/
		<< "JointAngleProprioceptor: Joint index="
//			<< jointProprioceptor.mJointIndex
			/** The motor index*/
			<< "/Motor index=" << jointProprioceptor.mMotorIndex;
	}

	/**
	 * Serializes the joint force proprioceptor to an xml file.
	 * @param ar The archive.
	 * @param The file version.
	 */
	template<class Archive>
	void serialize(Archive & ar, const unsigned int /* file_version */) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(JointProprioceptor); /**!< Serialize the base object */
	}

private:
	double mForce; /**!< The measured force */
};
BOOST_CLASS_VERSION(JointForceceptor, 1)
#endif /* MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_SENSOR_PROPRIOCEPTOR_JOINTFORCECEPTOR_HPP_ */
