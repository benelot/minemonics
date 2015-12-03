#ifndef MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_CONTROLLER_CONTROLOUTPUT_HPP_
#define MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_CONTROLLER_CONTROLOUTPUT_HPP_

//# corresponding headers
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
#include <boost/serialization/assume_abstract.hpp>
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
 * @brief		The controller output abstract class holds the output of the previous controller or sensor for the next computation.
 * @details		Details
 * @date		2015-04-30
 * @author		Benjamin Ellenberger
 */
class ControlOutput {
public:
	ControlOutput();
	ControlOutput(int outputIndex);
	virtual ~ControlOutput();

	/**
	 * Compare the control output to another control output.
	 * @param controlOutput Another control output.
	 * @return If the control output is equal to the other control output.
	 */
	bool equals(const ControlOutput &controlOutput) const;

	// Accessor methods ##########################

	double getOutputValue() const {
		return mOutputValue;
	}

	void setOutputValue(const double outputValue) {
		mOutputValue = outputValue;
	}

	// Serialization ##########################
	friend class boost::serialization::access; /**!<  Give access to boost serialization*/

	/**
	 * Serializes the control output to a string.
	 * @param os The ostream.
	 * @param controlOutput The control output we want to serialize.
	 * @return A string containing all information about the control output.
	 */
	friend std::ostream & operator<<(std::ostream &os,
	const ControlOutput &controlOutput) {
		return os << "/InputValue=" << controlOutput.mOutputValue; /**!< The output value*/
	}

	/**
	 * Serializes the creature to an xml file.
	 * @param ar The archive.
	 * @param The file version.
	 */
	template<class Archive>
	void serialize(Archive & ar, const unsigned int /* file_version */) {
		ar
		& BOOST_SERIALIZATION_NVP(mOutputIndex) /**!< The index of the output in the output array*/
		& BOOST_SERIALIZATION_NVP(mOutputValue); /**!< The input value*/
	}

private:

	int mOutputIndex; /**!< The index of the output in the output array */
	double mOutputValue; /**!< The control output value */
};
BOOST_CLASS_VERSION(ControlOutput, 1)
BOOST_SERIALIZATION_ASSUME_ABSTRACT(ControlOutput)
#endif /* MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_CONTROLLER_CONTROLOUTPUT_HPP_ */
