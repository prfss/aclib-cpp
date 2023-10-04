/// @file
/// @brief 組み合わせの総数@f$\binom{x}{y}@f$を計算します
#pragma once

#include "atcoder/modint.hpp"
#include <cassert>
#include <vector>

using namespace std;

namespace aclext {
// <---
// name: Combination
/// @brief 組み合わせの総数を計算するクラスです
/// @details 計算にあたって@f$\bmod m@f$を取ります.
/// ### 制約
/// - @f$m@f$は素数
template <int mod>
struct Comb {
    using M = atcoder::static_modint<mod>;
    int n;
    vector<M> fact, inv;

    /// @f$x@f$の最大値を@f$n@f$とします.
    /// ### 制約
    /// - @f$n \lt m@f$
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
    M operator()(int m, int k) {
        assert(!(m > n || m < k || k < 0));
        return fact[m] * inv[m - k] * inv[k];
    }
};
// --->
}