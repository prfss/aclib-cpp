/// @file
/// @brief 初等整数論関連の関数です
#pragma once

#include <map>
#include <vector>

using namespace std;

// <---
// name: Divisor
/// @brief 数@f$n@f$の約数を返します
vector<long long> divisor(long long n) {
    vector<long long> ret;
    for (long long i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            ret.push_back(int(i));
            if (i * i != n) ret.push_back(n / i);
        }
    }
    return ret;
}
// --->

// <---
// name: Prime Factorization
/// @brief 数@f$n@f$の素因数分解を返します
map<long long, int> prime_factor(long long n) {
    map<long long, int> res;
    for (long long i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            res[i]++;
            n /= i;
            i--;
        }
    }
    if (n != 1) res[n]++;
    return res;
}
// --->

// name: Is Prime
/// @brief 数@f$n@f$が素数であるか判定します
bool is_prime(long long n) {
    if (n == 1) return false;
    for (long long i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}
// --->

// <---
// name: Totient
/// @brief [オイラーのトーシェント関数](https://ja.wikipedia.org/wiki/%E3%82%AA%E3%82%A4%E3%83%A9%E3%83%BC%E3%81%AE%CF%86%E9%96%A2%E6%95%B0)です
/// @details
/// ### 制約
/// - @f$1 \leq n \leq 10^18@f$
long long totient(long long n) {
    long long ans = 1;
    for (long long i = 2; i * i <= n; i++) {
        long long temp = 1;
        while (n % i == 0) {
            temp *= i;
            n /= i;
        }

        if (temp != 1) {
            ans *= temp - temp / i;
        }
    }
    if (n != 1) {
        ans *= n - 1;
    }

    return ans;
}
// --->

// <---
// name: Extended Euclidean Algorithm
/// @brief 拡張ユークリッドの互除法です
/// @details
/// @f$ax + by = \gcd(a,b)@f$を満たす整数@f$x,y@f$を求め@f$(\gcd(x,y),x,y)@f$の形で返します.
template <typename T>
tuple<T, T, T> extgcd(T a, T b) {
    if (b == 0) {
        return make_tuple(a, 1, 0);
    } else {
        auto [g, x, y] = extgcd(b, a % b);
        return make_tuple(g, y, x - a / b * y);
    }
}
// --->