#ifndef MODEL_UNIVERSE_EVOLUTION_JURIES_AVERAGEHEIGHT_HPP_
#define MODEL_UNIVERSE_EVOLUTION_JURIES_AVERAGEHEIGHT_HPP_

//# corresponding header
//# forward declarations
//# system headers
#include <vector>

//## controller headers
//## model headers
//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
#include <model/universe/evolution/juries/Jury.hpp>

//## view headers
//## utils headers

/**
 * @brief		The average velocity jury evaluates how high an individual moves on average during its evaluation time.
 * @details		Details
 * @date		2015-05-02
 * @author		Benjamin Ellenberger
 */
class AverageHeight: public Jury {
public:
	AverageHeight(const bool higherIsBetter,const double weight);
	virtual ~AverageHeight();

	virtual void calculateFitness(CreatureModel* creature, double timeSinceLastTick);

	/**
	 * Evaluate the fitness.
	 */
	void evaluateFitness();

	virtual AverageHeight* clone();

private:
	int mSampleQty;
	bool mIsFirstTime;

	double mAvgHeight;
};

#endif /* MODEL_UNIVERSE_EVOLUTION_JURIES_AVERAGEHEIGHT_HPP_ */
