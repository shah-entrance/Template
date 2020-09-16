vector<ll> adj[100005];
vector<ll> timein,timeout;
vector<vector<ll> >parent;
ll timer=0,l,n;
void dfs(ll i,ll father){
    timer+=1;
    timein[i]=timer;
    parent[i][0]=father;
    for(ll k=1;k<=l;k++)
        parent[i][k]=parent[parent[i][k-1]][k-1];
    vector<ll>::iterator it;
    for(it=adj[i].begin();it!=adj[i].end();it++){
        if(*it!=father)
            dfs(*it,i);
    }
    timeout[i]=timer;
}
bool is_ancestor(ll u,ll v){
    return timein[u]<=timein[v] && timeout[u]>=timeout[v];
}
ll lca(ll u,ll v){
    if(is_ancestor(u,v))
        return u;
    if(is_ancestor(v,u))
        return v;
    for(ll i=l;i>=0;i--){
        if(is_ancestor(parent[u][i],v))
            u=parent[u][i];
    }
    return parent[u][0];
}
void preprocess(ll root){
    timein.resize(n);
    timeout.resize(n);
    l=ceil(log2(n));
    parent.assign(n,vector<ll>(l+1));
    dfs(root,root);
}
