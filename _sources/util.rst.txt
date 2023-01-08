Util
####

ユーティリティです

next_le
*******
.. code-block:: cpp

  template<typename T, typename S> next_le(S& s, T v, T def)


集合 :math:`s` に含まれる, :math:`v` と等しいかより小さい最大の要素を返します.そのような要素が存在しない場合は :math:`\mathrm{def}` を返します.

制約
====
- :math:`S` 型は ``upper_bound(T)`` メソッドを持つ

next_ge
*******
.. code-block:: cpp

  template<typename T, typename S> next_ge(S& s, T v, T def)


集合 :math:`s` に含まれる, :math:`v` と等しいかより大きい最小の要素を返します.そのような要素が存在しない場合は :math:`\mathrm{def}` を返します.

制約
====
- :math:`S` 型は ``lower_bound(T)`` メソッドを持つ