#ifndef MODEL_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_SENSORS_EXTEROCEPTOR_TACTIOCEPTOR_H_
#define MODEL_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_SENSORS_EXTEROCEPTOR_TACTIOCEPTOR_H_

//# corresponding header
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

private:
	bool mTouched;
};

#endif /* MODEL_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_SENSORS_EXTEROCEPTOR_ */
