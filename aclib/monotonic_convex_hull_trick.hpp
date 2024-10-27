/// @file
#pragma once

#include <cassert>
#include <deque>
#include <functional>

using namespace std;

// <---
// name: Monotonic Convex Hull Trick
/// @brief 追加クエリおよび最小値/最大値クエリが単調な場合のConvex Hull Trickを実装したクラスです
/// @details
/// 一次関数の集合 @f$L = \{f_1,f_2, \dots ,f_n\}@f$ に対して,
/// 次の2つの処理を行うことができます.
/// -   関数 @f$a_i x + b_i@f$ の追加
/// -   与えられた @f$x@f$ に対し, 全ての @f$1 \le j \le n@f$ について,
///     @f$\mathrm{compare}(f_i(x),f_j(x)) \lor f_i(x) = f_j(x)@f$ を満たす
///     @f$f_i(x)@f$ の取得
///
/// 後者について特に `compare` が `std::less` の場合は最小値を,`std::greater` の場合は最大値を得ることができます.
/// ### 制約
/// -   `operator()` で与えられるクエリ @f$x_1,x_2, \dots ,x_m@f$ は単調
/// -   `add` で追加される直線の傾きが順に @f$a_1,a_2, \dots ,a_n@f$ であるとき,
///     全ての @f$1 \le i \lt n@f$ に対して
///     - @f$x_i@f$ が狭義単調増加する場合
///     @f[\begin{aligned}
///     \begin{cases}
///     a_i \le a_{i+1} & (\mathrm{compare} = \mathrm{std::greater}) \\
///     a_i \ge a_{i+1} & (\mathrm{compare} = \mathrm{std::less})
///     \end{cases}
///     \end{aligned}@f]
///     - @f$x_i@f$ が狭義単調減少する場合
///     @f[\begin{aligned}
///     \begin{cases}
///     a_i \ge a_{i+1} & (\mathrm{compare} = \mathrm{std::greater}) \\
///     a_i \le a_{i+1} & (\mathrm{compare} = \mathrm{std::less})
///     \end{cases}
///     \end{aligned}@f]
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