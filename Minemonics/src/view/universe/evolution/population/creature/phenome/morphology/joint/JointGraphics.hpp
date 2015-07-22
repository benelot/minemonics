#ifndef VIEW_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_JOINT_JOINTGRAPHICS_HPP_
#define VIEW_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_JOINT_JOINTGRAPHICS_HPP_

//# corresponding header
//# forward declarations
class JointModel;
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
	JointGraphics(const JointModel* const jointModel);
	virtual ~JointGraphics();

	/**
	 * Clone the joint graphics.
	 * @return
	 */
	virtual JointGraphics* clone() = 0;

	/**
	 * Check if the joint graphics is in the world.
	 */
	virtual bool isInWorld(){
		return mInWorld;
	}

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

protected:
	/**
	 * A const handle to the joint model to render.
	 */
	const JointModel* mJointModel;

	bool mInWorld;
};

#endif /* VIEW_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_JOINT_JOINTGRAPHICS_HPP_ */
