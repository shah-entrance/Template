ll mulmod(ll a, ll b, ll mod){
    ll res = 0;
    a %= mod;
    while(b > 0){
        if(b & 1)
            res = (res + a) % mod;
        a = (a * 2) % mod;
        b /= 2;
    }
    return (res % mod);
}
