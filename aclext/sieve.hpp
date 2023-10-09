/// @file
/// @brief エラトステネスの篩です
#pragma once

#include <vector>

using namespace std;

// <---
// name: Sieve of Eratosthenes
/// @brief エラトステネスの篩を実装したクラスです
struct Sieve {
    /// 長さ@f$n@f$のブール配列です.
    /// @f[
    ///   \mathrm{is\_prime}[i] =
    ///   \begin{cases}
    ///   \mathrm{true} & \text{(iが素数)} \\
    ///   \mathrm{false} & \text{(iが素数でない)} \\
    ///   \end{cases}
    /// @f]
    vector<bool> is_prime;

    /// @f$n@f$以下の素数のリストです.
    vector<int> primes;

    /// @f$n@f$以下の素数を計算し, 結果をプロパティ`is_prime`, `primes`に格納します.
    Sieve(int n) {
        is_prime.resize(n + 1);
        fill(is_prime.begin(), is_prime.end(), true);
        is_prime[0] = is_prime[1] = false;
        for (long long i = 2; i <= n; i++) {
            if (is_prime[i]) {
                primes.push_back(i);
                for (long long j = i * i; j <= n; j += i) {
                    is_prime[j] = false;
                }
            }
        }
    }
};
// --->