#ifndef MODEL_UNIVERSE_EVOLUTION_JURIES_JURYFACTORY_HPP_
#define MODEL_UNIVERSE_EVOLUTION_JURIES_JURYFACTORY_HPP_

//# corresponding headers
//# forward declarations
//# system headers
//## controller headers
//## model headers
#include <model/universe/evolution/juries/AverageHeight.hpp>
#include <model/universe/evolution/juries/IntegralAverageVelocity.hpp>
#include <model/universe/evolution/juries/Jury.hpp>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers

/**
 * @brief		The jury factory builds juries for everyone.
 * @details		Details
 * @date		2015-08-08
 * @author		Benjamin Ellenberger
 */
class JuryFactory {
public:
	static Jury* buildJury(Jury::JuryType type, bool higherIsBetter,
		double weight) {
		Jury* jury;

		switch (type) {
		case Jury::AVG_VELOCITY:
			jury = new AverageVelocity(higherIsBetter, weight);
			break;
		case Jury::AVG_HEIGHT:
			jury = new AverageHeight(higherIsBetter, weight);
		}

		return jury;
	}
};

#endif /* MODEL_UNIVERSE_EVOLUTION_JURIES_JURYFACTORY_HPP_ */
