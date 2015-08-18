#ifndef MODEL_EVOLUTION_POPULATION_CREATURE_GENOME_SENSORS_PROPRIOCEPTOR_H_
#define MODEL_EVOLUTION_POPULATION_CREATURE_GENOME_SENSORS_PROPRIOCEPTOR_H_

//# corresponding header
#include <model/universe/evolution/population/creature/phenome/morphology/sensor/Sensor.hpp>

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
#include <model/universe/evolution/population/creature/phenome/morphology/joint/JointBt.hpp>

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

	virtual void update(double timeSinceLastTick) = 0;
};

#endif /* MODEL_EVOLUTION_POPULATION_CREATURE_GENOME_SENSORS_PROPRIOCEPTOR_H_ */
