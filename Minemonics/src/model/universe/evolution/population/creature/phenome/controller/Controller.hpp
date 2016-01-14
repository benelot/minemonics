#ifndef MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_CONTROLLER_CONTROLLER_HPP_
#define MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_CONTROLLER_CONTROLLER_HPP_
//# corresponding headers
//# forward declarations
//# system headers
#include <iostream>
#include <iterator>
#include <vector>

//## controller headers
//## model headers
#include <boost/serialization/vector.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/version.hpp>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
#include <model/data/DataSink.hpp>
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
		SINE_CONTROLLER,CHAOTIC_CONTROLLER, NEURAL_NETWORK_CONTROLLER, UNKNOWN_CONTROLLER
	};

	Controller(ControllerType controllerType);
	virtual ~Controller();

	virtual void initialize() = 0;

	virtual Controller* clone() = 0;

	/**
	 * Collect inputs and prepare for computation.
	 */
	virtual void collectInputs() = 0;

	/**
	 * Perform computation in the controller.
	 * @param timeSinceLastFrame The time passed since the last frame.
	 */
	virtual void perform(const double timeSinceLastFrame) = 0;

	/**
	 * Distribute the output among the adjacent controllers or endpoints
	 * @param output
	 */
	virtual void distributeOutput(const double output);

	/**
	 * Add a control input to the controller.
	 * @param controlOutput The control output of another controller.
	 */
	void addControlInput(ControlOutput* const controlOutput);

	/**
	 * Add a control output to the controller.
	 * @param controlInput The control input of another controller.
	 */
	void addControlOutput(ControlInput* const controlInput);

	void setControlInputs(std::vector<ControlOutput*> controlInputs);

	void setControlOutputs(std::vector<ControlInput*> controlOutputs);

	void storeControlIndices();

	ControllerType getType() const {
		return mType;
	}

	void setType(ControllerType type) {
		mType = type;
	}

	const std::vector<int>& getControlInputIndices() const {
		return mControlInputIndices;
	}

	const std::vector<int>& getControlOutputIndices() const {
		return mControlOutputIndices;
	}

	const DataSink* getDataSink() const {
		return &mDataSink;
	}

	const std::string& getLoggingID() const {
		return mLoggingID;
	}

	void setLoggingID(const std::string& loggingId) {
		mLoggingID = loggingId;
	}

	/**
	 * Compare the controller to another controller.
	 * @param controller Another controller.
	 * @return If the controller is equal to the other controller.
	 */
	bool equals(const Controller & controller) const;

	// Serialization ##########################
	friend class boost::serialization::access; /**!< Give access to boost serialization*/

	/**
	 * Serializes the controller to a string.
	 * @param os The ostream.
	 * @param controller The controller we want to serialize.
	 * @return A string containing all information about the controller.
	 */
	friend std::ostream & operator<<(std::ostream &os,
		const Controller &controller) {
		os << "Controller: type=" << controller.mType; /**The type of gene*/

		//TODO: Serialize inputs and outputs via indices
		/**The vector of control inputs.*/
		for (std::vector<ControlOutput*>::const_iterator it =
			controller.mControlInputs.begin();
			it != controller.mControlInputs.end(); it++) {
			os << (**it);
			os << "||";
		}

		/**The vector of control outputs.*/
		for (std::vector<ControlInput*>::const_iterator it =
			controller.mControlOutputs.begin();
			it != controller.mControlOutputs.end(); it++) {
			os << (**it);
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
		ar & BOOST_SERIALIZATION_NVP(mType) /**!< The type of controller*/

		& BOOST_SERIALIZATION_NVP(mControlInputIndices) /**!< The vector of control input indices */

		& BOOST_SERIALIZATION_NVP(mControlOutputIndices); /**!< The vector of control outputs indices */
	}

protected:

	DataSink mDataSink; /**!< Data sink for the plotting window */

	ControllerType mType; /**!< The type of controller that is running */

	std::vector<int> mControlInputIndices; /**!< The index of the control input the controller reads from. */

	std::vector<int> mControlOutputIndices; /**!< The index of the control output the controller writes to.*/

	std::vector<ControlOutput*> mControlInputs; /**!< The control input the controller reads from. */

	std::vector<ControlInput*> mControlOutputs; /**!< The control output the controller writes to.*/

	std::string mLoggingID;
};
BOOST_CLASS_VERSION(Controller, 1)
BOOST_SERIALIZATION_ASSUME_ABSTRACT(Controller)
#endif /* MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_CONTROLLER_CONTROLLER_HPP_ */
