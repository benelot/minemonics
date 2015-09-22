#ifndef MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_SENSOR_PROPRIOCEPTOR_JOINTANGLECEPTOR_HPP_
#define MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_SENSOR_PROPRIOCEPTOR_JOINTANGLECEPTOR_HPP_
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
#include <model/universe/evolution/population/creature/phenome/controller/ControlOutput.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/joint/JointPhysics.hpp>

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

	JointAngleceptor(std::vector<int*>::size_type jointIndex,
	FSJointPhysics::RotationalDegreeOfFreedom rotationalDOF);
	virtual ~JointAngleceptor();

	virtual void update(double timeSinceLastTick);

	//Accessor methods
	double getAngle() const {
		return mAngle;
	}

	void setAngle(double angle) {
		mAngle = angle;
		setOutputValue(angle);
	}

	//Serialization
	friend class boost::serialization::access; /**!< Give access to boost serialization */

	/**
	 * Serializes the jointangleceptor to a string.
	 * @param os The ostream.
	 * @param jointangleceptor The jointangleceptor we want to serialize.
	 * @return A string containing all information about the jointangleceptor.
	 */
	friend std::ostream & operator<<(std::ostream &os,
	const JointAngleceptor &jointangleceptor) {
		os << "JointAngleceptor";
		return os;
	}

	/**
	 * Serializes the jointangleceptor to an xml file.
	 * @param ar The archive.
	 * @param The file version.
	 */
	template<class Archive>
	void serialize(Archive & ar, const unsigned int /* file_version */) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(JointProprioceptor); /**!< Serialize the base object */
	}

private:
	double mAngle;
};
BOOST_CLASS_VERSION(JointAngleceptor, 1)
#endif /* MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_SENSOR_PROPRIOCEPTOR_JOINTANGLECEPTOR_HPP_ */
