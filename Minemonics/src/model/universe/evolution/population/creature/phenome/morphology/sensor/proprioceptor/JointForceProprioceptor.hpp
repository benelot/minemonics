#ifndef MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_SENSOR_PROPRIOCEPTOR_JOINTFORCEPROPRIOCEPTOR_HPP_
#define MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_SENSOR_PROPRIOCEPTOR_JOINTFORCEPROPRIOCEPTOR_HPP_

//# corresponding header
#include <model/universe/evolution/population/creature/phenome/morphology/sensor/proprioceptor/JointProprioceptor.hpp>

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
 * @brief		A receptor to measure the force applied to a joint.
 * @details		Details
 * @date		2015-08-18
 * @author		Benjamin Ellenberger
 */
class JointForceProprioceptor: public JointProprioceptor {
public:
	JointForceProprioceptor(std::vector<int*>::size_type jointIndex,
			JointPhysics::RotationalDegreeOfFreedom rotationalDOF);
	virtual ~JointForceProprioceptor();

	virtual void update(double timeSinceLastTick);

	//Accessor methods
	double getForce() const {
		return mForce;
	}

	void setForce(double force) {
		mForce = force;
		setOutputValue(force);
	}

private:
	double mForce;
};

#endif /* MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_SENSOR_PROPRIOCEPTOR_JOINTFORCEPROPRIOCEPTOR_HPP_ */
