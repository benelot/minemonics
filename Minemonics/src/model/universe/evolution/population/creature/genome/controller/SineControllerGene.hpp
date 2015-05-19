#ifndef MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_GENOME_CONTROLLER_SINECONTROLLERGENE_HPP_
#define MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_GENOME_CONTROLLER_SINECONTROLLERGENE_HPP_

//# corresponding headers
#include <model/universe/evolution/population/creature/genome/controller/ControllerGene.hpp>

//# forward declarations
namespace boost {
namespace serialization {
class access;
} /* namespace serialization */
} /* namespace boost */

//# system headers
#include <iostream>

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
 * @brief		The sine controller gene holds the definition of a sine wave controller of a limb's joint.
 * @details		Details
 * @date		2015-03-09
 * @author		Benjamin Ellenberger
 */
class SineControllerGene: public ControllerGene {
public:
	SineControllerGene();
	virtual ~SineControllerGene();

	void initialize();

	virtual SineControllerGene* clone();

	bool equals(const SineControllerGene& sineControllerGene) const;

	/**
	 * Give access to boost serialization
	 */
	friend class boost::serialization::access;

	/**
	 * Serializes the sine controller gene to a string.
	 * @param os The ostream.
	 * @param sineControllerGene The sine controller gene we want to serialize.
	 * @return A string containing all information about the sine controller gene.
	 */
	friend std::ostream & operator<<(std::ostream &os,
			const SineControllerGene &sineControllerGene) {
		return os << "SineControllerGene: XOffset = "
				<< sineControllerGene.mXOffset << "/YOffset = "
				<< sineControllerGene.mYOffset << "/Amplitude="
				<< sineControllerGene.mAmplitude << "/Frequency="
				<< sineControllerGene.mFrequency;

	}

	/**
	 * Serializes the sine controller gene to an xml file.
	 * @param ar The archive.
	 * @param The file version.
	 */
	template<class Archive>
	void serialize(Archive & ar, const unsigned int /* file_version */) {
		ar
				& BOOST_SERIALIZATION_BASE_OBJECT_NVP(
						ControllerGene) & BOOST_SERIALIZATION_NVP(mXOffset) & BOOST_SERIALIZATION_NVP(mYOffset) & BOOST_SERIALIZATION_NVP(mAmplitude) & BOOST_SERIALIZATION_NVP(mFrequency);
	}

	double getAmplitude() const {
		return mAmplitude;
	}

	void setAmplitude(double amplitude) {
		mAmplitude = amplitude;
	}

	double getFrequency() const {
		return mFrequency;
	}

	void setFrequency(double frequency) {
		mFrequency = frequency;
	}

	double getXOffset() const {
		return mXOffset;
	}

	void setXOffset(double xOffset) {
		mXOffset = xOffset;
	}

	double getYOffset() const {
		return mYOffset;
	}

	void setYOffset(double yOffset) {
		mYOffset = yOffset;
	}

private:
	// The x offset of the sine wave
	double mXOffset;

	// The y offset of the sine wave
	double mYOffset;

	// The amplitude of the sine wave
	double mAmplitude;

	//The frequency of the sine wave
	double mFrequency;

};
BOOST_CLASS_VERSION(SineControllerGene, 1)

#endif /* MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_GENOME_CONTROLLER_SINECONTROLLERGENE_HPP_ */
