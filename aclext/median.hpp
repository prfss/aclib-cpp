#pragma once

#include <cassert>
#include <set>

using namespace std;

namespace aclext {
// <---
// name: Median
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
    int size() {
        return suf.size() + pre.size();
    }

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