/*
 * Randomness.cpp
 *
 *  Created on: Nov 17, 2014
 *      Author: leviathan
 */

#include "Randomness.h"

#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <cstdlib>
#include <math.h>

Randomness::Randomness() {
	/* initialize random seed: */
	srand(time(NULL));

}

Randomness::~Randomness() {
	// TODO Auto-generated destructor stub
}

/**
 * Get a random double which is limited by a lower and an upper limit. This is done by taking a random number
 *  between 0 and 1 and by multiplying it with the difference between upper and lower limit.
 *  Then we add the lower limit to it and get a number between the limits.
 */
double Randomness::nextDouble(double lowerLimit, double upperLimit) {
	return lowerLimit
			+ (((double) rand()) / ((double) RAND_MAX)
					* (upperLimit - lowerLimit));
}

int Randomness::nextPosInt(int lowerLimit, int upperLimit) {
	if (upperLimit == 0) {
		return 0;
	}
	// 1+ is necessary for the upperlimit to be reached
	return lowerLimit + floor(rand() % (1 + upperLimit - lowerLimit));
}
