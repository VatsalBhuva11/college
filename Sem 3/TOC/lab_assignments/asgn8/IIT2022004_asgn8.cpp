#include <bits/stdc++.h>
using namespace std;

int main(){
    string var[5],ter[5];
    for(int i=0;i<5;i++){
        cin>>var[i]>>ter[i];
    }
    for(int i=0;i<5;i++){
        cout<<var[i]<<" "<<ter[i]<<endl;
    }
    for(int i=0;i<4;i++){
        if(ter[i]==var[i+1]){
            ter[i]=" ";
            var[i+1]=" ";
        }
    }
    // for(int i=0;i<5;i++){
    //     cout<<var[i]<<" "<<ter[i]<<endl;
    // }

    cout<<"Grammar after removing unit productions: \n";

    int var_ind = 0 , ter_ind = 0;
    for(int i =0;i<5;i++){
        if(var[i]!=" "&& ter[i]==" ") var_ind = i;
        if(var[i]==" " && ter[i]!=" ") ter_ind = i;
    }
    ter[var_ind] = ter[ter_ind];
    for(int i=0;i<5;i++){
        if(var[i]==" ") continue;
        cout<<var[i]<<"->"<<ter[i]<<endl;
    }
    
}