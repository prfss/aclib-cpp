#include "aclext/combination.hpp"
#include "gtest/gtest.h"

using namespace aclext;

TEST(CombinationTest, BasicProperties) {
    const long long MOD = 1'000'000'007;

    int n = 100000;

    Comb<MOD> comb(n);

    for (int i = 0; i <= n; i++) {
        EXPECT_EQ(comb(n, i), comb(n, n - i));
    }

    EXPECT_EQ(comb(n, n), 1);
}

TEST(CombinationTest, SmallExample) {
    const long long MOD = 1'000'000'007;

    int n = 7;

    Comb<MOD> comb(n);

    EXPECT_EQ(comb(n, 0), 1);
    EXPECT_EQ(comb(n, 1), 7);
    EXPECT_EQ(comb(n, 2), 21);
    EXPECT_EQ(comb(n, 3), 35);
}