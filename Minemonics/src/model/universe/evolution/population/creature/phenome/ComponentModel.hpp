/*
 * ComponentModel.hpp
 *
 *  Created on: May 9, 2015
 *      Author: leviathan
 */

#ifndef MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_COMPONENTMODEL_HPP_
#define MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_COMPONENTMODEL_HPP_

//# corresponding headers
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
 * @brief		The component model holds all the state information of the component independent of other models.
 * @details		Details
 * @date		2015-04-29
 * @author		Benjamin Ellenberger
 */
class ComponentModel {
public:
	enum ComponentType {
		UnknownComponent, LimbComponent, JointComponent,NUM_COMPONENTS
	};


	ComponentModel();
	virtual ~ComponentModel();

	void initialize(ComponentType type);

	ComponentType getComponentType() const {
		return mComponentType;
	}

private:
	/**
	 * Component type of the compoment.
	 */
	ComponentType mComponentType;
};

#endif /* MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_COMPONENTMODEL_HPP_ */
