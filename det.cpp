ll det(ll arr[][10],ll n){
    if(n==1)
        return arr[0][0];
    ll val=0,mul=1,x,y,i,j,k;
    for(i=0;i<n;i++){
        ll b[n][10];
        x=0;y=0;
        for(j=1;j<n;j++){
            y=0;
            for(k=0;k<n;k++){
                if(k==i)
                    continue;
                b[x][y]=arr[j][k];
                y+=1;
            }
            x+=1;
        }
        val+=(mul*arr[0][i]*det(b,n-1));
        mul*=-1;
    }
    return val;
}
