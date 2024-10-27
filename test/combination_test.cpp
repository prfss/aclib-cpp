#include "aclib/combination.hpp"
#include "gtest/gtest.h"

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

TEST(CombinationTest, SmallExample) {
    const int MOD = 11;

    int n = 7;

    Comb<MOD> comb(n);

    EXPECT_EQ(comb(n, 0), 1 % MOD);
    EXPECT_EQ(comb(n, 1), 7 % MOD);
    EXPECT_EQ(comb(n, 2), 21 % MOD);
    EXPECT_EQ(comb(n, 3), 35 % MOD);
}