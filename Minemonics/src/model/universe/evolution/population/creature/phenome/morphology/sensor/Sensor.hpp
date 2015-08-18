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

	virtual void update(double timeSinceLastTick) = 0;
};

#endif /* MODEL_EVOLUTION_POPULATION_CREATURE_GENOME_SENSORS_SENSOR_H_ */
