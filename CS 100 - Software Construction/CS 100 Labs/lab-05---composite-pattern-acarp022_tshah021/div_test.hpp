#ifndef __DIV_TEST_HPP__
#define __DIV_TEST_HPP__

#include "gtest/gtest.h"
#include "div.hpp"
#include "op.hpp"

TEST(DivTest, DivEvaluateNonZero) {
	Base* temp1  = new Op(8);
	Base* temp2 = new Op(8);
	Div* test = new Div(temp1, temp2);
	EXPECT_EQ(test->evaluate(), 1);
}

TEST(DivTest, DivEvaluateZero) {
	Base* temp1  = new Op(0);
	Base* temp2 = new Op(8);
	Div* test = new Div(temp1, temp2);
	EXPECT_EQ(test->evaluate(), 0);
}

TEST(DivTest, DivEvaluateZeroDenominator) {
	Base* temp1  = new Op(8);
	Base* temp2 = new Op(0);
	Div* test = new Div(temp1, temp2);
	EXPECT_EQ(test->evaluate(), 0);
}

TEST(DivTest, DivEvaluateLargeNum) {
	Base* temp1  = new Op(1000000);
	Base* temp2 = new Op(10);
	Div* test = new Div(temp1, temp2);
	EXPECT_EQ(test->evaluate(), 100000);
}


#endif //__MULT_TEST_HPP__
