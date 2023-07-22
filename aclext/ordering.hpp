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
    operator bool() const {
        return x < y;
    }
    Ordering then(const T other_x, const T other_y) const {
        if (x == y)
            return Ordering { other_x, other_y };
        else
            return *this;
    }
};
// --->
}