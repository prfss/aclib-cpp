#include "aclib/random.hpp"
#include "gtest/gtest.h"
#include <random>

TEST(RandomTest, Simple) {
    mt19937 rng(12345);

    for (int i = 0; i < 10000; i++) {
        EXPECT_EQ(1, rand_range(1, 2, rng));
        EXPECT_DOUBLE_EQ(1.0, rand_range(1.0, nextafter(1.0, DBL_MAX), rng));
    }

    for (int i = 0; i < 10000; i++) {
        EXPECT_TRUE(rand_bool(1.0, rng));
        EXPECT_FALSE(rand_bool(0.0, rng));
    }
}