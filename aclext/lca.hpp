/// @file
/// @brief 有向木の最小共通祖先(Lowest Common Ancestor)を求めます
#pragma once

#include "atcoder/segtree"
#include <cassert>
#include <functional>
#include <vector>

using namespace std;

// <---
// name: Lowest Common Ancestor
namespace aclext {
using P = pair<int, int>;
namespace lca {
    const int MAX_N = 100'000'000;
    P min(P x, P y) {
        return std::min(x, y);
    }

    P empty() {
        return { MAX_N, 0 };
    }
}

/// @brief LCAを計算するクラスです
class Lca {
    int n;
    vector<int> id, vis, depth;
    vector<bool> is_root;
    bool ok = false;
    vector<vector<int>> g;

    atcoder::segtree<P, lca::min, lca::empty> st;

    void dfs(int u, int p, int d) {
        vis.push_back(u);
        depth.push_back(d);

        for (auto v : g[u]) {
            if (v == p) continue;
            dfs(v, u, d + 1);
            vis.push_back(u);
            depth.push_back(d);
        }
    }

    void init() {
        if (ok) return;
        vis.clear();
        depth.clear();
        for (int i = 0; i < n; i++) {
            if (is_root[i]) {
                dfs(i, -1, 0);
                // 異なる木に所属する頂点が指定された場合-1を返す
                vis.push_back(-1);
                depth.push_back(-1);
            }
        }

        fill(id.begin(), id.end(), -1);
        for (size_t i = 0; i < vis.size(); i++) {
            if (vis[i] >= 0 and id[vis[i]] < 0) {
                id[vis[i]] = i;
            }
        }

        vector<P> l;
        for (size_t i = 0; i < vis.size(); i++) {
            l.emplace_back(depth[i], vis[i]);
        }

        st = decltype(st)(l);

        ok = true;
    }

public:
    /// @f$n@f$頂点@f$0@f$辺の有向グラフを作ります.
    /// @subsection constraint 制約
    /// @f$1 \le n \le 10^8@f$
    Lca(int n) :
        n(n), id(n), is_root(n, true), g(n) {
        assert(1 <= n and n <= lca::MAX_N);
    }

    /// 頂点@f$u@f$と頂点@f$v@f$の最小共通祖先を返します.
    /// @f$u@f$と@f$v@f$が互いに異なる木に所属する場合は@f$-1@f$を返します.
    /// ### 制約
    /// - @f$0 \le u,v \lt n@f$
    /// - このグラフは森である
    int operator()(int u, int v) {
        assert(0 <= u and u < n);
        assert(0 <= v and v < n);

        init();

        u = id[u];
        v = id[v];
        if (u > v) swap(u, v);

        return st.prod(u, v + 1).second;
    }

    /// 頂点@f$u@f$から頂点@f$v@f$への辺を追加します.
    /// ### 制約
    /// - @f$0 \le u,v \lt n@f$
    void add_edge(int u, int v) {
        assert(0 <= u and u < n);
        assert(0 <= v and v < n);

        ok = false;
        is_root[v] = false;
        g[u].push_back(v);
    }
};
// --->
}