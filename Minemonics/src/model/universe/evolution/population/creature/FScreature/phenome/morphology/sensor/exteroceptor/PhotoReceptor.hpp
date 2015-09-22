#ifndef MODEL_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_SENSORS_EXTEROCEPTOR_VISION_PHOTORECEPTOR_H_
#define MODEL_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_SENSORS_EXTEROCEPTOR_VISION_PHOTORECEPTOR_H_

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
//## view headers
//## utils headers

/**
 * @brief		A receptor for light.
 * @details		Details
 * @date		2014-12-02
 * @author		Benjamin Ellenberger
 */
class PhotoReceptor: public Sensor {
public:
	PhotoReceptor();
	virtual ~PhotoReceptor();
};

#endif /* MODEL_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_SENSORS_EXTEROCEPTOR_VISION_PHOTORECEPTOR_H_ */
