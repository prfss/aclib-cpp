Rerooting
#########

全方位木DPを行います

:doc:`rerooting_verification`

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

:math:`S` は部分木が親に返す値の型, :math:`M` はマージを表現する型, :math:`R` は解の型, :math:`C` はコストの型です.

:math:`u` を根とした時の解は

.. math::
  \mathrm{result}(\mathit{reduce}(f, \mathrm{em}(), \mathit{neighbor}(u)), u)

で定めます.

また :math:`u` から親頂点 :math:`p` に返す値は

.. math::
 \mathrm{subtree}(\mathit{reduce}(f, \mathrm{em}(), \mathit{neighbor}(u) \setminus \{p\}), u)

で定めますが, これは

.. math::
 \mathrm{subtree}(\mathrm{merge}(\mathit{reduce}(f,\mathrm{em}(),L), \mathit{reduce}(f,\mathrm{em}(),R), u))

と一致する必要があります.


ただし,

* :math:`\mathit{neighbor}(u)` は :math:`u` の隣接頂点の全体

* :math:`f(x,v) = \mathrm{introduce}(x, \mathit{dp}[v], \mathit{cost}(u,v), u, v)`

  * :math:`dp[v]` は 子頂点 :math:`v` から親頂点 :math:`u` に返す値

* :math:`reduce: (M \times \mathit{int} \to M) \times M \times (\mathit{Set\:of\:int}) \to M` は `重畳関数 <https://ja.wikipedia.org/wiki/%E9%AB%98%E9%9A%8E%E9%96%A2%E6%95%B0#fold>`_

* :math:`(L \cap R = \emptyset) \land (L \cup R = \mathit{neighbor}(u) \setminus \{p\})`

です.



メンバ
******

コンストラクタ
==============
.. code-block:: cpp

 rerooting(int n)

:math:`n` 頂点 :math:`0` 辺の無向グラフを作ります.


add_edge
========
.. code-block:: cpp

 void add_edge(int u, int v, C c = {})

頂点 :math:`u` と :math:`v` の間にコスト :math:`c` の辺を追加します.

制約
-----
* :math:`0 \le u,v < n`

calc
====
.. code-block:: cpp

 vector<R> calc()

全方位木DPの計算結果を返します.

制約
----
- このグラフは木である
