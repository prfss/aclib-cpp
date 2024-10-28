#include "aclib/depq.hpp"
#include "gtest/gtest.h"

#include <random>
#include <vector>

using namespace std;

const int SEED = 31415926;

TEST(DepqTest, IsIntervalHeap) {
    EXPECT_TRUE(is_interval_heap<int>({ 0, 6, 0, 6, 1, 4, 2, 2, 3 }));
    EXPECT_TRUE(is_interval_heap<int>({}));
    EXPECT_TRUE(is_interval_heap<int>({ 0 }));
    EXPECT_FALSE(is_interval_heap<int>({ 0, 6, 3, 2, 1, 4 }));
}

TEST(DepqTest, MakeIntervalHeap) {
    mt19937_64 rng(SEED);
    const int n = 1000;
    auto uf = uniform_int_distribution<int>(0, n);
    vector<int> vs(n);
    for (int i = 0; i < n; i++) vs[i] = uf(rng);

    // 高い確率で
    EXPECT_FALSE(is_interval_heap(vs));
    make_interval_heap(vs);
    EXPECT_TRUE(is_interval_heap(vs));

    vector<int> vs2;
    EXPECT_NO_FATAL_FAILURE(make_interval_heap(vs2)) << "empty";
    EXPECT_TRUE(is_interval_heap(vs2));

    vector<int> vs3 = { 1 };
    EXPECT_NO_FATAL_FAILURE(make_interval_heap(vs3)) << "single element";
    EXPECT_TRUE(is_interval_heap(vs3));

    vector<int> vs4 = { 2, 1 };
    EXPECT_NO_FATAL_FAILURE(make_interval_heap(vs4)) << "exactly 2 elements";
    EXPECT_TRUE(is_interval_heap(vs4));
}

TEST(DepqTest, Oracle) {
    const int n = 1000;
    mt19937_64 rng(SEED);
    auto uf = uniform_int_distribution<int>(0, n);
    auto gen_bool = bernoulli_distribution(0.5);

    DoubleEndedPriorityQueue<int> q;
    multiset<int> s;

    EXPECT_TRUE(q.empty());
    EXPECT_EQ(q.size(), 0);

    for (int k = 0; k < 5; k++) {
        int j = 0;
        for (int i = 0; i < 2 * n; i++) {
            if (s.empty() || (gen_bool(rng) && j < n)) {
                auto v = uf(rng);
                q.push(v);
                s.insert(v);
                j++;
            } else {
                assert(!q.empty() && !s.empty());

                bool get_min = gen_bool(rng);

                int v = 0;
                if (get_min)
                    v = q.pop_min();
                else
                    v = q.pop_max();

                if (get_min) {
                    EXPECT_EQ(v, *s.begin());
                    s.erase(s.begin());
                } else {
                    EXPECT_EQ(v, *s.rbegin());
                    s.erase(prev(s.end()));
                }
            }

            EXPECT_EQ(q.size(), s.size());
            EXPECT_TRUE(is_interval_heap(q.data));
            if (!q.empty()) {
                EXPECT_EQ(q.peek_min(), *s.begin());
                EXPECT_EQ(q.peek_max(), *s.rbegin());
            }
        }
        EXPECT_EQ(q.size(), 0);
        EXPECT_TRUE(q.empty());
    }
}