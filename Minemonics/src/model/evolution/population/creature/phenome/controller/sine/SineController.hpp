#ifndef MODEL_EVOLUTION_POPULATION_CREATURE_PHENOME_CONTROLLER_SINE_SINECONTROLLER_HPP_
#define MODEL_EVOLUTION_POPULATION_CREATURE_PHENOME_CONTROLLER_SINE_SINECONTROLLER_HPP_

//# corresponding headers
#include <model/evolution/population/creature/phenome/controller/Controller.hpp>

//# forward declarations
//# system headers
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
 * @brief		The sine controller takes the sin of the incoming value and passes it to the outputs.
 * @details		Details
 * @date		2015-03-09
 * @author		Benjamin Ellenberger
 */
class SineController: public Controller {
public:
	SineController();
	virtual ~SineController();

	/**
	 * Initialize the sine controller with a certain amplitude and frequency for the sine wave and the motor it controls.
	 * @param amplitude The amplitude of the sine wave.
	 * @param frequency The frequency of the sine wave.
	 * @param xShift shift in x direction.
	 * @param yShift shift in y direction.
	 */
	void initialize(double amplitude, double frequency, double xShift,double yShift);

	void perform(double time);

	void collectInputs();

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

#endif /* MODEL_EVOLUTION_POPULATION_CREATURE_PHENOME_CONTROLLER_SINE_SINECONTROLLER_HPP_ */
