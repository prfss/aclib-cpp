Median
#######

中央値を動的に求めるためのクラスです

.. code-block:: cpp

 template <typename A, typename B, B (*op)(int, A, A)> Median

中央値は要素数を :math:`k` とするとき, :math:`\mathrm{op}(k,x,y)` で定義します. ただし

.. math::

   x =
   \begin{cases}
   0 & (k = 0) \\
   \frac{k+1}{2}\text{番目の値} & (k\text{が奇数}) \\
   \frac{k}{2}\text{番目の値} & (k\text{が偶数})
   \end{cases}

.. math::

   y =
   \begin{cases}
   0 & (k = 0) \\
   \frac{k+1}{2}\text{番目の値} & (k\text{が奇数}) \\
   \frac{k}{2}+1\text{番目の値} & (k\text{が偶数})
   \end{cases}

です.

制約
*****
- 格納される要素数は :math:`10^9` 個以下

メンバ
******

コンストラクタ
==============
.. code-block:: cpp

  median()


operator()
===========
.. code-block:: cpp

 B operator()()

中央値を返します.

insert
======
.. code-block:: cpp

 void insert(A x)

数 :math:`x` を追加します.

erase
=====
.. code-block:: cpp

 void erase(A x)

数 :math:`x` が存在すれば一つ削除します.

size
====
.. code-block:: cpp

 int size()

要素数を返します.