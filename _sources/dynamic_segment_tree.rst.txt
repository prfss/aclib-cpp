Dynamic Segment Tree
#####################

動的セグメント木の実装です

:doc:`dynamic_segment_tree_verification`

.. code-block:: cpp

 template <typename S, S (*op)(S, S), S (*e)(), typename X = int> DynamicSegmentTree

メンバ
******

コンストラクタ
==============
.. code-block:: cpp

  DynamicSegmentTree(X min_x, X max_x)

set
===

get
===

prod
====

all_prod
========

max_right
=========

min_left
========