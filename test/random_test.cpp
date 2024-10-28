#include "aclib/random.hpp"
#include "gtest/gtest.h"
#include <random>

const int SEED = 31415926;

TEST(RandomTest, WeightedIndexDouble) {
    mt19937_64 rng(SEED);
    vector<double> weights = { 1.0, 1.5, 2.0, 10.0, 1.01, 7.5, 9.5, 0.0 };
    auto dist = WeightedIndex(weights);
    const int n = 1000000;
    vector<int> c(dist.size());
    for (int i = 0; i < n; i++) {
        size_t k = dist(rng);
        EXPECT_TRUE(0 <= k && k < dist.size());
        c[k]++;
    }

    // 確率的
    double ws = accumulate(weights.begin(), weights.end(), 0.0);
    for (size_t k = 0; k < dist.size(); k++) {
        double r = 1.0 * c[k] / n;
        // fprintf(stderr, "%f =~ %f\n", r, weights[k] / ws);
        long nearest = min_element(weights.begin(), weights.end(), [&](double a, double b) {
                           return abs(a / ws - r) < abs(b / ws - r);
                       })
                       - weights.begin();
        EXPECT_EQ(nearest, k);
    }
    EXPECT_EQ(c.back(), 0);
}

TEST(RandomTest, WeightedIndexUInt) {
    mt19937_64 rng(SEED);
    vector<uint> weights = { 1, 2, 5, 3, 10, 8, 100, 0 };
    auto dist = WeightedIndex(weights);
    const int n = 1000000;
    vector<int> c(dist.size());
    for (int i = 0; i < n; i++) {
        size_t k = dist(rng);
        EXPECT_TRUE(0 <= k && k < dist.size());
        c[k]++;
    }

    // 確率的
    double ws = accumulate(weights.begin(), weights.end(), 0.0);
    for (size_t k = 0; k < dist.size(); k++) {
        double r = 1.0 * c[k] / n;
        // fprintf(stderr, "%f =~ %f\n", r, weights[k] / ws);
        long nearest = min_element(weights.begin(), weights.end(), [&](double a, double b) {
                           return abs(a / ws - r) < abs(b / ws - r);
                       })
                       - weights.begin();
        EXPECT_EQ(nearest, k);
    }
    EXPECT_EQ(c.back(), 0);
}