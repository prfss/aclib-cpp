Random
#######

以下で, ``rng`` は `乱数エンジン <https://ja.cppreference.com/w/cpp/numeric/random#.E4.B9.B1.E6.95.B0.E3.82.A8.E3.83.B3.E3.82.B8.E3.83.B3>`_ です.


rand_range
***********
.. code-block:: cpp

 template <typename T> T rand_range(T l, T r, R& rng)

区間 :math:`[l,r)` から一様に数を選んで返します.

制約
====
- :math:`l \lt r`


rand_bool
**********
.. code-block:: cpp

 bool rand_bool(double p, R& rng)

:math:`p` の確率で ``true`` を, :math:`1 - p` の確率で ``false`` を返します.

制約
====
- :math:`0 \le p \le 1`