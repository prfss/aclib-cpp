/// @file
/// @brief きたまさ法により線形漸化式の項を求めます
/// @details
/// [Verification](verifications/kitamasa.md)
#pragma once

#include <cassert>
#include <cstdio>
#include <functional>
#include <vector>

using namespace std;

// <---
// name: Kitamasa
/// 漸化式の係数@f$\mathrm{coefficients} = \{ c_0, c_1, ..., c_{k-1} \}@f$と初期値@f$\mathrm{init} = \{a_0,a_1,...,a_{k-1}\}@f$から
/// @f$k@f$階線形漸化式@f$a_n = a_{n-1} \cdot c_{k-1} + a_{n-2} \cdot c_{k-1} + \dots +a_{n-k} \cdot c_0@f$の第@f$n@f$項を求めます.
/// ### 制約
/// - @f$\mathrm{add}(x, \mathrm{zero}()) = \mathrm{add}(\mathrm{zero}(), x) = x@f$
/// - @f$\mathrm{mul}(x, \mathrm{one}()) = \mathrm{mul}(\mathrm{one}(), x) = x@f$
/// - @f$n \ge 0@f$
template <typename S>
S kitamasa(const vector<S>& coefficients, function<S(S, S)> add, function<S()> zero, function<S(S, S)> mul, function<S()> one, const vector<S>& init, long long n) {
    assert(coefficients.size() == init.size());
    size_t k = coefficients.size();

    function<vector<S>(const vector<S>&)> next_coefficients = [&](const vector<S>& cur) {
        vector<S> res(k);
        for (size_t i = 0; i < k; ++i) {
            res[i] = mul(coefficients[i], cur[k - 1]);
            if (i > 0) res[i] = add(res[i], cur[i - 1]);
        }

        return res;
    };

    function<vector<S>(const vector<S>&)> double_coefficients = [&](const vector<S>& coefficients) {
        vector<vector<S>> temp = { coefficients };
        for (size_t i = 1; i < k; i++) {
            temp.push_back(next_coefficients(temp.back()));
        }
        vector<S> dbl(k);
        for (size_t i = 0; i < k; i++) {
            for (size_t j = 0; j < k; j++) {
                dbl[j] = add(dbl[j], mul(temp[0][i], temp[i][j]));
            }
        }

        return dbl;
    };

    function<vector<S>(long long)> calc_coefficients = [&](long long n) {
        if (n < (long long)k) {
            vector<S> res(k);
            res[n] = one();
            return res;
        }
        auto co = double_coefficients(calc_coefficients(n / 2));
        if ((n & 1LL) != 0LL) {
            co = next_coefficients(co);
        }
        return co;
    };

    auto co = calc_coefficients(n);

    S res = zero();
    for (size_t i = 0; i < k; i++) {
        res = add(res, mul(co[i], init[i]));
    }
    return res;
}
// --->