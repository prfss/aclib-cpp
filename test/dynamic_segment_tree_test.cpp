#include "aclib/dynamic_segment_tree.hpp"
#include "atcoder/segtree.hpp"
#include "gtest/gtest.h"

#include <algorithm>
#include <random>
#include <vector>

using namespace std;

namespace rmq {
int op(int a, int b) {
    return min(a, b);
}
int e() {
    return 1'000'000;
}
using stree = DynamicSegmentTree<int, op, e, int64_t>;
}

TEST(DynamicSegmentTreeTest, RMQSmall) {
    rmq::stree st(-5, 6);
    EXPECT_EQ(st.all_prod(), 1'000'000);
    st.set(2, 100);
    EXPECT_EQ(st.get(2), 100);
    EXPECT_EQ(st.all_prod(), 100);
    EXPECT_EQ(st.prod(-5, 2), 1'000'000);
    EXPECT_EQ(st.prod(-5, 3), 100);
    EXPECT_EQ(st.prod(2, 6), 100);
    EXPECT_EQ(st.prod(3, 6), 1'000'000);
    st.set(5, 200);
    EXPECT_EQ(st.get(5), 200);
    EXPECT_EQ(st.all_prod(), 100);
    EXPECT_EQ(st.prod(3, 6), 200);
    EXPECT_EQ(st.prod(2, 6), 100);
}

TEST(DynamicSegmentTreeTest, MaxRightSmall) {
    vector<int> v({ 10, 4, -3, 2, 1, 6, 5, -4, -5, -7 });
    rmq::stree st(0, v.size());

    for (size_t i = 0; i < v.size(); i++) {
        st.set(i, v[i]);
    }

    EXPECT_EQ(st.all_prod(), -7);
    EXPECT_EQ(st.max_right(4, [](int v) { return v > -5; }), 8);
    EXPECT_EQ(st.max_right(2, [](int v) { return v > -3; }), 2);
}

const int SEED = 314159;

TEST(DynamicSegmentTreeTest, RMQOracle) {
    const int64_t n = 100;
    rmq::stree st(0, n);
    atcoder::segtree<int, rmq::op, rmq::e> oracle(n);

    EXPECT_EQ(st.all_prod(), rmq::e());

    mt19937_64 rng(SEED);

    const int k = 500;
    for (int i = 0; i < k; i++) {
        const int64_t idx = uniform_int_distribution<int64_t>(0, n - 1)(rng);
        const int new_v = uniform_int_distribution<int>(-10000, 10000)(rng);
        st.set(idx, new_v);
        oracle.set(idx, new_v);
        EXPECT_EQ(st.all_prod(), oracle.all_prod());
        for (int l = 0; l < n; l++) {
            for (int r = l + 1; r <= n; r++) {
                EXPECT_EQ(st.prod(l, r), oracle.prod(l, r));
            }
        }

        for (int64_t l = 0; l < n; l++) {
            EXPECT_EQ(
                st.max_right(l, [](int v) { return v > -8000; }),
                oracle.max_right(l, [](int v) { return v > -8000; }));
        }

        for (int64_t r = 1; r <= n; r++) {
            EXPECT_EQ(
                st.min_left(r, [](int v) { return v > -8000; }),
                oracle.min_left(r, [](int v) { return v > -8000; }));
        }
    }
}

TEST(DynamicSegmentTreeTest, CopyMove) {
    mt19937_64 rng(SEED);

    const int64_t n = 1'000'000'000'000;
    rmq::stree st(0, n);
    rmq::stree copied = st;
    rmq::stree moved = std::move(copied);

    EXPECT_EQ(copied.all_prod(), rmq::e());

    const int k = 100000;
    for (int i = 0; i < k; i++) {
        const int64_t idx = uniform_int_distribution<int64_t>(0, n - 1)(rng);
        const int new_v = uniform_int_distribution<int>(-10000, 10000)(rng);
        st.set(idx, new_v);
        moved.set(idx, new_v);
        EXPECT_EQ(st.all_prod(), moved.all_prod());
    }
}