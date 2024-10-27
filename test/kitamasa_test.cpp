#include "aclib/kitamasa.hpp"
#include "gtest/gtest.h"

template <typename T>
T add(T a, T b) { return a + b; }
template <typename T>
T mul(T a, T b) { return a * b; }
template <typename T>
T zero() { return T(0); }
template <typename T>
T one() { return T(1); }

using ll = long long;

TEST(KitamasaTest, Fibonacci) {
    auto fib = [](long long n) {
        return kitamasa<ll>({ 1, 1 }, add<ll>, zero<ll>, mul<ll>, one<ll>, { 0, 1 }, n);
    };
    EXPECT_EQ(fib(0), 0);
    EXPECT_EQ(fib(1), 1);
    EXPECT_EQ(fib(2), 1);
    EXPECT_EQ(fib(3), 2);
    EXPECT_EQ(fib(4), 3);
    EXPECT_EQ(fib(5), 5);
    EXPECT_EQ(fib(10), 55);
    EXPECT_EQ(fib(50), 12586269025);
}