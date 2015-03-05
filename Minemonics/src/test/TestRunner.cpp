/*
 * TestRunner.cpp
 *
 *  Created on: Feb 27, 2015
 *      Author: leviathan
 */

#// AllTests.cpp
#include <gtest/gtest.h>

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
