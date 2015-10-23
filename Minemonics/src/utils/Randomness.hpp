#ifndef UTILS_RANDOMNESS_H_
#define UTILS_RANDOMNESS_H_

//# corresponding header
//# forward declarations
namespace Ogre {
class Quaternion;
class Vector3;
} /* namespace Ogre */

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
	double nextUnifDouble(double lowerLimit, double upperLimit);

	/**
	 * @brief nextPosInt returns a random integer between and including the limits.
	 *
	 * @param lowerLimit The lower inclusive limit of the random double.
	 * @param upperLimit The upper inclusive limit of the random double.
	 * @return a random double between and including the limits
	 */
	int nextUnifPosInt(int lowerLimit, int upperLimit);

	/**
	 * Returns a random double between the lower limit and the upper limit according to a biased log.
	 * @param lowerLimit The lower limit of the random double.
	 * @param upperLimit The upper limit of the random double.
	 * @return
	 */
	double nextBiasedLogDouble(double lowerLimit, double upperLimit);

	/**
	 * Return a random boolean.
	 * @return The random boolean.
	 */
	bool nextUnifBoolean();

	/**
	 * Return a positive normally distributed integer. The integer however can not be outside of limit variances to cut off extremely high and low numbers.
	 * @param mean The mean of the normal distribution.
	 * @param variance The variance of the normal distribution.
	 * @return The normally distributed integer.
	 */
	int nextNormalPosInt(double mean, double variance, double limit = 2);

	/**
	 * Return a normally distributed integer. The integer however can not be outside of limit variances to cut off extremely high and low numbers.
	 * @param mean The mean of the normal distribution.
	 * @param variance The variance of the normal distribution.
	 * @return The normally distributed integer.
	 */
	int nextNormalInt(double mean, double variance, double limit = 2);

	/**
	 * Return a normally distributed double. The double however can not be outside of limit variances to cut off extremely high and low numbers.
	 * @param mean The mean of the normal distribution.
	 * @param variance The variance of the normal distribution.
	 * @return The normally distributed double.
	 */
	double nextNormalDouble(double mean, double variance, double limit = 2);

	/**
	 * Return a normally distributed boolean.
	 * @param mean The mean of the normal distribution.
	 * @param variance The variance of the normal distribution.
	 * @return The normally distributed boolean.
	 */
	bool nextNormalBoolean(double mean, double variance);

	/**
	 * Return a random vector.
	 * @return The random vector.
	 */
	Ogre::Vector3 nextVector();

	/**
	 * Return a random quaternion.
	 * @return The random quaternion.
	 */
	Ogre::Quaternion nextQuaternion();

	// Accessor methods

	static Randomness* getSingleton(){
		return mRandomness;
	}

private:

	boost::random::mt19937 rng; 	/**!< A mersenne twister in a configuration that has a very long limitcycle */

	static Randomness* mRandomness; /**!< Singleton instance. */
};

#endif /* UTILS_RANDOMNESS_H_ */
