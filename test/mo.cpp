#include "aclext/mo.hpp"
#include "gtest/gtest.h"

using namespace aclext;

TEST(MoTest, RangeSum) {
    vector<int> a = { 3, 1, 6, -8, 4, 3, -3, 5, 10, -2 };

    vector<pair<int, int>> query = { { 0, 0 }, { 2, 4 }, { 3, 5 }, { 2, 5 }, { 0, 3 }, { 0, 9 }, { 5, 8 } };

    int v = 0;
    auto val = [&]() { return v; };
    auto extend = [&](int i) {
        v += a[i];
    };
    auto shrink = [&](int i) {
        v -= a[i];
    };

    auto ans = mo<int>(query, extend, shrink, val);

    EXPECT_EQ(ans, vector({ 3, 2, -1, 5, 2, 19, 15 }));
}