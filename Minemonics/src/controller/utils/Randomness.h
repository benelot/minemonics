/*
 * Randomness.h
 *
 *  Created on: Nov 17, 2014
 *      Author: leviathan
 */

#ifndef RANDOMNESS_H_
#define RANDOMNESS_H_

class Randomness {
public:
	Randomness();
	virtual ~Randomness();

	double nextDouble(double lowerLimit, double upperLimit);
	int nextPosInt(int lowerLimit, int upperLimit);
};

#endif /* RANDOMNESS_H_ */
