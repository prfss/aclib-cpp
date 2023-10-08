/// @file
/// @brief 組合わせの総数@f$\binom{x}{y}@f$を求めます
#pragma once

#include "atcoder/modint.hpp"
#include <cassert>
#include <vector>

using namespace std;

namespace aclext {
// <---
// name: Combination
/// @brief 組合わせの総数を計算するクラスです
/// @details 計算にあたって@f$\bmod m@f$を取ります.
template <int mod>
struct Comb {
    using M = atcoder::static_modint<mod>;
    int n;
    vector<M> fact, inv;

    /// @f$x@f$の最大値を@f$n@f$とします.
    /// ### 制約
    /// - @f$\gcd(n!,m) = 1@f$
    Comb(int n) :
        n(n), fact(n + 1, 0), inv(n + 1, 0) {
        assert(n < M::mod());
        fact[0] = 1;
        for (int i = 1; i <= n; i++) fact[i] = fact[i - 1] * i;
        inv[n] = fact[n].inv();
        for (int i = n; i >= 1; i--) inv[i - 1] = inv[i] * i;
    }

    /// @f$\binom{x}{y}@f$を@f$m@f$で割った余りを返します.
    /// ### 制約
    /// - @f$0 \le y \le x \le n@f$
    M operator()(int x, int y) const {
        assert(x <= n and y <= x and y >= 0);
        return fact[x] * inv[x - y] * inv[y];
    }
};
// --->
}