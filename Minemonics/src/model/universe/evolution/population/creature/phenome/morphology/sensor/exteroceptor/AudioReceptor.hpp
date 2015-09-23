#ifndef MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_SENSOR_EXTEROCEPTOR_AUDITION_AUDIORECEPTOR_HPP_
#define MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_SENSOR_EXTEROCEPTOR_AUDITION_AUDIORECEPTOR_HPP_

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
 * @brief		A receptor for sound.
 * @details		Details
 * @date		2015-03-20
 * @author		Benjamin Ellenberger
 */
class AudioReceptor: public Sensor {
public:
	AudioReceptor();
	virtual ~AudioReceptor();
};

#endif /* MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_SENSOR_EXTEROCEPTOR_AUDITION_AUDIORECEPTOR_HPP_ */
