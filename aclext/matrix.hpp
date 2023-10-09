/// @file
/// @brief 行列の計算をおこないます
/// @details
/// [Verification](verifications/matrix.md)
#pragma once

#include "atcoder/modint"
#include <cassert>
#include <functional>
#include <iostream>
#include <vector>

using namespace std;

// <---
// name:Matrix
/// @brief 和・差・積・累乗などの演算を備えた行列クラスです
/// @details
/// `T`は要素の型です.`add`,`zero`は加算とその単位元,`mul`,`one`は乗算とその単位元を表します.
/// また`has_subtraction == true`の時,`operator-`を定義します.
/// ### 制約
/// - @f$\mathrm{add}(x,\text{zero}()) = \mathrm{add}(\text{zero}(),x) = x@f$
/// - @f$\mathrm{mul}(x,\text{one}()) = \mathrm{mul}(\text{one}(),x) = x@f$
template <typename T, T (*add)(T, T), T (*mul)(T, T), T zero(), T one(), bool has_subtraction = false>
class Matrix {
    size_t n, m;
    vector<vector<T>> a;

public:
    /// 要素を @f$\mathrm{init}@f$ で初期化した @f$n \times m@f$ 行列を返します.
    /// ### 制約
    /// - @f$n,m \ge 1@f$
    Matrix(int n, int m, T init = zero()) :
        n(n), m(m) {
        assert(n >= 1 and m >= 1);
        a.assign(n, vector<T>(m, init));
    }

    /// @f$(i,j)@f$成分が@f$\mathrm{list}[i][j]@f$であるような行列を返します.
    /// ### 制約
    /// - @f$\mathrm{list}[i] (0 \le i \lt \mathrm{list.size}())@f$の長さはすべて等しい
    /// - @f$\mathrm{list}@f$は空ではない
    Matrix(const vector<vector<T>> list) {
        assert(!list.empty() && !list.front().empty());

        n = list.size();
        m = list.front().size();

        for (size_t i = 0; i < n; i++) {
            assert(list[i].size() == (size_t)m);
            a.push_back(list[i]);
        }
    }

    /// @f$n@f$次の単位行列@f$I_n@f$,すなわち
    /// @f[
    /// (I_n)_{ij} =
    /// \begin{cases}
    /// \mathrm{one}() & (i = j) \\
    /// \mathrm{zero}() & (\text{それ以外}) \\
    /// \end{cases}
    /// @f]
    /// を返します.
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

    /// この行列を@f$b@f$乗した行列を返します.
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

template <typename Type, typename = void>
struct has_val : false_type { };

template <typename Type>
struct has_val<Type,
               enable_if_t<is_member_function_pointer_v<decltype(&Type::val)>>> : true_type { };

template <typename T, auto add, auto mul, auto zero, auto one, bool b>
enable_if_t<!has_val<T>::value, ostream&> operator<<(ostream& out, const Matrix<T, add, mul, zero, one, b>& a) {
    for (size_t i = 0; i < a.nrow(); i++) {
        out << i << ": ";
        for (size_t j = 0; j < a.ncol(); j++)
            out << a[i][j] << " ";
        out << '\n';
    }
    return out;
}

template <typename M, auto add, auto mul, auto zero, auto one, bool b>
enable_if_t<has_val<M>::value, ostream&> operator<<(ostream& out, const Matrix<M, add, mul, zero, one, b>& a) {
    for (size_t i = 0; i < a.nrow(); i++) {
        out << i << ": ";
        for (size_t j = 0; j < a.ncol(); j++)
            out << a[i][j].val() << " ";
        out << '\n';
    }
    return out;
}
// --->