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
	srand (time(NULL));

}

Randomness::~Randomness() {
	// TODO Auto-generated destructor stub
}

/*
 * This method returns a random double between and including the limits.
 *
 * @param lowerLimit
 * @param upperLimit
 * @return
 */
double Randomness::nextDouble(double lowerLimit, double upperLimit)
{
	return lowerLimit + (((double)rand())/((double)RAND_MAX)*(upperLimit - lowerLimit));
}

/**
 * This method returns a random integer between and including the limits.
*
* @param lowerLimit
* @param upperLimit
* @return
*/
int Randomness::nextPosInt(int lowerLimit, int upperLimit)
{
	if (upperLimit == 0)
	{
		return 0;
	}
	// 1+ is necessary for the upperlimit to be reached
	return lowerLimit + floor(rand()%(1 + upperLimit - lowerLimit));
}
