#ifndef MODEL_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_SENSORS_EXTEROCEPTOR_TACTIOCEPTOR_H_
#define MODEL_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_SENSORS_EXTEROCEPTOR_TACTIOCEPTOR_H_

//# corresponding header
#include <model/universe/evolution/population/creature/phenome/morphology/sensor/Sensor.hpp>

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
#include <model/universe/evolution/population/creature/phenome/controller/ControlOutput.hpp>

//## view headers
//## utils headers

/**
 * @brief		A receptor for touch.
 * @details		Details
 * @date		2015-03-09
 * @author		Benjamin Ellenberger
 */
class Tactioceptor: public Sensor {
public:
	Tactioceptor();
	virtual ~Tactioceptor();

	virtual void update(double timeSinceLastTick);

	//Accessor methods
	bool isTouched() const {
		return mTouched;
	}

	void setTouched(bool touched) {
		mTouched = touched;
		setOutputValue(mTouched);
	}

	//Serialization
	friend class boost::serialization::access; /**!< Give access to boost serialization */

	/**
	 * Serializes the tactioceptor to a string.
	 * @param os The ostream.
	 * @param tactioceptor The tactioceptor we want to serialize.
	 * @return A string containing all information about the tactioceptor.
	 */
	friend std::ostream & operator<<(std::ostream &os,
	const Tactioceptor &tactioceptor) {
		os << "Tactioceptor";
		return os;
	}

	/**
	 * Serializes the tactioceptor to an xml file.
	 * @param ar The archive.
	 * @param The file version.
	 */
	template<class Archive>
	void serialize(Archive & ar, const unsigned int /* file_version */) {
	}

private:
	bool mTouched;
};

#endif /* MODEL_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_SENSORS_EXTEROCEPTOR_ */
