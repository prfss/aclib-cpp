#pragma once

#include <vector>

using namespace std;

namespace aclext {
struct Sieve {
    vector<bool> is_prime;
    vector<int> primes;
    Sieve(int n) {
        is_prime.resize(n + 1);
        fill(is_prime.begin(), is_prime.end(), true);
        is_prime[0] = is_prime[1] = false;
        for (int i = 2; i <= n; i++) {
            if (is_prime[i]) {
                primes.push_back(i);
                for (long long j = i * i; j <= n; j += i) {
                    is_prime[j] = false;
                }
            }
        }
    }
};
}