#pragma once

#include <cassert>
#include <cstdio>
#include <vector>

using namespace std;

namespace aclext {
// <---
// name: Kitamasa
template <typename S, S (*add)(S, S), S (*mul)(S, S), S (*zero)(), S (*one)()>
class Kitamasa {
    size_t k;
    vector<S> coefficients;

    vector<S> next_coefficients(const vector<S>& coefficients) {
        vector<S> res(k);
        for (size_t i = 0; i < k; ++i) {
            res[i] = mul(this->coefficients[i], coefficients[k - 1]);
            if (i > 0) res[i] = add(res[i], coefficients[i - 1]);
        }

        return res;
    }

    vector<S> double_coefficients(const vector<S>& coefficients) {
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
    }

    vector<S> calc_coefficients(long long n) {
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
    }

public:
    Kitamasa(const vector<S>& coefficients)
        : k(coefficients.size()), coefficients(coefficients) {
    }

    S calc(const vector<S>& init, long long n) {
        assert(init.size() == k);

        auto co = calc_coefficients(n);

        S res = zero();
        for (size_t i = 0; i < k; i++) {
            res = add(res, mul(co[i], init[i]));
        }
        return res;
    }
};
// --->
}