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
        while (pl < l) cur = shrink(cur, pl), pl++;
        while (l < pl) pl--, cur = extend(cur, pl);
        while (pr < r) pr++, cur = extend(cur, pr);
        while (r < pr) cur = shrink(cur, pr), pr--;
        ans[i] = cur;
    }

    return ans;
}
// --->
}