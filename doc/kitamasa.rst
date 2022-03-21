Kitamasa
########

きたまさ法により線形漸化式の項を求めます

:doc:`kitamasa_verification`

.. code-block:: cpp

 template <typename S>
 kitamasa(
     const vector<S>& coefficients,
     function<S(S,S)> add,
     function<S()> zero,
     function<S(S,S)> mul,
     function<S()> one,
     const vector<S>& init,
     ll n 
 )

漸化式の係数 :math:`\mathrm{coefficients} = \{ c_0, c_1, ..., c_{k-1} \}` と初期値 :math:`\mathrm{init} = \{a_0,a_1,...,a_{k-1}\}` から
:math:`k` 階線形漸化式 :math:`a_n = a_{n-1} \cdot c_{k-1} + a_{n-2} \cdot c_{k-2} + \dots + a_{n-k} \cdot c_0` の第 :math:`n` 項を求めます.

制約
****
- :math:`\mathrm{add}(x, \mathrm{zero}()) = \mathrm{add}(\mathrm{zero}(), x) = x`
- :math:`\mathrm{mul}(x, \mathrm{one}()) = \mathrm{mul}(\mathrm{one}(), x) = x`
- :math:`n \ge 0`