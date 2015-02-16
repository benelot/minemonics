/*
 * Randomness.h
 *
 *  Created on: Nov 17, 2014
 *      Author: leviathan
 */

#ifndef RANDOMNESS_H_
#define RANDOMNESS_H_

/**
 * The randomness class abstracts the randomness used in this program, making it easier to change it if necessary.
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
};

#endif /* RANDOMNESS_H_ */
