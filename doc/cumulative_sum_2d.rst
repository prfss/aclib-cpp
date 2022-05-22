2D Cumulative Sum
##################
2次元累積和を計算するためのクラスです

.. code-block:: cpp

 template <typename I, typename O> CumulativeSum2D

メンバ
******

コンストラクタ
===============
.. code-block:: cpp

 CumulativeSum2D(const vector<vector<I>> l)

operator()
==========
.. code-block:: cpp

 O operator()(size_t x1, size_t y1, size_t x2, size_t y2)