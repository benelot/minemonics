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
#include <boost/archive/tmpdir.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
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
	ChaoticControllerGene(ChaoticSystemType systemType, double initialX,
		double initialY, double initialZ, double speed);
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

	double getInitialX() const {
		return mInitialX;
	}

	double getInitialY() const {
		return mInitialY;
	}

	double getInitialZ() const {
		return mInitialZ;
	}

	double getSpeed() const {
		return mSpeed;
	}

	void setInitialX(double initialX) {
		mInitialX = initialX;
	}

	void setInitialY(double initialY) {
		mInitialY = initialY;
	}

	void setInitialZ(double initialZ) {
		mInitialZ = initialZ;
	}

	void setSpeed(double speed) {
		mSpeed = speed;
	}

	void setSystemType(ChaoticSystemType systemType) {
		mSystemType = systemType;
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
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(ControllerGene) /**!< The base class of the chaotic controller */
		& BOOST_SERIALIZATION_NVP(mSystemType) /**!< The chaotic system type*/
		& BOOST_SERIALIZATION_NVP(mInitialX) /**!< The initial conditions of the chaotic system */
		& BOOST_SERIALIZATION_NVP(mInitialY)/**!< The initial conditions of the chaotic system */
		& BOOST_SERIALIZATION_NVP(mInitialZ) /**!< The initial conditions of the chaotic system */
		& BOOST_SERIALIZATION_NVP(mSpeed); /**!< The speed of the change in the chaotic controller */
	}

private:
	ChaoticSystemType mSystemType; /**!< The chaotic system type*/
	double mInitialX, mInitialY, mInitialZ; /**!< The initial conditions of the chaotic system */
	double mSpeed; /**!< The integration speed */
};
BOOST_CLASS_VERSION(ChaoticControllerGene, 1)
#endif /* MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_GENOME_CONTROLLER_CHAOTICCONTROLLERGENE_HPP_ */
