/// @file
/// @brief 有向木の最小共通祖先(Lowest Common Ancestor)を求めます
/// @details
/// [Verification](verifications/lca.md)
#pragma once

#include <cassert>
#include <functional>
#include <iostream>
#include <vector>

using namespace std;

namespace aclext {
// <---
// name: Lowest Common Ancestor
/// @brief LCAを計算するクラスです
class Lca {
    const int n;
    const int log_max_k;
    vector<vector<int>> par;
    vector<vector<int>> g;
    vector<int> depth;
    bool ok = false;

    static int next_log2(const long long x) {
        long long y = 1;
        int e = 0;
        while (y < x) y <<= 1, e++;
        return e;
    }

    void dfs(int u, int d, int p) {
        if (depth[u] >= 0) return;
        par[0][u] = p;
        depth[u] = d;
        for (const auto& v : g[u]) {
            dfs(v, d + 1, u);
        }
    }

    void init() {
        if (ok) return;
        ok = true;

        fill(depth.begin(), depth.end(), -1);

        for (int u = 0; u < n; u++) {
            dfs(u, 0, n);
        }

        for (int k = 0; k < log_max_k; k++) {
            for (int u = 0; u <= n; u++) {
                par[k + 1][u] = par[k][par[k][u]];
            }
        }
    }

public:
    /// @brief @f$n@f$頂点@f$0@f$辺の有向グラフを作ります
    /// ### 制約
    /// @f$1 \le n \le 10^9@f$
    Lca(int n) :
        n(n), log_max_k(next_log2(n)), par(log_max_k + 1, vector<int>(n + 1)), g(n), depth(n) { }

    /// @brief 頂点@f$u@f$と頂点@f$v@f$の最小共通祖先を返します
    /// @details
    /// @f$u@f$と@f$v@f$が互いに異なる木に所属する場合は@f$-1@f$を返します.
    /// ### 制約
    /// - @f$0 \le u,v \lt n@f$
    /// - このグラフは森である
    int operator()(int u, int v) {
        assert(0 <= u and u < n);
        assert(0 <= v and v < n);

        init();

        if (depth[u] > depth[v]) swap(u, v);
        for (int k = 0; k <= log_max_k; k++) {
            if ((((depth[v] - depth[u]) >> k) & 1) == 1) {
                v = par[k][v];
            }
        }
        if (u == v) return u;

        for (int k = log_max_k; k >= 0; k--) {
            if (par[k][u] != par[k][v]) {
                u = par[k][u];
                v = par[k][v];
            }
        }
        return par[0][v] == n ? -1 : par[0][v];
    }

    /// @brief 頂点@f$u@f$から頂点@f$v@f$への辺を追加します
    /// @details
    /// ### 制約
    /// - @f$0 \le u,v \lt n@f$
    void add_edge(int u, int v) {
        assert(0 <= u and u < n);
        assert(0 <= v and v < n);
        ok = false;
        g[u].push_back(v);
    }
};
// --->
}