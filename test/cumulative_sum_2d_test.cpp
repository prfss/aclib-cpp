#include "aclib/cumulative_sum_2d.hpp"
#include "gtest/gtest.h"
#include <random>
#include <vector>

using namespace std;

const int SEED = 31415926;

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

long long naive(vector<vector<int>> l, int x1, int y1, int x2, int y2) {
    long long ret = 0;
    for (int i = x1; i < x2; i++) {
        for (int j = y1; j < y2; j++) {
            ret += l[i][j];
        }
    }
    return ret;
}

TEST(CumulativeSum2DTest, Naive) {
    mt19937_64 rng(SEED);
    const int n = 20;
    vector<vector<int>> v(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            v[i][j] = uniform_int_distribution<int>(0, 100)(rng);
        }
    }

    CumulativeSum2D<int> cs(v);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = i; k < n; k++) {
                for (int l = j; l < n; l++) {
                    EXPECT_EQ(cs(i, j, k, l), naive(v, i, j, k, l));
                }
            }
        }
    }
}