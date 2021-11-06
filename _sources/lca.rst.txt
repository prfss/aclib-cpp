Lca
####

最小共通祖先(Lowest Common Ancestor)を求めるためのクラスです

.. code-block:: cpp

 Lca

制約
*****
- 入力は根から葉へ向きづけられた森である

メンバ
******

コンストラクタ
==============
.. code-block:: cpp

 lca(int n)

節点数を :math:`n` としてグラフを初期化します.

制約
-----
* :math:`1 \le n \le 10^8` 

add_edge
========
.. code-block:: cpp

 void add_edge(int u, int v)

節点 :math:`u` から :math:`v` へ枝を張ります.

制約
-----
* :math:`0 \le u,v \lt n` 

operator()
==========
.. code-block:: cpp

 int operator()(int u, int v)

節点 :math:`u` と :math:`v` のLCAを返します.

:math:`u` と :math:`v` が互いに異なる木に所属する場合は :math:`-1` を返します.

制約
----
* :math:`0 \le u,v \lt n` 