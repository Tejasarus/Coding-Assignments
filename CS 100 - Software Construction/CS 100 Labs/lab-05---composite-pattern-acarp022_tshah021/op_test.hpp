#ifndef __OP_TEST_HPP__
#define __OP_TEST_HPP__

#include "gtest/gtest.h"

#include "op.hpp"

TEST(OpTest, OpEvaluateNonZero) {
    Op* test = new Op(8);
    EXPECT_EQ(test->evaluate(), 8);
}
TEST(OpTest, OpEvaluateZero) {
    Op* test = new Op(0);
    EXPECT_EQ(test->evaluate(), 0);
}
TEST(OpTest, OpEvaluateNegativeNumber) {
    Op* test = new Op(-8);
    EXPECT_EQ(test->evaluate(), -8);
}
TEST(OpTest, OpEvaluateLargeNumber) {
    Op* test = new Op(8000);
    EXPECT_EQ(test->evaluate(), 8000);
}

#endif //__OP_TEST_HPP__
