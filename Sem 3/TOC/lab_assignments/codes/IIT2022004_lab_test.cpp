#include <bits/stdc++.h>
using namespace std;

unordered_map<char,vector<string>>m;

//v is the production rule's RHS (vector of all production rules for a state), 
//isImp is the array containing the states
//that should be modified, check is helper variable.
vector<string> remove(vector<string>&v,vector<int>&isImp,int check){
    vector<string>ans;
    //check each individual rule for each state (v contains all the rules for the current state)
    for(int i=0; i<v.size(); i++){
        if (v[i].size()==1 and v[i][0]>='A' and v[i][0]<='Z'){
            //recursively remove (S->A, A->B, B->C. recursively it reaches B->C)
            vector<string>temp=remove(m[v[i][0]],isImp,(int)v[i][0]);
            if (!isImp[check]) v[i]="-1";
            for(auto s:temp) ans.push_back(s);
        }
        else {
            ans.push_back(v[i]);
            if (!isImp[check]) v[i]="-1";
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
    int n; cin>>n;
    for(int i=0; i<n; i++){
        char c; cin>>c;
        string s; cin>>s;
        m[c].push_back(s);
    }

    vector<int> isImp(100,0);
    for(int i=65; i<=90; i++){
        for(int j=0; j<m[i].size(); j++){
            if (m[i][j].size()>1){
                //mark all important states (if a state is appearing on the RHS of another state, the RHS state is imp.)
                for(int k=0; k<m[i][j].size(); k++){
                    if (m[i][j][k]>='A' and m[i][j][k]<='Z') isImp[m[i][j][k]]=1;
                }
            }
        }
    }
    for(int i=65; i<=90; i++){
        for(int j=0; j<m[i].size(); j++){
            //for productions of the kind S->A, A->B, etc.
            if (m[i][j].size()==1 and m[i][j][0]>='A' and m[i][j][0]<='Z'){
                //temp is the updated rule.
                vector<string>temp=remove(m[i],isImp,i);
                m[i]=temp;
            }
        }
    }
    cout<<endl;
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