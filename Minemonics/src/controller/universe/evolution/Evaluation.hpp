#ifndef CONTROLLER_UNIVERSE_EVOLUTION_EVALUATION_HPP_
#define CONTROLLER_UNIVERSE_EVOLUTION_EVALUATION_HPP_

#include <model/universe/evolution/EvaluationModel.hpp>



/**
 * @brief		Brief
 * @details		 Details
 * @date		2015-06-01
 * @author		Benjamin Ellenberger
 */
class Evaluation {
public:
	Evaluation();
	virtual ~Evaluation();

private:
	EvaluationModel mEvaluationModel;
};

#endif /* CONTROLLER_UNIVERSE_EVOLUTION_EVALUATION_HPP_ */
