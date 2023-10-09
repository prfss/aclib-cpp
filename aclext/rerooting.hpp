/// @file
/// @brief 全方位木DPをおこないます
/// @details [Verifications](verifications/rerooting.md)
#pragma once

#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

// <---
// name: Rerooting
/// @brief 全方位木DPをおこなうためのクラスです
/// @details
/// @f$S@f$は部分木が親に返す値の型,@f$M@f$はマージを表現する型, @f$R@f$は解の型, @f$C@f$はコストの型です.
/// @n
/// @f$u@f$を根とした時の解は
/// @f[\mathrm{result}(\mathit{reduce}(f, \mathrm{em}(), \mathit{neighbor}(u)), u)@f]
/// で定めます.
/// また@f$u@f$から親頂点@f$p@f$に返す値は
/// @f[\mathrm{subtree}(\mathit{reduce}(f, \mathrm{em}(), \mathit{neighbor}(u) \setminus \{p\}), u)@f]
/// で定めますが, これは
/// @f[\mathrm{subtree}(\mathrm{merge}(\mathit{reduce}(f,\mathrm{em}(),L), \mathit{reduce}(f,\mathrm{em}(),R), u))@f]
/// と一致する必要があります.
/// ただし,
/// - @f$\mathit{neighbor}(u)@f$は@f$u@f$の隣接頂点の全体
/// - @f$(x,v) = \mathrm{introduce}(x, \mathit{dp}[v], \mathit{cost}(u,v), u, v)@f$
///   - @f$dp[v]@f$は子頂点 @f$v@f$ から親頂点 @f$u@f$ に返す値
/// - @f$reduce: (M \times \mathit{int} \to M) \times M \times (\mathit{Set\:of\:int}) \to M@f$は[重畳関数](https://ja.wikipedia.org/wiki/%E9%AB%98%E9%9A%8E%E9%96%A2%E6%95%B0#fold)
/// - @f$(L \cap R = \emptyset) \land (L \cup R = \mathit{neighbor}(u) \setminus \{p\})@f$
///
/// です.
template <typename S, typename M, typename R, typename C, M (*merge)(M, M, int), M (*introduce)(M, S, C, int, int), M (*em)(), R (*result)(M, int), S (*subtree)(M, int)>
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
    Rerooting(int n) :
        n(n), g(n), ans(n) { }

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