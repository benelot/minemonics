/*
 * EvolutionConfiguration.h
 *
 *  Created on: Nov 17, 2014
 *      Author: leviathan
 */

#ifndef EVOLUTIONCONFIGURATION_H_
#define EVOLUTIONCONFIGURATION_H_

class EvolutionConfiguration {
public:
    //
    // constants
    //
    static const unsigned PopSize     = 20;
    static const unsigned Dimension   = 200;
    static const unsigned Iterations  = 1000;
    static const unsigned NElitists   = 1;
    static const unsigned Omega       = 5;
    static const unsigned CrossPoints = 2;
    static const double   CrossProb   = 0.6;
    static const double   FlipProb    = 1. / Dimension;
};

#endif /* EVOLUTIONCONFIGURATION_H_ */
