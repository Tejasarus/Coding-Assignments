#ifndef __ADD_TEST_HPP__
#define __ADD_TEST_HPP__

#include "gtest/gtest.h"
#include "add.hpp"
#include "op.hpp"

TEST(AddTest, AddEvaluateNonZero) {
	Base* temp1  = new Op(8);
	Base* temp2 = new Op(8);
	Add* test = new Add(temp1, temp2);
	EXPECT_EQ(test->evaluate(), 16);
}

TEST(AddTest, AddEvaluateZero)
{
	Base* temp1  = new Op(8);
	Base* temp2 = new Op(0);
	Add* test = new Add(temp1, temp2);
	EXPECT_EQ(test->evaluate(), 8);
}

TEST(AddTest, AddEvaluateNegativeNum)
{
	Base* temp1  = new Op(8);
	Base* temp2 = new Op(-10);
	Add* test = new Add(temp1, temp2);
	EXPECT_EQ(test->evaluate(), -2);
}

TEST(AddTest, AddEvaluateHighNum)
{
	Base* temp1  = new Op(800);
	Base* temp2 = new Op(1000);
	Add* test = new Add(temp1, temp2);
	EXPECT_EQ(test->evaluate(), 1800);
}
#endif //__MULT_TEST_HPP__
