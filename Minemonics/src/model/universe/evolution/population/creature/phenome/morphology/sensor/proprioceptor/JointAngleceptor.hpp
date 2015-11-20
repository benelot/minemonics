#ifndef MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_SENSOR_PROPRIOCEPTOR_JOINTANGLECEPTOR_HPP_
#define MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_SENSOR_PROPRIOCEPTOR_JOINTANGLECEPTOR_HPP_

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
 * @brief		A receptor to measure the angle of the joint.
 * @details		Details
 * @date		2015-08-18
 * @author		Benjamin Ellenberger
 */
class JointAngleceptor: public JointProprioceptor {
public:
	JointAngleceptor();
	JointAngleceptor(JointModel* jointModel,
		JointPhysics::RotationalDegreeOfFreedom rotationalDOF);
	virtual ~JointAngleceptor();

	virtual void initialize();

	virtual void update(double timeSinceLastTick);

	// Accessor methods ##########################
	double getAngle() const {
		return mAngle;
	}

	void setAngle(double angle) {
		mAngle = angle;
		setOutputValue(angle);
	}

	// Serialization ##########################
	/**
	 * Give access to boost serialization
	 */
	friend class boost::serialization::access;

	/**
	 * Serializes the joint angle proprioceptor to a string.
	 * @param os The ostream.
	 * @param jointAngleProprioceptor The joint angle proprioceptor we want to serialize.
	 * @return A string containing all information about the joint angle proprioceptor.
	 */
	friend std::ostream & operator<<(std::ostream &os,
		const JointAngleceptor &jointProprioceptor) {
		return os
		/**The joint index*/
		<< "JointAngleProprioceptor: Joint index="
//			<< jointProprioceptor.mJointIndex
			/** The motor index*/
			<< "/Motor index=" << jointProprioceptor.mMotorIndex;
	}

	/**
	 * Serializes the joint angle proprioceptor to an xml file.
	 * @param ar The archive.
	 * @param The file version.
	 */
	template<class Archive>
	void serialize(Archive & ar, const unsigned int /* file_version */) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(JointProprioceptor); /**!< Serialize the base object */
	}

private:
	double mAngle; /**!< The measured angle */
};
BOOST_CLASS_VERSION(JointAngleceptor, 1)
#endif /* MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_SENSOR_PROPRIOCEPTOR_JOINTANGLECEPTOR_HPP_ */
