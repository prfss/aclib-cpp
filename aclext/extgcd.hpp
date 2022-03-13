#include <tuple>

using namespace std;

namespace aclext {
template <typename T>
tuple<T, T, T> extgcd(T a, T b) {
    if (b == 0) {
        return make_tuple(a, 1, 0);
    } else {
        auto [g, x, y] = extgcd(b, a % b);
        return make_tuple(g, y, x - a / b * y);
    }
}
}