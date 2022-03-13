ExtGCD
#######
拡張ユークリッドの互除法

.. code-block:: cpp

  template <typename T> tuple<T, T, T> extgcd(T a, T b)

:math:`ax + by = \gcd(a,b)` を満たす整数 :math:`x,y` を求め :math:`(\gcd(x,y),x,y)` の形で返します.