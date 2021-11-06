#pragma once

#include "atcoder/string"
#include <vector>

using namespace std;

namespace aclext {
string bwt(const string& s, const vector<int>& sa) {
    string res;

    const size_t n = s.size();

    for (size_t i = 0; i < n; i++) {
        res.push_back(s[(sa[i] - 1 + n) % n]);
    }

    return res;
}

string bwt(const string& s) {
    return bwt(s, atcoder::suffix_array(s));
}
}