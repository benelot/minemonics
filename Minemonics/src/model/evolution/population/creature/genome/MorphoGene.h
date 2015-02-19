/*
 * MorphoGene.h
 *
 *  Created on: Dec 5, 2014
 *      Author: leviathan
 */

#ifndef MORPHOGENE_H_
#define MORPHOGENE_H_

#include "Gene.h"

/**
 * Any gene that is involved in growth or morphogenesis.
 */
class MorphoGene: public Gene {
public:
	MorphoGene();
	virtual ~MorphoGene();

private:
	//size ratio of the growing somites
	double width,length,height;
	double density;
};

#endif /* MORPHOGENE_H_ */
