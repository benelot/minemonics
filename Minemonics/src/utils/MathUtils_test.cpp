/*
 * MathUtils_test.cpp
 *
 *  Created on: Mar 13, 2015
 *      Author: leviathan
 */

//# corresponding header
#include <utils/MathUtils.hpp>
#include <gtest/gtest.h>

//## controller headers
//## model headers
#include <OgreVector3.h>
#include <OgreQuaternion.h>
#include <LinearMath/btVector3.h>
#include <LinearMath/btQuaternion.h>
#include <LinearMath/btTransform.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers

class MathUtilsTest: public ::testing::Test {
protected:
	virtual void SetUp() {
	}

	virtual void TearDown() {
	}
};

TEST_F(MathUtilsTest,DoubleFiniteClassification) {

	double i = 1; // Finite
	double j = -1; // Finite
	double inf = 1.0f / 0.0f; // Inf
	double nan = inf * 0.0f; // NaN

	ASSERT_TRUE(MathUtils::isInf(inf) && MathUtils::isNaN(nan));
	ASSERT_TRUE(MathUtils::isFinite(i));
	ASSERT_TRUE(MathUtils::isFinite(j));
	ASSERT_TRUE(!MathUtils::isFinite(inf));
	ASSERT_TRUE(!MathUtils::isFinite(nan));

}

TEST_F(MathUtilsTest,OgreVectorFiniteClassification) {

	double inf = 1.0f/0.0f;
	double nan = 1.0f/0.0f*0.0f;
	Ogre::Vector3 v1(0,0,0); // Finite
	Ogre::Vector3 v2(1,-1,1); // Finite
	Ogre::Vector3 v3(1,inf,0); // Inf
	Ogre::Vector3 v4(1,nan,0); // NaN
	Ogre::Vector3 v5(inf,nan,1); // Inf and NaN

	ASSERT_TRUE(MathUtils::isInf(inf) && MathUtils::isNaN(nan));
	ASSERT_TRUE(MathUtils::isFinite(v1));
	ASSERT_TRUE(MathUtils::isFinite(v2));
	ASSERT_TRUE(!MathUtils::isFinite(v3));
	ASSERT_TRUE(!MathUtils::isFinite(v4));
	ASSERT_TRUE(!MathUtils::isFinite(v5));

}

TEST_F(MathUtilsTest,BtVectorFiniteClassification) {

	double inf = 1.0f/0.0f;
	double nan = 1.0f/0.0f*0.0f;
	btVector3 v1(0,0,0); // Finite
	btVector3 v2(1,-1,1); // Finite
	btVector3 v3(1,inf,0); // Inf
	btVector3 v4(1,nan,0); // NaN
	btVector3 v5(inf,nan,1); // Inf and NaN

	// btVector3 can avoid Inf xor NaN
	ASSERT_TRUE(MathUtils::isInf(inf) && MathUtils::isNaN(nan));
	ASSERT_TRUE(MathUtils::isFinite(v1));
	ASSERT_TRUE(MathUtils::isFinite(v2));
	ASSERT_TRUE(MathUtils::isFinite(v3));
	ASSERT_TRUE(!MathUtils::isFinite(v4));
	ASSERT_TRUE(!MathUtils::isFinite(v5));

}

TEST_F(MathUtilsTest,OgreQuaternionFiniteClassification) {

	double inf = 1.0f/0.0f;
	double nan = 1.0f/0.0f*0.0f;
	Ogre::Quaternion q1(0,0,0,1); // Finite
	Ogre::Quaternion q2(1,-1,1,1); // Finite
	Ogre::Quaternion q3(1,inf,0,1); // Inf
	Ogre::Quaternion q4(1,nan,0,1); // NaN
	Ogre::Quaternion q5(inf,nan,0,1); // Inf and NaN

	ASSERT_TRUE(MathUtils::isInf(inf) && MathUtils::isNaN(nan));
	ASSERT_TRUE(MathUtils::isFinite(q1));
	ASSERT_TRUE(MathUtils::isFinite(q2));
	ASSERT_TRUE(!MathUtils::isFinite(q3));
	ASSERT_TRUE(!MathUtils::isFinite(q4));
	ASSERT_TRUE(!MathUtils::isFinite(q5));
}

TEST_F(MathUtilsTest,BtQuaternionFiniteClassification) {

	double inf = 1.0f/0.0f;
	double nan = 1.0f/0.0f*0.0f;
	btQuaternion q1(0,0,0,1); // Finite
	btQuaternion q2(1,-1,1,1); // Finite
	btQuaternion q3(1,inf,0,1); // Inf
	btQuaternion q4(1,nan,0,1); // NaN
	btQuaternion q5(inf,nan,1); // Inf and NaN

	//btQuaternion can avoid Inf xor NaN
	ASSERT_TRUE(MathUtils::isInf(inf) && MathUtils::isNaN(nan));
	ASSERT_TRUE(MathUtils::isFinite(q1));
	ASSERT_TRUE(MathUtils::isFinite(q2));
	ASSERT_TRUE(MathUtils::isFinite(q3));
	ASSERT_TRUE(!MathUtils::isFinite(q4));
	ASSERT_TRUE(!MathUtils::isFinite(q5));
}

//TEST_F(MathUtilsTest,BtTransformFiniteClassification) {
//
//	double inf = 1.0f/0.0f;
//	double nan = 1.0f/0.0f*0.0f;
//	btVector3 v1(0,0,0); // Finite
//	btVector3 v2(1,-1,1); // Finite
//	btVector3 v3(1,inf,0); // Inf
//	btVector3 v4(1,nan,0); // NaN
//	btQuaternion q1(0,0,0,1); // Finite
//	btQuaternion q2(1,-1,1,1); // Finite
//	btQuaternion q3(1,inf,0,1); // Inf
//	btQuaternion q4(1,nan,0,1); // NaN
//
//	btTransform bt1(q1,v1); // Finite
//	btTransform bt2(q2,v2); // Finite
//	btTransform bt3(q1,v3); // Finite and Inf
//	btTransform bt4(q2,v4); // Finite and NaN
//	btTransform bt5(q3,v1); // Inf and Finite
//	btTransform bt6(q3,v3); // Inf and Inf
//	btTransform bt7(q3,v4); // Inf and NaN
//	btTransform bt8(q4,v1); // NaN and Finite
//	btTransform bt9(q4,v3); // NaN and Inf
//	btTransform bt10(q4,v4); // NaN and NaN
//
//	ASSERT_TRUE(MathUtils::isInf(inf) && MathUtils::isNaN(nan));
//	ASSERT_TRUE(MathUtils::isFinite(bt1));
//	ASSERT_TRUE(MathUtils::isFinite(bt2));
//	ASSERT_TRUE(!MathUtils::isFinite(bt3));
//	ASSERT_TRUE(!MathUtils::isFinite(bt4));
//	ASSERT_TRUE(!MathUtils::isFinite(bt5));
//	ASSERT_TRUE(!MathUtils::isFinite(bt6));
//	ASSERT_TRUE(!MathUtils::isFinite(bt7));
//	ASSERT_TRUE(!MathUtils::isFinite(bt8));
//	ASSERT_TRUE(!MathUtils::isFinite(bt9));
//	ASSERT_TRUE(!MathUtils::isFinite(bt10));
//}

