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
 * @brief		The controller output abstract class holds the output of the previous controller or sensor for the next computation.
 * @details		Details
 * @date		2015-04-30
 * @author		Benjamin Ellenberger
 */
class ControlOutput {
public:
	ControlOutput();
	virtual ~ControlOutput();

	/**
	 * Compare the control output to another control output.
	 * @param controlOutput Another control output.
	 * @return If the control output is equal to the other control output.
	 */
	bool equals(const ControlOutput &controlOutput) const;

	//Serialization

	/**
	 * Give access to boost serialization
	 */
	friend class boost::serialization::access;

	/**
	 * Serializes the control output to a string.
	 * @param os The ostream.
	 * @param controlOutput The control output we want to serialize.
	 * @return A string containing all information about the control output.
	 */
	friend std::ostream & operator<<(std::ostream &os,
			const ControlOutput &controlOutput) {
		return os
		/**The output value*/
		<< "/InputValue=" << controlOutput.mValue;
	}

	/**
	 * Serializes the creature to an xml file.
	 * @param ar The archive.
	 * @param The file version.
	 */
	template<class Archive>
	void serialize(Archive & ar, const unsigned int /* file_version */) {
		ar
		/**The input value*/
		& BOOST_SERIALIZATION_NVP(mValue);
	}

	//Accessor methods

	double getValue() const {
		return mValue;
	}

	void setvalue(const double value) {
		mValue = value;
	}

private:
	/**
	 * The control output value
	 */
	double mValue;
};
BOOST_CLASS_VERSION(ControlOutput, 1)
BOOST_SERIALIZATION_ASSUME_ABSTRACT(ControlOutput)
#endif /* MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_CONTROLLER_CONTROLOUTPUT_HPP_ */
