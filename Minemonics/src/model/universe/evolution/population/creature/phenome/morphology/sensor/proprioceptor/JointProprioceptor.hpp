#ifndef MODEL_EVOLUTION_POPULATION_CREATURE_GENOME_SENSORS_JOINTPROPRIOCEPTOR_H_
#define MODEL_EVOLUTION_POPULATION_CREATURE_GENOME_SENSORS_JOINTPROPRIOCEPTOR_H_

//# corresponding header
#include <model/universe/evolution/population/creature/SRBcreature/phenome/morphology/joint/SRBJointPhysics.hpp>
#include <model/universe/evolution/population/creature/SRBcreature/phenome/morphology/sensor/proprioceptor/Proprioceptor.hpp>

//# forward declarations
//# system headers
//## controller headers
//## model headers
//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers

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
	JointProprioceptor(std::vector<CONSTRAINT_TYPE*>::size_type jointIndex,
		JointPhysics::RotationalDegreeOfFreedom rotationalDOF);
	~JointProprioceptor();

	/**
	 * Update the joint proprioceptor input.
	 * @param timeSinceLastTick
	 */
	virtual void update(double timeSinceLastTick) = 0;

	//Serialization
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
		<< "JointProprioceptor: Joint index=" << jointProprioceptor.mJointIndex
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
		& BOOST_SERIALIZATION_NVP(mJointIndex)
		/** The motor index*/
		& BOOST_SERIALIZATION_NVP(mMotorIndex);
	}

protected:
	/**
	 * The motor index the proprioceptor is working on.
	 */
	JointPhysics::RotationalDegreeOfFreedom mMotorIndex;

	/**
	 * The joint index the proprioceptor is working on.
	 */
	std::vector<CONSTRAINT_TYPE*>::size_type mJointIndex;

	/**
	 * A pointer for the joint the proprioceptor is working on.
	 */
	CONSTRAINT_TYPE* mJoint;
};
BOOST_CLASS_VERSION(JointProprioceptor, 1)
BOOST_SERIALIZATION_ASSUME_ABSTRACT(JointProprioceptor)
#endif /* MODEL_EVOLUTION_POPULATION_CREATURE_GENOME_SENSORS_JOINTPROPRIOCEPTOR_H_ */
