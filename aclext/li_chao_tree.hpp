#pragma once

#include <cassert>
#include <functional>
#include <vector>

using namespace std;

namespace aclext {
template <typename T>
struct Node {
    Node *left, *right;
    T f;
    Node(T f)
        : left(nullptr), right(nullptr), f(f) { }
};

template <typename X, typename Y, typename F, typename compare = std::less<Y>>
class LiChaoTree {
    X min_x, max_x;
    Node<F>* root = nullptr;
    int n = 0;

    Node<F>* allocate(F f) {
        return new Node<F>(f);
    }

    Y query(X x, Node<F>* cur, X l, X r) {
        Y v1 = cur->f(x);

        if (r - l == 1) return v1;

        Y m = l + (r - l) / 2;
        Y v2 = x < m ? (cur->left == nullptr ? v1 : query(x, cur->left, l, m)) : (cur->right == nullptr ? v1 : query(x, cur->right, m, r));

        return compare()(v1, v2) ? v1 : v2;
    }

    void add_line(F f, Node<F>* cur, X l, X r) {
        if (r - l == 1) {
            if (compare()(f(l), cur->f(l))) {
                cur->f = f;
            }
            return;
        }

        Y m = l + (r - l) / 2;

        bool bl = compare()(f(l), cur->f(l));
        bool bm = compare()(f(m), cur->f(m));
        bool br = compare()(f(r - 1), cur->f(r - 1));

        if (bl and br) {
            cur->f = f;
        } else if (bm) {
            F g = cur->f;
            cur->f = f;
            add_line(g, cur, l, r);
        } else if (bl) {
            if (cur->left == nullptr) {
                cur->left = allocate(f);
            }
            add_line(f, cur->left, l, m);
        } else if (br) {
            if (cur->right == nullptr) {
                cur->right = allocate(f);
            }
            add_line(f, cur->right, m, r);
        }
    }

    void merge(Node<F>* root, Node<F>* other) {
        if (other == nullptr) return;
        merge(root, other->left);
        merge(root, other->right);
        add_line(other->f, root, min_x, max_x);
    }

    void del(Node<F>* cur) {
        if (cur->left != nullptr) del(cur->left);
        if (cur->right != nullptr) del(cur->right);
        delete cur;
    }

public:
    LiChaoTree(const X& min_x, const X& max_x)
        : min_x(min_x), max_x(max_x) {
        assert(min_x <= max_x);
    }

    LiChaoTree(LiChaoTree<X, Y, F, compare>&& other) noexcept
        : min_x(other.min_x), max_x(other.max_x), root(other.root), n(other.n) {
        other.root = nullptr;
    }

    LiChaoTree<X, Y, F, compare>& operator=(LiChaoTree<X, Y, F, compare>&& other) noexcept {
        min_x = other.min_x;
        max_x = other.max_x;
        root = other.root;
        n = other.n;
        other.root = nullptr;
        return *this;
    }

    ~LiChaoTree() {
        if (root != nullptr) del(root);
    }

    Y operator()(const X& x) {
        assert(min_x <= x and x <= max_x);
        assert(root != nullptr);
        return query(x, root, min_x, max_x + 1);
    }

    void add(const F f) {
        if (root == nullptr) {
            root = allocate(f);
        }
        n++;
        add_line(f, root, min_x, max_x + 1);
    }

    void merge(const LiChaoTree<X, Y, F, compare>& other) {
        assert(min_x == other.min_x);
        assert(max_x == other.max_x);

        merge(root, other.root);
        n += other.n;
    }

    int size() {
        return n;
    }
};
}