/*
 * Ones.h
 *
 *  Created on: Feb 25, 2015
 *      Author: leviathan
 */

#ifndef ONES_H_
#define ONES_H_

#include "Jury.h"

class Ones: public Jury {
public:
	Ones(double weight);
	virtual ~Ones();
	//
	// fitness function: counting ones problem
	//
	double ones( const std::vector< bool >& x )
	{
	    unsigned i;
	    double   sum;
	    for( sum = 0., i = 0; i < x.size( ); sum += x[ i++ ] );
	    return sum;
	}
};

#endif /* ONES_H_ */
