/// @file
namespace aclext {
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
    Ordering then(const T other_x, const T other_y) const {
        if (x == y)
            return Ordering { other_x, other_y };
        else
            return *this;
    }
};
// --->
}