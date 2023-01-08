Util
####

ユーティリティです

find_le
*******
.. code-block:: cpp

  template<typename T, typename S> find_le(S& s, T v, T def)


集合 :math:`s` から :math:`v` と等しいか,より小さい要素を探します.そのような要素が存在しない場合は :math:`\mathrm{def}` を返します.

制約
====
- :math:`S` 型は ``upper_bound(T)`` メソッドを持つ

find_ge
*******
.. code-block:: cpp

  template<typename T, typename S> find_ge(S& s, T v, T def)


集合 :math:`s` から :math:`v` と等しいか,より大きい要素を探します.そのような要素が存在しない場合は :math:`\mathrm{def}` を返します.

制約
====
- :math:`S` 型は ``lower_bound(T)`` メソッドを持つ