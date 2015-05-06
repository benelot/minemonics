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
 * @brief		The component is a base class for all elements in the phenome representation.
 * @details		Details
 * @date		2015-03-23
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
