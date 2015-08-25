#ifndef MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_CONTROLLER_SINE_SINECONTROLLER_HPP_
#define MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_CONTROLLER_SINE_SINECONTROLLER_HPP_

//# corresponding headers
#include <model/universe/evolution/population/creature/phenome/controller/Controller.hpp>

//# forward declarations
namespace boost {
namespace serialization {
class access;
} /* namespace serialization */
} /* namespace boost */

//# system headers
#include <iostream>

//## controller headers
//## model headers
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/version.hpp>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers

/**
 * @brief		The sine controller takes the sin of the incoming value and passes it to the outputs.
 * @details		Details
 * @date		2015-03-09
 * @author		Benjamin Ellenberger
 */
class SineController: public Controller {
public:
	SineController();
	SineController(const SineController& sineController);

	virtual ~SineController();

	/**
	 * Initialize the sine controller with a certain amplitude and frequency for the sine wave and the motor it controls.
	 * @param amplitude The amplitude of the sine wave.
	 * @param frequency The frequency of the sine wave.
	 * @param xShift shift in x direction.
	 * @param yShift shift in y direction.
	 */
	void initialize(const double amplitude, const double frequency,
	const double xShift, const double yShift);

	/**
	 * Clone the sine controller.
	 * @return The clone of the sine controller.
	 */
	SineController* clone();

	void perform(const double timeSinceLastFrame);

	void collectInputs();

	//Serialization
	friend class boost::serialization::access; /**!< Give access to boost serialization*/

	/**
	 * Serializes the sine controller model to a string.
	 * @param os The ostream.
	 * @param creature The sine controller we want to serialize.
	 * @return A string containing all information about the sine controller.
	 */
	friend std::ostream & operator<<(std::ostream &os,
	const SineController &sineController) {
		os << "SineController: Type=" << sineController.mType /**!< The type of controller*/

		<< "/Amplitude=" << sineController.mAmplitude /**!< The amplitude of the sine controller*/

		<< "/Frequency= " << sineController.mFrequency << "Hz" /**!< The frequence of the sine controller*/

		<< "/XShift=" << sineController.mXShift /**!< The X shift of the sine controller*/

		<< "/YShift=" << sineController.mYShift; /**!< The YShift of the sine controller*/
		//TODO: Control inputs and outputs
		return os;
	}

	/**
	 * Serializes the sine controller to an xml file.
	 * @param ar The archive.
	 * @param The file version.
	 */
	template<class Archive>
	void serialize(Archive & ar, const unsigned int /* file_version */) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Controller) /**!< Serialize the base object */

		& BOOST_SERIALIZATION_NVP(mAmplitude) /**The amplitude of the sine controller*/

		& BOOST_SERIALIZATION_NVP(mFrequency) /**The frequence of the sine controller*/

		& BOOST_SERIALIZATION_NVP(mXShift) /**The X shift of the sine controller*/

		& BOOST_SERIALIZATION_NVP(mYShift) /**The YShift of the sine controller*/

		& BOOST_SERIALIZATION_NVP(mTime); /**The time of the sine controller*/
	}

private:
	/**
	 * The amplitude of the sine wave
	 */
	double mAmplitude;

	/**
	 * The frequency of the sine wave
	 */
	double mFrequency;

	/**
	 * The shift in the x axis of the sine wave.
	 */
	double mXShift;

	/**
	 * The shift in the y axis of the sine wave.
	 */
	double mYShift;

	/**
	 * The timer of of sine wave.
	 */
	double mTime;
};

BOOST_CLASS_VERSION(SineController, 1)

#endif /* MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_CONTROLLER_SINE_SINECONTROLLER_HPP_ */
