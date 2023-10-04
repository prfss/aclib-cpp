/// @file
/// @brief 中央値を動的に求めます
#pragma once

#include <cassert>
#include <set>

using namespace std;

namespace aclext {
// <---
// name: Median
/// @brief 中央値を動的に求めるクラスです
/// @details
/// 中央値は要素数を@f$k@f$とするとき,@f$\mathrm{op}(k,x,y)@f$で定義します. ただし
/// @f[
///    x =
///    \begin{cases}
///   0 & (k = 0) \\
///    \frac{k+1}{2}\text{番目の値} & (k\text{が奇数}) \\
///    \frac{k}{2}\text{番目の値} & (k\text{が偶数})
///    \end{cases}
/// @f]
/// @f[
///    y =
///    \begin{cases}
///    0 & (k = 0) \\
///    \frac{k+1}{2}\text{番目の値} & (k\text{が奇数}) \\
///    \frac{k}{2}+1\text{番目の値} & (k\text{が偶数})
///   \end{cases}
/// @f]
/// です.

/// ### 制約
/// - 格納される要素数は@f$10^9@f$個以下
template <typename A, typename B, B (*op)(int, A, A)>
class Median {
    multiset<A> suf;
    multiset<A, greater<A>> pre;

    void balance() {
        while (suf.size() > pre.size()) {
            auto it = suf.begin();
            pre.insert(*it);
            suf.erase(it);
        }

        while (pre.size() > suf.size() + 1) {
            auto it = pre.begin();
            suf.insert(*it);
            pre.erase(it);
        }

        assert(pre.size() == suf.size() or pre.size() == suf.size() + 1);
    }

public:
    /// 要素数を返します.
    int size() {
        return suf.size() + pre.size();
    }

    /// 中央値を返します.
    B operator()() {
        int k = size();
        if (k == 0) {
            return op(0, 0, 0);
        } else if (k % 2 == 1) {
            return op(k, *pre.begin(), *pre.begin());
        } else {
            return op(k, *pre.begin(), *suf.begin());
        }
    }

    /// 数@f$x@f$を追加します.
    void insert(A x) {
        if (!suf.empty() and *suf.begin() <= x) {
            suf.insert(x);
        } else if (!pre.empty() and *pre.begin() >= x) {
            pre.insert(x);
        } else {
            suf.insert(x);
        }

        balance();
    }

    /// 数@f$x@f$が存在すれば,一つ削除します.
    void erase(A x) {
        auto it = suf.find(x);
        if (it != suf.end()) {
            suf.erase(it);
        } else {
            auto it = pre.find(x);
            if (it != pre.end()) {
                pre.erase(it);
            }
        }

        balance();
    }
};
// --->
}