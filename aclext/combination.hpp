#pragma once

#include "atcoder/modint.hpp"
#include <cassert>
#include <vector>

using namespace std;

namespace aclext {
// <---
// name: Combination
template <int mod>
struct Comb {
    using M = atcoder::static_modint<mod>;
    int n;
    vector<M> fact, inv;

    Comb(int n)
        : n(n), fact(n + 1, 0), inv(n + 1, 0) {
        assert(n < M::mod());
        fact[0] = 1;
        for (int i = 1; i <= n; i++) fact[i] = fact[i - 1] * i;
        inv[n] = fact[n].inv();
        for (int i = n; i >= 1; i--) inv[i - 1] = inv[i] * i;
    }

    M operator()(int m, int k) {
        assert(!(m > n || m < k || k < 0));
        return fact[m] * inv[m - k] * inv[k];
    }
};
// --->
}