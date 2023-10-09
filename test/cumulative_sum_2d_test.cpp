#include "aclext/cumulative_sum_2d.hpp"
#include "gtest/gtest.h"
#include <vector>

using namespace std;

TEST(CumulativeSum2DTest, SmallExample) {
    vector<vector<int>> l = { { 1, 2, 3 }, { 4, 5, 6 }, { 8, 9, 10 } };
    CumulativeSum2D<int> cs(l);

    EXPECT_EQ(cs(0, 0, 2, 2), 48);
    EXPECT_EQ(cs(1, 1, 2, 2), 30);
}
