ll lis(vector<ll> arr){
    ll n=arr.size(),i,ans;
    multiset<ll> s;
    multiset<ll>::iterator it;
    for(i=0;i<n;i++){
        s.insert(arr[i]);
        it=s.lower_bound(arr[i]);
        it++;
        if(it!=s.end())
            s.erase(it);
    }
    ans=s.size();
    return ans;
    for(it=s.begin();it!=s.end();it++)
        cout<<*it<<" ";
    cout<<endl;
}
