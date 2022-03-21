Bwt
####

与えられた文字列の `Burrows-Wheeler変換 <https://ja.wikipedia.org/wiki/%E3%83%96%E3%83%AD%E3%83%83%E3%82%AF%E3%82%BD%E3%83%BC%E3%83%88>`_ を求めます

bwt
****
.. code-block:: cpp

 string bwt(const string &s, const vector<int> &sa) // (1)
 string bwt(const string &s) // (2)

1. 文字列 :math:`\mathrm{s}` とその接尾辞配列 :math:`\mathrm{sa}` からBurrows-Wheeler変換を計算して返します.
2. 文字列 :math:`\mathrm{s}` からBurrows-Wheeler変換を計算して返します.

制約
====
1. :math:`\mathrm{sa}` は :math:`\mathrm{s}` の接尾辞配列(AtCoder Libraryと同仕様)

