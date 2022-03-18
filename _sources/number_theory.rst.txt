Number Theory
#############

初等整数論関連の関数を提供します

divisor
*******
.. code-block:: cpp

  vector<ll> divisor(ll n)

:math:`n` の約数を返します.

is_prime
********
.. code-block:: cpp

  bool is_prime(ll n)

:math:`n` が素数であるかどうか判定します.

prime_factor
************
.. code-block:: cpp

  map<ll,int> prime_factor(ll n)

:math:`n` の素因数分解を返します.

totient
*******
.. code-block:: cpp

  ll totient(ll n)

`オイラーのトーシェント関数 <https://ja.wikipedia.org/wiki/%E3%82%AA%E3%82%A4%E3%83%A9%E3%83%BC%E3%81%AE%CF%86%E9%96%A2%E6%95%B0>`_ です.

制約
=====
- :math:`1 \leq n \leq 10^9`


extgcd
******
.. code-block:: cpp

  template <typename T> tuple<T, T, T> extgcd(T a, T b)

拡張ユークリッドの互除法です. :math:`ax + by = \gcd(a,b)` を満たす整数 :math:`x,y` を求め :math:`(\gcd(x,y),x,y)` の形で返します.