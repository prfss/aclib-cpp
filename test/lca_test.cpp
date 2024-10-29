#include "aclib/lca.hpp"
#include "gtest/gtest.h"
#include <random>

const int SEED = 31415926;

TEST(LcaTest, SmallExample) {
    const int n = 9;

    Lca lca(n);

    lca.add_edge(5, 0);
    lca.add_edge(5, 2);
    lca.add_edge(0, 3);
    lca.add_edge(0, 4);
    lca.add_edge(3, 1);
    lca.add_edge(2, 6);

    EXPECT_EQ(lca(3, 1), 3);
    EXPECT_EQ(lca(4, 1), 0);
    EXPECT_EQ(lca(1, 6), 5);
    EXPECT_EQ(lca(3, 4), 0);
    EXPECT_EQ(lca(0, 7), -1);
    EXPECT_EQ(lca(7, 8), -1);
    EXPECT_EQ(lca(0, 5), 5);
    EXPECT_EQ(lca(5, 0), 5);

    for (int i = 0; i < n; i++) {
        EXPECT_EQ(lca(i, i), i);
        for (int j = i + 1; j < n; j++) {
            EXPECT_EQ(lca(i, j), lca(j, i));
        }
    }
}

int naive(vector<int> par, int i, int j) {
    int ans = -1;
    set<int> s;
    while (i != -1) {
        s.insert(i);
        i = par[i];
    }
    while (j != -1) {
        if (s.count(j)) {
            return j;
        }
        j = par[j];
    }
    return ans;
}

TEST(LcaTest, Naive) {
    mt19937_64 rng(SEED);
    const int n = 300;

    Lca lca(n);
    vector<int> par(n, -1);

    for (int i = 1; i < n; i++) {
        // 2%の確率で根にする
        if (!bernoulli_distribution(0.02)(rng)) {
            int p = uniform_int_distribution<int>(0, i - 1)(rng);
            lca.add_edge(p, i);
            par[i] = p;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            EXPECT_EQ(lca(i, j), naive(par, i, j));
        }
    }
}
