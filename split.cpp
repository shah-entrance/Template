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
 
