#ifndef MODEL_EVOLUTION_POPULATION_CREATURE_PHENOME_CONTROLLER_CONTROLLER_HPP_
#define MODEL_EVOLUTION_POPULATION_CREATURE_PHENOME_CONTROLLER_CONTROLLER_HPP_

//# corresponding headers
//# forward declarations
//# system headers
#include <vector>

//## controller headers
//## model headers
#include <model/evolution/population/creature/phenome/controller/ControlInput.hpp>
#include <model/evolution/population/creature/phenome/controller/ControlOutput.hpp>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers

/**
 * @brief		The controller template defines the basic properties of all controllers for a creature.
 * @details		Details
 * @date		2015-03-09
 * @author		Benjamin Ellenberger
 */
class Controller: public ControlInput, public ControlOutput {
public:
	/**
	 * The type of controller that is running
	 */
	enum ControllerType {
		SINE_CONTROLLER, NEURAL_NETWORK_CONTROLLER, UNKNOWN_CONTROLLER
	};

	Controller(ControllerType controllerType);
	virtual ~Controller();

	virtual void collectInputs() = 0;

	virtual void perform(double time) = 0;

	/**
	 * Distribute the output among the adjacent controllers or endpoints
	 * @param output
	 */
	virtual void distributeOutput(double output);

	void addControlInput(ControlOutput* controlOutput);

	void addControlOutput(ControlInput* controlInput);



protected:

	/**
	 * The type of controller that is running
	 */
	ControllerType mControllerType;

	/**
	 * The control input the controller reads from.
	 */
	std::vector<ControlOutput*> mControlInputs;

	/**
	 * The control output the controller writes to.
	 */
	std::vector<ControlInput*> mControlOutputs;
};

#endif /* MODEL_EVOLUTION_POPULATION_CREATURE_PHENOME_CONTROLLER_CONTROLLER_HPP_ */
