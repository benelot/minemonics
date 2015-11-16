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
	SineControllerGene(const SineControllerGene& gene);
	virtual ~SineControllerGene();

	/**
	 * Initialize the sine controller gene.
	 */
	void initialize();

	/**
	 * Clone the sine controller gene.
	 * @return The cloned sinecontroller.
	 */
	virtual SineControllerGene* clone();

	/**
	 * Compare the sine controller gene to another sine controller gene.
	 * @param sineControllerGene Another sine controller gene.
	 * @return If the sine controller gene is equal to the other controller gene.
	 */
	bool equals(const SineControllerGene& sineControllerGene) const;

	//Accessor methods

	double getAmplitude() const {
		return mAmplitude;
	}

	void setAmplitude(const double amplitude) {
		mAmplitude = amplitude;
	}

	double getFrequency() const {
		return mFrequency;
	}

	void setFrequency(const double frequency) {
		mFrequency = frequency;
	}

	double getXOffset() const {
		return mXOffset;
	}

	void setXOffset(const double xOffset) {
		mXOffset = xOffset;
	}

	double getYOffset() const {
		return mYOffset;
	}

	void setYOffset(const double yOffset) {
		mYOffset = yOffset;
	}

	//Serialization
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
		return os
		/**The type of controller*/
		<< "SineControllerGene: Controllertype="
				<< sineControllerGene.mControllerType

				/**The x offset of the sine wave of the controller*/
				<< "/XOffset=" << sineControllerGene.mXOffset

				/**The y offset of the sine wave of the controller*/
				<< "/YOffset=" << sineControllerGene.mYOffset

				/**The amplitude of the sine wave of the controller*/
				<< "/Amplitude=" << sineControllerGene.mAmplitude

				/**The frequency of the sine wave of the controller*/
				<< "/Frequency=" << sineControllerGene.mFrequency;

	}

	/**
	 * Serializes the sine controller gene to an xml file.
	 * @param ar The archive.
	 * @param The file version.
	 */
	template<class Archive>
	void serialize(Archive & ar, const unsigned int /* file_version */) {
		ar
		/** Serialize the base object */
		& BOOST_SERIALIZATION_BASE_OBJECT_NVP(ControllerGene)

		/**The x offset of the sine wave of the controller*/
		& BOOST_SERIALIZATION_NVP(mXOffset)

		/**The y offset of the sine wave of the controller*/
		& BOOST_SERIALIZATION_NVP(mYOffset)

		/**The amplitude of the sine wave of the controller*/
		& BOOST_SERIALIZATION_NVP(mAmplitude)

		/**The frequency of the sine wave of the controller*/
		& BOOST_SERIALIZATION_NVP(mFrequency);
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
