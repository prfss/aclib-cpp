#include "aclext/median.hpp"
#include "gtest/gtest.h"
#include <vector>

using namespace aclext;
using namespace std;

int op(int k, int a, int b) {
    if (k % 2 == 0) {
        return (a + b) / 2;
    } else {
        return a;
    }
}

TEST(MedianTest, SmallExample) {

    Median<int, int, op> median;
    vector<int> arr = { 2, 8, 10, 2, 6, 4 };

    for (auto x : arr) {
        median.insert(x);
    }

    EXPECT_EQ(median.size(), 6);

    EXPECT_EQ(median(), 5);
    median.erase(2);
    EXPECT_EQ(median(), 6);
    median.erase(6);
    EXPECT_EQ(median(), 6);

    EXPECT_EQ(median.size(), 4);
}