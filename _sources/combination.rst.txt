Combination
###########
組合せの数 :math:`{}_x C_y` を計算するためのクラスです

.. code-block:: cpp

 template <ll m> Comb

計算にあたって :math:`\bmod m` を取ります.

メンバ
******

コンストラクタ
==============
.. code-block:: cpp

 comb(int n)

:math:`x` の最大値を :math:`n` とます.

operator()
===========
.. code-block:: cpp

 ll operator()(int x, int y)

:math:`{}_x C_y` を :math:`m` で割った余りを返します.

制約
-----
* :math:`0 \le y \le x \le n`