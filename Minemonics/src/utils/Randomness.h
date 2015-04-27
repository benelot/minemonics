/*
 * Randomness.h
 *
 *  Created on: Nov 17, 2014
 *      Author: leviathan
 */

#ifndef RANDOMNESS_H_
#define RANDOMNESS_H_

//# corresponding header
//# forward declarations
//# system headers
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/normal_distribution.hpp>

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
 * The randomness class abstracts the randomness used in this program, making it easier to change it if necessary.
 */

/**
 * @brief		Brief
 * @details		Details
 * @date		2015-04-27
 * @author		Benjamin Ellenberger
 */
class Randomness {
public:
	Randomness();
	virtual ~Randomness();

	/**
	 * @brief This method returns a random double between and including the limits.
	 *
	 * @param lowerLimit The lower inclusive limit of the random double.
	 * @param upperLimit The upper inclusive limit of the random double.
	 * @return a random double between and including the limits
	 */
	double nextDouble(double lowerLimit, double upperLimit);

	/**
	 * @brief This method returns a random integer between and including the limits.
	 *
	 * @param lowerLimit The lower inclusive limit of the random double.
	 * @param upperLimit The upper inclusive limit of the random double.
	 * @return a random double between and including the limits
	*/
	int nextPosInt(int lowerLimit, int upperLimit);

	double nextBiasedLog(double lowerLimit,double upperLimit);

	bool nextBoolean();

	int nextNormalInt(double mean,double variance);

	double nextNormalDouble(double mean, double variance);

	bool nextNormalBoolean(double mean, double variance);
private:

	// A mersenne twister in a very good configuration
	boost::random::mt19937 rng;
};

#endif /* RANDOMNESS_H_ */
