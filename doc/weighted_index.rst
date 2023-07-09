WeightedIndex
###############
重み付き乱択を行います

.. code-block:: cpp

  template <typename T> WeightedIndex

メンバ
******

コンストラクタ
==============
.. code-block:: cpp

 weighted_index(const vector<T>& weights)

重みを ``weigths`` として初期化します.以下 :math:`n = \mathrm{weights.size()}` とします.

制約
----
1. :math:`0 \le \mathrm{weights[i]} (0 \le i \lt n)`
2. :math:`0 \lt \sum_{i} \mathrm{weights[i]} \le Tの最大値`

計算量
------
- :math:`O(n)`

operator()
===========
.. code-block:: cpp

 size_t operator()(R& rng)

インデックスを重みに比例する確率で選択して返します.
``rng`` は `乱数エンジン <https://ja.cppreference.com/w/cpp/numeric/random#.E4.B9.B1.E6.95.B0.E3.82.A8.E3.83.B3.E3.82.B8.E3.83.B3>`_ です.

計算量
-----
- :math:`O(\log{n})`