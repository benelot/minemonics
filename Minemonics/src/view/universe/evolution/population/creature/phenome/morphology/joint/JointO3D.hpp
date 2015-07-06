#ifndef VIEW_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_JOINT_JOINTO3D_HPP_
#define VIEW_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_JOINT_JOINTO3D_HPP_

//# corresponding header
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
	JointO3D();
	JointO3D(const JointO3D& jointO3D);

	virtual ~JointO3D();

	void initialize();

	virtual JointO3D* clone();

	void update();

	void addToWorld();

	void removeFromWorld();

private:
	SimulationManager* mSimulationManager;

	Limb* mLimbA;

	Limb* mLimbB;

	btTransform mLocalA;

	btTransform mLocalB;
};

#endif /* VIEW_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_JOINT_JOINTO3D_HPP_ */
