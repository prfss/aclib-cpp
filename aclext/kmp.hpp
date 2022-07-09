#pragma once

#include <cassert>
#include <string>
#include <vector>

using namespace std;

namespace aclext {
// <---
// name: Prefix Function
vector<int> prefix_function(const string& s) {
    vector<int> p(s.size());
    size_t i = 1;
    size_t j = 0;
    while (i < s.size()) {
        if (s[j] == s[i]) {
            p[i] = j + 1;
            j++;
            i++;
        } else if (j > 0) {
            j = p[j - 1];
        } else {
            i++;
        }
    }
    return p;
}
// --->

// <---
// name: Knuth-Morris-Pratt (KMP) algorithm
vector<int> kmp_search(const string& s, const string& pattern) {
    assert(1 <= pattern.size());
    vector<int> pos;
    auto p = prefix_function(pattern);

    size_t i = 0;
    size_t j = 0;
    while (i < s.size()) {
        if (j < pattern.size() and s[i] == pattern[j]) {
            i++;
            j++;
        } else if (j > 0) {
            j = p[j - 1];
        } else {
            i++;
        }

        if (j == pattern.size()) {
            pos.push_back(i - pattern.size());
        }
    }

    return pos;
}
// --->
}