BoolArray
###############
リセット処理が高速な固定長の真偽値配列です

.. code-block:: cpp

  BoolArray

制約
****
-  ``init`` を ``LLONG_MAX`` 回以上呼び出した時の動作は未定義

メンバ
******

コンストラクタ
==============
.. code-block:: cpp

 bool_array(size_t n)

配列の長さを ``n`` として初期化します.

計算量
------
- :math:`O(n)`

operator[]
===========
.. code-block:: cpp

 bool operator[](size_t i) const
 BoolArrayElemProxy operator[](size_t)

計算量
-----
- :math:`O(1)`

reset
=====
.. code-block:: cpp

 void reset()

配列の要素をすべて ``false`` にします.

計算量
-----
- :math:`O(1)`

size
=====
.. code-block:: cpp

 size_t size() const

``n`` を返します.

計算量
-----
- :math:`O(1)`