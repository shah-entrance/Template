#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
ll binpow(ll x,ll y){
    ll res=1;
    while(y>0){
        if(y&1)
            res*=x;
        y>>=1;
        x*=x;
    }
    return res;
}
void updateQuery(ll *tree,ll low,ll high,ll treeNode,ll val,ll ind){
    if(ind<low | ind>high)
        return;
    if(low==high){
        tree[treeNode]=val;
        return;
    }
    ll mid=low+(high-low)/2;
    updateQuery(tree,low,mid,2*treeNode,val,ind);
    updateQuery(tree,mid+1,high,2*treeNode+1,val,ind);
    tree[treeNode]=tree[2*treeNode]+tree[2*treeNode+1];
}
ll rangeQuery(ll *tree,ll L,ll R,ll low,ll high,ll treeNode){
    if(low>R || high<L)
        return 0;
    if(L<=low && R>=high)
        return tree[treeNode];
    ll mid=low+(high-low)/2;
    return rangeQuery(tree,L,R,low,mid,2*treeNode)+rangeQuery(tree,L,R,mid+1,high,2*treeNode+1);
}
void constructTree(ll arr[],ll *tree,ll low,ll high,ll treeNode){
    if(low==high){
        tree[treeNode]=__builtin_popcountll(arr[low]);
        cout<<treeNode<<" "<<tree[treeNode]<<endl;
        return;
    }
    ll mid=low+(high-low)/2;
    constructTree(arr,tree,low,mid,2*treeNode);
    constructTree(arr,tree,mid+1,high,2*treeNode+1);
    tree[treeNode]=tree[2*treeNode]+tree[2*treeNode+1];
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll n,q,i,type,index,L,R;
    cin>>n>>q;
    ll arr[n]={};
    ll height,max_size,temp;
    height=(ll)(ceil(log2(n)));
    max_size=2*binpow(2,height)-1;
    ll *tree=new ll[max_size];
    constructTree(arr,tree,0,n-1,1);
    while(q--){
        cin>>type;
        if(type==1){
            cin>>index;
            arr[index]=2*arr[index]+1;
            temp=__builtin_popcountll(arr[index]);
            updateQuery(tree,0,n-1,1,temp,index);
        }
        else if(type==2){
            cin>>index;
            arr[index]/=2;
            temp=__builtin_popcountll(arr[index]);
            updateQuery(tree,0,n-1,1,temp,index);
        }
        else{
            cin>>L>>R;
            cout<<rangeQuery(tree,L,R,0,n-1,1)<<endl;
        }
    }
    return 0;
}

