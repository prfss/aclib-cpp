/// @file
/// @brief 初等整数論関連の関数です
#pragma once

#include <map>
#include <tuple>
#include <vector>

using namespace std;

/// @brief 数@f$n@f$の約数を返します
vector<long long> divisor(long long n);

/// @brief 数@f$n@f$の素因数分解を返します
map<long long, int> prime_factor(long long n);

/// @brief 数@f$n@f$が素数であるか判定します
bool is_prime(long long n);

/// @brief [オイラーのトーシェント関数](https://ja.wikipedia.org/wiki/%E3%82%AA%E3%82%A4%E3%83%A9%E3%83%BC%E3%81%AE%CF%86%E9%96%A2%E6%95%B0)です
/// @details
/// ### 制約
/// - @f$1 \leq n \leq 10^{18}@f$
long long totient(long long n);

// <---
// name: Extended Euclidean Algorithm
/// @brief 拡張ユークリッドの互除法です
/// @details
/// @f$ax + by = \gcd(a,b)@f$を満たす整数@f$x,y@f$を求め@f$(\gcd(x,y),x,y)@f$の形で返します.
template <typename T>
inline tuple<T, T, T> extgcd(T a, T b) {
    if (b == 0) {
        return make_tuple(a, 1, 0);
    } else {
        auto [g, x, y] = extgcd(b, a % b);
        return make_tuple(g, y, x - a / b * y);
    }
}
// --->

/// @brief エラトステネスの篩です
/// @details
/// @f$n@f$以下の素数を計算し, 結果を格納したペアを返します.
/// - 第1要素
/// 各数が素数かどうかを表す長さ@f$n@f$のブール配列です.
/// - 第2要素
/// @f$n@f$以下の素数のリストです.
pair<vector<bool>, vector<int>> sieve(int n);