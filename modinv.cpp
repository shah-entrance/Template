ll modinv(ll a, ll m){
    assert(m > 0);
    if(m == 1)
        return 0;
    a %= m;
    if(a < 0)
        a += m;
    assert(a != 0);
    if(a == 1)
        return 1;
    return m - modinv(m, a) * m / a;
}
