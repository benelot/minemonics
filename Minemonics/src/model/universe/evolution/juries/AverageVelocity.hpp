#ifndef MODEL_UNIVERSE_EVOLUTION_JURIES_AVERAGEVELOCITY_H_
#define MODEL_UNIVERSE_EVOLUTION_JURIES_AVERAGEVELOCITY_H_

//# corresponding headers
#include <model/universe/evolution/juries/Jury.hpp>

//# forward declarations
class CreatureModel;

//# system headers
#include <vector>

//## controller headers
//## model headers
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/version.hpp>
#include <OgreVector3.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers
#include <utils/logging/Logger.hpp>

/**
 * @brief		The average velocity jury evaluates how fast an individual moves on average during its evaluation time.
 * @details		Details
 * @date		2015-02-26
 * @author		Benjamin Ellenberger
 */
class AverageVelocity: public Jury {
public:
	AverageVelocity();
	AverageVelocity(const bool higherIsBetter, const double weight);
	virtual ~AverageVelocity();

	virtual void calculateFitness(CreatureModel* creature,
		double timeSinceLastTick);

	Ogre::Vector3 getDistanceVector(const double x1, const double x2,
		const double y1, const double y2, const double z1, const double z2);

	/**
	 * Calculates the distance.
	 * @param x2 The new x position.
	 * @param y2 The new y position.
	 * @param z2 The new z position.
	 * @param diffTime The time since the last velocity calculation.
	 */
	double calculateDistance(const double x1, const double x2, const double y1,
		const double y2, const double z1, const double z2,
		const float diffTime);

	/**
	 * Evaluate the fitness.
	 */
	void evaluateFitness();

	virtual AverageVelocity* clone();

	//Accessor methods

	// Serialization
	friend class boost::serialization::access; /**!< Give access to boost serialization */

	/**
	 * Serializes the average velocity jury to a string.
	 * @param os The ostream.
	 * @param avgVelocityJury The average velocity jury we want to serialize.
	 * @return A string containing all information about the average velocity jury.
	 */
	friend std::ostream & operator<<(std::ostream &os,
		const AverageVelocity &avgVelocityJury) {
		return os;
	}

	/**
	 * Serializes the average velocity jury to an xml file.
	 * @param ar The archive.
	 * @param The file version.
	 */
	template<class Archive>
	void serialize(Archive & ar, const unsigned int /* file_version */) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Jury); /**!< Serialize the base object */
	}

private:
	/**
	 * The boost logger.
	 */
	static BoostLogger mBoostLogger;

	/**
	 * Initializer of the boost logger to include the class name into the logging messages.
	 */
	static class _Init {
	public:
		_Init() {
			mBoostLogger.add_attribute("ClassName",
				boost::log::attributes::constant < std::string
					> ("AverageVelocity"));
		}
	} _initializer;

	Ogre::Vector3 mTotalMovement;

	double mAvgVelocity; /**!< The average velocity */

	double mTimestamp; /**!< The timestamp of the last invocation */

	bool mIsFirstTime; /** Is this the first time this jury is run */

	std::vector<Ogre::Vector3> mInitialCoords; /**!< The initial coordinates of each limb */
};

#endif /* MODEL_UNIVERSE_EVOLUTION_JURIES_AVERAGEVELOCITY_H_ */
