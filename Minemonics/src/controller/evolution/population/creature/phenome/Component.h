/*
 * Component.h
 *
 *  Created on: Mar 23, 2015
 *      Author: leviathan
 */

#ifndef MODEL_EVOLUTION_POPULATION_CREATURE_PHENOME_COMPONENT_H_
#define MODEL_EVOLUTION_POPULATION_CREATURE_PHENOME_COMPONENT_H_

class Component {
public:
	Component();
	virtual ~Component();

	enum ComponentType{
		UnknownComponent,
		Limb
	};

	void initialize(ComponentType componentType);
private:
	ComponentType mComponentType;
};

#endif /* MODEL_EVOLUTION_POPULATION_CREATURE_PHENOME_COMPONENT_H_ */
