#ifndef CREATUREO3D_H_
#define CREATUREO3D_H_

//# corresponding header
//# forward declarations
//# system headers
//## controller headers
#include <controller/evolution/population/creature/Creature.h>

//## model headers
//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers

/**
 * @brief		The Ogre3D graphical representation of the creature.
 * It is kept in sync with the physical model in the bullet engine.
 * @details		Details
 * @date		2014-12-02
 * @author		Benjamin Ellenberger
 */
class CreatureO3D: public Creature {
public:
	CreatureO3D();
	virtual ~CreatureO3D();
};

#endif /* CREATUREO3D_H_ */
