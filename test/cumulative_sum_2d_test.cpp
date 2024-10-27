#include "aclib/cumulative_sum_2d.hpp"
#include "gtest/gtest.h"
#include <vector>

using namespace std;

TEST(CumulativeSum2DTest, SmallExample) {
    // [1,2,3]
    // [4,5,6]
    // [8,9,10]
    vector<vector<int>> l = { { 1, 2, 3 }, { 4, 5, 6 }, { 8, 9, 10 } };
    CumulativeSum2D<int> cs(l);

    EXPECT_EQ(cs(0, 0, 3, 3), 48);
    EXPECT_EQ(cs(1, 1, 3, 3), 30);
    EXPECT_EQ(cs(1, 1, 3, 2), 14);
    EXPECT_EQ(cs(1, 1, 2, 2), 5);
}
