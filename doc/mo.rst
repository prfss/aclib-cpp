Mo's Algorithm
###############

Mo's Algorithmの実装です

:doc:`mo_verification`

.. code-block:: cpp

  template <typename T>
  vector<T> mo(
    vector<pair<int,int>> query,
    function<void(int)> extend,
    function<void(int)> shrink,
    function<T()> val
  )

区間クエリのリスト :math:`\text{query} = \{[l_1,r_1], [l_2,r_2], ... ,[l_q, r_q]\}` に対し, 答えのリスト :math:`\{ans(l_1,r_1),ans(l_2,r_2),..,ans(l_q,r_q)\}`
を返します.ただし

- :math:`extend,shrink` を一度も呼び出していない状態で, :math:`\text{extend}(0)` が呼ばれた直後に, :math:`\text{val}() = ans(0,0)`
- :math:`0 < l` のとき, :math:`\text{extend}(l-1)` が1回実行された直後 :math:`\text{val}() = ans(l-1,r)`
- :math:`l < n-1 \land l < r` のとき, :math:`\text(shrink)(l)` が1回実行された直後 :math:`\text{val}() = ans(l+1,r)` 
- :math:`r < n-1` のとき, :math:`\text{extend}(r+1)` が1回実行された直後 :math:`\text{val}() = ans(l,r+1)`
- :math:`0 < r \land l < r` のとき,  :math:`\text{shrink}(r)` が1回実行された直後 :math:`\text{val}() = ans(l,r-1)`

となる必要があります.

制約
=====
- :math:`0 \le l_i \le r_i`
