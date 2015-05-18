#ifndef RANDOMNESS_H_
#define RANDOMNESS_H_

//# corresponding header
//# forward declarations
//# system headers
//## controller headers
//## model headers
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/normal_distribution.hpp>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers

/**
 * @brief		The randomness class abstracts the randomness used in this program, making it easier to change it if necessary.
 * @details		Details
 * @date		2014-11-17
 * @author		Benjamin Ellenberger
 */
class Randomness {
public:
	Randomness();
	virtual ~Randomness();

	/**
	 * @brief nextDouble returns a random double between and including the limits.
	 *
	 * @param lowerLimit The lower inclusive limit of the random double.
	 * @param upperLimit The upper inclusive limit of the random double.
	 * @return a random double between and including the limits
	 */
	double nextDouble(double lowerLimit, double upperLimit);

	/**
	 * @brief nextPosInt returns a random integer between and including the limits.
	 *
	 * @param lowerLimit The lower inclusive limit of the random double.
	 * @param upperLimit The upper inclusive limit of the random double.
	 * @return a random double between and including the limits
	 */
	int nextPosInt(int lowerLimit, int upperLimit);

	double nextBiasedLog(double lowerLimit, double upperLimit);

	bool nextBoolean();

	int nextNormalInt(double mean, double variance);

	double nextNormalDouble(double mean, double variance);

	bool nextNormalBoolean(double mean, double variance);

private:

	// A mersenne twister in a very good configuration
	boost::random::mt19937 rng;
};

#endif /* RANDOMNESS_H_ */
