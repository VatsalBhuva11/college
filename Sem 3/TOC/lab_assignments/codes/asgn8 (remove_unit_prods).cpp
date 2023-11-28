#include <bits/stdc++.h>
using namespace std;

unordered_map<char,vector<string>>m;

vector<string> remove(vector<string>&v,vector<int>&isImportant,int check){
    vector<string>ans;
    for(int i=0; i<v.size(); i++){
        if (v[i].size()==1 and v[i][0]>='A' and v[i][0]<='Z'){
            vector<string>temp=remove(m[v[i][0]],isImportant,(int)v[i][0]);
            if (!isImportant[check]) v[i]="-1";
            for(auto s:temp) ans.push_back(s);
        }
        else {
            ans.push_back(v[i]);
            if (!isImportant[check]) v[i]="-1";
        }
    }
    return ans;
}

bool isValid(vector<string>&v){
    int ct=0;
    for(int i=0; i<v.size(); i++){
        if (v[i]!="-1") ct++;
    }
    if (ct>0) return true;
    return false;
}

int main(){
    cout<<"Enter No. of Productions:"<<endl;
    int n; cin>>n;
    cout<<"Enter Each Rule Seperately Ex.(S AB),(S Ac) write them in diff lines"<<endl;
    for(int i=0; i<n; i++){
        char c; cin>>c;
        string s; cin>>s;
        m[c].push_back(s);
    }
    vector<int> isImportant(100,0);
    for(int i=65; i<=90; i++){
        for(int j=0; j<m[i].size(); j++){
            if (m[i][j].size()>1){
                for(int k=0; k<m[i][j].size(); k++){
                    if (m[i][j][k]>='A' and m[i][j][k]<='Z') isImportant[m[i][j][k]]=1;
                }
            }
        }
    }
    for(int i=65; i<=90; i++){
        for(int j=0; j<m[i].size(); j++){
            if (m[i][j].size()==1 and m[i][j][0]>='A' and m[i][j][0]<='Z'){
                vector<string>temp=remove(m[i],isImportant,i);
                m[i]=temp;
            }
        }
    }
    cout<<"\nAfter Removing Unit Productions:\n";
    for(int i=65; i<=90; i++){
        if (m[i].size()!=0 and isValid(m[i])){
            cout<<char(i)<<"->";
            for(int j=0; j<m[i].size(); j++){
                if (m[i][j]!="-1"){
                    if (j>=1) cout<<" | "<<m[i][j];
                    else cout<<m[i][j];
                }
            }
            cout<<endl;
        }
    }
}