#pragma once

#include "random.hpp"
#include <random>
#include <vector>

using namespace std;

namespace aclext {

template <typename T>
class WeightedIndex {
private:
    const size_t n;
    vector<T> cumulative_weight;

public:
    WeightedIndex(const vector<T>& weights) :
        n(weights.size()) {
        assert(weights.size() > 0);
        cumulative_weight.resize(n);
        partial_sum(weights.begin(), weights.end(), cumulative_weight.begin());
        assert(cumulative_weight.back() > 0);
    }

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
}