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
	Velocity(const double weight);
	virtual ~Velocity();

	/**
	 * Calculates the current average velocity.
	 * @param x2 The new x position.
	 * @param y2 The new y position.
	 * @param z2 The new z position.
	 * @param diffTime The time since the last velocity calculation.
	 */
	void calculateAvgVelocity(const double x2, const double y2, const double z2,
			const float diffTime);

	/**
	 * Evaluate the fitness.
	 */
	void evaluateFitness();

	virtual Velocity* clone();

private:
	double mAvgVelocity;

	double mX, mY, mZ;
	float mTimestamp;
	int mSampleQty;
	bool mIsFirstTime;
};

#endif /* MODEL_UNIVERSE_EVOLUTION_JURIES_VELOCITY_H_ */
