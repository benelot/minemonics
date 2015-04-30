/*
 * LimbModel.h
 *
 *  Created on: Apr 29, 2015
 *      Author: leviathan
 */

#ifndef MODEL_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_LIMB_LIMBMODEL_HPP_
#define MODEL_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_LIMB_LIMBMODEL_HPP_

#include <LinearMath/btQuaternion.h>
#include <LinearMath/btVector3.h>
#include <model/evolution/population/creature/phenome/morphology/limb/LimbPhysics.hpp>



/**
 *@brief The limb model holds all the information of the limb state.
 *@details
 *@date 2015-04-29
 *@author Benjamin Ellenberger
 */
class LimbModel {
public:
	LimbModel();
	virtual ~LimbModel();

	//Accessor methods
	/**
	 * The the limb physics model of the limb.
	 * @return The limb physics model of the limb.
	 */
	const LimbPhysics*& getLimbPhysics() const {
		return mLimbPhysics;
	}

	/**
	 * Get the position of the limb in the physical world.
	 * @return The position of the limb in the physical world.
	 */
	btVector3 getPosition(){
		return mLimbPhysics->getPosition();
	}

	/**
	 * Get the orientation of the limb in the physical world.
	 * @return The orientation of the limb in the physical world.
	 */
	btQuaternion getOrientation(){
		return mLimbPhysics->getOrientation();
	}

private:
	LimbPhysics* mLimbPhysics;
};

#endif /* MODEL_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_LIMB_LIMBMODEL_HPP_ */
