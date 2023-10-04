/// @file
/// @brief 重み付き乱択を行います
#pragma once

#include "random.hpp"
#include <random>
#include <vector>

using namespace std;

namespace aclext {
// <---
// name: Weighted Index
template <typename T>
class WeightedIndex {
private:
    const size_t n;
    vector<T> cumulative_weight;

public:
    /// 重みを`weigths`として初期化します.
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