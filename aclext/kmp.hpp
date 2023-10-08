/// @file
/// @brief Knuth-Morris-Pratt法の実装です
/// @details
/// [Verification](verifications/kmp.md)
#pragma once

#include <cassert>
#include <string>
#include <vector>

using namespace std;

namespace aclext {
// <---
// name: Prefix Function
/// 文字列`s`のprefix function, すなわち以下のように定義される長さが`s.size()`の配列\f$\pi\f$を返します.
/// @f[ \pi = \max_{k \in [0,i]} \{k \mid \mathrm{s.substr(0,k)} = \mathrm{s.substr(i-(k-1),k)} \}@f]
/// 言い換えると, @f$\pi_i@f$は@f$\mathrm{s}@f$の接頭辞@f$t = \mathrm{s.substr(0,i+1)}@f$に対して,
/// @f$\mathrm{t}@f$の接頭辞かつ接尾辞であり, @f$\mathrm{t}@f$とは異なるような文字列のうち最長のものの長さです.
/// 特に@f$\pi_0 = 0@f$です.
/// ### 制約
/// - @f$0 \le \mathrm{s.size()} \lt 10^9@f$
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
/// 文字列`s`におけるパターン`pattern`の出現位置を返します.
/// ### 制約
/// - @f$0 \le \mathrm{s.size()} \lt 10^9@f$
/// - @f$0 \le \mathrm{pattern.size()} \lt 10^9@f$
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