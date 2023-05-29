#include <bits/stdc++.h>
using namespace std;



int main(){
    
    int t;
    cin>>t;
    
    while (t--){
        string s;
        int count[30]={0};
        cin>>s;
        for (int i = 0; i<s.size(); i++){
            count[s[i]-'a']++;
        }
        int flag = 0;
        for (int i = 0; i<28; i++){
            if(count[i]>=2){
                flag = 1;
                cout<<"YES"<<endl;
                break;
            }
        }
        if (flag == 0) cout<<"NO"<<endl;

    }   
    
return 0;
}