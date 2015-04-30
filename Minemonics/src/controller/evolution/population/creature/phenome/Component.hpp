/*
 * Component.h
 *
 *  Created on: Mar 23, 2015
 *      Author: leviathan
 */

#ifndef MODEL_EVOLUTION_POPULATION_CREATURE_PHENOME_COMPONENT_H_
#define MODEL_EVOLUTION_POPULATION_CREATURE_PHENOME_COMPONENT_H_

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
class Component {
public:
	Component();
	virtual ~Component();

	enum ComponentType {
		UnknownComponent, LimbComponent, JointComponent
	};

	void initialize(ComponentType componentType);
private:
	ComponentType mComponentType;
};

#endif /* MODEL_EVOLUTION_POPULATION_CREATURE_PHENOME_COMPONENT_H_ */
