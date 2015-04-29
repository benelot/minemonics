/*
 * JointGraphics.h
 *
 *  Created on: Apr 14, 2015
 *      Author: leviathan
 */

#ifndef VIEW_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_JOINT_JOINTGRAPHICS_H_
#define VIEW_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_JOINT_JOINTGRAPHICS_H_

//# corresponding header
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
 * @brief		Brief
 * @details		Details
 * @date		2015-04-27
 * @author		Benjamin Ellenberger
 */
class JointGraphics {
public:
	JointGraphics();
	virtual ~JointGraphics();

	virtual void addToWorld() = 0;

	virtual void removeFromWorld() = 0;

	virtual void update() = 0;
};

#endif /* VIEW_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_JOINT_JOINTGRAPHICS_H_ */
