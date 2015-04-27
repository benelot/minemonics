/*
 * SineControllerGene.h
 *
 *  Created on: Mar 9, 2015
 *      Author: leviathan
 */

#ifndef MODEL_EVOLUTION_POPULATION_CREATURE_GENOME_CONTROLLER_SINECONTROLLERGENE_H_
#define MODEL_EVOLUTION_POPULATION_CREATURE_GENOME_CONTROLLER_SINECONTROLLERGENE_H_

//# corresponding header
#include "model/evolution/population/creature/genome/controller/ControllerGene.h"

//# forward declarations
//# system headers
//## controller headers
//## model headers
// include headers that implement a archive in xml format
#include <boost/archive/tmpdir.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/base_object.hpp>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers

/**
 * @brief		Brief
 * @details		Details
 * @date		2015-04-27
 * @author		Benjamin Ellenberger
 */
class SineControllerGene: public ControllerGene {
public:
	SineControllerGene();
	virtual ~SineControllerGene();

	void initialize();

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
		return os << "SineControllerGene: InitialValue = "
				<< sineControllerGene.mInitialValue << "/Amplitude="
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
				& BOOST_SERIALIZATION_BASE_OBJECT_NVP(ControllerGene)
						& BOOST_SERIALIZATION_NVP(mInitialValue) & BOOST_SERIALIZATION_NVP(mAmplitude) & BOOST_SERIALIZATION_NVP(mFrequency);
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

	double getInitialValue() const {
		return mInitialValue;
	}

	void setInitialValue(double initialValue) {
		mInitialValue = initialValue;
	}

private:
	// The initial value of the sine curve
	double mInitialValue;

	// The amplitude of the sine wave
	double mAmplitude;

	//The frequency of the sine wave
	double mFrequency;

};
BOOST_CLASS_VERSION(SineControllerGene, 1)

#endif /* MODEL_EVOLUTION_POPULATION_CREATURE_GENOME_CONTROLLER_SINECONTROLLERGENE_H_ */
