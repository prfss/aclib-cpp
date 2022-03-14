#pragma once

#include <cassert>
#include <deque>
#include <functional>

using namespace std;

namespace aclext {
// <---
// name: Monotonic Convex Hull Trick
template <typename T, typename compare = std::less<T>>
class MonotonicConvexHullTrick {
    deque<pair<T, T>> q;

    bool is_required(const T& a1, const T& b1, const T& a2, const T& b2, const T& a3, const T& b3) {
        return ((b2 - b1) * (a2 - a3) < (b3 - b2) * (a1 - a2));
    };

public:
    MonotonicConvexHullTrick() { }

    void add(const T& a, const T& b) {
        while (q.size() >= 2
            and !is_required(a, b, q[q.size() - 1].first, q[q.size() - 1].second, q[q.size() - 2].first, q[q.size() - 2].second)) {
            q.pop_back();
        }
        q.push_back(make_pair(a, b));
    }

    T operator()(const T& x) {
        assert(!q.empty());

        while (q.size() >= 2) {
            auto [a1, b1] = q[0];
            auto [a2, b2] = q[1];
            if (compare()(a1 * x + b1, a2 * x + b2)) {
                break;
            }
            q.pop_front();
        }

        auto [a, b] = q.front();
        return a * x + b;
    }
};
// --->
}