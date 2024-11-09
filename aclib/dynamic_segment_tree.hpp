/// @file
/// @brief 動的セグメント木の実装です
#pragma once

// <---
// name: Dynamic Segment Tree
/// @brief 動的セグメント木を実装したクラスです
/// @details
/// `T`型の配列\f$a\f$とモノイド\f$(\mathrm{T}, \mathrm{op}, \mathrm{e})\f$に対して,
/// - 要素の変更(\f$a_i = \mathrm{val}\f$)
/// - 区間\f$[l, r)\f$の総積\f$\mathrm{op}(a[l], ..., a[r-1])\f$の取得
///
/// を行うことができるデータ構造です.
template <typename S, S (*op)(S, S), S (*e)(), typename I = int>
class DynamicSegmentTree {
    struct Node {
        S val;
        Node *l, *r;
        Node(S v) :
            val(v), l(nullptr), r(nullptr) { }
    };

    Node* root;
    I begin, end;

    static S get_val(Node* n) {
        return (n == nullptr) ? e() : n->val;
    }

    static Node* allocate() {
        return new Node(e());
    }

    static void deallocate_tree(Node* cur) {
        if (cur != nullptr) {
            deallocate_tree(cur->l);
            deallocate_tree(cur->r);
            delete cur;
        }
    }

    static Node* copy(const Node* src) {
        if (src == nullptr) return nullptr;
        Node* n = allocate();
        n->val = src->val;
        n->l = copy(src->l);
        n->r = copy(src->r);
        return n;
    }

    S set(long long i, S val, Node* cur, I l, I r) {
        if (r - l == 1) {
            cur->val = val;
            return val;
        }

        I m = l + (r - l) / 2;
        S v;
        if (i < m) {
            if (cur->l == nullptr) cur->l = allocate();
            v = op(set(i, val, cur->l, l, m), get_val(cur->r));
        } else {
            if (cur->r == nullptr) cur->r = allocate();
            v = op(get_val(cur->l), set(i, val, cur->r, m, r));
        }

        return cur->val = v;
    }

    S prod(I a, I b, Node* cur, I l, I r) {
        if (b <= l or r <= a) return e();
        if (a <= l and r <= b) return cur->val;
        I m = l + (r - l) / I(2);
        I lv = cur->l ? prod(a, b, cur->l, l, m) : e();
        I rv = cur->r ? prod(a, b, cur->r, m, r) : e();
        return op(lv, rv);
    }

public:
    /// @brief \f$[\mathrm{begin}, \mathrm{end})\f$の範囲を持つ配列\f$a\f$を構築します
    DynamicSegmentTree(I begin, I end) :
        root(allocate()),
        begin(begin),
        end(end) {
    }

    DynamicSegmentTree(const DynamicSegmentTree<S, op, e, I>& other) :
        root(copy(other.root)), begin(other.begin), end(other.end) {
    }

    DynamicSegmentTree<S, op, e, I>& operator=(const DynamicSegmentTree<S, op, e, I>& other) {
        if (this != &other) {
            deallocate_tree(root);
            root = copy(other.root);
            begin = other.begin;
            end = other.end;
        }
        return *this;
    }

    DynamicSegmentTree(DynamicSegmentTree<S, op, e, I>&& other) noexcept :
        root(other.root), begin(other.begin), end(other.end) {
        other.root = allocate();
    }

    DynamicSegmentTree<S, op, e, I>& operator=(DynamicSegmentTree<S, op, e, I>&& other) noexcept {
        deallocate_tree(root);
        begin = other.begin;
        end = other.end;
        root = other.root;
        other.root = allocate();

        return *this;
    }

    ~DynamicSegmentTree() {
        deallocate_tree(root);
    }

    /// @brief \f$a_i\f$に\f$\mathrm{val}\f$を代入します
    void set(I i, S val) {
        set(i, val, root, begin, end);
    }

    /// @brief \f$a_i\f$を返します
    S get(I i) {
        return prod(i, i + 1, root, begin, end);
    }

    /// @brief \f$\mathrm{op}(a[l],...,a[r-1])\f$を返します
    S prod(I l, I r) {
        return prod(l, r, root, begin, end);
    }

    /// @brief \f$\mathrm{op}(a[\mathrm{begin}],...,a[\mathrm{end}-1])\f$を返します
    S all_prod() {
        return prod(begin, end);
    }

    /// @brief \f$f\f$が単調な時,\f$f(\mathrm{op}(a[l],...,a[r-1])) = \mathrm{true}\f$となる最大の\f$r\f$を返します
    /// @details \f$f(a[l]) = \mathrm{false}\f$ならば\f$l\f$を返します.
    template <typename F>
    I max_right(I l, F f) {
        I x = l, y = end + 1;
        while (y - x > 1) {
            I m = x + (y - x) / 2;
            if (f(prod(l, m)))
                x = m;
            else
                y = m;
        }

        return x;
    }

    /// @brief \f$f\f$が単調な時,\f$f(\mathrm{op}(a[l],...,a[r-1])) = \mathrm{true}\f$となる最小の\f$l\f$を返します
    /// @details \f$f(a[r-1]) = \mathrm{false}\f$ならば\f$r\f$を返します.
    template <typename F>
    I min_left(I r, F f) {
        I x = begin - 1, y = r;
        while (y - x > 1) {
            I m = y - (y - x) / 2;
            if (f(prod(m, r)))
                y = m;
            else
                x = m;
        }

        return y;
    }
};
// --->