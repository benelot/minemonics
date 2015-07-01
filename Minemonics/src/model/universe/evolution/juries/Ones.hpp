#ifndef MODEL_UNIVERSE_EVOLUTION_JURIES_ONES_H_
#define MODEL_UNIVERSE_EVOLUTION_JURIES_ONES_H_

//# corresponding header
#include <model/universe/evolution/juries/Jury.hpp>
#include <vector>

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
 * @brief		The ones jury is for illustration purposes of a jury.
 * @details		Details
 * @date		2015-02-25
 * @author		Benjamin Ellenberger
 */
class Ones: public Jury {
public:
	Ones(double weight);
	virtual ~Ones();

	void setEvaluationSubject(const std::vector< bool >& x);
	void evaluateFitness();
private:
	std::vector< bool > mEvaluationSubject;
};

#endif /* MODEL_UNIVERSE_EVOLUTION_JURIES_ONES_H_ */
