#include <bits/stdc++.h>
using namespace std;

int lcs(string a,string b,int n,int m){
  if(n==0 or m==0){
    return 0;
  }
  if(a[n-1]==b[m-1]){
    return (1+lcs(a,b,n-1,m-1));
  }else{
    return max(lcs(a,b,n,m-1),lcs(a,b,n-1,m));
  }
}

int main(){
  string s1;
  string s2;
  cin>>s1;
  cin>>s2;
  int s=lcs(s1,s2,s1.size(),s2.size());
  cout<<s<<endl;
}