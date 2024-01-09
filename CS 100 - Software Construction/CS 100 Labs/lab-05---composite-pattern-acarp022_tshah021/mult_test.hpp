#ifndef __MULT_TEST_HPP__
#define __MULT_TEST_HPP__

#include "gtest/gtest.h"
#include "mult.hpp"
#include "op.hpp"

TEST(MultTest, MultEvaluateNonZero) {
	Base* temp1  = new Op(8);
	Base* temp2 = new Op(8);
	Mult* test = new Mult(temp1, temp2);
	EXPECT_EQ(test->evaluate(), 64);
}

TEST(MultTest, MultEvaluateZero)
{
	Base* temp1  = new Op(8);
	Base* temp2 = new Op(0);
	Mult* test = new Mult(temp1, temp2);
	EXPECT_EQ(test->evaluate(), 0);
}

TEST(MultTest, MultEvaluateNegativeNum)
{
	Base* temp1  = new Op(8);
	Base* temp2 = new Op(-1);
	Mult* test = new Mult(temp1, temp2);
	EXPECT_EQ(test->evaluate(), -8);
}

TEST(MultTest, MultEvaluateHighNum)
{
	Base* temp1  = new Op(800);
	Base* temp2 = new Op(100);
	Mult* test = new Mult(temp1, temp2);
	EXPECT_EQ(test->evaluate(), 80000);
}
#endif //__MULT_TEST_HPP__
