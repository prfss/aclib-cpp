/// @file
/// @brief Mo's algorithmの実装です
/// @details
/// [Verification](verifications/mo.md)
#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <math.h>
#include <numeric>
#include <tuple>
#include <vector>

using namespace std;

namespace aclext {
// <---
// name: Mo's Algorithm
/// 区間クエリのリスト @f$\mathrm{query} = \{[l_1,r_1], [l_2,r_2], \dots ,[l_q, r_q]\}@f$ に対し, 答えのリスト @f$\{\mathit{ans}(l_1,r_1),\mathit{ans}(l_2,r_2), \dots ,\mathit{ans}(l_q,r_q)\}@f$
/// を返します. ただし @f$n = \max_{{i \in [1,q]}} r_i@f$ とするとき
/// - @f$\mathrm{extend}(\mathrm{init},0) = ans(0,0)@f$
/// - @f$0 \lt l \le r \le n@f$ のとき, @f$\mathrm{extend}(\mathit{ans}(l,r),l-1) = \mathit{ans}(l-1,r)@f$
/// - @f$0 \le l \lt r \le n@f$ のとき, @f$\mathrm{shrink}(\mathit{ans}(l,r),l) = \mathit{ans}(l+1,r)@f$
/// - @f$0 \le l \le r \lt n@f$ のとき, @f$\mathrm{extend}(\mathit{ans}(l,r),r+1) = \mathit{ans}(l,r+1)@f$
/// - @f$0 \le l \lt r \le n@f$ のとき, @f$\mathrm{shrink}(\mathit{ans}(l,r),r) = \mathit{ans}(l,r-1)@f$
/// @n
/// を満たす必要があります.
/// ### 制約
/// - @f$0 \le l_i \le r_i@f$
template <typename T>
vector<T> mo(const vector<pair<int, int>> query, function<T(T, int)> extend, function<T(T, int)> shrink, T init) {
    const size_t q = query.size();
    assert(1 <= q);
    int n = 0;
    for (auto [x, y] : query) {
        assert(x >= 0 and x <= y);
        n = max(y, n);
    }

    const int h = max(1, int(n / sqrt(q)));

    vector<int> idx(q);
    iota(idx.begin(), idx.end(), 0);
    sort(idx.begin(), idx.end(), [&](int i, int j) {
        return make_pair(query[i].first / h, query[i].second) < make_pair(query[j].first / h, query[j].second);
    });

    T cur = init;
    vector<T> ans(q);
    int pl = 0, pr = -1;
    for (auto i : idx) {
        auto [l, r] = query[i];
        while (l < pl) pl--, cur = extend(cur, pl);
        while (pr < r) pr++, cur = extend(cur, pr);
        while (pl < l) cur = shrink(cur, pl), pl++;
        while (r < pr) cur = shrink(cur, pr), pr--;
        ans[i] = cur;
    }

    return ans;
}
// --->
}