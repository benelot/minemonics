/*
 * PhenomeModel.hpp
 *
 *  Created on: Apr 29, 2015
 *      Author: leviathan
 */

#ifndef MODEL_EVOLUTION_POPULATION_CREATURE_PHENOME_PHENOMEMODEL_HPP_
#define MODEL_EVOLUTION_POPULATION_CREATURE_PHENOME_PHENOMEMODEL_HPP_

/*
 *
 */
class PhenomeModel {
public:
	PhenomeModel();
	virtual ~PhenomeModel();

	//Accessor methods
	/**
	 * Is the phenotype in the world?
	 * @return
	 */
	bool isInWorld() const {
		return inWorld;
	}

	/**
	 * Set whether the phenotype is in the world or not.
	 * @param inWorld Whether the phenotype is in the world or not.
	 */
	void setInWorld(bool inWorld) {
		this->inWorld = inWorld;
	}
private:
	/**
	 * Whether the phenome is in the world or not.
	 */
	bool inWorld;
};

#endif /* MODEL_EVOLUTION_POPULATION_CREATURE_PHENOME_PHENOMEMODEL_HPP_ */
