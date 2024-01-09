#ifndef __POW_TEST_HPP__
#define __POW_TEST_HPP__

#include "gtest/gtest.h"
#include "pow.hpp"
#include "op.hpp"

TEST(PowTest, PowEvaluateNonZero) {
	Base* temp1  = new Op(8);
	Base* temp2 = new Op(2);
	Pow* test = new Pow(temp1, temp2);
	EXPECT_EQ(test->evaluate(), 64);
}

TEST(PowTest, PowEvaluateZero)
{
	Base* temp1  = new Op(8);
	Base* temp2 = new Op(0);
	Pow* test = new Pow(temp1, temp2);
	EXPECT_EQ(test->evaluate(), 1);
}

TEST(PowTest, PowEvaluateNegativeNum)
{
	Base* temp1  = new Op(-8);
	Base* temp2 = new Op(2);
	Pow* test = new Pow(temp1, temp2);
	EXPECT_EQ(test->evaluate(), 64);
}

TEST(PowTest, PowEvaluateHighNum)
{
	Base* temp1  = new Op(10);
	Base* temp2 = new Op(6);
	Pow* test = new Pow(temp1, temp2);
	EXPECT_EQ(test->evaluate(), 1000000);
}
#endif 
