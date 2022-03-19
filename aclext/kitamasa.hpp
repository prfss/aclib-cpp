#pragma once

#include <cassert>
#include <cstdio>
#include <functional>
#include <vector>

using namespace std;

namespace aclext {
// <---
// name: Kitamasa
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
}