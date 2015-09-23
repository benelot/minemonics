#ifndef MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_SENSOR_PROPRIOCEPTOR_JOINTANGLECEPTOR_HPP_
#define MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_SENSOR_PROPRIOCEPTOR_JOINTANGLECEPTOR_HPP_

//# corresponding header
#include <model/universe/evolution/population/creature/SRBcreature/phenome/morphology/sensor/proprioceptor/JointProprioceptor.hpp>

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
 * @brief		A receptor to measure the angle of the joint.
 * @details		Details
 * @date		2015-08-18
 * @author		Benjamin Ellenberger
 */
class JointAngleceptor: public JointProprioceptor {
public:
	JointAngleceptor(std::vector<CONSTRAINT_TYPE*>::size_type jointIndex,
		JointPhysics::RotationalDegreeOfFreedom rotationalDOF);
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

private:
	double mAngle;
};

#endif /* MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_SENSOR_PROPRIOCEPTOR_JOINTANGLECEPTOR_HPP_ */
