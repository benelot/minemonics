#ifndef MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_GENOME_CONTROLLER_CHAOTICCONTROLLERGENE_HPP_
#define MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_GENOME_CONTROLLER_CHAOTICCONTROLLERGENE_HPP_

//# corresponding headers
#include <model/universe/evolution/population/creature/genome/controller/ControllerGene.hpp>

//# forward declarations
namespace boost {
namespace serialization {
class access;
} /* namespace serialization */
} /* namespace boost */

//# system headers
//## controller headers
//## model headers
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/version.hpp>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers

/**
 * @brief		The chaotic controller gene keeps the parameters for the chaotic controller.
 * @details		Details
 * @date		2015-10-30
 * @author		Benjamin Ellenberger
 */
class ChaoticControllerGene: public ControllerGene {
public:
	enum ChaoticSystemType {
		CHUA_CIRCUIT
	};

	ChaoticControllerGene();
	ChaoticControllerGene(ChaoticSystemType systemType);
	ChaoticControllerGene(const ChaoticControllerGene& gene);
	virtual ~ChaoticControllerGene();

	virtual void initialize();

	/**
	 * Clone the chaotic controller gene.
	 * @return The cloned chaotic controller.
	 */
	virtual ChaoticControllerGene* clone();

	ChaoticSystemType getSystemType() const {
		return mSystemType;
	}

	// Serialization ##########################
	/**
	 * Give access to boost serialization
	 */
	friend class boost::serialization::access;

	/**
	 * Serializes the chaotic controller gene to a string.
	 * @param os The ostream.
	 * @param chaoticControllerGene The chaotic controller gene we want to serialize.
	 * @return A string containing all information about the chaotic controller gene.
	 */
	friend std::ostream & operator<<(std::ostream &os,
		const ChaoticControllerGene &chaoticControllerGene) {
		return os;

	}

	/**
	 * Serializes the chaotic controller gene to an xml file.
	 * @param ar The archive.
	 * @param The file version.
	 */
	template<class Archive>
	void serialize(Archive & ar, const unsigned int /* file_version */) {
		ar
		/** Serialize the base object */
		& BOOST_SERIALIZATION_BASE_OBJECT_NVP(ControllerGene);
	}

private:
	ChaoticSystemType mSystemType;
};
BOOST_CLASS_VERSION(ChaoticControllerGene, 1)
#endif /* MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_GENOME_CONTROLLER_CHAOTICCONTROLLERGENE_HPP_ */
