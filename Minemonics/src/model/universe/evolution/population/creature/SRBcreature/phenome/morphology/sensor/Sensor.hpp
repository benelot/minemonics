#ifndef MODEL_EVOLUTION_POPULATION_CREATURE_GENOME_SENSORS_SENSOR_H_
#define MODEL_EVOLUTION_POPULATION_CREATURE_GENOME_SENSORS_SENSOR_H_

//# corresponding header
#include <model/universe/evolution/population/creature/phenome/controller/ControlOutput.hpp>

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
 * @brief		A base class for all sensors.
 * @details		Details
 * @date		2015-03-09
 * @author		Benjamin Ellenberger
 */
class Sensor: public ControlOutput {
public:
	Sensor();
	~Sensor();

	/**
	 * Update the sensor values.
	 * @param timeSinceLastTick
	 */
	virtual void update(double timeSinceLastTick) = 0;

	// Accessor methods

	// Serialization
	/**
	 * Give access to boost serialization
	 */
	friend class boost::serialization::access;

	/**
	 * Serializes the sensor model to a string.
	 * @param os The ostream.
	 * @param sensor The sensor we want to serialize.
	 * @return A string containing all information about the sensor.
	 */
	friend std::ostream & operator<<(std::ostream &os, const Sensor &sensor) {
		return os;
	}

	/**
	 * Serializes the sensor to an xml file.
	 * @param ar The archive.
	 * @param The file version.
	 */
	template<class Archive>
	void serialize(Archive & ar, const unsigned int /* file_version */) {
	}
};
BOOST_CLASS_VERSION(Sensor, 1)
BOOST_SERIALIZATION_ASSUME_ABSTRACT(Sensor)
#endif /* MODEL_EVOLUTION_POPULATION_CREATURE_GENOME_SENSORS_SENSOR_H_ */
