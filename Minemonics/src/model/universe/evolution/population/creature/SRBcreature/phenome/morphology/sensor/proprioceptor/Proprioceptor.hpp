#ifndef MODEL_EVOLUTION_POPULATION_CREATURE_GENOME_SENSORS_PROPRIOCEPTOR_H_
#define MODEL_EVOLUTION_POPULATION_CREATURE_GENOME_SENSORS_PROPRIOCEPTOR_H_

//# corresponding header
#include <model/universe/evolution/population/creature/phenome/morphology/joint/SRBJointBt.hpp>
#include <model/universe/evolution/population/creature/SRBcreature/phenome/morphology/sensor/Sensor.hpp>

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
 * @brief		A base receptor for the internal movement of the limbs.
 * @details		Details
 * @date		2015-03-09
 * @author		Benjamin Ellenberger
 */
class Proprioceptor: public Sensor {
public:
	Proprioceptor();
	~Proprioceptor();

	/**
	 * Update the proprioceptor input.
	 * @param timeSinceLastTick
	 */
	virtual void update(double timeSinceLastTick) = 0;

	// Accessor methods

	//Serialization
	/**
	 * Give access to boost serialization
	 */
	friend class boost::serialization::access;

	/**
	 * Serializes the proprioceptor to a string.
	 * @param os The ostream.
	 * @param proprioceptor The proprioceptor we want to serialize.
	 * @return A string containing all information about the proprioceptor.
	 */
	friend std::ostream & operator<<(std::ostream &os,
		const Proprioceptor &proprioceptor) {
		return os;
	}

	/**
	 * Serializes the proprioceptor to an xml file.
	 * @param ar The archive.
	 * @param The file version.
	 */
	template<class Archive>
	void serialize(Archive & ar, const unsigned int /* file_version */) {
	}
};
BOOST_CLASS_VERSION(Proprioceptor, 1)
BOOST_SERIALIZATION_ASSUME_ABSTRACT(Proprioceptor)
#endif /* MODEL_EVOLUTION_POPULATION_CREATURE_GENOME_SENSORS_PROPRIOCEPTOR_H_ */
