#include "aclib/dynamic_segment_tree.hpp"
#include "gtest/gtest.h"

#include <algorithm>
#include <vector>

using namespace std;

namespace rmq {
int op(int a, int b) {
    return min(a, b);
}
int e() {
    return 1'000'000;
}
using stree = DynamicSegmentTree<int, op, e>;
}

TEST(DynamicSegmentTreeTest, RMQ) {
    rmq::stree st(-5, 5);
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

TEST(DynamicSegmentTreeTest, MaxRight) {
    vector<int> v({ 10, 4, -3, 2, 1, 6, 5, -4, -5, -7 });
    rmq::stree st(0, v.size() - 1);

    for (size_t i = 0; i < v.size(); i++) {
        st.set(i, v[i]);
    }

    EXPECT_EQ(st.all_prod(), -7);
    EXPECT_EQ(st.max_right(4, [](int v) { return v > -5; }), 8);
    EXPECT_EQ(st.max_right(2, [](int v) { return v > -3; }), 2);
}