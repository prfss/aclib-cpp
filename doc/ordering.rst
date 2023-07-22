Ordering
###############

.. code-block:: cpp

  template <typename T> Ordering

メンバ
******

コンストラクタ
==============
.. code-block:: cpp

 Ordering(T x, T y)


operator bool
================
.. code-block:: cpp

 bool operator bool()

:math:`x \lt y` の時, ``true`` , それ以外の時 ``false`` を返す.

then
=====
.. code-block:: cpp

 Ordering then(const T other_x, const T other_y)

:math:`x = y` の時, ``Ordering(other_x,other_y)``, それ以外の時 ``*this`` を返す.
