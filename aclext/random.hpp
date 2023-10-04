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
/// 区間@f$[l,r)@f$から一様に数を選んで返します.
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
}