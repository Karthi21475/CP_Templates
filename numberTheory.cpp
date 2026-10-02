
struct numbertheory{
    int n;
    vector<int> spf;
    numbertheory(int x) : n(x), spf(n+1,-1){
        build();
    }

    void build(){
        spf[1]=1;
        for(int i=2;i<=n;i++){
            if(spf[i]!=-1) continue;
            for(int j=1;i*j<=n;j++){
                spf[i*j]=i;
            }
        }
    }

    map<int,int> factorise(int x){
        map<int,int> mp;
        int z=x;
        while(z>1){
            mp[spf[z]]++;
            z/=spf[z];
        }
        if(z>1) mp[z]++;
        return mp;
    }

    bool isPrime(int n){
        if(n==1) return false;
        if(spf[n]==n) return true;
        return false;
    }

    set<int> getFactors(int z){
        set<int> sol;
        sol.insert(1);
        sol.insert(z);
        for(int i=2;i*i<=z;i++){
            if(z%i==0){
                sol.insert(i);
                sol.insert(z/i);
            }
        }
        return sol;
    }
};

void pf(int n, map<int,vi> &mp){
    int tem=n;
    int cnt=0;
    while (tem%2==0){
        cnt++;
        tem/=2;
    }
    if (cnt>0) mp[2].pb(cnt);
    for (int j=3;j*j<=tem;j+=2){
        cnt=0;
        while (tem%j==0){
            tem/=j;
            cnt++;
        }
        if (cnt>0) mp[j].pb(cnt);
    }
    if (tem>0){
        mp[tem].pb(1);
    }
}
vi spf;
vector<vi> factors(maxxx);
vector<vi> multiples(maxxx);
void pre_compute(){
    for(int i=2;i<maxxx;i++){
        for(int j=i+i;j<maxxx;j+=i){
            multiples[i].pb(j);
            factors[j].pb(i);
        }
    }
}
void pre_spf(){
    for(int i=0;i<maxxx;i++) spf.pb(i);
    spf[1]=0;
    for(int i=2;i<maxxx;i++){
        if(spf[i]==i){
            for(int j=i;j<maxxx;j+=i){
                if(spf[j]==j) spf[j]=i;
            }
        }
    }

    //prime factors
    // for(int i=2;i<maxxx;i++) {
    //     int t=i;
    //     while(t>1) {
    //         factors[i].push_back(spf[t]);
    //         int temp=spf[t];
    //         while(t%temp==0)t/=temp;
    //     }
    // }
}



vi isprime(maxxx,1);
vi primes;
void seive(){
    isprime[0]=isprime[1]=0;
    for(int i=2;i<maxxx;i++){
        if(isprime[i]){
            for(int j=i+i;j<maxxx;j+=i){
                isprime[j]=0;
            }
        }
    }
    for(int i=2;i<maxxx;i++){
        if(isprime[i]){
            primes.pb(i);
        }
    }
}

