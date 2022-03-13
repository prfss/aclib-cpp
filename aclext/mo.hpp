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
template <typename T>
vector<int> mo(const vector<pair<int, int>> query, function<void(int)> extend, function<void(int)> shrink, function<T()> val) {
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

    vector<T> ans(q);
    int pl = 0, pr = -1;
    for (auto i : idx) {
        auto [l, r] = query[i];
        while (pl < l) shrink(pl), pl++;
        while (l < pl) pl--, extend(pl);
        while (pr < r) pr++, extend(pr);
        while (r < pr) shrink(pr), pr--;
        ans[i] = val();
    }

    return ans;
}
}