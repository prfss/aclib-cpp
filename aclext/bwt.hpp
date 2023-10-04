/// @file
/// @brief [Burrows-Wheeler変換](https://ja.wikipedia.org/wiki/%E3%83%96%E3%83%AD%E3%83%83%E3%82%AF%E3%82%BD%E3%83%BC%E3%83%88)を求めます
#pragma once

#include "atcoder/string"
#include <vector>

using namespace std;

namespace aclext {
// <---
// name: Burrows-Wheeler Transform
/// 文字列`s`とその接尾辞配列`sa`からBurrows-Wheeler変換を計算します.
/// ### 制約
/// `sa`は`s`の接尾辞配列(AtCoder Libraryと同仕様)
string bwt(const string& s, const vector<int>& sa) {
    string res;

    const size_t n = s.size();

    for (size_t i = 0; i < n; i++) {
        res.push_back(s[(sa[i] - 1 + n) % n]);
    }

    return res;
}

/// 文字列`s`からBurrows-Wheeler変換を計算します.
string bwt(const string& s) {
    return bwt(s, atcoder::suffix_array(s));
}
// --->
}