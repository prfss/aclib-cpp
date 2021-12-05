Sieve
######

エラトステネスの篩を実装したクラスです

.. code-block:: cpp

 Sieve


メンバ
*******

コンストラクタ
==============
.. code-block:: cpp

  sieve(int n)

:math:`n` 以下の素数を計算し, 結果をプロパティ ``is_prime``, ``primes`` に格納します.

制約
-----
- :math:`n` は非負整数

is_prime
========
.. code-block:: cpp

  vector<bool> is_prime

長さ :math:`n+1` のブール配列です.

.. math::
  \text{is_prime}[i] = 
  \begin{cases}
      \text{true} & (iが素数) \\
      \text{false} & (iが素数でない) \\
  \end{cases}

primes
=======
.. code-block:: cpp

  vector<int> primes

:math:`n` 以下の素数のリストです.