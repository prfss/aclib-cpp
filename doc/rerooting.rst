Rerooting
#########

全方位木DPのためのクラスです

.. code-block:: cpp

 template <
     typename S,
     typename M,
     typename R,
     typename C,
     M (*merge)(M,M,int),
     M (*introduce)(M,S,C,int,int)
     M (*em)(),
     R (*result)(M,int),
     S (*subtree)(M,int)>
    Rerooting

:math:`\text{S}` は部分木が親に返す値の型, :math:`\text{M}` はマージを表現する型, :math:`\text{R}` は解の型, :math:`\text{C}` はコストの型です.

:math:`u` を根とした時の解は

.. math::
  \text{result}(reduce(f, \text{em}(), neighbor(u)), u)

で定めます.

また :math:`u` から親節点 :math:`p` に返す値は

.. math::
 \text{subtree}(reduce(f, \text{em}(), neighbor(u) \setminus \{p\}), u)

で定めますが, これは

.. math::
 \text{subtree}(\text{merge}(reduce(f,\text{em}(),L), reduce(f,\text{em}(),R), u))

と一致する必要があります.


ただし,

* :math:`neighbor(u)` は :math:`u` の隣接節点の全体

* :math:`f(x,v) = \text{introduce}(x, dp[v], cost(u,v), u, v)`

  * :math:`dp[v]` は 子節点 :math:`v` から親節点 :math:`u` に返す値

* :math:`reduce: (M \times int \to M) \times M \times (Set\:of\:int) \to M` は `重畳関数 <https://ja.wikipedia.org/wiki/%E9%AB%98%E9%9A%8E%E9%96%A2%E6%95%B0#fold>`_

* :math:`(L \cap R = \emptyset) \land (L \cup R = neighbor(u) \setminus \{p\})`

です.

制約
****
- 入力は木

メンバ
******

コンストラクタ
==============
.. code-block:: cpp

 rerooting(int n)

グラフの節点数を :math:`n` として初期化します.


add_edge
========
.. code-block:: cpp

 void add_edge(int u, int v, C c = {})

節点 :math:`u` と :math:`v` の間にコスト :math:`c` の枝を張ります.

制約
-----
- :math:`0 \le u,v < n`

calc
====
.. code-block:: cpp

 vector<R> calc()

全方位木DPの計算結果を返します.
