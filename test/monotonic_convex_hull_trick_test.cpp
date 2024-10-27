#include "aclib/monotonic_convex_hull_trick.hpp"
#include "gtest/gtest.h"

TEST(MonotonicCHTTest, IncrementalMin) {
    MonotonicConvexHullTrick<int> cht;
    cht.add(5, 1);
    EXPECT_EQ(cht(1), 6);
    cht.add(5, 0);
    EXPECT_EQ(cht(2), 10);
    cht.add(3, 2);
    EXPECT_EQ(cht(2), 8);
    cht.add(2, 2);
    EXPECT_EQ(cht(2), 6);
    cht.add(1, 6);
    cht.add(-1, 8);
    EXPECT_EQ(cht(2), 6);
    EXPECT_EQ(cht(4), 4);
}

TEST(MonotonicCHTTest, IncrementalMax) {
    MonotonicConvexHullTrick<int, std::greater<int>> cht;
    cht.add(-4, 10);
    EXPECT_EQ(cht(1), 6);
    cht.add(-2, 6);
    EXPECT_EQ(cht(1), 6);
    EXPECT_EQ(cht(2), 2);
    EXPECT_EQ(cht(3), 0);
    cht.add(-1, 5);
    EXPECT_EQ(cht(3), 2);
    EXPECT_EQ(cht(4), 1);
    cht.add(0, 2);
    EXPECT_EQ(cht(4), 2);
    cht.add(1, -5);
    EXPECT_EQ(cht(4), 2);
    EXPECT_EQ(cht(8), 3);
}

TEST(MonotonicCHTTest, DecrementalMin) {
    MonotonicConvexHullTrick<int> cht;
    cht.add(-2, 12);
    EXPECT_EQ(cht(8), -4);
    EXPECT_EQ(cht(4), 4);
    cht.add(-1, 8);
    EXPECT_EQ(cht(8), -4);
    EXPECT_EQ(cht(4), 4);
    cht.add(0, 3);
    EXPECT_EQ(cht(4), 3);
    EXPECT_EQ(cht(3), 3);
    cht.add(1, -1);
    EXPECT_EQ(cht(3), 2);
}

TEST(MonotonicCHTTest, DecrementalMax) {
    MonotonicConvexHullTrick<int, std::greater<int>> cht;
    cht.add(4, -20);
    EXPECT_EQ(cht(6), 4);
    cht.add(3, -14);
    EXPECT_EQ(cht(6), 4);
    EXPECT_EQ(cht(5), 1);
    cht.add(1, -3);
    EXPECT_EQ(cht(5), 2);
    EXPECT_EQ(cht(4), 1);
    cht.add(0, 2);
    EXPECT_EQ(cht(4), 2);
    EXPECT_EQ(cht(2), 2);
    cht.add(-1, 5);
    EXPECT_EQ(cht(2), 3);
}