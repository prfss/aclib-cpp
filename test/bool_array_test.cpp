#include "aclib/bool_array.hpp"
#include "gtest/gtest.h"

TEST(BoolArrayTest, SmallExample) {
    auto ba = BoolArray(3);
    // auto ba = vector<bool>(3);
    ba[0] = true;
    auto a = ba[0];

    EXPECT_TRUE(a);
    EXPECT_FALSE(ba[1]);
    ba[1] = a;
    EXPECT_TRUE(ba[1]);

    // assign ElemProxy
    ba[0] = a;

    const auto b = ba[2];
    const bool c = ba[2];
    EXPECT_FALSE(b);
    EXPECT_FALSE(c);
    EXPECT_FALSE(ba[2]);
    // true
    ba[2] = ba[1];
    // shared state
    EXPECT_TRUE(b);
    EXPECT_FALSE(c);
    EXPECT_TRUE(ba[2]);
}
