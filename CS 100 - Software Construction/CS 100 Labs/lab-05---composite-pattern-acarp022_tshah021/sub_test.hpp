#ifndef __SUB_TEST_HPP__
#define __SUB_TEST_HPP__

#include "gtest/gtest.h"
#include "sub.hpp"
#include "op.hpp"

TEST(SubTest, SubEvaluateNonZero) {
	Base* temp1  = new Op(8);
	Base* temp2 = new Op(8);
	Sub* test = new Sub(temp1, temp2);
	EXPECT_EQ(test->evaluate(), 0);
}

TEST(SubTest, SubEvaluateZero)
{
	Base* temp1  = new Op(8);
	Base* temp2 = new Op(0);
	Sub* test = new Sub(temp1, temp2);
	EXPECT_EQ(test->evaluate(), 8);
}

TEST(SubTest, SubEvaluateNegativeNum)
{
	Base* temp1  = new Op(8);
	Base* temp2 = new Op(-10);
	Sub* test = new Sub(temp1, temp2);
	EXPECT_EQ(test->evaluate(), 18);
}

TEST(SubTest, SubEvaluateHighNum)
{
	Base* temp1  = new Op(800);
	Base* temp2 = new Op(1000);
	Sub* test = new Sub(temp1, temp2);
	EXPECT_EQ(test->evaluate(), -200);
}
#endif 
