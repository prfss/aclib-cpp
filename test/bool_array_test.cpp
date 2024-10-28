#include "aclib/bool_array.hpp"
#include "gtest/gtest.h"

TEST(BoolArrayTest, SmallExample) {
    auto ba = BoolArray(3);
    for (size_t i = 0; i < ba.size(); i++) {
        EXPECT_FALSE(ba[i]) << "All elements must be initialized to false";
    }
    ba[0] = true;
    EXPECT_TRUE(ba[0]) << "Boolean assignment";
    auto a = ba[0];
    EXPECT_TRUE(a) << "Copied";
    EXPECT_FALSE(ba[1]) << "Unchanged element";
    ba[1] = a;
    EXPECT_TRUE(ba[1]) << "ElemProxy assignment";

    const auto b = ba[2];
    const bool c = ba[2];
    EXPECT_FALSE(b);
    EXPECT_FALSE(c);
    EXPECT_FALSE(ba[2]);
    ba[2] = ba[1];
    EXPECT_TRUE(b) << "const ElemProxy shares original element value";
    EXPECT_FALSE(c);
    EXPECT_TRUE(ba[2]);
}
