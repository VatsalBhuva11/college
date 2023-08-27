#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,a,b) for(int i = a; i<b; i++)
#define outnew(a) cout<<(a)<<endl 
#define outsame(a) cout<<(a)<<" " 
typedef vector<int> vi;
typedef pair<int,int> pi;
const int N = 1e9+7;

int nfa_transitions[][3][3] = {
//   a      b
    {{0}, {0,1}}, //q0
    {{-1}, {2}},  //q1
    {{2}, {2}}    //q2
};

int dfa_transitions[][1000][2] = {};

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    // #ifndef ONLINE_JUDGE
    // freopen("inputf.in", "r", stdin);
    // freopen("outputf.in", "w", stdout);
    // #endif
    
    dfa_transitions[0][0][0] = nfa_transitions[0][0][0];
    
    
    
return 0;
}