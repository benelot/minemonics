//# corresponding header
#include <utils/Randomness.hpp>

//## controller headers
//## model headers
#include <boost/random/uniform_real_distribution.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/math/special_functions/round.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <OgreVector3.h>
#include <OgreQuaternion.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers
Randomness* Randomness::mRandomness;
Randomness::Randomness() {
	mRandomness = this;
	boost::posix_time::ptime time_t_epoch(boost::gregorian::date(1970, 1, 1));
	boost::posix_time::ptime now =
		boost::posix_time::microsec_clock::local_time();
	boost::posix_time::time_duration diff = now - time_t_epoch;

	rng.seed(diff.total_milliseconds());
}

Randomness::~Randomness() {

}

/**
 * Get a uniformly distributed random double which is limited by a lower and an upper limit.
 *
 * @param lowerLimit The lower limit we want to draw from.
 * @param upperLimit The upper limit we want to draw from.
 * @return A random double which is limited by a lower and an upper limit.
 */
double Randomness::nextUnifDouble(double lowerLimit, double upperLimit) {
	if (lowerLimit == upperLimit) {
		return lowerLimit;
	}

	boost::random::uniform_real_distribution<> unifDoubleDistribution(
		lowerLimit, upperLimit);

	return unifDoubleDistribution(rng);
}
/**
 * Get a non-negative uniformly distributed random integer number to draw random array elements.
 * @param lowerLimit The lower limit we want to draw from.
 * @param upperLimit The upper limit we want to draw from.
 * @return A non-negative integer number.
 */
int Randomness::nextUnifPosInt(int lowerLimit, int upperLimit) {
	if (upperLimit <= 0) {
		return 0;
	} else if (lowerLimit == upperLimit) {
		return lowerLimit;
	}

//	std::cout <<" Limits: " << lowerLimit << "," << upperLimit;

	//create a uniform integer distribution
	boost::random::uniform_int_distribution<> unifIntDistribution(lowerLimit,
		upperLimit);

	//draw from it via the mersenne twister
	int i = unifIntDistribution(rng);
	//TODO: It seems that the distribution sometimes returns very high values
	if(i > upperLimit){
		i = upperLimit;
	}else if(i < lowerLimit){
		i = lowerLimit;
	}
	return i;
}
/**
 * Is a function which generates two values,
 1O^m and 10^n, both between 10^lowerLimit and 10^upperLimit with exponents m and n chosen uniformly at random from the
 range [10^lowerLimit..10^upperLimit],and returning whichever of the two values is closer to upperLimit.
 * @param lowerLimit The lower limit we want to draw from.
 * @param upperLimit The upper limit we want to draw from.
 * @return The double which is nearer to
 */
double Randomness::nextBiasedLogDouble(double lowerLimit, double upperLimit) {
	if (lowerLimit == upperLimit) {
		return lowerLimit;
	}

	boost::random::uniform_real_distribution<> unifDoubleDistribution(
		pow(10, lowerLimit), pow(10, upperLimit));

	//draw m and n
	double tenpowm = unifDoubleDistribution(rng);
	double tenpown = unifDoubleDistribution(rng);

	//return m or n whichever is higher
	return (tenpowm > tenpown) ? log10(tenpowm) : log10(tenpown);
}

bool Randomness::nextUnifBoolean() {
	//create a uniform integer distribution
	boost::random::uniform_int_distribution<> unifIntDistribution(0, 1);

	// return true if 1 else false
	return (unifIntDistribution(rng)) ? true : false;
}

int Randomness::nextNormalInt(double mean, double variance, double limit) {
	//create a uniform integer distribution
	boost::random::normal_distribution<> normalIntDistribution(mean,
		(variance));

	double number = normalIntDistribution(rng);
	int integer = round(number);

	if (limit > 0) {
		//99.9% lie in between mean +- variance*2.0f
		if (integer > mean + variance * limit) {
			integer = mean + variance * limit;
		} else if (integer < mean - variance * limit) {
			integer = mean - variance * limit;
		}
	}
	return integer;
}

double Randomness::nextNormalDouble(double mean, double variance,
	double limit) {
	//create a uniform integer distribution
	boost::random::normal_distribution<> normalDoubleDistribution(mean,
		variance);

	double number = normalDoubleDistribution(rng);

	if (limit > 0) {
		//99.9% lie in between mean +- variance*2.0f
		if (number > mean + variance * limit) {
			number = mean + variance * limit;
		} else if (number < mean - variance * limit) {
			number = mean - variance * limit;
		}
	}

	return number;
}

bool Randomness::nextNormalBoolean(double mean, double variance) {
	//create a uniform integer distribution
	boost::random::normal_distribution<> normalBooleanDistribution(mean,
		variance);

	double number = normalBooleanDistribution(rng);
	bool result = false;
	if (number > 1) {
		result = true;
	} else if (number < 0) {
		result = false;
	} else {
		result = ((int) round(number)) ? true : false;
	}

	return result;
}

Ogre::Vector3 Randomness::nextVector() {
	double theta = nextUnifDouble(0.0,
		2 * boost::math::constants::pi<double>());

	double rawX = sin(theta);

	double rawY = cos(theta);

	double z = nextUnifDouble(-1.0, 1.0);

	double phi = asin(z);

	double scalar = cos(phi);

	double x = rawX * scalar;

	double y = rawY * scalar;

	return Ogre::Vector3(x, y, z);
}

Ogre::Quaternion Randomness::nextQuaternion() {
	Ogre::Vector3 v = nextVector();

	double x = v.x;

	double y = v.y;

	double z = v.z;

	double theta = nextUnifDouble(0.0,
		2 * boost::math::constants::pi<double>());

	double cosTheta = cos(theta);

	double sinTheta = sin(theta);

	return Ogre::Quaternion(cosTheta, x * sinTheta, y * sinTheta, z * sinTheta);
}
