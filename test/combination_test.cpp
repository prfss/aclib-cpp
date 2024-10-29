#include "aclib/combination.hpp"
#include "gtest/gtest.h"

long long pow_mod(long long a, long long b, long long mod) {
    long long res = 1;
    while (b > 0) {
        if (b & 1) {
            res = (res * a) % mod;
        }
        a = (a * a) % mod;
        b >>= 1;
    }
    return res;
}

long long inv(long long a, long long mod) {
    return pow_mod(a, mod - 2, mod);
}

TEST(CombinationTest, BasicProperties) {
    const int MOD = 1'000'000'007;

    int n = 100000;

    Comb<MOD> comb(n);

    for (int i = 0; i <= n; i++) {
        EXPECT_EQ(comb(n, i), comb(n, n - i));
        EXPECT_EQ(comb(i, 0), 1);
    }

    EXPECT_EQ(comb(n, n), 1);
}

TEST(CombinationTest, Naive) {
    const int MOD = 99991;
    const int n = 1000;

    Comb<MOD> comb(n);

    for (int i = 1; i <= n; i++) {
        long long v = 1;
        for (int j = 1; j <= i; j++) {
            v = (v * (i - j + 1)) % MOD;
            v = (v * inv(j, MOD)) % MOD;
            EXPECT_EQ(comb(i, j), v);
        }
    }
}

TEST(CombinationTest, SmallExample) {
    const int MOD = 11;

    int n = 7;

    Comb<MOD> comb(n);

    EXPECT_EQ(comb(n, 0), 1 % MOD);
    EXPECT_EQ(comb(n, 1), 7 % MOD);
    EXPECT_EQ(comb(n, 2), 21 % MOD);
    EXPECT_EQ(comb(n, 3), 35 % MOD);
}