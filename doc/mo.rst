Mo's Algorithm
###############

Mo's Algorithmの実装です

:doc:`mo_verification`

.. code-block:: cpp

  template <typename T>
  vector<T> mo(
    vector<pair<int,int>> query,
    function<T(T,int)> extend,
    function<T(T,int)> shrink,
    T init
  )

区間クエリのリスト :math:`\mathtt{query} = \{[l_1,r_1], [l_2,r_2], ... ,[l_q, r_q]\}` に対し, 答えのリスト :math:`\{ans(l_1,r_1),ans(l_2,r_2),..,ans(l_q,r_q)\}`
を返します. ただし :math:`n = \max_{{i \in [1,q]}} r_i` とするとき

- :math:`\mathtt{extend}(\text{init},0) = ans(0,0)`
- :math:`0 \lt l \le r \le n` のとき, :math:`\mathtt{extend}(ans(l,r),l-1) = ans(l-1,r)`
- :math:`0 \le l \lt r \le n` のとき, :math:`\mathtt{shrink}(ans(l,r),l) = ans(l+1,r)` 
- :math:`0 \le l \le r \lt n` のとき, :math:`\mathtt{extend}(ans(l,r),r+1) = ans(l,r+1)`
- :math:`0 \le l \lt r \le n` のとき, :math:`\mathtt{shrink}(ans(l,r),r) = ans(l,r-1)`

を満たす必要があります.

制約
=====
- :math:`0 \le l_i \le r_i`
