/*
 * VelocityTestCase.cpp
 *
 *  Created on: Feb 26, 2015
 *      Author: leviathan
 */

#define BOOST_TEST_DYN_LINK
#include "model/evolution/juries/Velocity.h"
#include <boost/test/unit_test.hpp>

struct VelocityFixture {
	VelocityFixture():velocity(1)
	{
		BOOST_TEST_MESSAGE( "Setup Velocity fixture..." );
	}
	~VelocityFixture()
	{
		BOOST_TEST_MESSAGE( "Teardown Velocity fixture..." );
	}
	Velocity velocity;
};

BOOST_FIXTURE_TEST_SUITE( test_suite, VelocityFixture )

BOOST_AUTO_TEST_CASE( hasWeightOne )
{
	BOOST_CHECK(velocity.getWeight() == 1);
}

BOOST_AUTO_TEST_CASE( evaluateVelocity )
{
	velocity.calculateAvgVelocity(0,0,0,0);
	velocity.calculateAvgVelocity(1,0,0,1);
	velocity.evaluateFitness();
	BOOST_CHECK(velocity.getFitness() == 1);
}


BOOST_AUTO_TEST_SUITE_END()


