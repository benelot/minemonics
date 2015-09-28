#ifndef MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_SENSOR_PROPRIOCEPTOR_JOINTFORCECEPTOR_HPP_
#define MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_SENSOR_PROPRIOCEPTOR_JOINTFORCECEPTOR_HPP_

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
 * @brief		A receptor to measure the force applied to a joint.
 * @details		Details
 * @date		2015-08-18
 * @author		Benjamin Ellenberger
 */
class JointForceceptor: public JointProprioceptor {
public:
	JointForceceptor();
	JointForceceptor(std::vector<int*>::size_type jointIndex,
		JointPhysics::RotationalDegreeOfFreedom rotationalDOF);
	virtual ~JointForceceptor();

	virtual void update(double timeSinceLastTick);

	//Accessor methods
	double getForce() const {
		return mForce;
	}

	void setForce(double force) {
		mForce = force;
		setOutputValue(force);
	}

	//Serialization
	friend class boost::serialization::access; /**!< Give access to boost serialization */

	/**
	 * Serializes the jointforceceptor to a string.
	 * @param os The ostream.
	 * @param jointforceceptor The jointforceceptor we want to serialize.
	 * @return A string containing all information about the jointforceceptor.
	 */
	friend std::ostream & operator<<(std::ostream &os,
		const JointForceceptor &jointForceceptor) {
		os << "JointForceceptor";
		return os;
	}

	/**
	 * Serializes the jointforceceptor to an xml file.
	 * @param ar The archive.
	 * @param The file version.
	 */
	template<class Archive>
	void serialize(Archive & ar, const unsigned int /* file_version */) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(JointProprioceptor); /**!< Serialize the base object */
	}

private:
	double mForce; /**!< The force that is applied to the joint */
};
BOOST_CLASS_VERSION(JointForceceptor, 1)
#endif /* MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_SENSOR_PROPRIOCEPTOR_JOINTFORCECEPTOR_HPP_ */
