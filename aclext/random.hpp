/// @file
/// @brief 確率的な選択を行う関数を提供します
/// @details
/// 以下で,`rng`は[乱数エンジン](https://ja.cppreference.com/w/cpp/numeric/random#.E4.B9.B1.E6.95.B0.E3.82.A8.E3.83.B3.E3.82.B8.E3.83.B3)です.
#pragma once

#include <cassert>
#include <cfloat>
#include <cmath>
#include <random>
#include <type_traits>

using namespace std;

namespace aclext {
// <---
// name: rand range
/// 整数区間@f$[l,r)@f$から一様に数を選んで返します.
/// ### 制約
/// - @f$l \lt r@f$
template <typename T, typename R>
inline typename enable_if<is_integral<T>::value, T>::type rand_range(T l, T r, R& rng) {
    assert(l < r);
    return uniform_int_distribution<T>(l, r - 1)(rng);
}

template <typename T, typename R>
inline typename enable_if<is_floating_point<T>::value, T>::type rand_range(T l, T r, R& rng) {
    assert(l <= r);
    return uniform_real_distribution<double>(l, r)(rng);
}
// --->

// <---
// name: rand bool
/// @f$p@f$の確率で`true`を,@f$1 - p@f$の確率で`false`を返します.
/// ### 制約
/// - @f$0 \le p \le 1@f$
template <typename R>
inline bool rand_bool(double p, R& rng) {
    assert(0.0 <= p and p <= 1.0);
    static auto dist = uniform_real_distribution<double>(0.0, 1.0);
    return dist(rng) < p;
}
// --->

// <---
// name: Weighted Index
/// @brief 重み付き乱択を行います
template <typename T>
class WeightedIndex {
private:
    const size_t n;
    vector<T> cumulative_weight;

public:
    /// 重みを`weights`として初期化します.
    /// ### 制約
    /// - @f$0 \le \mathrm{weights[i]} (0 \le i \lt \mathrm{weights.size()})@f$
    /// - @f$0 \lt \sum_{i} \mathrm{weights[i]} \le Tの最大値@f$
    WeightedIndex(const vector<T>& weights) :
        n(weights.size()) {
        assert(weights.size() > 0);
        cumulative_weight.resize(n);
        partial_sum(weights.begin(), weights.end(), cumulative_weight.begin());
        assert(cumulative_weight.back() > 0);
    }

    /// インデックスを重みに比例する確率で選択して返します.
    /// `rng`は[乱数エンジン](https://ja.cppreference.com/w/cpp/numeric/random#.E4.B9.B1.E6.95.B0.E3.82.A8.E3.83.B3.E3.82.B8.E3.83.B3)です.
    template <typename R>
    size_t operator()(R& rng) const {
        T x = rand_range<T>(T(0), cumulative_weight.back(), rng);

        long long l = -1, r = n - 1;
        while (r - l > 1) {
            auto m = (l + r) / 2;
            T v = cumulative_weight[m];
            if (x >= v)
                l = m;
            else
                r = m;
        }
        return (size_t)r;
    }
};
// --->
}