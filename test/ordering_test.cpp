#include "aclib/ordering.hpp"
#include "gtest/gtest.h"

TEST(OrderingTest, ItWorks) {
    EXPECT_TRUE(Ordering(1, 2));
    EXPECT_FALSE(Ordering(2, 1));
    EXPECT_FALSE(Ordering(1, 1).then(true, false));
    EXPECT_TRUE(Ordering(2, 2).then(23.0, 42.0));
}