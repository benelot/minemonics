#ifndef MODEL_UNIVERSE_EVOLUTION_JURIES_AVERAGEVELOCITY_H_
#define MODEL_UNIVERSE_EVOLUTION_JURIES_AVERAGEVELOCITY_H_

//# corresponding headers
#include <model/universe/evolution/juries/Jury.hpp>

//# forward declarations
class CreatureModel;

//# system headers
#include <vector>

//## controller headers
//## model headers
#include <OgreVector3.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers

/**
 * @brief		The average velocity jury evaluates how fast an individual moves on average during its evaluation time.
 * @details		Details
 * @date		2015-02-26
 * @author		Benjamin Ellenberger
 */
class AverageVelocity: public Jury {
public:
	AverageVelocity(const bool higherIsBetter,const double weight);
	virtual ~AverageVelocity();

	virtual void calculateFitness(CreatureModel* creature, double timeSinceLastTick);

	Ogre::Vector3 getDistanceVector(const double x1, const double x2,
			const double y1, const double y2, const double z1, const double z2);

	/**
	 * Calculates the distance.
	 * @param x2 The new x position.
	 * @param y2 The new y position.
	 * @param z2 The new z position.
	 * @param diffTime The time since the last velocity calculation.
	 */
	double calculateDistance(const double x1, const double x2, const double y1,
			const double y2, const double z1, const double z2,
			const float diffTime);

	/**
	 * Evaluate the fitness.
	 */
	void evaluateFitness();

	virtual AverageVelocity* clone();

private:
	Ogre::Vector3 mTotalMovement;
	double mAvgVelocity;
	int mCreatureLimbQty;

	double mTimestamp;
	int mSampleQty;
	bool mIsFirstTime;

	std::vector<Ogre::Vector3> mLastCoords;
};

#endif /* MODEL_UNIVERSE_EVOLUTION_JURIES_AVERAGEVELOCITY_H_ */
