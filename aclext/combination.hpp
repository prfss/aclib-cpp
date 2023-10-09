/// @file
/// @brief 組合わせの総数@f$\binom{x}{y}@f$を求めます
#pragma once

#include "number_theory.hpp"
#include <cassert>
#include <vector>

using namespace std;

// <---
// name: Combination
/// @brief 組合わせの総数を計算するクラスです
/// @details 計算にあたって@f$\bmod m@f$を取ります.
struct DynamicComb {
    const int n;
    const int m;
    vector<long long> fact, inv;

    /// @f$x@f$の最大値を@f$n@f$とします.
    /// ### 制約
    /// - @f$\gcd(n!,m) = 1@f$
    DynamicComb(int n, int m) :
        n(n), m(m), fact(n + 1, 0), inv(n + 1, 0) {

        fact[0] = 1;
        for (int i = 1; i <= n; i++) fact[i] = (fact[i - 1] * i) % m;
        const auto [g, x, y] = extgcd(fact[n], (long long)m);
        inv[n] = (x + m) % m;
        for (int i = n; i >= 1; i--) inv[i - 1] = (inv[i] * i) % m;
    }

    /// @f$\binom{x}{y}@f$を@f$m@f$で割った余りを返します.
    /// ### 制約
    /// - @f$0 \le y \le x \le n@f$
    int operator()(int x, int y) const {
        assert(x <= n and y <= x and y >= 0);
        return fact[x] * inv[x - y] % m * inv[y] % m;
    }
};

/// modをコンパイル時定数として組合わせの総数を計算するクラスです
template <int Mod>
struct Comb : public DynamicComb {
    Comb(int n) :
        DynamicComb(n, Mod) {
    }
};
// --->