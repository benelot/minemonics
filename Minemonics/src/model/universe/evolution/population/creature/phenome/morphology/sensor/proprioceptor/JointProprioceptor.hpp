#ifndef MODEL_EVOLUTION_POPULATION_CREATURE_GENOME_SENSORS_JOINTPROPRIOCEPTOR_H_
#define MODEL_EVOLUTION_POPULATION_CREATURE_GENOME_SENSORS_JOINTPROPRIOCEPTOR_H_

//# corresponding header
#include <model/universe/evolution/population/creature/phenome/morphology/sensor/proprioceptor/Proprioceptor.hpp>

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
	JointProprioceptor(CONSTRAINT_TYPE* g6DofJoint,
			JointPhysics::RotationalDegreeOfFreedom rotationalDOF);
	~JointProprioceptor();

	virtual void update(double timeSinceLastTick) = 0;

protected:
	JointPhysics::RotationalDegreeOfFreedom mMotorIndex;
	/**
	 * The 6 Degrees of freedom joint that is used as a physical model.
	 */
	CONSTRAINT_TYPE* mG6DofJoint;
};

#endif /* MODEL_EVOLUTION_POPULATION_CREATURE_GENOME_SENSORS_JOINTPROPRIOCEPTOR_H_ */
