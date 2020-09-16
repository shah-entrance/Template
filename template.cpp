#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;


ll Xor(ll a,ll b){
    return a * (a & 1) ^ b * !(b & 1) ^ !!(((a ^ b) + 1) & 2);
}

vector<string> split(string str,char delimeter){
    stringstream ss(str);
    string s;
    vector<string> out;
    while(getline(ss,s,delimeter)){
        if(s.length()!=0)
            out.push_back(s);
    }
    return out;
}

vector<ll> prime;
void sieve(ll n){
    ll i,j;
    bool p[n+5];
    memset(p,true,sizeof(p));
    for(i=2;i*i<=n;i++){
        if(p[i]){
            for(j=i*i;j<=n;j+=i)
                p[j]=false;
        }
    }
    for(i=2;i<=n;i++){
        if(p[i])
            prime.push_back(i);
    }
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



ll remainder(string str){
    ll num,rem=0,len = str.length(),i;
    for(i=0;i<len;i++){
        num = rem * 10 + (str[i] - '0');
        rem = num % 2;
    }
    return rem;
}

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

ll mulmod(ll a,ll b){
    ll res=0;
    a%=mod;
    while(b){
        if(b&1)
            res=(res+a)%mod;
        a=(2*a)%mod;
        b>>=1;
    }
    return res;
}

ll modinv(ll a,ll m){
    assert(m>0);
    if(m==1)
        return 0;
    a%=m;
    if(a<0)
        a+=m;
    assert(a!=0);
    if(a==1)
        return 1;
    return m-modinv(m,a)*m/a;
}

typedef unsigned char byte;
int count = 0;
vector<int> primes;
void sieve(int lim) /// up_to 90e6 = 90.000.000 (get prime)  168e6 = 168.000.000 (count only)
{
    if (lim < 2) return ;
    int sqrt = std::sqrt(lim);
    int sieve_size = max(sqrt, (1 << 15));
    int segment_size = sieve_size * 16;

    vector<byte> mark(sieve_size);
    vector<byte> is_prime(sqrt + 1, true);
    vector<int> seg_prime;
    vector<int> seg_multi;

    for (int i = 3; i <= sqrt; i += 2)
        if (is_prime[i])
            for (int j = i * i; j <= sqrt; j += i)
                is_prime[j] = false;

    int reset[16];
    for (int i = 0; i < 8; ++i)
        reset[2 * i] = reset[2 * i + 1] = ~(1 << i);

    int popcnt[256];
    for (int i = 0; i < 256; ++i)
        popcnt[i] = __builtin_popcount(i);

    int s = 3;
    for (int low = 0; low <= lim; low += segment_size)
    {
        fill(mark.begin(), mark.end(), 0xff);
        int high = min(low + segment_size - 1, lim);
        sieve_size = (high - low) / 16 + 1;

        for (; s * s <= high; s += 2)
        {
            if (is_prime[s])
            {
                seg_prime.push_back(s);
                seg_multi.push_back(s * s - low);
            }
        }

        for (size_t i = 0; i < seg_prime.size(); ++i)
        {
            int j = seg_multi[i];
            for (int k = seg_prime[i] * 2; j < segment_size; j += k)
                mark[j >> 4] &= reset[j % 16];

            seg_multi[i] = j - segment_size;
        }

        if (high == lim)
        {
            int bits = 0xff << ((lim % 16) + 1) / 2;
            mark[sieve_size - 1] &= ~bits;
        }

        for (int n = 0; n < sieve_size; n++)
        {
//             count += popcnt[mark[n]]; continue;
            for (int i = 0; i < 8; i++)
                if (mark[n] & (1 << i))
                    primes.push_back(low + n * 16 + i * 2 + 1);
        }
    }
}


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

void computeLPSArray(string pat,ll m,ll lps[]){
    ll len=0,i=1;
    lps[0]=0;
    while(i<m){
        if(pat[i]==pat[len]){
            len+=1;
            lps[i]=len;
            i+=1;
        }
        else{
            if(len!=0)
                len=lps[len-1];
            else{
                lps[i]=0;
                i+=1;
            }
        }
    }
}
void KMPsearch(string txt,string pat){
    ll m=pat.length(),n=txt.length();
    ll lps[m];
    computeLPSArray(pat,m,lps);
    ll i=0,j=0;
    while(i<n){
        if(pat[j]==txt[i]){
            i+=1;
            j+=1;
        }
        if(j==m){
            flag=true;
            j=lps[j-1];
        }
        else if(i<n && pat[j]!=txt[i]){
            if(j!=0)
                j=lps[j-1];
            else
                i+=1;
        }
    }
}

bool isPalindrome(string &str){
    ll n=str.length(),low=0,high=n-1;
    while(low<high){
        if(str[low++]!=str[high--])
            return false;
    }
    return true;
}

const ll n=1e5+10,d=20;
ll basis[d],sz=0;
void insertVector(ll mask){
    for(i=0;i<d;i++){
        if((mask&1<<i)==0)
            continue;
        if(!basis[i]){
            basis[i]=mask;
            ++sz;
            return;
        }
        mask^=basis[i];
    }
}

ll gcd(ll a,ll b){
    if(b==0)
        return a;
    return gcd(b,a%b);
}

string divide(string number,ll divisor){
    ll idx = 0;
    ll temp = number[idx] - '0';
    while (temp < divisor)
       temp = temp * 10 + (number[++idx] - '0');
    while (number.size()>idx){
        ans += (temp / divisor) + '0';
        temp = (temp % divisor) * 10 + number[++idx] - '0';
    }
    if (ans.length() == 0)
        return "0";
    return ans;
}

vector<ll> adj[200005];
bool visited[200005];
void dfs(ll i,ll parent){
    if(visited[i]==false){
        visited[i]=true;
        vector<ll>::iterator it;
        for(it=adj[i].begin();it!=adj[i].end();it++){
            if(*it!=parent)
                dfs(*it,i);
        }
    }
}

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

string add(string str1,string str2){
    if(str1.length()>str2.length())
        swap(str1,str2);
    string str = "";
    ll i,n1 = str1.length(),n2=str2.length();
    reverse(str1.begin(), str1.end());
    reverse(str2.begin(), str2.end());
    int carry = 0;
    for(i=0;i<n1;i++){
        ll sum = ((str1[i]-'0')+(str2[i]-'0')+carry);
        str.push_back(sum%10 + '0');
        carry = sum/10;
    }
    for (i=n1;i<n2;i++){
        ll sum = ((str2[i]-'0')+carry);
        str.push_back(sum%10 + '0');
        carry = sum/10;
    }
    if (carry)
        str.push_back(carry+'0');
    reverse(str.begin(), str.end());
    return str;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);

    return 0;
}

