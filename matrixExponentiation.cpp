#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
ll mod = 1e9, n,k,i,j,x;
vector<ll> a,b;
vector<vector<ll> > multiply(vector<vector<ll> > a, vector<vector<ll> > b){
    vector<vector<ll> > C(k+1, vector<ll> (k+1));
    for(i=1;i<=k;i++){
        for(j=1;j<=k;j++){
            for(x=1;x<=k;x++)
                C[i][j] = ((C[i][j] + a[i][x]*b[x][j])%mod)%mod;
        }
    }
    return C;
}
vector<vector<ll> > power(vector<vector<ll> > &arr, ll n){
    if(n==1)
        return arr;
    if(n&1)
        return multiply(arr,power(arr,n-1));
    else{
        vector<vector<ll> > temp = power(arr,n/2);
        return multiply(temp,temp);
    }
}
ll compute_nth(ll n){
    vector<ll> F(k+1);
    for(i=1;i<=k;i++)
        F[i]=a[i-1];
    vector<vector<ll> > T(k+1,vector<ll> (k+1));
    for(i=1;i<=k;i++){
        for(j=1;j<=k;j++){
            if(i<k){
                if(i+1==j)
                    T[i][j] = 1;
                else
                    T[i][j] = 0;
            }
            else{
                T[i][j] = b[k-j];
            }
        }
    }
    T = power(T,n-1);
    ll ans = 0;
    for(i=1;i<=k;i++)
        ans = (ans + (T[1][i]*F[i])%mod)%mod;
    return ans;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int t;
    cin>>t;
    while(t--){
        cin>>k;
        a = vector<ll> (k);
        b = vector<ll> (k);
        for(i=0;i<k;i++)
            cin>>a[i];
        for(i=0;i<k;i++)
            cin>>b[i];
        cin>>n;
        cout<<compute_nth(n)<<endl;
    }
    return 0;
}

