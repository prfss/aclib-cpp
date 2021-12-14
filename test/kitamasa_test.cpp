#include "aclext/kitamasa.hpp"
#include "gtest/gtest.h"

using namespace aclext;

template <typename T>
T add(T a, T b) { return a + b; }
template <typename T>
T mul(T a, T b) { return a * b; }
template <typename T>
T zero() { return T(0); }
template <typename T>
T one() { return T(1); }

TEST(KitamasaTest, Fibonacci) {
    auto fib = Kitamasa<long long, add, mul, zero, one>({ 1, 1 });
    vector<long long> init = { 0, 1 };
    EXPECT_EQ(fib.calc(init, 0), 0);
    EXPECT_EQ(fib.calc(init, 1), 1);
    EXPECT_EQ(fib.calc(init, 2), 1);
    EXPECT_EQ(fib.calc(init, 3), 2);
    EXPECT_EQ(fib.calc(init, 4), 3);
    EXPECT_EQ(fib.calc(init, 5), 5);
    EXPECT_EQ(fib.calc(init, 10), 55);
    EXPECT_EQ(fib.calc(init, 50), 12586269025);
}