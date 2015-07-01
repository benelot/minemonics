#ifndef VIEW_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_JOINT_JOINTGRAPHICS_HPP_
#define VIEW_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_JOINT_JOINTGRAPHICS_HPP_

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
 * @brief		The generic graphical representation of the joint.
 * @details		Details
 * @date		2015-04-14
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

#endif /* VIEW_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_JOINT_JOINTGRAPHICS_HPP_ */
