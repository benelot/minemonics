#ifndef MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_CONTROLLER_CONTROLLER_HPP_
#define MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_CONTROLLER_CONTROLLER_HPP_

//# corresponding headers
//# forward declarations
//# system headers
#include <vector>

//## controller headers
//## model headers
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/version.hpp>
#include <boost/archive/tmpdir.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
#include <model/universe/evolution/population/creature/phenome/controller/ControlInput.hpp>
#include <model/universe/evolution/population/creature/phenome/controller/ControlOutput.hpp>

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

	/**
	 * Collect inputs and prepare for computation.
	 */
	virtual void collectInputs() = 0;

	/**
	 * Perform computation in the controller.
	 * @param timeSinceLastFrame The time passed since the last frame.
	 */
	virtual void perform(double timeSinceLastFrame) = 0;

	/**
	 * Distribute the output among the adjacent controllers or endpoints
	 * @param output
	 */
	virtual void distributeOutput(double output);

	/**
	 * Add a control input to the controller.
	 * @param controlOutput The control output of another controller.
	 */
	void addControlInput(ControlOutput* controlOutput);

	/**
	 * Add a control output to the controller.
	 * @param controlInput The control input of another controller.
	 */
	void addControlOutput(ControlInput* controlInput);


	/**
	 * Compare the controller to another controller.
	 * @param controller Another controller.
	 * @return If the controller is equal to the other controller.
	 */
	bool equals(const Controller & controller) const;

	//Serialization

	/**
	 * Give access to boost serialization
	 */
	friend class boost::serialization::access;

	/**
	 * Serializes the controller to a string.
	 * @param os The ostream.
	 * @param controller The controller we want to serialize.
	 * @return A string containing all information about the controller.
	 */
	friend std::ostream & operator<<(std::ostream &os,
			const Controller &controller) {
		os
		/**The type of gene*/
		<< "Controller: type=" << controller.mType;

		/**The vector of control inputs.*/
		std::vector<ControlOutput*>::const_iterator it;
		for (it = controller.mControlInputs.begin();
				it != controller.mControlInputs.end(); it++) {
			os << (**it);
			os << "||";
		}

		/**The vector of control outputs.*/
		std::vector<ControlInput*>::const_iterator it1;
		for (it1 = controller.mControlOutputs.begin();
				it1 != controller.mControlOutputs.end(); it1++) {
			os << (**it1);
			os << "||";
		}
		return os;
	}

	/**
	 * Serializes the gene to an xml file.
	 * @param ar The archive.
	 * @param The file version.
	 */
	template<class Archive>
	void serialize(Archive & ar, const unsigned int /* file_version */) {
		ar
		/**The type of controller*/
		& BOOST_SERIALIZATION_NVP(mType)

		/**The vector of control inputs*/
		& BOOST_SERIALIZATION_NVP(mControlInputs);

		/**The vector of control outputs*/
		&BOOST_SERIALIZATION_NVP(mControlOutputs);
	}

protected:

	/**
	 * The type of controller that is running
	 */
	ControllerType mType;

	/**
	 * The control input the controller reads from.
	 */
	std::vector<ControlOutput*> mControlInputs;

	/**
	 * The control output the controller writes to.
	 */
	std::vector<ControlInput*> mControlOutputs;
};
BOOST_CLASS_VERSION(Controller, 1)
BOOST_SERIALIZATION_ASSUME_ABSTRACT(Controller)
#endif /* MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_CONTROLLER_CONTROLLER_HPP_ */
