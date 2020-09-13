#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
vector<int> ans;
void simpleSieve(int limit, vector<int> &prime){
    bool mark[limit + 1];
    memset(mark, true, sizeof(mark));
    for(int p = 2; p * p < limit; p++){
        if(mark[p] == true){
            for(int i = p * 2; i < limit; i += p)
                mark[i] = false;
        }
    }
    for(int p = 2; p < limit; p++){
        if(mark[p]){
            ans.push_back(p);
            prime.push_back(p);
        }
    }
}
void segmentedSieve(int n){
    int limit = floor(sqrt(n)) + 1;
    vector<int> prime;
    simpleSieve(limit, prime);
    int low = limit, high = 2 * limit;
    while(low < n){
        if(high >= n)
            high = n;
        bool mark[limit + 1];
        memset(mark, true, sizeof(mark));
        for(int i = 0; i < prime.size(); i++){
            int loLim = floor(low / prime[i]) * prime[i];
            if(loLim < low)
                loLim += prime[i];
            for(int j = loLim; j < high; j += prime[i])
                mark[j - low] = false;
        }
        for(int i = low; i < high; i++){
            if(mark[i - low] == true)
                ans.push_back(i);
        }
        low = low + limit;
        high = high + limit;
    }
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);

    return 0;
}

