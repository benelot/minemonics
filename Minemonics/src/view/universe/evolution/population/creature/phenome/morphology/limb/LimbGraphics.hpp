#ifndef VIEW_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_LIMB_LIMBGRAPHICS_HPP_
#define VIEW_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_LIMB_LIMBGRAPHICS_HPP_

//# corresponding header
//# forward declarations
class LimbModel;

//# system headers
//## controller headers
//## model headers
#include <OgreVector3.h>
#include <OgreQuaternion.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers

/**
 * @brief		The generic graphical representation of a limb.
 * @details		Details
 * @date		2015-03-24
 * @author		Benjamin Ellenberger
 */
class LimbGraphics {
public:
	LimbGraphics(const LimbModel* const limbModel);
	virtual ~LimbGraphics();

	/**
	 * Add the limb to the graphical world.
	 */
	virtual void addToWorld() = 0;

	/**
	 * Remove the limb from the graphical world.
	 */
	virtual void removeFromWorld() = 0;

	/**
	 * Update the graphical representation of the limb with the physical representation.
	 */
	virtual void update(double timeSinceLastTick) = 0;

	/**
	 * Clone the limb graphics.
	 * @return The clone of the limb graphics.
	 */
	virtual LimbGraphics* clone() = 0;

	// Accessor methods ##########################

	bool isInWorld() const {
		return mInWorld;
	}

protected:

	void setInWorld(bool mInWorld) {
		this->mInWorld = mInWorld;
	}

protected:

	const LimbModel* mLimbModel; /**!< The limb model to get the information to render. */

	bool mInWorld; /**!< Whether the limb is in the world or not. */
};

#endif /* VIEW_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_LIMB_LIMBGRAPHICS_HPP_ */
