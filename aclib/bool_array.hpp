/// @file
/// @brief リセット処理が高速な真偽値配列です
#pragma once

#include <limits.h>
#include <vector>

using namespace std;

// <---
// name: Bool Array
/// @brief リセット処理が高速な固定長の真偽値配列です
/// @details
/// ### 制約
/// - reset() を`numeric_limits<T>::max()`回以上呼び出したときの動作は未定義
template <typename T = int>
class BoolArray {

private:
    T threshold;
    vector<T> data;
    size_t popcnt;
    struct Reference {
        const size_t idx;
        BoolArray* const ba;
        Reference& operator=(const Reference& other) {
            if (this == &other) return *this;
            return *this = bool(other);
        }
        Reference& operator=(bool b) {
            ba->set(idx, b);
            return *this;
        }
        operator bool() const {
            return ba->data[idx] == ba->threshold;
        }
    };

    void set(size_t i, bool b) {
        if (b) {
            if (threshold > data[i]) popcnt++;
            data[i] = threshold;
        } else {
            if (threshold == data[i]) popcnt--;
            data[i] = 0;
        }
    }

public:
    /// @brief 長さ@f$n@f$の配列を構築します
    BoolArray(size_t n) :
        threshold(1), data(n), popcnt(0) {
    }

    bool operator[](size_t i) const {
        return data[i] == threshold;
    }

    Reference operator[](size_t i) {
        return { i, this };
    }

    /// @brief この配列の長さを返します
    size_t size() const {
        return data.size();
    }

    /// @brief 配列の要素をすべて`false`にします
    void reset() {
        threshold++;
        popcnt = 0;
    }

    /// @brief `true`である要素の数を返します
    size_t pop_count() const {
        return popcnt;
    }
};
// --->