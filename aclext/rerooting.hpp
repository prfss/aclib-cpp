#pragma once

#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

namespace aclext {
// <---
// name: Rerooting
template <typename S, typename M, typename R, typename C,
    M (*merge)(M, M, int),
    M (*introduce)(M, S, C, int, int),
    M (*em)(),
    R (*result)(M, int),
    S (*subtree)(M, int)>
class Rerooting {
    int n;
    vector<vector<pair<int, C>>> g;
    vector<R> ans;
    vector<vector<S>> dp;

    S dfs1(int u, int p) {
        M s = em();

        int k = g[u].size();

        dp[u] = vector<S>(k);

        for (int i = 0; i < k; i++) {
            auto [v, c] = g[u][i];
            if (v == p) continue;
            dp[u][i] = dfs1(v, u);
            s = introduce(s, dp[u][i], c, u, v);
        }

        return subtree(s, u);
    }

    void dfs2(int u, S par, int p) {
        int k = g[u].size();
        for (int i = 0; i < k; i++) {
            auto [v, c] = g[u][i];
            if (v == p) {
                dp[u][i] = par;
            }
        }

        vector<M> dp_l(k + 1, em()), dp_r(k + 1, em());
        for (int i = 0; i < k; i++) {
            dp_l[i + 1] = introduce(dp_l[i], dp[u][i], g[u][i].second, u, g[u][i].first);
        }
        ans[u] = result(dp_l[k], u);

        for (int i = k - 1; i >= 0; i--) {
            dp_r[i] = introduce(dp_r[i + 1], dp[u][i], g[u][i].second, u, g[u][i].first);
        }

        for (int i = 0; i < k; i++) {
            auto [v, c] = g[u][i];

            if (v == p) continue;

            dfs2(v, subtree(merge(dp_l[i], dp_r[i + 1], u), u), u);
        }
    }

public:
    Rerooting(int n)
        : n(n), g(n), ans(n) { }

    void add_edge(int u, int v, C c = {}) {
        assert(0 <= u && u < n);
        assert(0 <= v && v < n);

        g[u].emplace_back(v, c);
        g[v].emplace_back(u, c);
    }

    vector<R> calc() {
        dp = vector<vector<S>>(n);
        dfs1(0, -1);
        dfs2(0, {}, -1);
        return ans;
    }
};
// --->
}