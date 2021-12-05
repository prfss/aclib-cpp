
Matrix
#######

和・差・積・累乗などの演算を備えた行列クラスです

.. code-block:: cpp

 template <typename T> Matrix

:``T`` は要素の型です.

メンバ
******

コンストラクタ
==============
.. code-block:: cpp

 matrix(int n, int m, T init = 0) // (1)
 matrix(const vector<vector<T>> list) // (2)

1. 要素を :math:`\text{init}` で初期化した :math:`n \times m` 行列を返します.
2. :math:`(i,j)` 成分が :math:`\text{list}[i][j]` であるような行列を返します.

制約
----
1. :math:`1 \le n,m`
2. * :math:`\text{list}[i] (0 \le i \lt \text{list.size()})` の長さはすべて等しい 
   * リストは空ではない

identity
=========
.. code-block:: cpp

 static Matrix<T> identity(int n)

次数 :math:`n` の単位行列を返します.

row_vector
==========
.. code-block:: cpp

 static Matrix<T> row_vector(vector<T> row)

column_vector
=============
.. code-block:: cpp

 static Matrix<T> column_vector(vector<T> col)

operator+
=========
.. code-block:: cpp

 Matrix<T> operator+(const Matrix<T> &other)

operator-
=========
.. code-block:: cpp

 Matrix<T> operator-(const Matrix<T> &other)

operator*
=========
.. code-block:: cpp

 Matrix<T> operator*(const Matrix<T> &other)

operator^
=========
.. code-block:: cpp

 Matrix<T> operator^(ll x)

この行列を :math:`x` 乗した行列を返します.