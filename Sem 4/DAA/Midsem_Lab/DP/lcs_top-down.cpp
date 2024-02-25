#include <bits/stdc++.h>
using namespace std;

int main(){
  string s1;
  string s2;
  cin>>s1;
  cin>>s2;
  int t[s1.size()+1][s2.size()+1];
  for(int i=0;i<=s1.size();i++){
    for(int j=0;j<=s2.size();j++){
      if(i==0 or j==0){
        t[i][j]=0;
      }
    }
  }
  for (int i = 1; i <= s1.size(); i++)
  {
    for (int j = 1; j <= s2.size(); j++)
    {
      if(s1[i-1]==s2[j-1]){
        t[i][j]=1+t[i-1][j-1];
      }else{
        t[i][j]=max(t[i-1][j],t[i][j-1]);
      }
    }
  }
  cout<<t[s1.size()][s2.size()]<<endl;
}