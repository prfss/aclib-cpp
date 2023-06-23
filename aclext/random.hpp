#pragma once

#include <cassert>
#include <cfloat>
#include <cmath>
#include <random>
#include <type_traits>

using namespace std;

namespace aclext {
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

template <typename R>
inline bool rand_bool(double p, R& rng) {
    assert(0.0 <= p and p <= 1.0);
    static auto dist = uniform_real_distribution<double>(0.0, 1.0);
    return dist(rng) < p;
}
}