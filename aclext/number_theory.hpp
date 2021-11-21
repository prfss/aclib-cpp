#pragma once

#include <map>
#include <vector>

using namespace std;

namespace aclext {
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

bool is_prime(long long n) {
    if (n == 1) return false;
    for (long long i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

long long totient(long long x) {
    long long ans = 1;
    for (long long i = 2; i * i <= x; i++) {
        long long temp = 1;
        while (x % i == 0) {
            temp *= i;
            x /= i;
        }

        if (temp != 1) {
            ans *= temp - temp / i;
        }
    }
    if (x != 1) {
        ans *= x - 1;
    }

    return ans;
}
}