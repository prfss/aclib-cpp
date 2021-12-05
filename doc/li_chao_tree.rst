Li-Chao Tree
############

Li-Chao tree を実装したクラスです

:doc:`li_chao_tree_verification`

.. code-block:: cpp

 template <typename X, typename Y, typename F, typename compare = std::less<Y>> LiCharTree

関数の集合 :math:`L = \{f_1,f_2,...,f_n\}` に対して, 次の2つの処理を行うことができます.

- 関数の追加
- ある :math:`x` と全ての :math:`1 \le j \le n` に対し, :math:`\text{compare}(f_i(x),f_j(x)) \lor f_i(x) = f_j(x)` を満たす :math:`f_i(x)` の取得

後者について特に ``compare`` が ``std::less`` の場合は最小値を, ``std::greater`` の場合は最大値を得ることになります.

制約
****
- ``X`` は整数型
- ``F`` は ``Y operator()(X)`` を持つ
- ``add`` で追加される相異なる関数 :math:`f` と :math:`g` について, :math:`f(x) = g(x)` となるような :math:`x` は高々一つ

メンバ
******

コンストラクタ
==============
.. code-block:: cpp

 LiChaoTree(X min_x, X max_x)

制約
----
- :math:`\text{min_x} \le \text{max_x} \lt Xの最大値`

add
===
.. code-block:: cpp

 void add(F f)

operator()
==========
.. code-block:: cpp

 Y operator()(X x)

``add`` で追加した関数 :math:`f_1, f_2, ..., f_n` に対して, :math:`\text{compare}(f_i(x), f_j(x)) \lor f_i(x) = f_j(x)` を全ての :math:`1 \le j \le n` について満たす :math:`f_i(x)` を返します.

merge
=====
.. code-block:: cpp

 void merge(const LiChaoTree<X, Y, F, compare>& other)

制約
----
- :math:`\text{min_y} = \text{other.min_y} \land \text{max_y} = \text{other.max_y}`

size
====
.. code-block:: cpp

 int size()

これまでに追加された関数の数を返します.