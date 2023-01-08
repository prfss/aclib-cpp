#pragma once

namespace aclext {
// <---
// name: find LE
template <typename T, typename S>
T find_le(S& s, T v, T def) {
    auto it = s.upper_bound(v);
    if (it == s.begin()) {
        return def;
    } else {
        it--;
        return *it;
    }
}
// --->

// <---
// name: find GE
template <typename T, typename S>
T find_ge(S& s, T v, T def) {
    auto it = s.lower_bound(v);
    if (it == s.end()) {
        return def;
    } else {
        return *it;
    }
}
// --->
}
