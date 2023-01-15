Lca
####

有向木の最小共通祖先(Lowest Common Ancestor)を求めます

.. code-block:: cpp

 Lca

メンバ
******

コンストラクタ
==============
.. code-block:: cpp

 lca(int n)

:math:`n` 頂点 :math:`0` 辺の有向グラフを作ります.

制約
----
* :math:`1 \le n \le 10^8` 
.. AtCoder LibraryのSegtreeの制約に基づく

add_edge
========
.. code-block:: cpp

 void add_edge(int u, int v)

頂点 :math:`u` から :math:`v` への辺を追加します.

制約
----
* :math:`0 \le u,v \lt n` 

operator()
==========
.. code-block:: cpp

 int operator()(int u, int v)

頂点 :math:`u` と :math:`v` の最小共通祖先を返します.

:math:`u` と :math:`v` が互いに異なる木に所属する場合は :math:`-1` を返します.

制約
----
* :math:`0 \le u,v \lt n` 
* このグラフは森である