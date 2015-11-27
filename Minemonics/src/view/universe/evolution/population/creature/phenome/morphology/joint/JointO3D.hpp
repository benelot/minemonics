#ifndef VIEW_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_JOINT_JOINTO3D_HPP_
#define VIEW_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_JOINT_JOINTO3D_HPP_

//# corresponding header
#include <configuration/Definitions.hpp>
#include <view/universe/evolution/population/creature/phenome/morphology/joint/JointGraphics.hpp>

//# forward declarations
class SimulationManager;

//# system headers
//## controller headers
//## model headers
#include <bullet/LinearMath/btTransform.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
#include <controller/universe/evolution/population/creature/phenome/morphology/Limb.hpp>

//## view headers
//## utils headers

/**
 * @brief		The graphical representation of the joint in Ogre3D.
 * @details		Details
 * @date		2015-04-14
 * @author		Benjamin Ellenberger
 */
class JointO3D: public JointGraphics {
public:
	JointO3D(const JointModel* const jointModel);
	JointO3D(const JointO3D& jointO3D);

	virtual ~JointO3D();

	/**
	 * Initialize the Joint O3D.
	 */
	void initialize();

	/**
	 * Clone the joint O3D.
	 * @return The clone of the joint O3D.
	 */
	virtual JointO3D* clone();

	/**
	 * Update the joint graphical representation.
	 */
	void update(double timeSinceLastTick);

	/**
	 * Add the joint to the world.
	 */
	void addToWorld();

	/**
	 * Remove the joint from the world.
	 */
	void removeFromWorld();

private:
	Limb* mLimbA; /**!< The limb A */

	Limb* mLimbB; /**!< The limb B */

	btTransform mLocalA; /**!< The transform to A */

	btTransform mLocalB; /**!< The transform to B */
};

#endif /* VIEW_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_JOINT_JOINTO3D_HPP_ */
