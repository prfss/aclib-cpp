Combination
###########
組合せの総数 :math:`\binom{x}{y}` を計算するためのクラスです

.. code-block:: cpp

 template <int m> Comb

計算にあたって :math:`\bmod m` を取ります.

制約
****
- :math:`m` は素数

メンバ
******

コンストラクタ
==============
.. code-block:: cpp

 comb(int n)

:math:`x` の最大値を :math:`n` とします.

制約
----
- :math:`n < m`

operator()
==========
.. code-block:: cpp

 ll operator()(int x, int y)

:math:`\binom{x}{y}` を :math:`m` で割った余りを返します.

制約
----
* :math:`0 \le y \le x \le n`