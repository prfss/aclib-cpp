Monotonic Convex Hull Trick
###########################

追加クエリおよび最小値/最大値クエリが単調な場合のConvex Hull Trickを実装したクラスです

:doc:`monotonic_convex_hull_trick_verification`

.. code-block:: cpp

 template <typename T, typename compare = std::less> MonotonicConvexHullTrick

一次関数の集合 :math:`L = \{f_1,f_2,...,f_n\}` に対して, 次の2つの処理を行うことができます.

- 関数 :math:`a_i x + b_i` の追加
- 与えられた :math:`x` に対し, 全ての :math:`1 \le j \le n` について, :math:`\text{compare}(f_i(x),f_j(x)) \lor f_i(x) = f_j(x)` を満たす :math:`f_i(x)` の取得

後者について特に ``compare`` が ``std::less`` の場合は最小値を, ``std::greater`` の場合は最大値を得ることができます.

制約
****
* ``operator()`` で与えられるクエリ :math:`x_1,x_2,...x_m` は単調

* ``add`` で追加される直線の傾きが順に :math:`a_1,a_2,...,a_n` であるとき, 全ての :math:`1 \le i \lt n` に対して

  - :math:`x_i` が狭義単調増加する場合

  .. math::
    \begin{cases}
      a_i \le a_{i+1} & (\text{compare} = \text{std::greater}) \\
      a_i \ge a_{i+1} & (\text{compare} = \text{std::less})
    \end{cases}
  
  - :math:`x_i` が狭義単調減少する場合

  .. math::
    \begin{cases}
      a_i \ge a_{i+1} & (\text{compare} = \text{std::greater}) \\
      a_i \le a_{i+1} & (\text{compare} = \text{std::less})
    \end{cases}

メンバ
******

コンストラクタ
==============
.. code-block:: cpp

 MonotonicConvexHullTrick()

add
==========
.. code-block:: cpp

 void add(const T& a, const T& b)

operator()
===================
.. code-block:: cpp

 T operator()(const T& x)