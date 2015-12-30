#ifndef VIEW_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_LIMB_LIMBO3D_H_
#define VIEW_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_LIMB_LIMBO3D_H_

//# corresponding headers
#include <view/universe/evolution/population/creature/phenome/morphology/limb/LimbGraphics.hpp>
#include <configuration/Definitions.hpp>

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
#include <utils/logging/Logger.hpp>

/**
 * @brief		The graphical representation of the limb in Ogre3D.
 * @details		Details
 * @date		2014-12-19
 * @author		Benjamin Ellenberger
 */
class LimbO3D: public LimbGraphics {
public:
	LimbO3D(const LimbModel* const limbModel);
	LimbO3D(const LimbO3D& limbO3D);

	virtual ~LimbO3D();

	/**
	 * Clone the limbO3D
	 * @return The clone of the limbO3D.
	 */
	virtual LimbO3D* clone();

	/**
	 * Update the graphical representation of the limb with the physical representation.
	 */
	virtual void update(double timeSinceLastTick);

	/**
	 * Add the limb to the graphical world.
	 */
	void addToWorld();

	/**
	 * Add the limb to the graphical world.
	 */
	void removeFromWorld();

	// Accessor methods ##########################

	Ogre::Entity*& getEntity() {
		return mLimbEntity;
	}

	Ogre::SceneNode*& getEntityNode() {
		return mLimbEntityNode;
	}

private:

	static BoostLogger mBoostLogger; /**!< The boost logger. */

	/**
	 * Initializer of the boost logger to include the class name into the logging messages.
	 */
	static class _Init {
	public:
		_Init() {
			mBoostLogger.add_attribute("ClassName",
				boost::log::attributes::constant < std::string > ("LimbO3D"));
		}
	} _initializer;

	Ogre::Entity* mLimbEntity; /**!< The limb object in the graphical world. */
	Ogre::MeshPtr mMesh; /**!< In case it uses a custom mesh */
	Ogre::SceneNode* mLimbEntityNode; /**!< The entity node of the limb to perform rotations and translations with. */

};

#endif /* LIMBO3D_H_ */
