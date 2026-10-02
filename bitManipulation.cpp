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

int nxor(int a){if(a%4==0){return a;}if(a%4==1){return 1;}if(a%4==2){return a+1;}return 0;}

int subsetXORSum(vector<int> &arr) {
    int n = arr.size();
    int bits = 0;

    for (int i=0; i < n; ++i) bits |= arr[i];

    int ans = bits * pow(2, n-1);

    return ans;
}