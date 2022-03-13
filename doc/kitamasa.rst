Kitamasa
########

きたまさ法を実装したクラスです

:doc:`kitamasa_verification`

.. code-block:: cpp

 template <typename S, S (*add)(S, S), S (*mul)(S, S), S (*zero)(), S (*one)()> Kitamasa

制約
****
- :math:`\text{add}(x, \text{zero()}) = \text{add}(\text{zero()}, x) = x`
- :math:`\text{mul}(x,\text{one}()) = \text{mul}(\text{one}(),x) = x`

メンバ
******

コンストラクタ
==============
.. code-block:: cpp

 Kitamasa(const vector<S>& c)

:math:`c` は漸化式の係数です.

calc
====
.. code-block:: cpp

 S calc(const vector<S>& a, long long n)

初期値 :math:`\{a_0,a_1,...,a_{k-1}\}` から
:math:`k` 階線形漸化式 :math:`a_n = a_{n-1}c_{k-1} + a_{n-2}c_{k-2} + ... + a_{n-k}c_0` の第 :math:`n` 項を求めます.

制約
----
- :math:`0 \le n`