#pragma once

#include "atcoder/modint"
#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

namespace aclext {
template <typename T>
class Matrix {
    size_t n, m;
    vector<vector<T>> a;

public:
    Matrix(int n, int m, T init = 0)
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
        Matrix m = Matrix(n, n);
        for (size_t i = 0; i < n; i++) {
            m[i][i] = 1;
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
                r[i][j] = a[i][j] + rhs[i][j];
            }
        }

        return r;
    }

    Matrix operator-() const {
        Matrix r(n, m);

        for (size_t i = 0; i < n; i++) {
            for (size_t j = 0; j < m; j++) {
                r[i][j] = -a[i][j];
            }
        }

        return r;
    }

    Matrix operator-(const Matrix& rhs) const {
        return (*this) + (-rhs);
    }

    Matrix operator*(const Matrix& rhs) const {
        assert(m == rhs.n);

        Matrix r(n, rhs.m);

        for (size_t i = 0; i < n; i++) {
            for (size_t j = 0; j < rhs.m; j++) {
                for (size_t k = 0; k < m; k++)
                    r[i][j] += a[i][k] * rhs[k][j];
            }
        }

        return r;
    }

    Matrix operator^(long long b) const {
        assert(n == m);

        Matrix r(n, m, 0), a(*this);

        for (size_t i = 0; i < n; i++) r[i][i] = 1;

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

template <typename T>
ostream& operator<<(ostream& out, const Matrix<T>& a) {
    for (size_t i = 0; i < a.nrow(); i++) {
        out << i << ": ";
        for (size_t j = 0; j < a.ncol(); j++)
            out << a[i][j] << " ";
        out << '\n';
    }
    return out;
}

template <int m>
ostream& operator<<(ostream& out, const Matrix<atcoder::static_modint<m>>& a) {
    for (size_t i = 0; i < a.nrow(); i++) {
        out << i << ": ";
        for (size_t j = 0; j < a.ncol(); j++)
            out << a[i][j].val() << " ";
        out << '\n';
    }
    return out;
}
}