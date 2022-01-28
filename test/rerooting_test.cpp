#include "../aclext/rerooting.hpp"
#include "gtest/gtest.h"
#include <algorithm>
#include <vector>

using S = int;
using M = pair<int, int>;
using R = int;
using C = int;

namespace longest_path {
M merge(M a, M b, int u) {
    auto x = a.first;
    auto y = b.first;
    return { max(x, y), min(x, y) };
}

M introduce(M a, S b, C c, int u, int v) {
    vector<int> x = { a.first, a.second, b + c };
    sort(x.begin(), x.end());
    return { x[2], x[1] };
}

M em() {
    return { 0, 0 };
}

R result(M a, int u) {
    if (a.second == 0)
        return 0;
    else
        return a.first + a.second;
}

S subtree(M a, int u) {
    return a.first;
}

using dp = aclext::Rerooting<S, M, R, C, merge, introduce, em, result, subtree>;
};

TEST(RerootingTest, LongestPath) {
    longest_path::dp g(8);
    g.add_edge(0, 1, 5);
    g.add_edge(0, 3, 1);
    g.add_edge(0, 5, 2);
    g.add_edge(1, 2, 4);
    g.add_edge(1, 6, 1);
    g.add_edge(3, 4, 1);
    g.add_edge(6, 7, 2);

    auto ans = vector<int>({ 11, 11, 0, 11, 0, 0, 10, 0 });

    EXPECT_EQ(ans, g.calc());
}

namespace subtree_max {
using S = int;
using M = pair<int, int>;
using R = int;
using C = int;

M merge(M a, M b, int u) {
    return make_pair(a.first + b.first, max(a.second, b.second));
}

M introduce(M m, S s, C c, int u, int v) {
    return make_pair(m.first + s, max(m.second, s));
}

M em() {
    return make_pair(0, 0);
}

R result(M m, int u) {
    return m.second;
}

S subtree(M m, int u) {
    return m.first + 1;
}

using dp = aclext::Rerooting<S, M, R, C, merge, introduce, em, result, subtree>;
}

TEST(RerootingTest, SubtreeMax) {
    subtree_max::dp dp(10);
    dp.add_edge(0, 1);
    dp.add_edge(0, 2);
    dp.add_edge(1, 3);
    dp.add_edge(1, 4);
    dp.add_edge(2, 7);
    dp.add_edge(2, 8);
    dp.add_edge(2, 9);
    dp.add_edge(4, 5);
    dp.add_edge(4, 6);

    auto ans = vector({ 5, 5, 6, 9, 7, 9, 9, 9, 9, 9 });

    EXPECT_EQ(ans, dp.calc());
}