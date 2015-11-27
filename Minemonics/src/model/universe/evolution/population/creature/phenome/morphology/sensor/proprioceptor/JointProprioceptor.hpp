#ifndef MODEL_EVOLUTION_POPULATION_CREATURE_GENOME_SENSORS_JOINTPROPRIOCEPTOR_H_
#define MODEL_EVOLUTION_POPULATION_CREATURE_GENOME_SENSORS_JOINTPROPRIOCEPTOR_H_

//# corresponding header
#include <configuration/Definitions.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/sensor/proprioceptor/Proprioceptor.hpp>

//# forward declarations
class JointModel;

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
#include <model/universe/evolution/population/creature/phenome/morphology/joint/JointPhysics.hpp>

//## view headers
//## utils headers

/**
 * @brief		A base joint receptor for the internal movement of the limbs.
 * @details		Details
 * @date		2015-03-09
 * @author		Benjamin Ellenberger
 */
class JointProprioceptor: public Proprioceptor {
public:
	JointProprioceptor();
	JointProprioceptor(JointModel* jointModel,
		JointPhysics::RotationalDegreeOfFreedom rotationalDOF);
	~JointProprioceptor();

	virtual void initialize();

	/**
	 * Update the joint proprioceptor input.
	 * @param timeSinceLastTick
	 */
	virtual void update(double timeSinceLastTick) = 0;

	// Serialization ##########################
	/**
	 * Give access to boost serialization
	 */
	friend class boost::serialization::access;

	/**
	 * Serializes the joint proprioceptor to a string.
	 * @param os The ostream.
	 * @param jointProprioceptor The joint proprioceptor we want to serialize.
	 * @return A string containing all information about the joint proprioceptor.
	 */
	friend std::ostream & operator<<(std::ostream &os,
		const JointProprioceptor &jointProprioceptor) {
		return os
		/**The joint index*/
//		<< "JointProprioceptor: Joint index=" << jointProprioceptor.mJointIndex
		/** The motor index*/
		<< "/Motor index=" << jointProprioceptor.mMotorIndex;
	}

	/**
	 * Serializes the joint proprioceptor to an xml file.
	 * @param ar The archive.
	 * @param The file version.
	 */
	template<class Archive>
	void serialize(Archive & ar, const unsigned int /* file_version */) {
		ar
		/**The joint index*/
//		& BOOST_SERIALIZATION_NVP(mJointIndex)
		/** The motor index*/
		& BOOST_SERIALIZATION_NVP(mMotorIndex);
	}

protected:
	JointPhysics::RotationalDegreeOfFreedom mMotorIndex; /** The motor index the proprioceptor is working on. */

	JointModel* mJoint; /**!< A pointer for the joint the proprioceptor is working on. */
};
BOOST_CLASS_VERSION(JointProprioceptor, 1)
BOOST_SERIALIZATION_ASSUME_ABSTRACT(JointProprioceptor)
#endif /* MODEL_EVOLUTION_POPULATION_CREATURE_GENOME_SENSORS_JOINTPROPRIOCEPTOR_H_ */
