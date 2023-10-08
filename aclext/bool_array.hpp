/// @file
/// @brief リセット処理が高速な真偽値配列です
#pragma once

#include <limits.h>
#include <vector>

using namespace std;

// <---
// name: Bool Array
namespace aclext {
class BoolArray;
struct BoolArrayElemProxy {
    size_t idx;
    BoolArray& ba;
    BoolArrayElemProxy& operator=(const bool b);
    operator bool() const;
};

/// @brief リセット処理が高速な固定長の真偽値配列です
/// @details
/// ### 制約
/// - reset() を`LLONG_MAX`回以上呼び出したときの動作は未定義
class BoolArray {
private:
    long long threshold;
    vector<long long> data;

public:
    /// @brief 長さ@f$n@f$の配列を構築します
    BoolArray(size_t n) :
        threshold(1), data(n) {
    }

    bool operator[](size_t i) const {
        return data[i] == threshold;
    }

    BoolArrayElemProxy operator[](size_t i) {
        return { i, *this };
    }

    /// @brief この配列の長さを返します
    size_t size() const {
        return data.size();
    }

    /// @brief 配列の要素をすべて`false`にします
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
// --->