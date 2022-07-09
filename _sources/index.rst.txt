acl-ext
########
AtCoderの問題で要求される(かもしれない)アルゴリズムを提供するライブラリです

特徴
*****
- 基本的には ``namespace aclext {...}`` の部分をコピペ(+適宜改造)して使う感じです
- STL,ACLのヘッダーのインクルードが必要です
- ``using namespace std`` が必要です
- ``long long`` はドキュメントでは便宜上 ``ll`` と書かれていますが, コード中では ``long long`` と書いています

アルゴリズム
*************
.. toctree::
   :maxdepth: 1

   bwt
   combination
   cumulative_sum_2d
   dynamic_segment_tree
   kitamasa
   kmp
   lca
   li_chao_tree
   matrix
   median
   mo
   monotonic_convex_hull_trick
   number_theory
   rerooting
   sieve   