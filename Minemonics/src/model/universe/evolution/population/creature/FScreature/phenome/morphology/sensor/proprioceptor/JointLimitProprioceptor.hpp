#ifndef MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_SENSOR_PROPRIOCEPTOR_JOINTLIMITPROPRIOCEPTOR_HPP_
#define MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_SENSOR_PROPRIOCEPTOR_JOINTLIMITPROPRIOCEPTOR_HPP_

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
 * @brief		A receptor to measure the reaching of a joint limit.
 * @details		Details
 * @date		2015-08-18
 * @author		Benjamin Ellenberger
 */
class JointLimitProprioceptor: public JointProprioceptor {
public:
	enum Limit {
		LOWER_LIMIT, UPPER_LIMIT, BOTH_LIMITS
	};
	JointLimitProprioceptor(std::vector<CONSTRAINT_TYPE*>::size_type jointIndex,
			FSJointPhysics::RotationalDegreeOfFreedom rotationalDOF, Limit limit);
	virtual ~JointLimitProprioceptor();

	virtual void update(double timeSinceLastTick);

	//Accessor methods
	double getLimitError() const {
		return mLimitError;
	}

	void setLimitError(double limitError) {
		mLimitError = limitError;
		setOutputValue(limitError);
	}

private:
	double mLimitError;
	Limit mLimit;
};

#endif /* MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_SENSOR_PROPRIOCEPTOR_JOINTLIMITPROPRIOCEPTOR_HPP_ */
