/// @file
/// @brief 確率的な選択を行う関数です
/// @details
/// 以下で,`rng`は[乱数エンジン](https://ja.cppreference.com/w/cpp/numeric/random#.E4.B9.B1.E6.95.B0.E3.82.A8.E3.83.B3.E3.82.B8.E3.83.B3)です.
#pragma once

#include <cassert>
#include <cfloat>
#include <cmath>
#include <random>
#include <vector>

using namespace std;

// <---
// name: Weighted Index
/// @brief 重み付き乱択を行います
template <typename T>
class WeightedIndex {
private:
    const size_t n;
    vector<double> cumulative_weight;

public:
    /// 重みを`weights`として初期化します.
    /// ### 制約
    /// - @f$0 \le \mathrm{weights[i]} \ (0 \le i \lt \mathrm{weights.size()})@f$
    /// - @f$0 \lt \sum_{i} \mathrm{weights[i]} \lt \mathrm{DBL\_MAX}@f$
    WeightedIndex(const vector<T>& weights) :
        n(weights.size()) {
        assert(weights.size() > 0);
        cumulative_weight.resize(n);
        partial_sum(weights.begin(), weights.end(), cumulative_weight.begin(), [](double a, T b) { return a + b; });
        assert(cumulative_weight.back() > 0);
    }

    size_t size() const {
        return n;
    }

    /// インデックスを重みに比例する確率で選択して返します.
    /// `rng`は[乱数エンジン](https://ja.cppreference.com/w/cpp/numeric/random#.E4.B9.B1.E6.95.B0.E3.82.A8.E3.83.B3.E3.82.B8.E3.83.B3)です.
    template <typename R>
    size_t operator()(R& rng) const {
        auto dist = uniform_real_distribution<double>(0.0, cumulative_weight.back());
        double x = dist(rng);
        long long l = -1, r = n - 1;
        while (r - l > 1) {
            auto m = (l + r) / 2;
            double v = cumulative_weight[m];
            if (x >= v)
                l = m;
            else
                r = m;
        }
        return (size_t)r;
    }
};
// --->