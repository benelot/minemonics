/*
 * ControlInput.hpp
 *
 *  Created on: Apr 30, 2015
 *      Author: leviathan
 */

#ifndef MODEL_EVOLUTION_POPULATION_CREATURE_PHENOME_CONTROLLER_CONTROLINPUT_HPP_
#define MODEL_EVOLUTION_POPULATION_CREATURE_PHENOME_CONTROLLER_CONTROLINPUT_HPP_

/**
 * @brief		The controller input abstract class holds the inputs of the previous controller or sensor for the next computation.
 * @details		Details
 * @date		2015-04-30
 * @author		Benjamin Ellenberger
 */
class ControlInput {
public:
	ControlInput();
	virtual ~ControlInput();

	double getValue() {
		mReceivedInput = false;
		return mValue;
	}

	void setValue(double value) {
		mReceivedInput = true;
		mValue = value;
	}

	bool isReceivedInput() const {
		return mReceivedInput;
	}

private:
	bool mReceivedInput;
	double mValue;
};

#endif /* MODEL_EVOLUTION_POPULATION_CREATURE_PHENOME_CONTROLLER_CONTROLINPUT_HPP_ */
