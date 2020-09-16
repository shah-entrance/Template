ll Xor(ll a,ll b){
    return a * (a & 1) ^ b * !(b & 1) ^ !!(((a ^ b) + 1) & 2);
}
 
