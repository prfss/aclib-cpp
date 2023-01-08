#pragma once

namespace aclext {
// <---
// name: next LE
template <typename T, typename S>
T next_le(S& s, T v, T def) {
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
// name: next GE
template <typename T, typename S>
T next_ge(S& s, T v, T def) {
    auto it = s.lower_bound(v);
    if (it == s.end()) {
        return def;
    } else {
        return *it;
    }
}
// --->
}
