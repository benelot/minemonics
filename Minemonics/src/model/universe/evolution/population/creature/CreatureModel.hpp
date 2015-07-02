#ifndef MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_CREATUREM_H_
#define MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_CREATUREM_H_

//# corresponding header
//# forward declarations
class PopulationModel;
namespace boost {
namespace serialization {
class access;
} /* namespace serialization */
} /* namespace boost */

//# system headers
#include <fstream>
#include <iterator>
#include <string>
#include <vector>

//## controller headers
//## model headers
// include headers that implement a archive in xmlformat
#include <boost/archive/tmpdir.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/math/special_functions/cbrt.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/version.hpp>
#include <OgreVector3.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
#include <model/universe/PlanetModel.hpp>
#include <model/universe/evolution/juries/Jury.hpp>
#include <model/universe/evolution/population/creature/genome/morphology/Morphogene.hpp>
#include <model/universe/evolution/population/creature/genome/MixedGenome.hpp>
#include <model/universe/evolution/population/creature/phenome/PhenomeModel.hpp>

//## view headers
//## utils headers

/**
 * @brief		The model of the creature holds the important information about the creature.
 * @details		Details
 * @date		2014-12-02
 * @author		Benjamin Ellenberger
 */
class CreatureModel {
public:
	CreatureModel();
	virtual ~CreatureModel();

	/**
	 * Initializes a creature with random values for its genome, name, total segments quantity and segments path limit.
	 * @param branchiness The branchiness parameter defining whether the creature branches into many limbs.
	 */
	void initialize(PopulationModel* populationModel,
			PhenomeModel* phenomeModel, Ogre::Vector3 position,
			double branchiness);

	/**
	 * Reset the creature to the way it was born.
	 */
	void reset(Ogre::Vector3 position);

	/**
	 * Reposition the creature without resetting it.
	 */
	void reposition(Ogre::Vector3 position);

	/**
	 * Evaluate the creature model.
	 */
	void evaluate();

	/**
	 * Provides a creature size to scale certain values in compensation for the overall size
	 * of a creature's body. We do this by summing all creature volumes of all cuboids and
	 * then we take the cube square of it (size(C) = sqrt^3{\sum\limits^{N(C)}_{i=1} v(c_i)}).
	 * @return The size of a creature.
	 */
	double getCreatureSize() {
		return boost::math::cbrt(getCreatureVolume());
	}

	/**
	 * Provides the total volume of the whole creature body.
	 * @return The total volume of the whole creature body.
	 */
	double getCreatureVolume() {
		std::vector<Gene*>::const_iterator it;
		double totalVolume = 0;
		for (it = mGenotype.getGenes().begin();
				it != mGenotype.getGenes().end(); it++) {
			if ((*it)->getType() == Gene::MorphoGene) {
				totalVolume += ((Morphogene*) *it)->getX()
						* ((Morphogene*) *it)->getY()
						* ((Morphogene*) *it)->getZ();
			}
		}
		return totalVolume;
	}

	/**
	 * Compare the creature model to another creature model.
	 * @param creature Another creature model.
	 * @return If the creature model is equal to the other creature model.
	 */
	bool equals(const CreatureModel & creature) const;

	/**
	 * Give access to boost serialization
	 */
	friend class boost::serialization::access;

	/**
	 * Serializes the creature model to a string.
	 * @param os The ostream.
	 * @param creature The creature we want to serialize.
	 * @return A string containing all information about the creature.
	 */
	friend std::ostream & operator<<(std::ostream &os,
			const CreatureModel &creature) {
		os
		/**The name of the creature*/
		<< "CreatureModel: Name=" << creature.mFirstName

		/**If the creature is developed*/
		<< "/isDeveloped=" << creature.mDeveloped

		/**The genome of the creature*/
		<< "/Genotype=" << creature.mGenotype;

		/**The juries of the creature model*/
		std::vector<Jury*>::const_iterator it;
		for (it = creature.mJuries.begin(); it != creature.mJuries.end();
				it++) {
			os << (**it);
			os << "||";
		}

		/**The position of the creature model*/
		return os << "/Position=(" << creature.mPosition.x << ","
				<< creature.mPosition.y << "," << creature.mPosition.z << ")";
	}

	/**
	 * Serializes the creature to an xml file.
	 * @param ar The archive.
	 * @param The file version.
	 */
	template<class Archive>
	void serialize(Archive & ar, const unsigned int /* file_version */) {
		ar
		/**The name of the creature*/
		& BOOST_SERIALIZATION_NVP(mFirstName)

		/**if the creature is developed already*/
		& BOOST_SERIALIZATION_NVP(
				mDeveloped)

		/**The genome of the creature model*/
		& BOOST_SERIALIZATION_NVP(mGenotype)

		/**The juries of the creature model*/
		& BOOST_SERIALIZATION_NVP(mJuries)

		/**The position of the creature model*/
		& BOOST_SERIALIZATION_NVP(mPosition.x)
		& BOOST_SERIALIZATION_NVP(mPosition.y)
		& BOOST_SERIALIZATION_NVP(mPosition.z);
	}

	//Accessor methods
	MixedGenome& getGenotype() {
		return mGenotype;
	}

	bool isDeveloped() const {
		return mDeveloped;
	}

	void setDeveloped(bool developed) {
		mDeveloped = developed;
	}

	const std::vector<Jury*>& getJuries() const {
		return mJuries;
	}

	const std::string& getFirstName() const {
		return mFirstName;
	}

	const Ogre::Vector3& getPosition() const {
		return mPosition;
	}

	void setPosition(const Ogre::Vector3& position) {
		mPosition = position;
	}

	PopulationModel* getPopulationModel() {
		return mPopulationModel;
	}

	void setPhenotypeModel(PhenomeModel* phenotypeModel) {
		mPhenotypeModel = phenotypeModel;
	}

	const Ogre::Vector3& getInitialPosition() const {
		return mInitialPosition;
	}

private:

	/**
	 * The name of the creature.
	 */
	std::string mFirstName;

	/**
	 * The genotype (genomic individual) of the creature.
	 */
	MixedGenome mGenotype;

	/**
	 * Is the phenotype developed?
	 */
	bool mDeveloped;

	/**
	 * The phenotype (morphological individual) of the creature.
	 */
	PhenomeModel* mPhenotypeModel;

	/**
	 * The juries that rate the creature according to their fitness function.
	 */
	std::vector<Jury*> mJuries;

	/**
	 * The position of the creature.
	 */
	Ogre::Vector3 mPosition;

	/**
	 * The initial position of the creature.
	 */
	Ogre::Vector3 mInitialPosition;

	/**
	 * The population the creature lives in.
	 */
	PopulationModel* mPopulationModel;

};
BOOST_CLASS_VERSION(CreatureModel, 1)

#endif /* MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_CREATUREM_H_ */
