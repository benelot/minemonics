#ifndef MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_CONTROLLER_CONTROLINPUT_HPP_
#define MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_CONTROLLER_CONTROLINPUT_HPP_

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
//## view headers
//## utils headers

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

	/**
	 * Compare the control input to another control input.
	 * @param controlInput Another control input.
	 * @return If the control input is equal to the other control input.
	 */
	bool equals(const ControlInput &controlInput) const;

	//Serialization

	/**
	 * Give access to boost serialization
	 */
	friend class boost::serialization::access;

	/**
	 * Serializes the control input to a string.
	 * @param os The ostream.
	 * @param controlInput The control input we want to serialize.
	 * @return A string containing all information about the control input.
	 */
	friend std::ostream & operator<<(std::ostream &os,
			const ControlInput &controlInput) {
		return os
		/**If the control input has new input*/
		<< "ControlInput: ReceivedInput=" << controlInput.mReceivedInput

		/**The input value*/
		<< "/InputValue=" << controlInput.mValue;
	}

	/**
	 * Serializes the creature to an xml file.
	 * @param ar The archive.
	 * @param The file version.
	 */
	template<class Archive>
	void serialize(Archive & ar, const unsigned int /* file_version */) {
		ar
		/**If the control input has new input*/
		& BOOST_SERIALIZATION_NVP(mReceivedInput)

		/**The input value*/
		& BOOST_SERIALIZATION_NVP(mValue);
	}

	//Accessor methods

	double getValue() {
		mReceivedInput = false;
		return mValue;
	}

	void setValue(const double value) {
		mReceivedInput = true;
		mValue = value;
	}

	bool isReceivedInput() const {
		return mReceivedInput;
	}

private:
	/**
	 * If it received input.
	 */
	bool mReceivedInput;

	/**
	 * The input that was received.
	 */
	double mValue;
};
BOOST_CLASS_VERSION(ControlInput, 1)
BOOST_SERIALIZATION_ASSUME_ABSTRACT(ControlInput)

#endif /* MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_CONTROLLER_CONTROLINPUT_HPP_ */
