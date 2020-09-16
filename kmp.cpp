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
