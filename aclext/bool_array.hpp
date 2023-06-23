#include <limits.h>
#include <vector>

using namespace std;

namespace aclext {
class BoolArray;
struct BoolArrayElemProxy {
    size_t idx;
    BoolArray& ba;
    BoolArrayElemProxy& operator=(const bool b);
    operator bool() const;
};
class BoolArray {
private:
    long long threshold;
    vector<long long> data;

public:
    BoolArray(size_t n) :
        threshold(1), data(n) {
    }

    bool operator[](size_t i) const {
        return data[i] == threshold;
    }

    BoolArrayElemProxy operator[](size_t i) {
        return { i, *this };
    }

    size_t size() const {
        return data.size();
    }

    void reset() {
        threshold++;
    }

    friend BoolArrayElemProxy;
};

BoolArrayElemProxy& BoolArrayElemProxy::operator=(const bool b) {
    ba.data[idx] = b ? ba.threshold : 0;
    return *this;
}
BoolArrayElemProxy::operator bool() const {
    return ba.data[idx] == ba.threshold;
}
}