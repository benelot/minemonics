/*
 * Randomness.cpp
 *
 *  Created on: Nov 17, 2014
 *      Author: leviathan
 */

#include "Randomness.h"

#include <boost/random/uniform_real_distribution.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <boost/math/special_functions/round.hpp>

Randomness::Randomness() {

}

Randomness::~Randomness() {
	// TODO Auto-generated destructor stub
}

/**
 * Get a random double which is limited by a lower and an upper limit.
 *
 * @param lowerLimit The lower limit we want to draw from.
 * @param upperLimit The upper limit we want to draw from.
 * @return A random double which is limited by a lower and an upper limit.
 */
double Randomness::nextDouble(double lowerLimit, double upperLimit) {
	boost::random::uniform_real_distribution<> unifDoubleDistribution(
			lowerLimit, upperLimit);
	return unifDoubleDistribution(rng);
}
/**
 * Get a non-negative integer number to draw random array elements.
 * @param lowerLimit The lower limit we want to draw from.
 * @param upperLimit The upper limit we want to draw from.
 * @return A non-negative integer number.
 */
int Randomness::nextPosInt(int lowerLimit, int upperLimit) {
	if (upperLimit <= 0) {
		return 0;
	}

	//create a uniform integer distribution
	boost::random::uniform_int_distribution<> unifIntDistribution(lowerLimit,
			upperLimit);

	//draw from it via the mersenne twister
	return unifIntDistribution(rng);
}
/**
 * Is a function which generates two values,
 1O^m and 10^n, both between 10^lowerLimit and 10^upperLimit with exponents m and n chosen uniformly at random from the
 range [10^lowerLimit..10^upperLimit],and returning whichever of the two values is closer to upperLimit .
 * @param lowerLimit The lower limit we want to draw from.
 * @param upperLimit The upper limit we want to draw from.
 * @return The double which is nearer to
 */
double Randomness::nextBiasedLog(double lowerLimit, double upperLimit) {
	boost::random::uniform_real_distribution<> unifDoubleDistribution(
			pow(10,lowerLimit), pow(10,upperLimit));

	//draw m and n
	double tenpowm = unifDoubleDistribution(rng);
	double tenpown = unifDoubleDistribution(rng);

	//return m or n whichever is higher
	return (tenpowm>tenpown)?log(tenpowm):log(tenpown);
}

bool Randomness::nextBoolean(){
	//create a uniform integer distribution
	boost::random::uniform_int_distribution<> unifIntDistribution(0,
			1);

	// return true if 1 else false
	return (unifIntDistribution(rng))?true:false;
}

int Randomness::nextNormalInt(double mean,double twovariances){
	//create a uniform integer distribution
	boost::random::normal_distribution<> normalIntDistribution(mean,(twovariances/2.0f));

	double number = normalIntDistribution(rng);
	int integer = round(number);

	//99.9% lie in between mean +- twovariances
	if(integer > mean + twovariances)
	{
		integer = mean + twovariances;
	}
	else if(integer < mean - twovariances)
	{
		integer = mean - twovariances;
	}
	return integer;
}

double Randomness::nextNormalDouble(double mean, double variance){
	//create a uniform integer distribution
	boost::random::normal_distribution<> normalDoubleDistribution(mean,variance);

	return normalDoubleDistribution(rng);
}

bool Randomness::nextNormalBoolean(double mean, double variance){
	//create a uniform integer distribution
	boost::random::normal_distribution<> normalBooleanDistribution(mean,variance);

	double number = normalBooleanDistribution(rng);
	bool result = false;
	if(number > 1)
	{
		result = true;
	}
	else if(number < 0)
	{
		result = false;
	}
	else
	{
		result = ((int)round(number))?true:false;
	}


	return result;
}
