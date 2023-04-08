#pragma once

#include "atcoder/modint"
#include <cassert>
#include <functional>
#include <iostream>
#include <vector>

using namespace std;

namespace aclext {
// <---
// name:Matrix
template <typename T, T (*add)(T, T), T (*mul)(T, T), T zero(), T one(), bool has_subtraction = false>
class Matrix {
    size_t n, m;
    vector<vector<T>> a;

public:
    Matrix(int n, int m, T init = zero())
        : n(n), m(m) {
        assert(n >= 1 and m >= 1);
        a.assign(n, vector<T>(m, init));
    }

    Matrix(const vector<vector<T>> list) {
        assert(!list.empty() && !list.front().empty());

        n = list.size();
        m = list.front().size();

        for (size_t i = 0; i < n; i++) {
            assert(list[i].size() == (size_t)m);
            a.push_back(list[i]);
        }
    }

    static Matrix identity(int n) {
        assert(n >= 1);
        Matrix m = Matrix(n, n, zero());
        for (size_t i = 0; i < size_t(n); i++) {
            m[i][i] = one();
        }
        return m;
    }

    static Matrix column_vector(const vector<T> list) {
        assert(list.size() >= 1);
        return row_vector(list).transpose();
    }

    static Matrix row_vector(const vector<T> list) {
        assert(list.size() >= 1);
        return Matrix({ list });
    }

    size_t nrow() const {
        return n;
    }

    size_t ncol() const {
        return m;
    }

    Matrix transpose() const {
        Matrix t(this->m, this->n);

        for (size_t i = 0; i < this->n; i++) {
            for (size_t j = 0; j < this->m; j++) {
                t[j][i] = this->a[i][j];
            }
        }

        return t;
    }

    Matrix map(function<T(T, int, int)> f) const {
        Matrix r(n, m);
        for (size_t i = 0; i < n; i++) {
            for (size_t j = 0; j < m; j++) {
                r[i][j] = f(this->a[i][j], i, j);
            }
        }
        return r;
    }

    vector<T>& operator[](size_t i) {
        return a[i];
    }

    const vector<T>& operator[](size_t i) const {
        return a[i];
    }

    Matrix operator+(const Matrix& rhs) const {
        assert(n == rhs.n && m == rhs.m);

        Matrix r(n, m);

        for (size_t i = 0; i < n; i++) {
            for (size_t j = 0; j < m; j++) {
                r[i][j] = add(a[i][j], rhs[i][j]);
            }
        }

        return r;
    }

    template <bool enabled = has_subtraction>
    typename enable_if<enabled, Matrix>::type operator-() const {
        return this->map([](T v, int i, int j) { return -v; });
    }

    template <bool enabled = has_subtraction>
    typename enable_if<enabled, Matrix>::type operator-(const Matrix& rhs) const {
        return (*this) + (-rhs);
    }

    Matrix operator*(const Matrix& rhs) const {
        assert(m == rhs.n);

        Matrix r(int(n), int(rhs.m));

        for (size_t i = 0; i < n; i++) {
            for (size_t j = 0; j < rhs.m; j++) {
                for (size_t k = 0; k < m; k++)
                    r[i][j] = add(r[i][j], mul(a[i][k], rhs[k][j]));
            }
        }

        return r;
    }

    Matrix pow(long long b) const {
        assert(n == m);

        Matrix r = Matrix::identity(int(n)), a(*this);

        while (b > 0) {
            if (b & 1) r = r * a;
            a = a * a;
            b >>= 1;
        }

        return r;
    }

    bool operator==(const Matrix& rhs) const {
        assert(n == rhs.n && m == rhs.m);

        bool ok = true;
        for (size_t i = 0; i < n; i++) {
            for (size_t j = 0; j < m; j++) {
                ok &= a[i][j] == rhs.a[i][j];
            }
        }

        return ok;
    }
};

template <typename T, auto add, auto mul, auto zero, auto one, bool b>
ostream& operator<<(ostream& out, const Matrix<T, add, mul, zero, one, b>& a) {
    for (size_t i = 0; i < a.nrow(); i++) {
        out << i << ": ";
        for (size_t j = 0; j < a.ncol(); j++)
            out << a[i][j] << " ";
        out << '\n';
    }
    return out;
}

#ifdef ATCODER_MODINT_HPP
template <int m, auto add, auto mul, auto zero, auto one, bool b>
ostream& operator<<(ostream& out, const Matrix<atcoder::static_modint<m>, add, mul, zero, one, b>& a) {
    for (size_t i = 0; i < a.nrow(); i++) {
        out << i << ": ";
        for (size_t j = 0; j < a.ncol(); j++)
            out << a[i][j].val() << " ";
        out << '\n';
    }
    return out;
}
#endif
// --->
}