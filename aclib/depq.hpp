/// @file
/// @brief [Double Ended Priority Queue](https://en.wikipedia.org/wiki/Double-ended_priority_queue)のInterval Heapによる実装です
#pragma once

#include <cassert>
#include <vector>

using namespace std;

// <---
// name: Double Ended Priority Queue
/// @brief ベクタ`v`をin-placeにInterval Heapに変換します.
/// @details
/// 言い換えると,\f$n\f$をベクタ`v`の長さとしたとき,`v`が次の条件を満たすように要素を並び替えます.
/// - 偶数\f$i\f$に対して,
///   - \f$i + 1 \lt n\f$ならば\f$v_i \le v_{i+1}\f$
///   - \f$ k \in \{2,3,4,5\}\f$に対して,\f$2i+k \lt n\f$ならば\f$v_i \le v_{2i+k} \le v_{i+1}\f$
///
/// さらにこの実装では次の条件も満たします.
/// - 偶数\f$i \lt n\f$と奇数\f$j \lt n\f$に対して, \f$ v_{i} \le v_{j}\f$
template <typename T>
void make_interval_heap(vector<T>& v) {
    size_t min_heap_len = (v.size() + 1) / 2;
    nth_element(v.begin(), v.begin() + min_heap_len, v.end());

    size_t j = (min_heap_len & 1) == 0 ? min_heap_len : min_heap_len + 1;
    for (size_t i = 1; i < min_heap_len; i += 2) {
        swap(v[i], v[j]);
        j += 2;
    }

    if (v.size() <= 2) return;

    for (int i = (v.size() & 1) == 0 ? v.size() - 2 : v.size() - 1; i >= 0; i -= 2) {
        size_t j = i;
        while (j < v.size()) {
            assert((i & 1) == 0);
            size_t l = (j << 1) + 2;
            size_t r = l + 2;
            if (r < v.size() && v[r] <= v[l] && v[r] < v[j]) {
                swap(v[r], v[j]);
                j = r;
            } else if (l < v.size() && v[l] < v[j]) {
                swap(v[l], v[j]);
                j = l;
            } else {
                break;
            }
        }
    }

    for (int i = (v.size() & 1) == 1 ? v.size() - 2 : v.size() - 1; i >= 1; i -= 2) {
        size_t j = i;
        while (j < v.size()) {
            assert((i & 1) == 1);
            size_t l = ((j - 1) << 1) + 3;
            size_t r = l + 2;
            if (r < v.size() && v[r] >= v[l] && v[r] > v[j]) {
                swap(v[r], v[j]);
                j = r;
            } else if (l < v.size() && v[l] > v[j]) {
                swap(v[l], v[j]);
                j = l;
            } else {
                break;
            }
        }
    }
}

template <typename T>
bool is_interval_heap_inner(const vector<T>& v, const size_t l, const size_t r) {
    assert(l < r);
    assert(r < v.size());
    if (v[l] > v[r]) return false;

    size_t l1 = (l << 1) + 2;
    if (l1 >= v.size()) return true;
    const T& x1 = v[l1];
    const T& y1 = l1 + 1 < v.size() ? v[l1 + 1] : x1;
    const T& x2 = l1 + 2 < v.size() ? v[l1 + 2] : x1;
    const T& y2 = l1 + 3 < v.size() ? v[l1 + 3] : x2;

    if (!(v[l] <= x1 && y1 <= v[r] && v[l] <= x2 && y2 <= v[r])) return false;

    return (l1 + 1 >= v.size() || is_interval_heap_inner(v, l1, l1 + 1))
           && (l1 + 3 >= v.size() || is_interval_heap_inner(v, l1 + 2, l1 + 3));
}

template <typename T>
bool is_interval_heap(const vector<T>& v) {
    if (v.size() <= 1) return true;
    return is_interval_heap_inner(v, 0, 1);
}

/// @brief Double Ended Priority Queueを実現する構造体です
template <typename T>
struct DoubleEndedPriorityQueue {
    DoubleEndedPriorityQueue() = default;
    DoubleEndedPriorityQueue(const vector<T>& v) :
        data(v) {
        make_interval_heap(data);
    }
    DoubleEndedPriorityQueue(vector<T>&& v) :
        data(v) {
        make_interval_heap(data);
    }

    /// @brief キューのサイズを返します
    inline size_t size() const { return data.size(); }

    /// @brief キューが空かどうかを返します
    inline bool empty() const { return data.empty(); }

    /// @brief キューに要素を追加します
    void push(T x) {
        data.push_back(x);
        if (size() < 2) return;
        heap_up(size() - 1);
    }

    /// @brief キューに含まれる最小値を返します
    inline const T& peek_min() const {
        assert(!empty());
        return data[0];
    }

    /// @brief キューに含まれる最大値を返します
    inline const T& peek_max() const {
        assert(!empty());
        return size() == 1 ? data[0] : data[1];
    }

    /// @brief キューから最小値を取り出します
    T pop_min() {
        assert(!data.empty());
        swap(data[0], data[size() - 1]);
        T x = std::move(data[size() - 1]);
        data.pop_back();
        if (size() >= 2) heap_up(heap_down_left(0));
        return x;
    }

    /// @brief キューから最大値を取り出します
    T pop_max() {
        assert(!data.empty());
        swap(data[size() == 1 ? 0 : 1], data[size() - 1]);
        T x = std::move(data[size() - 1]);
        data.pop_back();
        if (size() >= 2) heap_up(heap_down_right(1));
        return x;
    }

private:
    vector<T> data;
    void heap_up(size_t i) {
        if ((i | 1) < size() && data[i & ~size_t(1)] > data[i | size_t(1)]) {
            swap(data[i & ~size_t(1)], data[i | size_t(1)]);
            i ^= 1;
        }
        heap_up_right(heap_up_left(i));
    }

    size_t heap_up_left(size_t i) {
        T v = std::move(data[i]);
        while (i > 1) {
            size_t p = ((i - 2) >> 1) & ~size_t(1);
            if (v < data[p]) {
                data[i] = std::move(data[p]);
                i = p;
            } else {
                break;
            }
        }
        data[i] = v;
        return i;
    }

    size_t heap_up_right(size_t i) {
        T v = std::move(data[i]);
        while (i > 1) {
            size_t p = ((i - 2) >> 1) | size_t(1);
            if (data[p] < v) {
                data[i] = std::move(data[p]);
                i = p;
            } else {
                break;
            }
        }
        data[i] = v;
        return i;
    }

    size_t heap_down_left(size_t i) {
        T v = std::move(data[i]);
        while (true) {
            size_t c = (i << 1) + 2;
            if (c >= data.size()) break;
            if (c + 2 < data.size() && data[c] > data[c + 2]) c += 2;
            if (v > data[c]) {
                data[i] = std::move(data[c]);
                i = c;
            } else {
                break;
            }
        }
        data[i] = v;
        return i;
    }

    size_t heap_down_right(size_t i) {
        T v = std::move(data[i]);
        while (true) {
            size_t c = ((i & ~size_t(1)) << 1) + 3;
            if (c >= data.size()) break;
            if (c + 2 < data.size() && data[c] < data[c + 2]) c += 2;
            if (v < data[c]) {
                data[i] = std::move(data[c]);
                i = c;
            } else {
                break;
            }
        }
        data[i] = v;
        return i;
    }
};
// --->