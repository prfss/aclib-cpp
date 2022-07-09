Knuth-Morris-Pratt Algorithm
############################

Knuth-Morris-Pratt法の実装です

:doc:`kmp_verification`

prefix_function
****************
.. code-block:: cpp

  vector<int> prefix_function(const string& s)

文字列 :math:`\mathrm{s}` の prefix function, すなわち以下のように定義される, 長さが :math:`\mathrm{s.size()}` の配列 :math:`\pi` を返します.

.. math::
 
  \pi_i = \max_{k \in [0,i]} \{k \mid \mathrm{s.substr(0,k)} = \mathrm{s.substr(i-(k-1),k)} \}

言い換えると, :math:`\pi_i` は :math:`\mathrm{s}` の接頭辞 :math:`\mathrm{t} = \mathrm{s.substr(0,i+1)}` に対して,
:math:`\mathrm{t}` の接頭辞かつ接尾辞であり, :math:`\mathrm{t}` とは異なるような文字列のうち最長のものの長さです.
特に :math:`\mathrm{\pi_0} = 0` です.

制約
====
- :math:`0 \le \mathrm{s.size()} \lt 10^8`

kmp_search
**********
.. code-block:: cpp

  vector<int> kmp_search(const string& s, const string& pattern)

文字列 :math:`\mathrm{s}` におけるパターン :math:`\mathrm{pattern}` の出現位置を返します.

制約
====
- :math:`0 \le \mathrm{s.size()} \lt 10^8`
- :math:`1 \le \mathrm{pattern.size()} \lt 10^8`
