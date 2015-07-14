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

	/**
	 * Clone the joint graphics.
	 * @return
	 */
	virtual JointGraphics* clone() = 0;

	/**
	 * Add the joint to the world.
	 */
	virtual void addToWorld() = 0;

	/**
	 * Remove the joint from the world.
	 */
	virtual void removeFromWorld() = 0;

	/**
	 * Update the joint.
	 */
	virtual void update() = 0;
};

#endif /* VIEW_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_JOINT_JOINTGRAPHICS_HPP_ */
