#pragma once

#include "atcoder/math"
#include <cassert>
#include <vector>

using namespace std;

namespace aclext {
template <int mod>
struct Comb {
    int n;
    vector<long long> fact, inv;

    Comb(int n)
        : n(n), fact(n + 1, 0), inv(n + 1, 0) {
        assert(n < mod);
        fact[0] = 1;
        for (int i = 1; i <= n; i++) fact[i] = fact[i - 1] * i % mod;
        inv[n] = atcoder::pow_mod(fact[n], mod - 2, mod);
        for (int i = n; i >= 1; i--) inv[i - 1] = inv[i] * i % mod;
    }

    long long operator()(int m, int k) {
        assert(!(m > n || m < k || k < 0));
        return fact[m] * inv[m - k] % mod * inv[k] % mod;
    }
};
}