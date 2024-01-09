#ifndef __RAND_TEST_HPP__
#define __RAND_TEST_HPP__

#include "gtest/gtest.h"

#include "rand.hpp"

TEST(RandTest, AnythingBut100v1) {
    Rand* test = new Rand();
    EXPECT_TRUE((test->evaluate() < 100) && (test->evaluate() >= 0));
}
TEST(RandTest, AnythingBut100v2) {
    Rand* test = new Rand();
    EXPECT_TRUE((test->evaluate() < 100) && (test->evaluate() >= 0));
}
TEST(RandTest, AnythingBut100v3) {
    Rand* test = new Rand();
    EXPECT_TRUE((test->evaluate() < 100) && (test->evaluate() >= 0));
}
TEST(RandTest, AnythingBut100v4) {
    Rand* test = new Rand();
    EXPECT_TRUE((test->evaluate() < 100) && (test->evaluate() >= 0));
}
#endif //__RAND_TEST_HPP__
