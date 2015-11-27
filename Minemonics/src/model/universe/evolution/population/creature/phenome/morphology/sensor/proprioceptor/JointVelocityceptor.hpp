#ifndef MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_SENSOR_PROPRIOCEPTOR_JointVelocityceptor_HPP_
#define MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_SENSOR_PROPRIOCEPTOR_JointVelocityceptor_HPP_

//# corresponding header
#include <configuration/Definitions.hpp>
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
 * @brief		A receptor to measure the velocity of the joint.
 * @details		Details
 * @date		2015-08-18
 * @author		Benjamin Ellenberger
 */
class JointVelocityceptor: public JointProprioceptor {
public:
	JointVelocityceptor();
	JointVelocityceptor(JointModel* jointModel,
		JointPhysics::RotationalDegreeOfFreedom rotationalDOF);
	virtual ~JointVelocityceptor();

	virtual void initialize();

	virtual void update(double timeSinceLastTick);

	// Accessor methods ##########################
	double getVelocity() const {
		return mVelocity;
	}

	void setVelocity(double velocity) {
		mVelocity = velocity;
		setOutputValue(velocity);
	}

	// Serialization ##########################
	/**
	 * Give access to boost serialization
	 */
	friend class boost::serialization::access;

	/**
	 * Serializes the joint velocity proprioceptor to a string.
	 * @param os The ostream.
	 * @param jointVelocityProprioceptor The joint velocity proprioceptor we want to serialize.
	 * @return A string containing all information about the joint velocity proprioceptor.
	 */
	friend std::ostream & operator<<(std::ostream &os,
		const JointVelocityceptor &jointProprioceptor) {
		return os
		/**The joint index*/
		<< "JointAngleProprioceptor: Joint index="
//			<< jointProprioceptor.mJointIndex
			/** The motor index*/
			<< "/Motor index=" << jointProprioceptor.mMotorIndex;
	}

	/**
	 * Serializes the joint velocity proprioceptor to an xml file.
	 * @param ar The archive.
	 * @param The file version.
	 */
	template<class Archive>
	void serialize(Archive & ar, const unsigned int /* file_version */) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(JointProprioceptor); /**!< Serialize the base object */
	}

private:
	double mVelocity; /**!< The measured velocity */
};
BOOST_CLASS_VERSION(JointVelocityceptor, 1)
#endif /* MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_SENSOR_PROPRIOCEPTOR_JointVelocityceptor_HPP_ */
