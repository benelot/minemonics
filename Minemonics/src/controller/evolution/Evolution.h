#ifndef CONTROLLER_EVOLUTION_EVOLUTION_H_
#define CONTROLLER_EVOLUTION_EVOLUTION_H_



//# forward declarations
//# system headers
//## controller headers
//## model headers
//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
#include <controller/environments/Environment.h>
#include <controller/evolution/population/creature/Creature.h>

//## model headers
#include <model/evolution/EvolutionM.h>

//## view headers
//## utils headers
/**
 * @brief		Brief
 * @details		Details
 * @date		2015-04-28
 * @author		Benjamin Ellenberger
 */
class Evolution {
public:
	Evolution();
	virtual ~Evolution();

	void initialize();


	Environment* getEnvironment() {
		return mEnvironment;
	}

	void setEnvironment(Environment*& environment) {
		mEnvironment = environment;
	}

private:

	EvolutionM mEvolutionM;

	Creature* mCurrentCreature;

	Environment* mEnvironment;
};

#endif /* CONTROLLER_EVOLUTION_EVOLUTION_H_ */
