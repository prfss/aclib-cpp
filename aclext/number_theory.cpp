#include <map>
#include <vector>

using namespace std;

// <---
// name: Divisor
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