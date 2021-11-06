#pragma once

#include "atcoder/segtree"
#include <cassert>
#include <vector>

using namespace std;

namespace aclext {
namespace lca_inner {
    const int MAX_N = 100'000'000;
    pair<int, int> min(pair<int, int> x, pair<int, int> y) {
        return std::min(x, y);
    }

    pair<int, int> empty() {
        return { MAX_N, 0 };
    }
}

class Lca {
    int n;
    vector<int> id, vis, depth;
    vector<bool> is_root;
    bool ok = true;
    vector<vector<int>> g;

    atcoder::segtree<pair<int, int>, lca_inner::min, lca_inner::empty> st;

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
                // 異なる木に所属する節点が指定された場合-1を返す
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

        vector<pair<int, int>> l;
        for (size_t i = 0; i < vis.size(); i++) {
            l.emplace_back(depth[i], vis[i]);
        }

        st = decltype(st)(l);

        ok = true;
    }

public:
    Lca(int n)
        : n(n), id(n), is_root(n, true), g(n) {
        assert(1 <= n and n <= lca_inner::MAX_N);
    }

    int operator()(int u, int v) {
        assert(0 <= u and u < n);
        assert(0 <= v and v < n);

        init();

        u = id[u];
        v = id[v];
        if (u > v) swap(u, v);

        return st.prod(u, v + 1).second;
    }

    void add_edge(int u, int v) {
        assert(0 <= u and u < n);
        assert(0 <= v and v < n);

        ok = false;
        is_root[v] = false;
        g[u].push_back(v);
    }
};
}