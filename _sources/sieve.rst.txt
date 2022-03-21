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
- :math:`n \ge 0`

is_prime
========
.. code-block:: cpp

  vector<bool> is_prime

長さ :math:`n+1` のブール配列です.

.. math::
  \mathrm{is\_prime}[i] = 
  \begin{cases}
      \mathrm{true} & \text{(iが素数)} \\
      \mathrm{false} & \text{(iが素数でない)} \\
  \end{cases}

primes
=======
.. code-block:: cpp

  vector<int> primes

:math:`n` 以下の素数のリストです.