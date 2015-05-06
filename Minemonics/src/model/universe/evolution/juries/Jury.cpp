/*
 * Jury.cpp
 *
 *  Created on: Dec 7, 2014
 *      Author: leviathan
 */

//# corresponding headers
#include <model/universe/evolution/juries/Jury.hpp>

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

Jury::Jury(JuryType juryType, int weight) :
		mJuryType(juryType), mFitness(0), mWeight(weight) {

}

Jury::~Jury() {

}

/**
 * Returns the weight associated with this jury component.
 * @return the weight
 */
double Jury::getWeight() {
	return mWeight;
}

/**
 * Returns the fitness value that this jury assigns.
 * @return the fitness value
 */
double Jury::getFitness() {
	return mFitness;
}

Jury::JuryType Jury::getJuryType() {
	return mJuryType;
}

