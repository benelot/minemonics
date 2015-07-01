#ifndef MODEL_UNIVERSE_EVOLUTION_JURIES_VELOCITY_H_
#define MODEL_UNIVERSE_EVOLUTION_JURIES_VELOCITY_H_

//# corresponding headers
#include <model/universe/evolution/juries/Jury.hpp>

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
 * @brief		The velocity jury evaluates how fast an individual moves on average during its evaluation time.
 * @details		Details
 * @date		2015-02-26
 * @author		Benjamin Ellenberger
 */
class Velocity: public Jury {
public:
	Velocity(double weight);
	virtual ~Velocity();

	void calculateAvgVelocity(double x2, double y2, double z2, float diffTime);
	void evaluateFitness();

private:
	double mAvgVelocity;

	double mX, mY, mZ;
	float mTimestamp;
	int mSampleQty;
	bool mIsFirstTime;
};

#endif /* MODEL_UNIVERSE_EVOLUTION_JURIES_VELOCITY_H_ */
