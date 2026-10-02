#define MAX_N 200000
vector<long long> fact(MAX_N + 1), inv_fact(MAX_N + 1);

long long binExp(long long base, long long exponent, long long mod) {
    long long result = 1;
    base = base % mod;  

    while (exponent > 0) {
        if (exponent & 1) {
            result = (result * base) % mod;  
        }
        base = (base * base) % mod;
        exponent >>= 1; 
    }

    return result;
}


void precompute_factorials() {
    fact[0] = inv_fact[0] = 1;
    for (int i = 1; i <= MAX_N; ++i) {
        fact[i] = fact[i - 1] * i % MOD;
    }
    inv_fact[MAX_N] = binExp(fact[MAX_N], MOD-2,MOD);
    for (int i = MAX_N - 1; i >= 1; --i) {
        inv_fact[i] = inv_fact[i + 1] * (i + 1) % MOD;
    }
    inv_fact[0] = 1;
}

long long comb(int n, int k) {
    if (k > n || k < 0) return 0;
    return fact[n] * inv_fact[k] % MOD * inv_fact[n - k] % MOD;
}
