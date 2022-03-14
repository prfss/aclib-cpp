#pragma once

// <---
// name:Dynamic Segment Tree
namespace aclext {
template <typename S>
struct Node {
    S val;
    Node *l, *r;
    Node(S v)
        : val(v), l(nullptr), r(nullptr) { }
};
template <typename S, S (*op)(S, S), S (*e)(), typename X = int>
class DynamicSegmentTree {
    Node<S>* root;
    X min_x, max_x;

    S get_val(Node<S>* n) {
        return (n == nullptr) ? e() : n->val;
    }

    Node<S>* allocate() {
        return new Node<S>(e());
    }

    S set(long long i, S val, Node<S>* cur, X l, X r) {
        if (r - l == 1) {
            cur->val = val;
            return val;
        }

        X m = l + (r - l) / 2;
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

    S prod(X a, X b, Node<S>* cur, X l, X r) {
        if (b <= l or r <= a) return e();
        if (a <= l and r <= b) return cur->val;
        X m = l + (r - l) / X(2);
        X lv = cur->l ? prod(a, b, cur->l, l, m) : e();
        X rv = cur->r ? prod(a, b, cur->r, m, r) : e();
        return op(lv, rv);
    }

    void del(Node<S>* cur) {
        if (cur != nullptr) {
            del(cur->l);
            del(cur->r);
            delete cur;
        }
    }

public:
    DynamicSegmentTree(X l, X r)
        : min_x(l), max_x(r) {
        root = allocate();
    }

    DynamicSegmentTree(const DynamicSegmentTree<S, op, e>&& other)
        : min_x(other.min_x), max_x(other.max_x), root(other.root) {
        other.root = nullptr;
    }

    DynamicSegmentTree<S, op, e>* operator=(const DynamicSegmentTree<S, op, e>&& other) {
        min_x = other.min_x;
        max_x = other.max_x;
        root = other.root;
        other.root = nullptr;
    }

    ~DynamicSegmentTree() {
        del(root);
    }

    void set(X i, S val) { set(i, val, root, min_x, max_x + 1); }

    S get(X i) { return prod(i, i + 1, root, min_x, max_x + 1); }

    S prod(X l, X r) { return prod(l, r, root, min_x, max_x + 1); }

    S all_prod() { return prod(min_x, max_x + 1); }

    template <typename F>
    X max_right(X l, F f) {
        X x = l, y = max_x + 2;
        while (y - x > 1) {
            X m = x + (y - x) / 2;
            if (f(prod(l, m)))
                x = m;
            else
                y = m;
        }

        return x;
    }

    template <typename F>
    X min_left(X r, F f) {
        X x = min_x - 1, y = r;
        while (y - x > 1) {
            X m = x + (y - x) / 2;
            if (f(prod(m, r)))
                y = m;
            else
                x = m;
        }

        return y;
    }
};
}
// --->