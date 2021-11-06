Number_theory
#############

初等整数論関連の関数を提供します

divisor
*******
.. code-block:: cpp

  vector<int> divisor(int n)

:math:`n` の約数を返します.

is_prime
********
.. code-block:: cpp

  bool is_prime(int n)

:math:`n` が素数であるかどうか判定します.

prime_factor
************
.. code-block:: cpp

  map<int,int> prime_factor(int n)

:math:`n` の素因数分解を返します.

totient
*******
.. code-block:: cpp

  ll totient(ll n)

オイラーの `トーシェント関数 <https://ja.wikipedia.org/wiki/%E3%82%AA%E3%82%A4%E3%83%A9%E3%83%BC%E3%81%AE%CF%86%E9%96%A2%E6%95%B0>`_ です.

制約
=====
- :math:`1 \leq n \leq 10^9`