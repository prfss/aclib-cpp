#include "aclext/number_theory.hpp"
#include "gtest/gtest.h"

TEST(TotientTest, ItWorks) {
    EXPECT_EQ(totient(100), 40);
    EXPECT_EQ(totient(1000), 400);
    EXPECT_EQ(totient(31415926535), 20847434400);
}