#ifndef MODEL_EVOLUTION_POPULATION_CREATURE_PHENOME_CONTROLLER_CONTROLOUTPUT_HPP_
#define MODEL_EVOLUTION_POPULATION_CREATURE_PHENOME_CONTROLLER_CONTROLOUTPUT_HPP_

/**
 * @brief		The controller output abstract class holds the output of the previous controller or sensor for the next computation.
 * @details		Details
 * @date		2015-04-30
 * @author		Benjamin Ellenberger
 */
class ControlOutput {
public:
	ControlOutput();
	virtual ~ControlOutput();

	double getValue() const {
		return mValue;
	}

	void setvalue(double value) {
		mValue = value;
	}

private:
	/**
	 * The control output value
	 */
	double mValue;
};

#endif /* MODEL_EVOLUTION_POPULATION_CREATURE_PHENOME_CONTROLLER_CONTROLOUTPUT_HPP_ */
