2D Cumulative Sum
##################
2次元累積和を計算します

.. code-block:: cpp

 template <typename T> CumulativeSum2D

メンバ
******

コンストラクタ
===============
.. code-block:: cpp

 template <typename I> CumulativeSum2D(const vector<vector<I>> l)

:math:`l` から2次元配列 :math:`a` を作ります.

operator()
==========
.. code-block:: cpp

 T operator()(size_t x1, size_t y1, size_t x2, size_t y2)

:math:`i \in [x1,x2], j \in [y1,y2]` を満たす :math:`i,j` について :math:`a[i][j]` の総和を取得します.