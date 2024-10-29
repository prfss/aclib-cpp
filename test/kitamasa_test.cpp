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

long long fib_naive(int v) {
    vector<long long> xs = { 0, 1 };
    for (int i = 2; i <= v; i++) {
        xs.push_back(xs[i - 1] + xs[i - 2]);
    }
    return xs[v];
}

TEST(KitamasaTest, Fibonacci) {
    auto fib = [](long long n) {
        return kitamasa<ll>({ 1, 1 }, add<ll>, zero<ll>, mul<ll>, one<ll>, { 0, 1 }, n);
    };

    for (int i = 0; i <= 50; i++) {
        EXPECT_EQ(fib(i), fib_naive(i));
    }
}