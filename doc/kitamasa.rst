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
     long long n 
 )

漸化式の係数 :math:`\mathtt{coefficients} = \{ c_0, c_1, ..., c_{k-1} \}` と初期値 :math:`\mathtt{init} = \{a_0,a_1,...,a_{k-1}\}` から
:math:`k` 階線形漸化式 :math:`a_n = a_{n-1}c_{k-1} + a_{n-2}c_{k-2} + ... + a_{n-k}c_0` の第 :math:`n` 項を求めます.

制約
****
- :math:`\mathtt{add}(x, \mathtt{zero}()) = \mathtt{add}(\mathtt{zero}(), x) = x`
- :math:`\mathtt{mul}(x,\mathtt{one}()) = \mathtt{mul}(\mathtt{one}(),x) = x`
- :math:`0 \le n`