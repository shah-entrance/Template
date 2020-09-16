ll ncr(ll n,ll r){
    ll ans=1,i;
    if(r>n-r)
        r=n-r;
    for(i=0;i<r;i++){
        ans = mulmod(ans,n-i);
        ans = mulmod(ans,modinv(i+1,mod));
    }
    return ans%mod;
}
