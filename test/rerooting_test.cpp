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

namespace ABC223F {
vector<long long> d;

using S = long long;
using M = long long;
using R = long long;
using C = long long;
M e() {
    return 0;
}

M merge(M a, M b, int i) {
    return max(a, b);
}

M introduce(M a, S b, C c, int u, int v) {
    return max(a, b + c);
}

S subtree(M r, int u) {
    return max(r, d[u]);
}

R result(S r, int u) {
    return r;
}

using dp = aclext::Rerooting<S, M, R, C, merge, introduce, e, result, subtree>;

}

TEST(RerootingTest, ABC223F) {
    ABC223F::d = { 9, 2, 6, 5, 3, 100 };

    ABC223F::dp g(6);
    g.add_edge(0, 1, 3);
    g.add_edge(0, 2, 1);
    g.add_edge(0, 3, 4);
    g.add_edge(0, 4, 1);
    g.add_edge(0, 5, 5);

    vector<long long> ans = { 105, 108, 106, 109, 106, 14 };

    EXPECT_EQ(ans, g.calc());
}