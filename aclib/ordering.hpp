/// @file
#pragma once

// <---
// name: Ordering
template <typename T>
class Ordering {
    T x;
    T y;

public:
    Ordering(T x, T y) :
        x(x), y(y) { }
    /// @f$x \lt y@f$の時,`true`,それ以外の時`false`を返します.
    operator bool() const {
        return x < y;
    }
    /// @f$x = y@f$の時,`Ordering(other_x,other_y)`,それ以外の時`*this`を返す.
    template <typename U>
    Ordering then(const U other_x, const U other_y) const {
        if (x == y)
            return Ordering { other_x, other_y };
        else
            return *this;
    }
};
// --->