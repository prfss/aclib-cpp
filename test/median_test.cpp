#include "aclib/median.hpp"
#include "gtest/gtest.h"
#include <vector>

using namespace std;

namespace small_example {
int op(int k, int a, int b) {
    if (k % 2 == 0) {
        return (a + b) / 2;
    } else {
        return a;
    }
}
}

TEST(MedianTest, SmallExample) {

    Median<int, int, small_example::op> median;
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

namespace int_double {
double op(int k, int a, int b) {
    return (a + b) / 2.0;
}
}

TEST(MedianTest, IntDouble) {

    Median<int, double, int_double::op> median;
    vector<int> arr = { 5, 3, 8, 1, 3, 10 };

    for (auto x : arr) {
        median.insert(x);
    }

    EXPECT_EQ(median(), 4.0);
    median.erase(3);
    EXPECT_EQ(median(), 5.0);
    median.erase(3);
    EXPECT_EQ(median(), 6.5);
}